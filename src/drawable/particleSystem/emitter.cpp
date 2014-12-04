#include <SFML_Snips.hpp>

namespace bzsf {

	inline sf::Color SpreadColor(sf::Color c, float spread) {
		sf::Int16 tR = static_cast<sf::Int16>(
			floor(randf(-255.f, 255.f) * spread)
			);
		if(c.r + tR < 0) tR = -c.r; else if(c.r + tR > 255) tR = 255 - c.r;

		sf::Int16 tG = static_cast<sf::Int16>(
			floor(randf(-255.f, 255.f) * spread)
			);
		if(c.g + tG < 0) tG = -c.g; else if(c.g + tG > 255) tG = 255 - c.g;

		sf::Int16 tB = static_cast<sf::Int16>(
			floor(randf(-255.f, 255.f) * spread)
			);
		if(c.b + tB < 0) tB = -c.b; else if(c.b + tB > 255) tB = 255 - c.b;

		sf::Int16 tA = static_cast<sf::Int16>(
			floor(randf(-255.f, 255.f) * spread)
			);
		if(c.a + tA < 0) tA = -c.a; else if(c.a + tA > 255) tA = 255 - c.a;

		return sf::Color(c.r + tR, c.g + tG, c.b + tB, c.a + tA);
	}



	void Emitter::Init() {
		fuel = 0;
		pps = 0;
		ppsOverflow = 0;

		angle = 0;
		angleSpread = PI / 2;

		velocity = 100;
		velocitySpread = 0.6f;

		color = sf::Color(255, 255, 255, 255);
		colorSpread = 0.01f;

		scale = 1.f;
		scaleSpread = 0.05f;

		life = sf::seconds(1);
		lifeSpread = 0.05f;

		origin = sf::Vector2f(0, 0);

		friction = 0;
		gravity = sf::Vector2f(0, 0);

		dead = false;
		firstFuel = false;
		cutType = 0;
		tileset = nullptr;
		anim = nullptr;

		particle_vertices = sf::VertexArray(sf::Points);
	}

	
	Emitter::Emitter() : texture(nullptr) {
		Init();
	}

	Emitter::Emitter(Animation* anim) : texture(&anim->GetTexture()) {
		Init();

		this->anim = anim;
	}

	Emitter::Emitter(Tileset* ts) : texture(ts->at(0)[0].texture) {
		Init();

		this->tileset = ts;
	}


	Emitter::~Emitter() {
		particles.clear();
	}


	sf::Uint32 Emitter::GetFuel()			{ return fuel;				}
	sf::Uint32 Emitter::GetParticleCount()	{ return particles.size();	}
	bool Emitter::IsEmpty()					{ return particles.empty(); }
	bool Emitter::IsDead()					{ return dead;				}

	void Emitter::Kill(Cut cut) {
		cutType = cut;

		if(cut == HARD) dead = true;
		else if(cut == MEDIUM) fuel = 0;
	}



	void Emitter::SetTileset(const TilesetPtr& ts, bool redraw) {
		tileset = ts.get();
		
		if(tileset != nullptr) {
			texture = ts->at(0)[0].texture;

			anim = nullptr;

			// the Drawable is not created within the Particle, if the emitter didn't give it the tileset
			// or animation from when it was created. This will result in the particle having a nullptr,
			// which will cause problems when the draw call for tileset != nullptr is reached

			particles.erase(particles.begin(), particles.end());

			/*if(redraw) {
				for(ParticlePtr& p : particles) {
					p->SetTileset(tileset);
				}
			}*/
		}
	}

	void Emitter::SetAnimation(Animation* a, bool redraw) {
		anim = a;
		
		if(a != nullptr) {
			texture = &a->GetTexture();

			tileset = nullptr;

			particles.erase(particles.begin(), particles.end());

			/*if(redraw) {
				for(ParticlePtr& p : particles) {
					p->CopyAnimation(a);
					p->drawable->GetEntity().setOrigin((sf::Vector2f)a->GetFrameSize() / 2.f);
				}
			}*/
		}
	}


