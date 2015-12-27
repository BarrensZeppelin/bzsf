#include <SFML_Snips.hpp>

namespace bzsf {
	Emitter::Emitter() : texture(nullptr) {
		init();
	}

	Emitter::Emitter(Animation* anim) : texture(anim->getTexture()) {
		init();

		this->anim = anim;
	}

	Emitter::Emitter(const Tileset& ts) : texture(ts.texture) {
		init();
		
		this->tileset = &ts;
	}


	inline sf::Color SpreadColor(const sf::Color& c, float spread) {
		int tR = static_cast<int>(randf(-255.f, 255.f) * spread);
		tR = std::max(0, std::min(255, c.r + tR));

		int tG = static_cast<int>(randf(-255.f, 255.f) * spread);
		tG = std::max(0, std::min(255, c.g + tG));

		int tB = static_cast<int>(randf(-255.f, 255.f) * spread);
		tB = std::max(0, std::min(255, c.b + tB));

		int tA = static_cast<int>(randf(-255.f, 255.f) * spread);
		tA = std::max(0, std::min(255, c.a + tA));

		return sf::Color(tR, tG, tB, tA);
	}


	void Emitter::init() {
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
		cut = NONE;
		tileset = nullptr;
		anim = nullptr;

		vertices = sf::VertexArray(sf::Quads);
		needsVertexUpdate = true;
	}

	void Emitter::update(sf::Time dt) {
		if(dead) return;
		
		if(fuel > 0) {
			sf::Uint32 pToAdd = fuel;
			if(pps > 0) {
				ppsOverflow += dt.asSeconds() * (float)pps;
				pToAdd = static_cast<sf::Uint32>(floor(ppsOverflow));
				ppsOverflow -= floor(ppsOverflow);
				pToAdd = std::min(pToAdd, fuel);
			}

			for(sf::Uint32 i = 0; i < pToAdd; i++) {
				float a = angle + randf(-angleSpread, angleSpread);
				float v = velocity + randf(-velocitySpread, velocitySpread);
				float l = life.asSeconds() + randf(-lifeSpread, lifeSpread);
				float s = scale + randf(-scaleSpread, scaleSpread);;

				particles.push_back(Particle::Ptr(new Particle(a, v, friction, gravity, sf::seconds(l), origin, s, SpreadColor(color, colorSpread))));// Add New particle
			}

			fuel -= pToAdd;
		}


		if(cut == SOFT) {
			if(fuel == 0 && empty()) dead = true;
		} else if(cut == MEDIUM) {
			if(empty()) dead = true;
		}


		particles.erase(std::remove_if(particles.begin(), particles.end(), [](Particle::Ptr& p) {return p->isDead(); }), particles.end());

		for(Particle::Ptr& p : particles)
			p->update(dt);
	
		needsVertexUpdate = true;
	}

	void Emitter::draw(sf::RenderTarget& window, sf::RenderStates states) const {
		if(needsVertexUpdate)
			computeVertices();

		states.texture = texture;
		window.draw(vertices, states);
	}

	
	void Emitter::computeVertices() const {
		vertices.clear();

		auto r = getTextureRect();
		sf::Vector2f size(r.width, r.height);
		sf::Vector2f half = size / 2.f;

		for(const Particle::Ptr& p : particles) {
			addVertex(origin - sf::Vector2f(half.x, half.y), sf::Vector2f(0, 0), color);
			addVertex(origin - sf::Vector2f(-half.x, half.y), sf::Vector2f(size.x, 0), color);
			addVertex(origin + sf::Vector2f(half.x, half.y), sf::Vector2f(size.x, size.y), color);
			addVertex(origin + sf::Vector2f(-half.x, half.y), sf::Vector2f(0, size.y), color);
		}

		needsVertexUpdate = false;
	}

	void Emitter::addVertex(sf::Vector2f pos, sf::Vector2f texCoords, const sf::Color& color) const {
		sf::Vertex vertex(pos, color, texCoords);
		vertices.append(vertex);
	}


	Emitter::~Emitter() {
		particles.clear();
	}


	sf::Uint32 Emitter::getFuel() const			{ return fuel;				}
	sf::Uint32 Emitter::getParticleCount() const	{ return particles.size();	}
	bool Emitter::empty()	const				{ return particles.empty(); }
	bool Emitter::isDead() const					{ return dead;				}

	void Emitter::kill(Cut cut) {
		this->cut = cut;

		if(cut == HARD) dead = true;
		else if(cut == MEDIUM) fuel = 0;
	}



	void Emitter::setTileset(const Tileset::Ptr& ts) {
		tileset = ts.get();

		texture = ts->texture;
		anim = nullptr;
	}

	void Emitter::setAnimation(const Animation& a) {
		anim = const_cast<Animation*>(&a);
		tileset = nullptr;

		texture = a.getTexture();
	}


	void Emitter::setAngle(float a, float spread) { angle = a; angleSpread = spread / 2.f; }
	void Emitter::setVelocity(float v, float spread) { velocity = v; velocitySpread = (velocity * spread) / 2.f; }
	void Emitter::setColor(sf::Color c, float spread) { color = c; colorSpread = spread; }
	void Emitter::setScale(float s, float spread) { scale = s; scaleSpread = (scale * spread) / 2.f; }
	void Emitter::setLifeTime(sf::Time l, float spread) { life = l; lifeSpread = (l.asSeconds() * spread) / 2.f; }
	void Emitter::setOrigin(sf::Vector2f o) { origin = o; }
	void Emitter::setParticlesPerSecond(sf::Uint32 p) { pps = p; }
	void Emitter::setFriction(float f) { friction = f; }
	void Emitter::setGravity(sf::Vector2f grav) { gravity = grav; }
	void Emitter::setGravity(float angle, float velocity) { setGravity(sf::Vector2f(angle, velocity)); }

	void Emitter::fuelParticles(sf::Uint32 amount, bool relative) {
		if(cut == NONE || (cut == SOFT && !firstFuel)) { 
			if(relative) fuel += amount; 
			else fuel = amount; firstFuel = true;
		}
	}
}