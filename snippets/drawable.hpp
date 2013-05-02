#include <BZeps-SFML-Snippets\snippets\drawable\animation.hpp>
#include <BZeps-SFML-Snippets\snippets\drawable\tileset.hpp>
#include <BZeps-SFML-Snippets\snippets\drawable\particleSystem.hpp>

namespace bzsf {

	class Drawable {
	protected:
		enum drawType {texture, tile, animation, none};

		drawType dType;

		sf::Sprite entity;
		
		bzsf::tsTile * texTile;
		bzsf::Animation * anim;
		bool customTile;

	public:
		bzsf::tsTile * GetTile()		{return texTile;}
		sf::Sprite& GetEntity()			{return entity;	}
		bzsf::Animation * GetAnimation(){return anim;	}
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
		

		void SetAnimation(bzsf::Animation * a) {
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
				texTile = new bzsf::tsTile();
				customTile = 1;
			}
			texTile->height = tex->getSize().y;
			texTile->width = tex->getSize().x;
			texTile->xOffset = 0;
			texTile->yOffset = 0;

			texTile->texture = tex;

			entity.setPosition(xPos, yPos);

			dType = tile;
		}

		void SetTile(bzsf::tsTile * tl) {
			float xPos = entity.getPosition().x;
			float yPos = entity.getPosition().y;
			
			entity.setTexture(*tl->texture);
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
				sf::Texture * tTex = texTile->texture;

				texTile = new bzsf::tsTile();
				customTile = 1;

				texTile->xOffset = txOff;
				texTile->yOffset = tyOff;
				texTile->texture = tTex;
			}
			texTile->width = width;
			texTile->height = height;

			dType = tile;
		}


		Drawable() {
			customTile = 0;
			texTile = 0;
			anim = 0;

			dType = texture;
		}

		virtual ~Drawable() {
			if(customTile) {
				delete texTile;
			}

			texTile = 0;
		}
	};

} //ENDOF NAMESPACE BZSF

void bzsf::Animation::SetFrame(int index, Drawable& entity, bool speedToZero = false) {
	if(index < numFrames) {
		frameIndex = index;
		
		entity.GetEntity().setTextureRect(sf::IntRect(frameWidth*frameIndex, 0, frameWidth, GetHeight()));
	} else { std::cerr << "Tried to assign invalid frame " << index << "/" << numFrames-1 << " to an animation." << std::endl; }
	
	if(speedToZero) {speed = 0;}
}