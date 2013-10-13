
namespace bzsf {

	class tsTile {
	public:
		int xOffset;
		int yOffset;
		int width;
		int height;

		sf::Texture * texture;
		
		tsTile();
		~tsTile();
	};


	std::vector<std::vector<tsTile>> newTileset(sf::Texture * texture, int hSize, int vSize);

	typedef std::vector<std::vector<tsTile>> Tileset;

} //ENDOF NAMESPACE bzsf