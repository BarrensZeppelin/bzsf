namespace bzsf {

	class ParticleSystem;


	class Particle : public Drawable {
		// No randomization is done within this class except choosing a tile

		sf::Vector2f force; // x -> angle & y -> velocity
		sf::Vector2f gravity;
		
		sf::Color color;
		bool dead;

		bool noGravity;

		float life;
		sf::Clock fadeClock;

		void SetTileset(Tileset * ts) {
			SetTile(&(ts->at(rand()%ts->size()).at(rand()%ts[0].size())));
			entity.setOrigin(float(GetTile()->width)/2, float(GetTile()->height)/2);
		}

		void fixAngle() {
			while(force.x < 0) {force.x += 2*PI;}
			while(force.x >= 2*PI) {force.x -= 2*PI;}
		}

	public:
		sf::Clock getClock() {return fadeClock;}
		bool isDead() {return dead;}


		Particle(float _a, float _v, float friction, sf::Vector2f pos, float scale, sf::Color _color, Tileset * ts) : force(_a, _v), gravity(-_a, friction), dead(false), noGravity(true), color(_color) {
			life = _v / friction;

			SetTile(&(ts->at(rand()%ts->size()).at(rand()%ts[0].size())));
			entity.setPosition(pos);
			entity.setScale(scale, scale);
			entity.setRotation(RADTODEG(_a));
			entity.setOrigin(entity.getLocalBounds().width/2, entity.getLocalBounds().height/2);
			entity.setColor(color);
		}

		Particle(float _a, float _v, float grav_a, float grav_v, sf::Vector2f pos, float scale, float seconds, sf::Color _color, Tileset * ts) : force(_a, _v), gravity(grav_a, grav_v), dead(false), noGravity(false), color(_color), life(seconds) {
			SetTile(&(ts->at(rand()%ts->size()).at(rand()%ts[0].size())));
			entity.setPosition(pos);
			entity.setScale(scale, scale);
			entity.setRotation(RADTODEG(_a));
			entity.setOrigin(entity.getLocalBounds().width/2, entity.getLocalBounds().height/2);
			entity.setColor(color);
		}


		void update(float mDelta) {
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

		friend class ParticleSystem;
	};



	class ParticleSystem {
	
		sf::Clock clock;

		std::vector<Particle> particles;

		Tileset * tileset;
	public:
		ParticleSystem(Tileset * ts) : tileset(ts) {}

		void SetTileset(Tileset * ts, bool redraw = false) {
			tileset = ts;

			if(redraw) {
				for(std::vector<Particle>::iterator iter = particles.begin(); iter!=particles.end(); iter++) {
					Particle particle = *iter;

					particle.SetTileset(tileset);
				}
			}
		}

		
		///////////////////////////////////
		/// \brief Fuel the particle system with particles using a friction method of movement
		///
		/// angles are in radians
		///	velocity is pixels per second
		/// friction is also pixels per second
		/// 
		/// velocity = velocity - (velocity * velocitySpread) + rand()%(velocity * velocitySpread)*2
		///
		////////////////////////////////////////
		void fuelFric(float angle, float velocity, int amount, float friction, sf::Vector2f origin, sf::Color color = sf::Color(255, 255, 255, 255), float angleSpread = PI/4, float velocitySpread = 0.5f, float scale = 1) {
			
			if(angleSpread > 2*PI) angleSpread = 2*PI;

			for(int i = 0; i < amount; i++) {
				float as = float(rand()%(int)(angleSpread*1000))/1000;
				float vs = float(rand()%(int)(velocity * velocitySpread));
				particles.push_back(Particle(angle - angleSpread/2 + as, velocity - (velocity * velocitySpread) + vs*2, friction, origin, scale, color, tileset));
			}
		}

		///////////////////////////////////
		/// \brief Fuel the particle system with particles affected by a gravity
		///
		/// angles are in radians
		///	velocity is pixels per second
		/// friction is also pixels per second
		/// life is lifetime in seconds
		/// 
		/// velocity = velocity - (velocity * velocitySpread) + rand()%(velocity * velocitySpread)*2
		///
		////////////////////////////////////////
		void fuelGrav(float angle, float velocity, float gravity_angle, float gravity_velocity, int amount, sf::Vector2f origin, sf::Color color = sf::Color(255, 255, 255, 255), float life = 2.f, float angleSpread = PI/4, float velocitySpread = 0.5f, float scale = 1) {
			
			if(angleSpread > 2*PI) angleSpread = 2*PI;


			for(int i = 0; i < amount; i++) {
				float as = float(rand()%(int)(angleSpread*1000))/1000;
				float vs = float(rand()%(int)(velocity * velocitySpread));
				particles.push_back(Particle(angle - angleSpread/2 + as, velocity - (velocity * velocitySpread) + vs*2, gravity_angle, gravity_velocity, origin, scale, life, color, tileset));
			}
		}



		void draw() {
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

		~ParticleSystem() {
			particles.clear();
		}
	};

} //ENDOF NAMESPACE bzsf