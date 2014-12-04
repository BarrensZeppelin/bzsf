

namespace bzsf {

	namespace {
		class PElement {
		private:
			sf::Text elementText;
			sf::Text avgText;

			std::string postfix;

			sf::Time overflow;
			sf::Time updateInterval;

			std::vector<float> values;
			float average;

			sf::Clock clock;

			void Update();

		public:
			PElement(sf::Font& font, 
				std::string elementText,
				std::string postfix, 
				sf::Time updateInterval, 
				sf::Uint32 textSize);

			void PushValue(float value);

			void SetFont(sf::Font& font);
			void SetColor(sf::Color color);

			void Draw(sf::RenderTarget& window, sf::Vector2f pos1, sf::Vector2f pos2, sf::RenderStates states = sf::RenderStates::Default);
		};
	}

	class PerformanceDisplay {
	private:
		std::map<std::string, PElement> elements;
		sf::Font* font;
		sf::Uint32 textSize;
		sf::Uint32 offset;
		sf::Color color;

		sf::Vector2f pos;

	public:
		PerformanceDisplay(sf::Font* Font = nullptr, 
			sf::Color c = sf::Color(),
			sf::Vector2f pos = sf::Vector2f(100 , 10),
			sf::Uint32 textSize = 12u, 
			sf::Uint32 offset = 2u);

		void RegisterElement(std::string ID, 
			std::string elementText, 
			sf::Time updateInterval = sf::seconds(0.1f), 
			std::string postfix = "");
		void PushValue(std::string ID, float value);


		void SetFont(sf::Font& font);
		void SetColor(sf::Color c);


		void Draw(sf::RenderTarget& window, sf::RenderStates states = sf::RenderStates::Default);
	};

}