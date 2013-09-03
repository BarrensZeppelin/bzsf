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


	sf::Clock Particle::getClock() {return fadeClock;}
	bool Particle::isDead() {return dead;}



	Particle::Particle(float _a, float _v, float friction, sf::Vector2f pos, float scale, Animation* anim) : force(_a, _v), gravity(-_a, friction), dead(false), noGravity(true), color(sf::Color(255, 255, 255)){
		life = _v / friction;

		//animation = Animation(anim);

		SetAnimation(anim);
		entity.setPosition(pos);
		entity.setScale(scale, scale);
		entity.setOrigin(entity.getLocalBounds().width/2, entity.getLocalBounds().height/2);
		entity.setColor(color);
	}

	
	Particle::Particle(float _a, float _v, float friction, sf::Vector2f pos, float scale, sf::Color _color, Tileset * ts) : force(_a, _v), gravity(-_a, friction), dead(false), noGravity(true), color(_color) {
		life = _v / friction;

		SetTile(&(ts->at(rand()%ts->size()).at(rand()%ts[0].size())));
		entity.setPosition(pos);
		entity.setScale(scale, scale);
		entity.setRotation(RADTODEG(_a));
		entity.setOrigin(entity.getLocalBounds().width/2, entity.getLocalBounds().height/2);
		entity.setColor(color);
	}


	Particle::Particle(float _a, float _v, float grav_a, float grav_v, sf::Vector2f pos, float scale, float seconds, sf::Color _color, Tileset * ts) : force(_a, _v), gravity(grav_a, grav_v), dead(false), noGravity(false), color(_color), life(seconds) {
		SetTile(&(ts->at(rand()%ts->size()).at(rand()%ts[0].size())));
		entity.setPosition(pos);
		entity.setScale(scale, scale);
		entity.setRotation(RADTODEG(_a));
		entity.setOrigin(entity.getLocalBounds().width/2, entity.getLocalBounds().height/2);
		entity.setColor(color);
	}



	void Particle::update(float mDelta) {
		float elapsed = fadeClock.getElapsedTime().asSeconds() / life;
		if(elapsed >= 1) {dead = true; return;}
		
		sf::Color col = entity.getColor();
		col.a = sf::Uint8(255 - 255*elapsed);
		entity.setColor(col);

		entity.setPosition(entity.getPosition().x + cos(force.x)*force.y * mDelta, entity.getPosition().y + sin(force.x)*force.y * mDelta);
		
		if(noGravity) {
			force.y -= gravity.y * mDelta;
		} else {
			fixAngle();
			float a = (cos(force.x)*force.y + cos(gravity.x)*gravity.y*mDelta);
			float b = (sin(force.x)*force.y + sin(gravity.x)*gravity.y*mDelta);
			force.x = ((force.x <= PI/2 || force.x > (3*PI)/2) ? 0 : PI) + atan(b / a);
			force.y = sqrt(pow(a, 2) + pow(b, 2));
		}
	}
	///////////////////////




	// ParticleSystem ////////
	ParticleSystem::ParticleSystem(Tileset * ts) : tileset(ts) {}
	ParticleSystem::~ParticleSystem() {
		particles.clear();
	}


	void ParticleSystem::SetTileset(Tileset * ts, bool redraw) {
		tileset = ts;

		if(redraw) {
			for(std::vector<Particle>::iterator iter = particles.begin(); iter!=particles.end(); iter++) {
				Particle particle = *iter;

				particle.SetTileset(tileset);
			}
		}
	}


	void ParticleSystem::draw() {
		float mDelta = clock.restart().asSeconds();
		for(unsigned int i = 0; i < particles.size(); i++){
			particles[i].update(mDelta);

			if(particles[i].isDead()) {
				particles.erase(particles.begin() + i);
				i--;
			} else {
				particles[i].draw();
			}
		}
	}


	void ParticleSystem::fuelFricAnim(float angle, float velocity, int amount, float friction, sf::Vector2f origin, bzsf::Animation* anim, sf::Color color, float angleSpread, float velocitySpread, float scale) {
		if(angleSpread > 2*PI) angleSpread = 2*PI;

		for(int i = 0; i < amount; i++) {
			float as = float(rand()%(int)(angleSpread*1000))/1000;
			float vs = float(rand()%(int)(velocity * velocitySpread));
			particles.push_back(Particle(angle - angleSpread/2 + as, velocity - (velocity * velocitySpread) + vs*2, friction, origin, scale, anim));
		}
	} 



	void ParticleSystem::fuelFric(float angle, float velocity, int amount, float friction, sf::Vector2f origin, sf::Color color, float angleSpread, float velocitySpread, float scale) {
		if(angleSpread > 2*PI) angleSpread = 2*PI;

		for(int i = 0; i < amount; i++) {
			float as = float(rand()%(int)(angleSpread*1000))/1000;
			float vs = float(rand()%(int)(velocity * velocitySpread));
			particles.push_back(Particle(angle - angleSpread/2 + as, velocity - (velocity * velocitySpread) + vs*2, friction, origin, scale, color, tileset));
		}
	}



	void ParticleSystem::fuelGrav(float angle, float velocity, float gravity_angle, float gravity_velocity, int amount, sf::Vector2f origin, sf::Color color, float life, float angleSpread, float velocitySpread, float scale) {
		if(angleSpread > 2*PI) angleSpread = 2*PI;


		for(int i = 0; i < amount; i++) {
			float as = float(rand()%(int)(angleSpread*1000))/1000;
			float vs = float(rand()%(int)(velocity * velocitySpread));
			particles.push_back(Particle(angle - angleSpread/2 + as, velocity - (velocity * velocitySpread) + vs*2, gravity_angle, gravity_velocity, origin, scale, life, color, tileset));
		}
	}
	//////////////////////////
}