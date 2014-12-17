#include <bzsf\snippets\drawable\animation.hpp>
#include <bzsf\snippets\drawable\tileset.hpp>

namespace bzsf {

	class Drawable : public sf::Sprite {
	private:
		enum DrawType {TEXTURE, TILE, ANIMATION, NONE};

		DrawType dType;

		mutable int animIndex;
		bzsf::Animation* anim = nullptr;

	private:
		void init();

		void draw(sf::RenderTarget& window, sf::RenderStates states = sf::RenderStates::Default) const;

	public:
		Animation* getAnimation();

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