#include <SFML_Snips.hpp>

namespace bzsf {
	Drawable::Drawable() {}

	Drawable::Drawable(const bzsf::Animation& animation) {
		init();
		setAnimation(animation);
	}

	Drawable::Drawable(const sf::Texture& texture) {
		init();
		setTexture(texture);
	}

	Drawable::Drawable(tsTile* tile) {
		init();
		setTile(tile);
	}


	void Drawable::init() {
		texTile = nullptr;
		animIndex = 0;
		dType = NONE;
	}

	void Drawable::draw(sf::RenderTarget& window, sf::RenderStates states) const {
		states.transform *= getTransform();
		
		if(dType == ANIMATION) {
			anim->update();
			if(anim->getIndex() != animIndex) {
				animIndex = anim->getIndex();
				sprite.setTextureRect(anim->getFrameRect());
			}
		}

		if(dType != NONE) { window.draw(sprite, states); }
	}



	const tsTile *	Drawable::getTile()	const{return texTile;}
	Animation&		Drawable::getAnimation() {return *anim;}
	const sf::Texture&	Drawable::getTexture() {return *tex;}
	
	sf::FloatRect Drawable::getLocalBounds() const {
		return sprite.getLocalBounds();
	}

	sf::FloatRect Drawable::getGlobalBounds() const {
		return sprite.getGlobalBounds();
	}

	const sf::Color& Drawable::getColor() const {
		return sprite.getColor();
	}


	void Drawable::setColor(const sf::Color& color) {
		sprite.setColor(color);
	}


	void Drawable::setAnimation(const bzsf::Animation& a) {
		anim = const_cast<Animation*>(&a);
		sprite.setTexture(a.getTexture());
		sprite.setTextureRect(a.getFrameRect());

		dType = ANIMATION;
	}


	void Drawable::setTexture(const sf::Texture& Tex) {
		tex = &Tex;

		sprite.setTexture(*tex);
		
		dType = TEXTURE;
	}


	void Drawable::setTile(const bzsf::tsTile * tl) {
		texTile = const_cast<bzsf::tsTile*>(tl); // WOW - MUCH HACK
		
		sprite.setTexture(*tl->texture);
		sprite.setTextureRect(sf::IntRect(tl->xOffset, tl->yOffset, tl->width, tl->height));

		dType = TILE;
	}
}