#include <BZeps-SFML-Snippets\snippets\drawable\animation.hpp>
#include <BZeps-SFML-Snippets\snippets\drawable\tileset.hpp>

namespace bzsf {

	class Drawable {
	protected:
		enum drawType {texture, tile, animation, none};

		drawType dType;

		sf::Sprite entity;
		
		bzsf::tsTile* texTile;
		bzsf::Animation* anim;
		sf::Texture tex;
		int animIndex;

	public:
		const tsTile * GetTile() const;
		sf::Sprite& GetEntity();
		Animation *GetAnimation();
		sf::Texture& GetTexture();
		drawType GetDrawType();


		virtual void Draw(sf::RenderTarget& window, sf::RenderStates states = sf::RenderStates::Default);
		

		void SetAnimation(Animation* a);

		void SetTexture(sf::Texture& Tex);

		void SetTile(const tsTile * tl);

		void Init();

		Drawable();

		explicit Drawable(Animation* animation);
		
		explicit Drawable(std::string filename);

		explicit Drawable(sf::Texture& texture);

		explicit Drawable(tsTile * tile);

		virtual ~Drawable();
	};

} //ENDOF NAMESPACE bzsf 

#include <BZeps-SFML-Snippets\snippets\drawable\particleSystem.hpp>