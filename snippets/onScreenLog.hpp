
namespace bzsf {

	class OnScreenLog {
		typedef std::deque<std::pair<std::string, sf::Clock>> Log;
		typedef sf::Vector2<sf::Time> Vector2t;

		std::vector<sf::Text> entities;
		Log log;

		sf::Vector2f position;
		sf::Uint32 maxSize;
		sf::Uint32 fSize;
		sf::Font* logFont;
		sf::Uint32 rowOffset;
		sf::Color logColor;
		Vector2t fadeTime;

		void UpdateEntities();
		void FitLog();

	public:
		void SetPosition(sf::Vector2f pos);
		void SetSize(sf::Uint32 size);
		void SetFont(sf::Font& font);
		void SetFadeTime(sf::Time fadeDelay, sf::Time fadeDuration);

		void Append(const std::string& str);
		void Clear();

		void Draw();

		OnScreenLog();
		OnScreenLog(sf::Font& font,
					sf::Uint32 fontSize = 12,
					sf::Uint32 size = 5,
					sf::Uint32 offset = 2,
					sf::Color color = sf::Color(255, 255, 255),
					sf::Vector2f pos = sf::Vector2f(10, 10),
					sf::Time fadeDelay = sf::seconds(5),
					sf::Time fadeDuration = sf::seconds(0.5));
	};

}