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
		tsTile * GetTile();
		sf::Sprite& GetEntity();
		Animation *GetAnimation();
		sf::Texture& GetTexture();
		drawType GetDrawType();


		virtual void draw();
		

		void SetAnimation(bzsf::Animation* a);

		void SetTexture(sf::Texture& Tex);

		void SetTile(bzsf::tsTile * tl);

		void Init();

		Drawable();

		explicit Drawable(bzsf::Animation* animation);
		
		explicit Drawable(std::string filename);

		explicit Drawable(sf::Texture& texture);

		explicit Drawable(tsTile * tile);

		virtual ~Drawable();
	};

} //ENDOF NAMESPACE bzsf 

#include <BZeps-SFML-Snippets\snippets\drawable\particleSystem.hpp>