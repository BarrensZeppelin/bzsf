#ifndef BZSF_TILESET_H
#define BZSF_TILESET_H

namespace bzsf {

	class tsTile {
	public:
		int xOffset;
		int yOffset;
		int width;
		int height;

		const sf::Texture* texture;
		
		tsTile();
	};


	typedef std::vector<std::vector<tsTile>> Tileset;
	typedef std::unique_ptr<Tileset> TilesetPtr;


	TilesetPtr NewTileset(const sf::Texture& texture, int hSize, int vSize);


} //ENDOF NAMESPACE bzsf

#endif