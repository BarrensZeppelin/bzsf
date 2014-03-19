#include <SFML_Snips.hpp>

namespace bzsf {



	// Particle ////////////
	void Particle::SetTileset(Tileset * ts) {
		SetTile(&(ts->at(rand()%ts->size()).at(rand()%ts[0].size())));
		entity.setOrigin(float(GetTile()->width)/2, float(GetTile()->height)/2);
	}

	void Particle::CopyAnimation(Animation* a) {
		animCopy.reset(new Animation(a->GetFrameSize(), a->GetTexture(), a->GetTimePerFrame(), a->IsRepeating()));
		SetAnimation(animCopy.get());
	}

	Particle::Particle(const Particle& p) : animCopy(nullptr) {
		if(p.animCopy != nullptr)
			CopyAnimation(p.animCopy.get());
		else
			SetTile(dynamic_cast<const Drawable *>(&p)->GetTile());
	
		Initialise(p.force.x, p.force.y,
			p.friction,
			p.gravity,
			p.life,
			p.entity.getPosition(),
			p.entity.getScale().x,
			p.entity.getColor());
	}

	void Particle::FixAngle() {
		while(force.x < 0) force.x += 2*PI;
		while(force.x >= 2*PI) force.x -= 2*PI;
	}


	sf::Clock Particle::GetClock() {return fadeClock;}
	bool Particle::IsDead() {return dead;}


	void Particle::Initialise(float _a, float _v, float fric, sf::Vector2f grav, sf::Time lifeTime, sf::Vector2f pos, float scale, sf::Color col) {
		dead = false;
		force = sf::Vector2f(_a, _v);
		friction = fric;
		gravity = grav;
		startAlpha = col.a;
		life = lifeTime;

		if(grav.y == 0) if(_v / fric < lifeTime.asSeconds()) life = sf::seconds(_v / fric);
		
		entity.setColor(col);
		entity.setPosition(pos);
		entity.setScale(scale, scale);
		entity.setOrigin(entity.getLocalBounds().width/2, entity.getLocalBounds().height/2);
		entity.setRotation(RADTODEG(force.x));
	}

	Particle::Particle(float _a, float _v, float fric, sf::Vector2f grav, sf::Time lifeTime, sf::Vector2f pos, float scale, sf::Color col, Animation* anim) : animCopy(nullptr) {
		CopyAnimation(anim);

		Initialise(_a, _v, fric, grav, lifeTime, pos, scale, col);
	}

	
	Particle::Particle(float _a, float _v, float fric, sf::Vector2f grav, sf::Time lifeTime, sf::Vector2f pos, float scale, sf::Color col, Tileset * ts) : animCopy(nullptr) {
		SetTileset(ts);

		Initialise(_a, _v, fric, grav, lifeTime, pos, scale, col);
	}



	void Particle::Update(sf::Time mDelta) {
		float fTime = mDelta.asSeconds();
		float elapsed = fadeClock.getElapsedTime().asSeconds() / life.asSeconds();
		if(elapsed >= 1) {dead = true; return;}
		
		sf::Color col = entity.getColor();
		col.a = sf::Uint8(startAlpha - startAlpha*elapsed);
		entity.setColor(col);


		force.y -= friction * fTime;
		
		if(gravity.y != 0) {
			FixAngle();
			float a = (cos(force.x)*force.y + cos(gravity.x)*gravity.y*fTime);
			float b = (sin(force.x)*force.y + sin(gravity.x)*gravity.y*fTime);
			force.x = ((force.x <= PI / 2 || force.x > (3 * PI) / 2) ? 0 : PI) + atan(b / a);
			force.y = sqrt(pow(a, 2) + pow(b, 2));
		}

		if(force.y <= 0) {dead = true; return;}

		entity.move(sf::Vector2f(cos(force.x)*force.y * fTime, sin(force.x)*force.y * fTime));
	}
	///////////////////////



