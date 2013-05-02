namespace bzsf {

	class particle : public bzsf::Drawable {
		float velocity;
		float friction;
		float angle;
		
		sf::Color color;
		bool dead;

		float life;
		sf::Clock fadeClock;
	public:
		sf::Clock getClock() {return fadeClock;}
		bool isDead() {return dead;}

		particle(float _a, float _v, sf::Vector2f pos, float scale, sf::Color _color) : velocity(_v), angle(_a), friction(800.f), dead(false), color(_color) {
			//cout << "angle: " << angle << endl;
			
			life = 1.6f + (rand()%8)/10.f;

			SetTile(&particles[rand()%particles.size()][rand()%particles[0].size()]);
			entity.setPosition(pos);
			entity.setScale(0.5f, 0.5f);
			entity.setColor(color);
		}

		void update(float mDelta) {
			float elapsed = fadeClock.getElapsedTime().asSeconds() / life;
			if(elapsed >= 1) {dead = true; return;}
			
			sf::Color c = entity.getColor();
			entity.setColor(sf::Color(c.r, c.g ,c.b, sf::Uint8(255 - 255*elapsed)));
			entity.setPosition(entity.getPosition().x + cos(angle)*velocity * mDelta, entity.getPosition().y + sin(angle)*velocity * mDelta);

			velocity -= friction * mDelta;
			if(velocity < 0) {velocity = 0; dead = true;}
		}
	};



	class particleSystem {
	
		sf::Clock clock;

		std::vector<particle*> particles;
	public:
		particleSystem(){

		}

		void fuel(float angle, float angleSpread, float intensity, sf::Vector2f origin, float amountFactor = 1.f, sf::Color color = sf::Color(255, 255, 255, 255)) {
			int amount = floor(intensity / 1.5f) * amountFactor;
			
			angleSpread = PI/4 + angleSpread;
			if(angleSpread > 2*PI) angleSpread = 2*PI;

			//cout << "angle: " << angle << endl << "as: " << as << endl;

			for(int i = 0; i < amount; i++) {
				float as = float(rand()%(int)(angleSpread*1000))/1000;
				particles.push_back(new particle(angle - angleSpread/2 + as,  600.f*intensity/100 + (rand()%((int)(200*intensity/10)))*intensity/50, origin, 1.f + 1.f*intensity/40, color ));
			}
		}



		void draw() {
			float mDelta = clock.restart().asSeconds();
			for(unsigned int i = 0; i < particles.size(); i++){
				particles[i]->update(mDelta);
				if(particles[i]->isDead()) {
					particles.erase(particles.begin() + i);
					i--;
				} else {
					particles[i]->draw();
				}
			}
		}
	};

} //ENDOF NAMESPACE bzsg