namespace bzsf {

	class Emitter;

	class Particle : public Drawable {
		// No randomization is done within this class except choosing a tile

		sf::Vector2f force; // x -> angle & y -> velocity
		
		bool dead;
		sf::Uint8 startAlpha;

		sf::Time life;
		sf::Clock fadeClock;

		float friction;
		sf::Vector2f gravity;

		std::shared_ptr<Animation> animCopy;

		void SetTileset(Tileset * ts);
		void CopyAnimation(Animation* a);

		void FixAngle();

		void Initialise(float _a, float _v, float fric, sf::Vector2f grav, sf::Time lifeTime, sf::Vector2f pos, float scale, sf::Color col);

	public:
		sf::Clock GetClock();
		bool IsDead();

		Particle(const Particle&);

		Particle(float _a, float _v, float fric, sf::Vector2f grav, sf::Time lifeTime, sf::Vector2f pos, float scale, sf::Color col, Animation* anim);

		Particle(float _a, float _v, float fric, sf::Vector2f grav, sf::Time lifeTime, sf::Vector2f pos, float scale, sf::Color col, Tileset * ts);

		void Update(sf::Time mDelta);

		friend class Emitter;
	};

	class Emitter {
	public:
		enum Cut {SOFT = 1, MEDIUM, HARD};
	
	private:
		sf::Uint32 fuel;
		sf::Uint32 pps;
		float ppsOverflow;

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


		float friction;
		sf::Vector2f gravity;


		sf::Uint8 cutType;
		bool dead;

		bool firstFuel;


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

		void SetFriction(float f);
		void SetGravity(float angle, float velocity);
		void SetGravity(sf::Vector2f grav);


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
		/////////////////////////////////////////
		/// \brief Create a new unowned Emitter
		///
		/// Assign to a bzsf::Emitter ptr and
		/// control with ->Set'ers
		/// Won't display unless without call to
		/// bzsf::ParticleSystem::Draw() and
		/// some Fuel()
		///
		/// \see bzsf::ParticleSystem::Draw
		/////////////////////////////////////////
		static Emitter* NewEmitter();

		static std::vector<std::unique_ptr<Emitter>>& GetUnownedEmitters();
		

		static void Draw();
	};

} //ENDOF NAMESPACE bzsf