	inline sf::Color SpreadColor(sf::Color c, float spread) {
		sf::Int16 tR = static_cast<sf::Int16>(
			-(255 * (spread/2)) + (floor(255 * spread) != 0 ? rand()%(sf::Uint8)(255 * spread) : 0)
		);
		if(c.r + tR < 0) tR = -c.r; else if(c.r + tR > 255) tR = 255-c.r;

		sf::Int16 tG = static_cast<sf::Int16>(
			-(255 * (spread / 2)) + (floor(255 * spread) != 0 ? rand() % (sf::Uint8)(255 * spread) : 0)
		);
		if(c.g + tG < 0) tG = -c.g; else if(c.g + tG > 255) tG = 255-c.g;

		sf::Int16 tB = static_cast<sf::Int16>(
			-(255 * (spread / 2)) + (floor(255 * spread) != 0 ? rand() % (sf::Uint8)(255 * spread) : 0)
		);
		if(c.b + tB < 0) tB = -c.b; else if(c.b + tB > 255) tB = 255-c.b;

		sf::Int16 tA = static_cast<sf::Int16>(
			-(255 * (spread / 2))*0.1f + (floor(c.a * spread) != 0 ? rand() % (sf::Uint8)(255 * spread)*0.1f : 0)
		);
		if(c.a + tA < 0) tA = -c.a; else if(c.a + tA > 255) tA = 255-c.a;

		return sf::Color(c.r + tR, c.g + tG, c.b + tB, c.a + tA);
	}




	// Emitter ////////
	Emitter::Emitter() :
		fuel(0),
		pps(0),
		ppsOverflow(0),

		angle(0),
		angleSpread(PI/2),

		velocity(100),
		velocitySpread(0.1f),

		color(255, 255, 255, 255),
		colorSpread(0.01f),

		scale(1.f),
		scaleSpread(0.05f),

		life(sf::seconds(1)),
		lifeSpread(0.05f),

		origin(0, 0),

		friction(0),
		gravity(0, 0),

		dead(false),
		firstFuel(false),
		cutType(0),
		tileset(nullptr),
		anim(nullptr) {}
	
	Emitter::~Emitter() {
		particles.clear();
	}

	bool Emitter::IsDead() {return dead;}
	
	void Emitter::Kill(Cut cut) {
		cutType = cut;

		if(cut == HARD) dead = true;
		else if(cut == MEDIUM) fuel = 0;
	}



	void Emitter::SetTileset(Tileset * ts, bool redraw) {
		tileset = ts;
		anim = nullptr;

		if(redraw) {
			for(Particle& p : particles) {
				p.SetTileset(ts);
			}
		}
	}

	void Emitter::SetAnimation(Animation* a, bool redraw) {
		anim = a;
		tileset = nullptr;

		if(redraw) {
			for(Particle& p : particles) {
				p.CopyAnimation(a);
				p.GetEntity().setOrigin((sf::Vector2f)a->GetFrameSize()/2.f);
			}
		}
	}


	void Emitter::SetAngle(float a, float spread)		{angle = a; angleSpread = spread;		}
	void Emitter::SetVelocity(float v, float spread)	{velocity = v; velocitySpread = spread;	}
	void Emitter::SetColor(sf::Color c, float spread, bool redraw) {
		color = c;
		colorSpread = spread;

		if(redraw) {
			for(Particle& p : particles) {
				sf::Color c = SpreadColor(color, colorSpread);
				p.startAlpha = c.a;
				p.GetEntity().setColor(c);
			}
		}
	}
	void Emitter::SetScale(float s, float spread, bool redraw) {
		scale = s;
		scaleSpread = spread;

		if(redraw) {
			for(Particle& p : particles) {
				float ss = float(rand()%(sf::Uint32)((scale*scaleSpread)*1000))/1000;
				p.GetEntity().setScale(scale - (scale*scaleSpread)/2 + ss, scale - (scale*scaleSpread)/2 + ss);
			}
		}
	}
	void Emitter::SetLifeTime(sf::Time l, float spread)	{life = l; lifeSpread = spread;			}
	void Emitter::SetOrigin(sf::Vector2f o)				{origin = o;							}
	void Emitter::SetParticlesPerSecond(sf::Uint32 p)	{pps = p;								}
	void Emitter::SetFriction(float f)					{friction = f;							}
	void Emitter::SetGravity(sf::Vector2f grav)			{gravity = grav;						}
	void Emitter::SetGravity(float angle, float velocity) {SetGravity(sf::Vector2f(angle, velocity));}

