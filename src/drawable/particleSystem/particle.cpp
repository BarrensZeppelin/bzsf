#include <SFML_Snips.hpp>

namespace bzsf {

	void Particle::SetTileset(Tileset * ts) {
		drawable->SetTile(&(ts->at(rand() % ts->size()).at(rand() % ts[0].size())));
		drawable->GetEntity().setOrigin(float(drawable->GetTile()->width) / 2, float(drawable->GetTile()->height) / 2);
	}

	void Particle::CopyAnimation(Animation* a) {
		animCopy.reset(new Animation(a->GetFrameSize(), a->GetTexture(), a->GetTimePerFrame(), a->IsRepeating()));
		drawable->SetAnimation(animCopy.get());
	}

	void Particle::FixAngle(float& a) {
		while(a < 0) a += 2 * PI;
		while(a >= 2 * PI) a -= 2 * PI;
	}


	sf::Clock Particle::GetClock() { return fadeClock; }
	bool Particle::IsDead() { return dead; }


	void Particle::Initialise(float _a, float _v, float fric, sf::Vector2f grav, sf::Time lifeTime, sf::Vector2f pos, float scale, sf::Color col) {
		dead = false;
		force = sf::Vector2f(cos(_a) * _v, sin(_a) * _v);
		friction = -UnitVector(force) * fric;
		gravity = sf::Vector2f(cos(grav.x) * grav.y, sin(grav.x) * grav.y);
		startAlpha = col.a;
		life = lifeTime;
		position = pos;
		color = col;


		if(fric != 0) if(_v / fric < lifeTime.asSeconds()) life = sf::seconds(_v / fric);

		if(drawable) {
			drawable->GetEntity().setColor(col);
			drawable->GetEntity().setPosition(pos);
			drawable->GetEntity().setScale(scale, scale);
			drawable->GetEntity().setOrigin(drawable->GetEntity().getLocalBounds().width / 2,
											drawable->GetEntity().getLocalBounds().height / 2);
			drawable->GetEntity().setRotation(RADTODEG(_a));
		}
	}

	Particle::Particle(float _a, float _v, float fric, sf::Vector2f grav, sf::Time lifeTime, sf::Vector2f pos, float scale, sf::Color col) {
		Initialise(_a, _v, fric, grav, lifeTime, pos, scale, col);
	}

	Particle::Particle(float _a, float _v, float fric, sf::Vector2f grav, sf::Time lifeTime, sf::Vector2f pos, float scale, sf::Color col, Animation* anim) : animCopy(nullptr) {
		drawable.reset(new Drawable()); // Only construct the Drawable if it is needed
		CopyAnimation(anim);

		Initialise(_a, _v, fric, grav, lifeTime, pos, scale, col);
	}


	Particle::Particle(float _a, float _v, float fric, sf::Vector2f grav, sf::Time lifeTime, sf::Vector2f pos, float scale, sf::Color col, Tileset * ts) : animCopy(nullptr) {
		drawable.reset(new Drawable());
		SetTileset(ts);

		Initialise(_a, _v, fric, grav, lifeTime, pos, scale, col);
	}



	void Particle::Update(const sf::Time& mDelta) {
		float elapsed = fadeClock.getElapsedTime().asSeconds() / life.asSeconds();
		if(elapsed >= 1) { dead = true; return; }

		color.a = sf::Uint8(startAlpha - startAlpha * elapsed);

		force -= friction * mDelta.asSeconds() - gravity * mDelta.asSeconds();

		position += force * mDelta.asSeconds();

		if(drawable) {
			drawable->GetEntity().setPosition(position);
			drawable->GetEntity().setColor(color);

			drawable->GetEntity().setRotation(RADTODEG(
				(gravity.x != 0 ? atan(gravity.y / gravity.x) : 0)
				));
		}
	}
	///////////////////////

}