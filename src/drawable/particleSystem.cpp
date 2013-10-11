#include <SFML_Snips.hpp>

namespace bzsf {
	// Particle ////////////
	void Particle::SetTileset(Tileset * ts) {
		SetTile(&(ts->at(rand()%ts->size()).at(rand()%ts[0].size())));
		entity.setOrigin(float(GetTile()->width)/2, float(GetTile()->height)/2);
	}

	void Particle::fixAngle() {
		while(force.x < 0) {force.x += 2*PI;}
		while(force.x >= 2*PI) {force.x -= 2*PI;}
	}


	sf::Clock Particle::GetClock() {return fadeClock;}
	bool Particle::IsDead() {return dead;}



	Particle::Particle(float _a, float _v, float friction, sf::Time lifeTime, sf::Vector2f pos, float scale, Animation* anim, sf::Color col) : force(_a, _v), gravity(-_a, friction), dead(false), noGravity(true), color(col){
		life = sf::seconds(_v / friction);
		if(lifeTime < life) life = lifeTime;

		SetAnimation(anim);
		entity.setPosition(pos);
		entity.setScale(scale, scale);
		entity.setOrigin(entity.getLocalBounds().width/2, entity.getLocalBounds().height/2);
		entity.setColor(color);
	}

	
	Particle::Particle(float _a, float _v, float friction, sf::Time lifeTime, sf::Vector2f pos, float scale, sf::Color _color, Tileset * ts) : force(_a, _v), gravity(-_a, friction), dead(false), noGravity(true), color(_color) {
		life = sf::seconds(_v / friction);
		if(lifeTime < life) life = lifeTime;

		SetTile(&(ts->at(rand()%ts->size()).at(rand()%ts[0].size())));
		entity.setPosition(pos);
		entity.setScale(scale, scale);
		entity.setRotation(RADTODEG(_a));
		entity.setOrigin(entity.getLocalBounds().width/2, entity.getLocalBounds().height/2);
		entity.setColor(color);
	}


	Particle::Particle(float _a, float _v, float grav_a, float grav_v, sf::Time lifeTime, sf::Vector2f pos, float scale, sf::Color _color, Tileset * ts) : force(_a, _v), gravity(grav_a, grav_v), dead(false), noGravity(false), color(_color), life(lifeTime) {
		SetTile(&(ts->at(rand()%ts->size()).at(rand()%ts[0].size())));
		entity.setPosition(pos);
		entity.setScale(scale, scale);
		entity.setRotation(RADTODEG(_a));
		entity.setOrigin(entity.getLocalBounds().width/2, entity.getLocalBounds().height/2);
		entity.setColor(color);
	}



	void Particle::Update(sf::Time mDelta) {
		float fTime = mDelta.asSeconds();
		float elapsed = fadeClock.getElapsedTime().asSeconds() / life.asSeconds();
		if(elapsed >= 1) {dead = true; return;}
		
		sf::Color col = entity.getColor();
		col.a = sf::Uint8(255 - 255*elapsed);
		entity.setColor(col);

		entity.setPosition(entity.getPosition().x + cos(force.x)*force.y * fTime, entity.getPosition().y + sin(force.x)*force.y * fTime);
		
		if(noGravity) {
			force.y -= gravity.y * fTime;
		} else {
			fixAngle();
			float a = (cos(force.x)*force.y + cos(gravity.x)*gravity.y*fTime);
			float b = (sin(force.x)*force.y + sin(gravity.x)*gravity.y*fTime);
			force.x = ((force.x <= PI/2 || force.x > (3*PI)/2) ? 0 : PI) + atan(b / a);
			force.y = sqrt(pow(a, 2) + pow(b, 2));
		}
	}
	///////////////////////



	inline sf::Color SpreadColor(sf::Color c, float spread) {
		sf::Uint8 tR = c.r - (c.r * (spread/2)) + rand()%(sf::Uint8)(c.r * spread);
		if(c.r + tR < 0) tR = -c.r; else if(c.r + tR > 255) tR = 255-c.r;

		sf::Uint8 tG = c.g - (c.g * (spread/2)) + rand()%(sf::Uint8)(c.g * spread);
		if(c.g + tG < 0) tG = -c.g; else if(c.g + tG > 255) tG = 255-c.g;

		sf::Uint8 tB = c.b - (c.b * (spread/2)) + rand()%(sf::Uint8)(c.b * spread);
		if(c.b + tB < 0) tB = -c.b; else if(c.b + tB > 255) tB = 255-c.b;

		sf::Uint8 tA = c.a - (c.a * (spread/2)) + rand()%(sf::Uint8)(c.a * spread);
		if(c.a + tA < 0) tA = -c.a; else if(c.a + tA > 255) tA = 255-c.a;

		return sf::Color(c.r + tR, c.g + tG, c.b + tB, c.a + tA);
	}



	// Emitter ////////
	Emitter::Emitter() :
		fuel(0),
		pps(0),

		angle(0),
		angleSpread(PI/2),

		velocity(100),
		velocitySpread(0.1f),

		color(),
		colorSpread(0.01f),

		scale(1.f),
		scaleSpread(0.05f),

		life(sf::seconds(1)),
		lifeSpread(0.05f),

		origin(0, 0),

		dead(false),
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
				p.SetAnimation(a);
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
				p.GetEntity().setColor(SpreadColor(color, colorSpread));
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


	void Emitter::Fuel(sf::Uint32 amount, bool relative) {
		if(cutType == 0) {if(relative) fuel+=amount; else fuel = amount;}
	}



	void Emitter::Draw() {
		sf::Time mDelta = clock.restart();
		if(fuel > 0) {
			sf::Uint32 pToAdd = fuel;
			if(pps > 0) {
				pToAdd = (mDelta.asSeconds() / 1.f) * pps;
				if(pToAdd > fuel) pToAdd = fuel;
			}

			for(sf::Uint32 i = 0; i<pToAdd; i++) {
				//particles.push_back(Particle()); // Add New particle
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
				p.draw();
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
	void ParticleSystem::Draw() {
		unownedEmitters.erase(std::remove_if(unownedEmitters.begin(), unownedEmitters.end(), [] (std::unique_ptr<Emitter>& e) {return e->IsDead();}), unownedEmitters.end());


		for(std::unique_ptr<Emitter>& e : unownedEmitters) {
			e->Draw();
		}
	}


	// Destructor
	ParticleSystem::~ParticleSystem() {
		for(std::unique_ptr<Emitter>& e : unownedEmitters) {
			e.reset();
		}
	}


	/////////////////////////
}