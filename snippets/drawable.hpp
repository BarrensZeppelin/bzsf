#include <BZeps-SFML-Snippets\snippets\drawable\animation.hpp>
#include <BZeps-SFML-Snippets\snippets\drawable\tileset.hpp>



class drawable {
protected:
	enum drawType {texture, tile, animation, none};

	drawType dType;

	sf::Sprite entity;
	
	tsTile * texTile;
	sf::Animation * anim;
	bool customTile;

public:
	tsTile * GetTile()				{return texTile;}
	sf::Sprite& GetEntity()			{return entity;	}
	sf::Animation * GetAnimation()	{return anim;	}
	drawType GetDrawType()			{return dType;	}


	virtual void draw() {
		if(dType == animation) {
			if((unsigned int)anim->GetTimer()->getElapsedTime().asMilliseconds() > anim->GetSpeed() && anim->GetSpeed()!=0) {
				anim->GetTimer()->restart();
				anim->UpIndex();

				entity.setTextureRect(sf::IntRect(anim->GetWidth()*anim->GetIndex(), 0, anim->GetWidth(), anim->GetHeight()));
			}
		}

		if(dType!=none) {game::window->draw(entity);}
	}
	

	void SetAnimation(sf::Animation * a) {
		anim = a;
		entity.setTexture(*a->GetTexture());
		entity.setTextureRect(sf::IntRect(0, 0, a->GetWidth(), a->GetHeight()));

		dType = animation;
	}

	void SetCustomTexture(sf::Texture * tex) {
		float xPos = entity.getPosition().x;
		float yPos = entity.getPosition().y;
		
		entity.setTexture(*tex);

		anim = 0;

		if(!customTile) {
			texTile = new tsTile();
			customTile = 1;
		}
		texTile->height = tex->getSize().y;
		texTile->width = tex->getSize().x;
		texTile->xOffset = 0;
		texTile->yOffset = 0;

		texTile->eTexture = tex;

		entity.setPosition(xPos, yPos);

		dType = tile;
	}

	void SetTile(tsTile * tl) {
		float xPos = entity.getPosition().x;
		float yPos = entity.getPosition().y;
		
		entity.setTexture(*tl->eTexture);
		entity.setTextureRect(sf::IntRect(tl->xOffset, tl->yOffset, tl->width, tl->height));

		entity.setPosition(xPos, yPos);

		texTile = tl;

		dType = tile;
	}

	void NewCRegion(int width, int height) {
		if(!customTile) {
			int txOff = texTile->xOffset;
			int tyOff = texTile->yOffset;
			int tWidth = texTile->width;
			int tHeight = texTile->height;
			sf::Texture * tTex = texTile->eTexture;

			texTile = new tsTile();
			customTile = 1;

			texTile->xOffset = txOff;
			texTile->yOffset = tyOff;
			texTile->eTexture = tTex;
		}
		texTile->width = width;
		texTile->height = height;

		dType = tile;
	}


	drawable() {
		customTile = 0;
		texTile = 0;
		anim = 0;

		dType = texture;
	}

	virtual ~drawable() {
		if(customTile) {
			delete texTile;
		}

		texTile = 0;
	}
};


void sf::Animation::SetFrame(int index, drawable& entity, bool speedToZero = false) {
	if(index < numFrames) {
		frameIndex = index;
		
		entity.GetEntity().setTextureRect(sf::IntRect(frameWidth*frameIndex, 0, frameWidth, GetHeight()));
	} else { std::cerr << "Tried to assign invalid frame " << index << "/" << numFrames-1 << " to an animation." << std::endl; }
	
	if(speedToZero) {speed = 0;}
}