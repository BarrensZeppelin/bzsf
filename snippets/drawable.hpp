#include <bzsf\snippets\drawable\animation.hpp>
#include <bzsf\snippets\drawable\tileset.hpp>

namespace bzsf {

	class Drawable : public sf::Transformable, public sf::Drawable {
	private:
		enum DrawType {TEXTURE, TILE, ANIMATION, NONE};

		DrawType dType;

		mutable sf::Sprite sprite;
		mutable int animIndex;

		bzsf::Animation* anim = nullptr;

	private:
		void init();

		void draw(sf::RenderTarget& window, sf::RenderStates states = sf::RenderStates::Default) const;

	public:
		Animation& getAnimation();
		const sf::Texture& getTexture() const;
		sf::IntRect getTextureRect() const;

		sf::FloatRect getLocalBounds() const;
		sf::FloatRect getGlobalBounds() const;
		const sf::Color& getColor() const;


		void setColor(const sf::Color& color);

		void setAnimation(const Animation& a);
		void setTexture(const sf::Texture& Tex);
		void setTile(const tsTile* tl);


		Drawable();
		explicit Drawable(Animation& animation);
		explicit Drawable(const sf::Texture& texture);
		explicit Drawable(const tsTile* tile);
	};

} //ENDOF NAMESPACE bzsf 

#include <bzsf\snippets\drawable\particleSystem.hpp>