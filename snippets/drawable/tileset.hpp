
namespace bzsf {

	class tsTile {
	public:
		int xOffset;
		int yOffset;
		int width;
		int height;

		sf::Texture * texture;
		
		tsTile(){}
		~tsTile(){}
	};

	std::vector<std::vector<tsTile>> newTileset(sf::Texture * texture, int hSize, int vSize) {
		std::vector<std::vector<tsTile>> tileset;
		tileset.resize(texture->getSize().x/hSize);
		for(unsigned int i=0; i<tileset.size(); i++) {
			tileset[i].resize(texture->getSize().y/vSize);
		}

		for(unsigned int i=0; i < texture->getSize().x/hSize; i++) {
			for(unsigned int u=0; u < texture->getSize().y/vSize; u++) {
				tileset[i][u].xOffset = i*hSize;
				tileset[i][u].yOffset = u*vSize;
				tileset[i][u].width	= hSize;
				tileset[i][u].height = vSize;
				tileset[i][u].texture = texture;
			}
		}
		return tileset;
	}

	typedef std::vector<std::vector<tsTile>> Tileset;

} //ENDOF NAMESPACE bzsf