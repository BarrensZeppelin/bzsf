#include <BZeps-SFML-Snippets\snippets\drawable\animation.hpp>
#include <BZeps-SFML-Snippets\snippets\drawable\tileset.hpp>

namespace bzsf {

	class Drawable {
	protected:
		enum drawType {texture, tile, animation, none};

		drawType dType;

		sf::Sprite entity;
		
		bzsf::tsTile * texTile;
		bzsf::Animation anim;
		bool customTile;

	public:
		bzsf::tsTile * GetTile()		{return texTile;}
		sf::Sprite& GetEntity()			{return entity;	}
		bzsf::Animation& GetAnimation() {return anim;	}
		drawType GetDrawType()			{return dType;	}


		virtual void draw() {
			if(dType == animation) {
				if(anim.Update()) {
					entity.setTextureRect(sf::IntRect(anim.GetWidth()*anim.GetIndex(), 0, anim.GetWidth(), anim.GetHeight()));
				}
			}

			if(dType!=none) {game::window->draw(entity);}
		}
		

		void SetAnimation(bzsf::Animation& a) {
			anim = a;
			entity.setTexture(a.GetTexture());
			entity.setTextureRect(sf::IntRect(a.GetWidth()*a.GetIndex(), 0, a.GetWidth(), a.GetHeight()));

			dType = animation;
		}

		void SetTexture(sf::Texture * tex) {
			float xPos = entity.getPosition().x;
			float yPos = entity.getPosition().y;
			
			entity.setTexture(*tex, true);

			entity.setPosition(xPos, yPos);

			dType = texture;
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
			if(dType == tile) {
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
			} else {std::cerr << "Tried to assign new Collision Region to an entity without a tile." << std::endl;}
		}


		Drawable() : customTile(false), texTile(0) {

			dType = none;
		}

		explicit Drawable(bzsf::Animation& animation) : customTile(false), texTile(0) {
			SetAnimation(animation);
		}

		explicit Drawable(sf::Texture& texture) : customTile(false), texTile(0) {
			SetTexture(&texture);
		}

		explicit Drawable(tsTile * tile) : customTile(false), texTile(0) {
			SetTile(tile);
		}

		virtual ~Drawable() {
			if(customTile) {
				delete texTile;
			}

			texTile = 0;
		}
	};

} //ENDOF NAMESPACE bzsf

//void bzsf::Animation::SetFrame(int index, Drawable& entity, bool speedToZero = false) 

#include <BZeps-SFML-Snippets\snippets\drawable\particleSystem.hpp>