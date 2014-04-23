
namespace bzsf {

	class Emitter {
	public:
		enum Cut { SOFT = 1, MEDIUM, HARD };

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

		std::vector<ParticlePtr> particles;
		sf::VertexArray particle_vertices;

		const sf::Texture* texture;

		Tileset* tileset;
		Animation* anim;


		void Init();

	public:
		explicit Emitter();
		explicit Emitter(Animation* anim);
		explicit Emitter(Tileset* ts);

		void SetTileset(const TilesetPtr& ts, bool redraw = false);
		void SetAnimation(Animation* a, bool redraw = false);

		void SetAngle(float a, float spread = PI / 2);
		void SetVelocity(float v, float spread = 0.6f);
		void SetColor(sf::Color c, float spread = 0.01f, bool redraw = false);
		void SetScale(float s, float spread = 0.05f, bool redraw = false);
		void SetLifeTime(sf::Time l, float spread = 0.05f);

		void SetOrigin(sf::Vector2f o);

		void SetParticlesPerSecond(sf::Uint32 p);

		void SetFriction(float f);
		void SetGravity(float angle, float velocity);
		void SetGravity(sf::Vector2f grav);


		void Fuel(sf::Uint32 amount, bool relative = true);


		sf::Uint32 GetFuel();
		sf::Uint32 GetParticleCount();
		bool IsEmpty();
		bool IsDead();

		///////////////////////////////////////////////
		/// A Soft cut will wait for fuel to empty
		///		and for the last particles to disappear
		/// A Medium cut will set fuel to 0, but
		///		waits for every particle to disappear
		/// A Hard cut removes both fuel and particles
		///////////////////////////////////////////////
		void Kill(Cut cut = Cut::MEDIUM);

		void Draw(sf::RenderTarget& window, sf::RenderStates states = sf::RenderStates::Default);

		~Emitter();

		friend class ParticleSystem;
	};

}