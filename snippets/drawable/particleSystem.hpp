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

		void SetTileset(Tileset * ts);

		void fixAngle();

	public:
		sf::Clock getClock();
		bool isDead();

		Particle(float _a, float _v, float friction, sf::Vector2f pos, float scale, Animation* anim);

		Particle(float _a, float _v, float friction, sf::Vector2f pos, float scale, sf::Color _color, Tileset * ts);

		Particle(float _a, float _v, float grav_a, float grav_v, sf::Vector2f pos, float scale, float seconds, sf::Color _color, Tileset * ts);


		void update(float mDelta);

		friend class ParticleSystem;

	};



	class ParticleSystem {
	
		sf::Clock clock;

		std::vector<Particle> particles;

		Tileset * tileset;
	public:
		explicit ParticleSystem(Tileset * ts);

		void SetTileset(Tileset * ts, bool redraw = false);

		void fuelFricAnim(float angle, float velocity, int amount, float friction, sf::Vector2f origin, bzsf::Animation* anim, sf::Color color = sf::Color(255, 255, 255, 255), float angleSpread = PI/4, float velocitySpread = 0.5f, float scale = 1);

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
		void fuelFric(float angle, float velocity, int amount, float friction, sf::Vector2f origin, sf::Color color = sf::Color(255, 255, 255, 255), float angleSpread = PI/4, float velocitySpread = 0.5f, float scale = 1);

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
		void fuelGrav(float angle, float velocity, float gravity_angle, float gravity_velocity, int amount, sf::Vector2f origin, sf::Color color = sf::Color(255, 255, 255, 255), float life = 2.f, float angleSpread = PI/4, float velocitySpread = 0.5f, float scale = 1);



		void draw();

		~ParticleSystem();
	};

} //ENDOF NAMESPACE bzsf