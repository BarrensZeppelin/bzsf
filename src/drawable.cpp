#include <SFML_Snips.hpp>
#include <bzsf\snippets\drawable\tsTile.hpp>

namespace bzsf {
	Drawable::Drawable() {}

	Drawable::Drawable(Animation& animation) {
		init();
		setAnimation(animation);
	}

	Drawable::Drawable(const sf::Texture& texture) {
		init();
		setTexture(texture);
	}

	Drawable::Drawable(const tsTile* tile) {
		init();
		setTile(tile);
	}


	void Drawable::init() {
		animIndex = 0;
		dType = NONE;
	}

	void Drawable::draw(sf::RenderTarget& window, sf::RenderStates states) const {
		if(dType == ANIMATION) {
			anim->update();
			if(anim->getIndex() != animIndex) {
				animIndex = anim->getIndex();
				const_cast<sf::Sprite*>((const sf::Sprite*)this)->setTextureRect(anim->getFrameRect());
			}
		}

		if(dType != NONE) { 
			sf::Sprite s(*this); // Wow - I can't seem to find a way to call sf::Sprite's draw function that isn't this overridden version, that causes a stack overflow
			window.draw(s, states);
		}
	}


	Animation* Drawable::getAnimation() { return anim; }

	void Drawable::setAnimation(const bzsf::Animation& a) {
		setTexture(a.getTexture());
		setTextureRect(a.getFrameRect());
		
		anim = const_cast<Animation*>(&a);
		animIndex = anim->getIndex();
		dType = ANIMATION;
	}


	void Drawable::setTexture(const sf::Texture& Tex) {	
		sf::Sprite::setTexture(Tex, true);
		
		anim = nullptr;
		dType = TEXTURE;
	}


	void Drawable::setTile(const bzsf::tsTile* tl) {
		setTexture(*tl->texture);
		setTextureRect(sf::IntRect(tl->xOffset, tl->yOffset, tl->width, tl->height));

		anim = nullptr;
		dType = TILE;
	}
}