namespace bzsf {

	class Emitter;


	class Particle : public Drawable {
		// No randomization is done within this class except choosing a tile

		sf::Vector2f force; // x -> angle & y -> velocity
		sf::Vector2f gravity;
		
		sf::Color color;
		bool dead;

		bool noGravity;

		sf::Time life;
		sf::Clock fadeClock;

		void SetTileset(Tileset * ts);

		void fixAngle();

	public:
		sf::Clock GetClock();
		bool IsDead();

		Particle(float _a, float _v, sf::Time lifeTime, sf::Vector2f pos, float scale, Animation* anim, sf::Color col);

		Particle(float _a, float _v, sf::Time lifeTime, sf::Vector2f pos, float scale, sf::Color _color, Tileset * ts);

		Particle(float _a, float _v, sf::Time lifeTime, sf::Vector2f pos, float scale, sf::Color _color, Tileset * ts);


		void Update(sf::Time mDelta);

		friend class Emitter;

	};



	class Emitter {
		enum Cut {SOFT = 1, MEDIUM, HARD};


		sf::Uint32 fuel;
		sf::Uint32 pps;

		float angle;
		float angleSpread;

		float velocity;
		float velocitySpread;

		sf::Color color;
		float colorSpread;

		float scale;
		float scaleSpread;

		sf::Time life;
		float lifeSpread;

		sf::Vector2f origin;



		sf::Uint8 cutType;
		bool dead;


		sf::Clock clock;

		std::vector<Particle> particles;

		Tileset* tileset;
		Animation* anim;


	public:
		explicit Emitter();

		void SetTileset(Tileset* ts, bool redraw = false);
		void SetAnimation(Animation* a, bool redraw = false);

		void SetAngle(float a,		float spread = PI/2);
		void SetVelocity(float v,	float spread = 0.1f);
		void SetColor(sf::Color c,	float spread = 0.01f, bool redraw = false);
		void SetScale(float s,		float spread = 0.05f, bool redraw = false);
		void SetLifeTime(sf::Time l,float spread = 0.05f);

		void SetOrigin(sf::Vector2f o);
		
		void SetParticlesPerSecond(sf::Uint32 p);


		void Fuel(sf::Uint32 amount, bool relative = true);


		bool IsDead();

		void Kill(Cut cut);
		void Draw();

		~Emitter();

		friend class ParticleSystem;
	};



	class ParticleSystem {

		static std::vector<std::unique_ptr<Emitter>> unownedEmitters;


	public:
		static Emitter* NewEmitter();

		static std::vector<std::unique_ptr<Emitter>>& GetUnownedEmitters();

		

		static void Draw();


		~ParticleSystem();
	};

} //ENDOF NAMESPACE bzsf