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


	Animation&		Drawable::getAnimation() { return *anim; }
	const sf::Texture&	Drawable::getTexture() const { return *sprite.getTexture(); }
	sf::IntRect Drawable::getTextureRect() const { return sprite.getTextureRect(); }
	
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
		animIndex = anim->getIndex();

		sprite.setTexture(a.getTexture());
		sprite.setTextureRect(a.getFrameRect());

		dType = ANIMATION;
	}


	void Drawable::setTexture(const sf::Texture& Tex) {
		anim = nullptr;
		sprite.setTexture(Tex);
		
		dType = TEXTURE;
	}


	void Drawable::setTile(const bzsf::tsTile* tl) {
		anim = nullptr;

		sprite.setTexture(*tl->texture);
		sprite.setTextureRect(sf::IntRect(tl->xOffset, tl->yOffset, tl->width, tl->height));

		dType = TILE;
	}
}