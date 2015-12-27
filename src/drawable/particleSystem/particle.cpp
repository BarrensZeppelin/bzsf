#include <SFML_Snips.hpp>

namespace bzsf {
	Particle::Particle(float _a, float _v, float fric, sf::Vector2f grav, sf::Time lifeTime, sf::Vector2f pos, float scale, sf::Color col) {
		initialise(_a, _v, fric, grav, lifeTime, pos, scale, col);
	}

	/*Particle::Particle(float _a, float _v, float fric, sf::Vector2f grav, sf::Time lifeTime, sf::Vector2f pos, float scale, sf::Color col, Animation* anim) : animCopy(nullptr) {
	copyAnimation(anim);

	initialise(_a, _v, fric, grav, lifeTime, pos, scale, col);
	}


	Particle::Particle(float _a, float _v, float fric, sf::Vector2f grav, sf::Time lifeTime, sf::Vector2f pos, float scale, sf::Color col, Tileset * ts) : animCopy(nullptr) {
	initialise(_a, _v, fric, grav, lifeTime, pos, scale, col);
	}*/

	/*void Particle::setTileset(Tileset * ts) {
		drawable->setTile(&(ts->at(rand() % ts->size()).at(rand() % ts[0].size())));
		drawable->getEntity().setOrigin(float(drawable->getTile()->width) / 2, float(drawable->getTile()->height) / 2);
	}*/

	void Particle::copyAnimation(const Animation* a) {
		animCopy.reset(new Animation(a->getFrameSize(), *a->getTexture(), a->getTimePerFrame(), a->isRepeating()));
	}


	void Particle::initialise(float _a, float _v, float fric, sf::Vector2f grav, sf::Time lifeTime, sf::Vector2f pos, float scale, sf::Color col) {
		dead = false;
		force = sf::Vector2f(std::cos(_a) * _v, std::sin(_a) * _v);
		friction = -unitVector(force) * fric;
		gravity = sf::Vector2f(std::cos(grav.x) * grav.y, std::sin(grav.x) * grav.y);
		startAlpha = col.a;
		life = lifeTime;
		position = pos;
		color = col;


		if(fric != 0) if(_v / fric < lifeTime.asSeconds()) life = sf::seconds(_v / fric);
	}



	const sf::Clock& Particle::getClock() const { return fadeClock; }
	bool Particle::isDead() { return dead; }


	void Particle::update(sf::Time dt) {
		float elapsed = fadeClock.getElapsedTime().asSeconds() / life.asSeconds();
		if(elapsed >= 1) { dead = true; return; }

		color.a = sf::Uint8(startAlpha - startAlpha * elapsed);

		force -= friction * dt.asSeconds() + gravity * dt.asSeconds();

		position += force * dt.asSeconds();
	}
	///////////////////////

}