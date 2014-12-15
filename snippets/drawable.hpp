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
		bzsf::tsTile* texTile = nullptr;
		const sf::Texture* tex = nullptr;

	private:
		void init();

		void draw(sf::RenderTarget& window, sf::RenderStates states = sf::RenderStates::Default) const;

	public:
		const tsTile * getTile() const;
		Animation& getAnimation();
		const sf::Texture& getTexture();
		
		sf::FloatRect getLocalBounds() const;
		sf::FloatRect getGlobalBounds() const;
		const sf::Color& getColor() const;


		void setColor(const sf::Color& color);

		void setAnimation(const Animation& a);
		void setTexture(const sf::Texture& Tex);
		void setTile(const tsTile * tl);


		Drawable();
		explicit Drawable(const Animation& animation);
		explicit Drawable(const sf::Texture& texture);
		explicit Drawable(tsTile * tile);
	};

} //ENDOF NAMESPACE bzsf 

#include <bzsf\snippets\drawable\particleSystem.hpp>