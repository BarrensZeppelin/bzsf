#include <BZeps-SFML-Snippets\snippets\drawable\animation.hpp>
#include <BZeps-SFML-Snippets\snippets\drawable\tileset.hpp>

namespace bzsf {

	class Drawable {
	protected:
		enum drawType {texture, tile, animation, none};

		drawType dType;

		sf::Sprite entity;
		
		bzsf::tsTile * texTile;
		bzsf::Animation * anim;
		sf::Texture tex;
		int animIndex;

	public:
		bzsf::tsTile * GetTile()		{return texTile;}
		sf::Sprite& GetEntity()			{return entity;	}
		bzsf::Animation *GetAnimation() {return anim;	}
		sf::Texture& GetTexture()		{return tex;}
		drawType GetDrawType()			{return dType;	}


		virtual void draw() {
			if(dType == animation) {
				anim->Update();
				if(anim->GetIndex() != animIndex) {
					animIndex = anim->GetIndex();
					entity.setTextureRect(sf::IntRect(anim->GetWidth()*anim->GetIndex(), 0, anim->GetWidth(), anim->GetHeight()));
				}
			}

			if(dType!=none) {game::window->draw(entity);}
		}
		

		void SetAnimation(bzsf::Animation& a) {
			anim = &a;
			entity.setTexture(a.GetTexture());
			entity.setTextureRect(sf::IntRect(a.GetWidth()*a.GetIndex(), 0, a.GetWidth(), a.GetHeight()));

			dType = animation;
		}

		void SetTexture(sf::Texture& Tex) {
			tex = Tex;
			
			float xPos = entity.getPosition().x;
			float yPos = entity.getPosition().y;

			entity.setTexture(tex);
			
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

		Drawable() : texTile(0), animIndex(0) {
			dType = none;
		}

		explicit Drawable(bzsf::Animation& animation) : texTile(0), animIndex(0) {
			SetAnimation(animation);
		}

		
		explicit Drawable(std::string filename) : texTile(0), tex(), animIndex(0) {
			tex.loadFromFile(filename);
			entity.setTexture(tex);
			dType = texture;
		}

		explicit Drawable(sf::Texture texture) : texTile(0), animIndex(0) {
			SetTexture(texture);
		}

		explicit Drawable(tsTile * tile) : texTile(0), animIndex(0) {
			SetTile(tile);
		}

		virtual ~Drawable() {
			texTile = 0;
		}
	};

} //ENDOF NAMESPACE bzsf 

#include <BZeps-SFML-Snippets\snippets\drawable\particleSystem.hpp>