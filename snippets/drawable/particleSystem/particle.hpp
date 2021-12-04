#include <SFML/Graphics.hpp>

#include "../animation.hpp"

namespace bzsf {

	class Emitter;
	class tsTile;

	class Particle {
	public:
		typedef std::unique_ptr<Particle> Ptr;

	private:
		sf::Color color;
		sf::Vector2f position;

		// No randomization is done within this class except choosing a tile

		sf::Vector2f force;
		sf::Vector2f friction;
		sf::Vector2f gravity;

		bool dead;
		sf::Uint8 startAlpha;

		sf::Time life;
		sf::Clock fadeClock;

		std::unique_ptr<Animation> animCopy;
		tsTile* tile;

	private:
		//void setTileset(Tileset * ts);
		void copyAnimation(const Animation* a);

		void initialise(float _a, float _v, float fric, sf::Vector2f grav, sf::Time lifeTime, sf::Vector2f pos, float scale, sf::Color col);

	public:
		const sf::Clock& getClock() const;
		bool isDead();
		sf::IntRect getTextureRect();

		Particle(float _a, float _v, float fric, sf::Vector2f grav, sf::Time lifeTime, sf::Vector2f pos, float scale, sf::Color col);

		void update(sf::Time dt);
	};
}