	void Emitter::SetAngle(float a, float spread) { angle = a; angleSpread = spread / 2.f; }
	void Emitter::SetVelocity(float v, float spread) { velocity = v; velocitySpread = (velocity * spread) / 2.f; }
	void Emitter::SetColor(sf::Color c, float spread, bool redraw) {
		color = c;
		colorSpread = spread;

		/*if(redraw) {
			for(ParticlePtr& p : particles) {
				sf::Color c = SpreadColor(color, colorSpread);
				p->startAlpha = c.a;
				p->drawable->GetEntity().setColor(c);
			}
		}*/
	}
	void Emitter::SetScale(float s, float spread, bool redraw) {
		scale = s;
		scaleSpread = (scale * spread) / 2.f;

		/*if(redraw) {
			for(ParticlePtr& p : particles) {
				float ss = float(rand() % (sf::Uint32)((scale*scaleSpread) * 1000)) / 1000;
				p.GetEntity().setScale(scale - (scale*scaleSpread) / 2 + ss, scale - (scale*scaleSpread) / 2 + ss);
			}
		}*/
	}
	void Emitter::SetLifeTime(sf::Time l, float spread) { life = l; lifeSpread = (l.asSeconds() * spread) / 2.f; }
	void Emitter::SetOrigin(sf::Vector2f o) { origin = o; }
	void Emitter::SetParticlesPerSecond(sf::Uint32 p) { pps = p; }
	void Emitter::SetFriction(float f) { friction = f; }
	void Emitter::SetGravity(sf::Vector2f grav) { gravity = grav; }
	void Emitter::SetGravity(float angle, float velocity) { SetGravity(sf::Vector2f(angle, velocity)); }

	void Emitter::Fuel(sf::Uint32 amount, bool relative) {
		if(cutType == 0 || (cutType == SOFT && !firstFuel)) { if(relative) fuel += amount; else fuel = amount; firstFuel = true; }
	}



	void Emitter::Draw(sf::RenderTarget& window, sf::RenderStates states) {
		sf::Time mDelta = clock.restart();
		
		if(fuel > 0) {
			sf::Uint32 pToAdd = fuel;
			if(pps > 0) {
				ppsOverflow += mDelta.asSeconds() * (float)pps;
				pToAdd = static_cast<sf::Uint32>(floor(ppsOverflow));
				ppsOverflow -= floor(ppsOverflow);
				if(pToAdd > fuel) pToAdd = fuel;
			}

			for(sf::Uint32 i = 0; i < pToAdd; i++) {
				float a = angle				+ randf(-angleSpread, angleSpread);
				float v = velocity			+ randf(-velocitySpread, velocitySpread);
				float l = life.asSeconds()	+ randf(-lifeSpread, lifeSpread);
				float s = scale				+ randf(-scaleSpread, scaleSpread);;

				if(tileset != nullptr)
					particles.push_back(ParticlePtr(new Particle(a, v, friction, gravity, sf::seconds(l), origin, s, SpreadColor(color, colorSpread), tileset)));// Add New particle
				else if(anim != nullptr)
					particles.push_back(ParticlePtr(new Particle(a, v, friction, gravity, sf::seconds(l), origin, s, SpreadColor(color, colorSpread), anim)));// Add New particle
				else
					particles.push_back(ParticlePtr(new Particle(a, v, friction, gravity, sf::seconds(l), origin, s, SpreadColor(color, colorSpread))));// Add New particle
			}

			fuel -= pToAdd;
		}


		if(cutType == SOFT) {
			if(fuel == 0 && particles.size() == 0) dead = true;
		} else if(cutType == MEDIUM) {
			if(particles.size() == 0) dead = true;
		}


		// Actual drawing and updating particles
		if(!dead) {
			particles.erase(std::remove_if(particles.begin(), particles.end(), [](ParticlePtr& p) {return p->IsDead(); }), particles.end());
		
			if(anim == nullptr && tileset == nullptr) {
				
				size_t s = particles.size();
				particle_vertices.resize(s);

				for(sf::Uint32 i = 0; i < s; i++) {
					ParticlePtr& p = particles[i];

					p->Update(mDelta);

					particle_vertices[i] = sf::Vertex(p->position,
														p->color);
				}

				window.draw(particle_vertices, states);

			} else {
				for(ParticlePtr& p : particles) {
					p->Update(mDelta);
					p->drawable->Draw(window, states);
				}
			}
		}
	}

}