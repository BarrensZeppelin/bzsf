namespace bzsf {
	struct tsTile {
	public:
		int xOffset = 0;
		int yOffset = 0;
		int width = 0;
		int height = 0;

		const sf::Texture* texture = nullptr;
	};
}