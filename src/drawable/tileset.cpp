#include <SFML_Snips.hpp>

namespace bzsf {
	
	tsTile::tsTile() : xOffset(0), yOffset(0), width(0), height(0), texture(0) {}

	TilesetPtr NewTileset(const sf::Texture& texture, int hSize, int vSize) {
		TilesetPtr tilesetptr = TilesetPtr(new Tileset(texture.getSize().x / hSize));
		Tileset& tileset = *tilesetptr.get();
		for(sf::Uint32 i = 0; i < tileset.size(); i++) {
			tileset[i].resize(texture.getSize().y / vSize);
		}

		for(sf::Uint32 i = 0; i < texture.getSize().x / hSize; i++) {
			for(sf::Uint32 u = 0; u < texture.getSize().y / vSize; u++) {
				tileset[i][u].xOffset = i*hSize;
				tileset[i][u].yOffset = u*vSize;
				tileset[i][u].width	= hSize;
				tileset[i][u].height = vSize;
				tileset[i][u].texture = &texture;
			}
		}

		return tilesetptr;
	}


}