	void Emitter::Fuel(sf::Uint32 amount, bool relative) {
		if(cutType == 0 || (cutType == SOFT && !firstFuel)) {if(relative) fuel+=amount; else fuel = amount; firstFuel = true;}
	}



	void Emitter::Draw(sf::RenderTarget& window, sf::RenderStates states) {
		sf::Time mDelta = clock.restart();
		if(fuel > 0) {
			sf::Uint32 pToAdd = fuel;
			if(pps > 0) {
				pToAdd = 0;
				ppsOverflow += mDelta.asSeconds() * (float)pps;
				while(ppsOverflow >= 1) {pToAdd++; ppsOverflow--;}
				if(pToAdd > fuel) pToAdd = fuel;
			}

			for(sf::Uint32 i = 0; i<pToAdd; i++) {
				float a = angle - (angleSpread/2) + float(rand()%(sf::Uint32)(angleSpread*1000))/1000;
				float v = velocity - (velocity * velocitySpread/2) + float(rand()%(sf::Uint32)(velocity * velocitySpread * 1000))/1000;
				float l = life.asSeconds() - (life.asSeconds() * lifeSpread/2) + float(rand()%(sf::Uint32)(life.asSeconds() * lifeSpread * 1000))/1000;
				float s = scale - (scale * scaleSpread/2) + float(rand()%(sf::Uint32)(scale * scaleSpread*1000))/1000;

				if(anim == nullptr) 
					particles.push_back(Particle(a, v, friction, gravity, sf::seconds(l), origin, s, SpreadColor(color, colorSpread), tileset));// Add New particle
				else 
					particles.push_back(Particle(a, v, friction, gravity, sf::seconds(l), origin, s, SpreadColor(color, colorSpread), anim));// Add New particle
			}

			fuel -= pToAdd;
		}
		
		
		if(cutType == SOFT) {
			if(fuel == 0 && particles.size() == 0) dead = true;
		} else if(cutType == MEDIUM) {
			if(particles.size() == 0) dead = true;
		}

		if(!dead) {
			particles.erase(std::remove_if(particles.begin(), particles.end(), [] (Particle& p) {return p.IsDead();}), particles.end());
			
			for(Particle& p : particles){
				p.Update(mDelta);
				p.Draw(window, states);
			}
		}
	}
	//////////////////////////




	

	// ParticleSystem ////////
	std::vector<std::unique_ptr<Emitter>> ParticleSystem::unownedEmitters = std::vector<std::unique_ptr<Emitter>>();



	Emitter* ParticleSystem::NewEmitter() {
		std::unique_ptr<Emitter> e(new Emitter());
		e->Kill(Emitter::SOFT);
		unownedEmitters.push_back(std::move(e));

		return unownedEmitters[unownedEmitters.size()-1].get();
	}


	std::vector<std::unique_ptr<Emitter>>& ParticleSystem::GetUnownedEmitters() {
		return unownedEmitters;
	}


	// Draw
	void ParticleSystem::Draw(sf::RenderTarget& window, sf::RenderStates states) {
		unownedEmitters.erase(std::remove_if(unownedEmitters.begin(), unownedEmitters.end(), [] (std::unique_ptr<Emitter>& e) {return e->IsDead();}), unownedEmitters.end());


		for(std::unique_ptr<Emitter>& e : unownedEmitters) {
			e->Draw(window, states);
		}
	}
	/////////////////////////
}