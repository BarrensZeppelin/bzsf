#include <SFML_Snips.hpp>

namespace bzsf {
	
	tsTile *		Drawable::GetTile()		{return texTile;}
	sf::Sprite&		Drawable::GetEntity()	{return entity;}
	Animation *		Drawable::GetAnimation(){return anim;}
	sf::Texture&	Drawable::GetTexture()	{return tex;}
	Drawable::drawType	Drawable::GetDrawType() {return dType;}

	void Drawable::draw() {
		if(dType == animation) {
			anim->Update();
			if(anim->GetIndex() != animIndex) {
				animIndex = anim->GetIndex();
				entity.setTextureRect(sf::IntRect(anim->GetWidth()*anim->GetIndex(), 0, anim->GetWidth(), anim->GetHeight()));
			}
		}

		if(dType!=none) {game::window->draw(entity);}
	}


	void Drawable::SetAnimation(bzsf::Animation& a) {
		anim = &a;
		entity.setTexture(a.GetTexture());
		entity.setTextureRect(sf::IntRect(a.GetWidth()*a.GetIndex(), 0, a.GetWidth(), a.GetHeight()));

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


	void Drawable::SetTile(bzsf::tsTile * tl) {
		float xPos = entity.getPosition().x;
		float yPos = entity.getPosition().y;
		
		entity.setTexture(*tl->texture);
		entity.setTextureRect(sf::IntRect(tl->xOffset, tl->yOffset, tl->width, tl->height));

		entity.setPosition(xPos, yPos);

		texTile = tl;

		dType = tile;
	}

	
	void Drawable::Init() {
		texTile = 0;
		animIndex = 0;
		dType = none;
		entity = sf::Sprite();
		tex = sf::Texture();
		anim = 0;
	}


	Drawable::Drawable() {
		Init();
	}

	Drawable::Drawable(bzsf::Animation& animation) {
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