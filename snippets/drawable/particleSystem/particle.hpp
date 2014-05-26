
namespace bzsf {

	class Emitter;

	class Particle {
	private:
		std::unique_ptr<Drawable> drawable;
		sf::Color color;
		sf::Vector2f position;

		// No randomization is done within this class except choosing a tile

		sf::Vector2f force;
		sf::Vector2f friction;

		bool dead;
		sf::Uint8 startAlpha;

		sf::Time life;
		sf::Clock fadeClock;

		sf::Vector2f gravity;

		std::shared_ptr<Animation> animCopy;

		void SetTileset(Tileset * ts);
		void CopyAnimation(Animation* a);

		void FixAngle(float& a);

		void Initialise(float _a, float _v, float fric, sf::Vector2f grav, sf::Time lifeTime, sf::Vector2f pos, float scale, sf::Color col);

	public:
		sf::Clock GetClock();
		bool IsDead();

		Particle(float _a, float _v, float fric, sf::Vector2f grav, sf::Time lifeTime, sf::Vector2f pos, float scale, sf::Color col);
		Particle(float _a, float _v, float fric, sf::Vector2f grav, sf::Time lifeTime, sf::Vector2f pos, float scale, sf::Color col, Animation* anim);
		Particle(float _a, float _v, float fric, sf::Vector2f grav, sf::Time lifeTime, sf::Vector2f pos, float scale, sf::Color col, Tileset * ts);

		void Update(const sf::Time& mDelta);

		friend class Emitter;
	};

	typedef std::unique_ptr<Particle> ParticlePtr;
}