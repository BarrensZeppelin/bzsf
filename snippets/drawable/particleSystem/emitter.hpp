#include <SFML/Graphics.hpp>

#include "particle.hpp"

namespace bzsf {

	class Emitter : public sf::Drawable {
	public:
		enum Cut { NONE, SOFT, MEDIUM, HARD };

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

		Cut cut;
		bool dead;

		bool firstFuel;

		std::vector<Particle::Ptr> particles;
		mutable sf::VertexArray vertices;
		mutable bool needsVertexUpdate;

		const sf::Texture* texture;

		const Tileset* tileset;
		Animation* anim;


	private:
		void init();
		void update(sf::Time dt);
		void draw(sf::RenderTarget& window, sf::RenderStates states = sf::RenderStates::Default) const;

		void computeVertices() const;
		void addVertex(sf::Vector2f pos, sf::Vector2f texCoords, const sf::Color& color) const;

		sf::IntRect getTextureRect() const;

	public:
		Emitter();
		explicit Emitter(Animation* anim);
		explicit Emitter(const Tileset& ts);

		void setTileset(const Tileset::Ptr& ts);
		void setAnimation(const Animation& a);

		void setAngle(float a, float spread = PI / 2);
		void setVelocity(float v, float spread = 0.6f);
		void setColor(sf::Color c, float spread = 0.01f);
		void setScale(float s, float spread = 0.05f);
		void setLifeTime(sf::Time l, float spread = 0.05f);

		void setOrigin(sf::Vector2f o);

		void setParticlesPerSecond(sf::Uint32 p);

		void setFriction(float f);
		void setGravity(float angle, float velocity);
		void setGravity(sf::Vector2f grav);


		void fuelParticles(sf::Uint32 amount, bool relative = true);


		sf::Uint32 getFuel() const;
		sf::Uint32 getParticleCount() const;
		bool empty() const;
		bool isDead() const;

		///////////////////////////////////////////////
		/// A Soft cut will wait for fuel to empty
		///		and for the last particles to disappear
		/// A Medium cut will set fuel to 0, but
		///		waits for every particle to disappear
		/// A Hard cut removes both fuel and particles
		///////////////////////////////////////////////
		void kill(Cut cut = Cut::MEDIUM);

		~Emitter();
	};

}
