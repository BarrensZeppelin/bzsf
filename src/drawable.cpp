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


	Animation* Drawable::getAnimation() { return anim; }

	void Drawable::setAnimation(bzsf::Animation& a) {
		setTexture(a.getTexture());
		setTextureRect(a.getFrameRect());
		
		anim = &a;
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


	
	void Drawable::update(sf::Time dt) {
		if(dType == ANIMATION) {
			anim->update();
			if(anim->getIndex() != animIndex) {
				animIndex = anim->getIndex();
				const_cast<Drawable*>(this)->setTextureRect(anim->getFrameRect());
			}
		}
	}
}