#include <SFML_Snips.hpp>

namespace bzsf {
	
	const tsTile *	Drawable::GetTile()	const{return texTile;}
	sf::Sprite&		Drawable::GetEntity()	{return entity;}
	Animation *		Drawable::GetAnimation(){return anim;}
	sf::Texture&	Drawable::GetTexture()	{return tex;}
	Drawable::drawType	Drawable::GetDrawType() {return dType;}

	void Drawable::Draw(sf::RenderTarget& window, sf::RenderStates states) {
		if(dType == animation) {
			anim->Update();
			if(anim->GetIndex() != animIndex) {
				animIndex = anim->GetIndex();
				entity.setTextureRect(anim->GetFrameRect());
			}
		}

		if(dType != none) { window.draw(entity, states); }
	}


	void Drawable::SetAnimation(bzsf::Animation* a) {
		anim = a;
		entity.setTexture(a->GetTexture());
		entity.setTextureRect(a->GetFrameRect());

		dType = animation;
	}


	void Drawable::SetTexture(sf::Texture& Tex) {
		tex = Tex;
		
		float xPos = entity.getPosition().x;
		float yPos = entity.getPosition().y;

		entity.setTexture(tex);
		
		entity.setPosition(xPos, yPos);
		
		dType = texture;
	}


	void Drawable::SetTile(const bzsf::tsTile * tl) {
		float xPos = entity.getPosition().x;
		float yPos = entity.getPosition().y;
		
		entity.setTexture(*tl->texture);
		entity.setTextureRect(sf::IntRect(tl->xOffset, tl->yOffset, tl->width, tl->height));

		entity.setPosition(xPos, yPos);

		texTile = const_cast<bzsf::tsTile*>(tl);

		dType = tile;
	}

	
	void Drawable::Init() {
		texTile = nullptr;
		animIndex = 0;
		dType = none;
		entity = sf::Sprite();
		tex = sf::Texture();
		anim = nullptr;
	}


	Drawable::Drawable() {
		Init();
	}

	Drawable::Drawable(bzsf::Animation* animation) {
		Init();
		SetAnimation(animation);
	}

	Drawable::Drawable(std::string filename) {
		Init();
		tex.loadFromFile(filename);
		entity.setTexture(tex);
		dType = texture;
	}

	Drawable::Drawable(sf::Texture& texture) {
		Init();
		SetTexture(texture);
	}

	Drawable::Drawable(tsTile * tile) {
		Init();
		SetTile(tile);
	}

	Drawable::~Drawable() {}
}