
namespace bzsf {

	class OnScreenLog : public sf::Drawable {
		typedef std::deque<std::pair<std::string, sf::Clock>> Log;
		typedef sf::Vector2<sf::Time> Vector2t;

		mutable std::vector<sf::Text> entities;
		mutable Log log;

		sf::Vector2f position;
		sf::Uint32 maxSize;
		sf::Uint32 fSize;
		sf::Font* logFont;
		sf::Uint32 rowOffset;
		sf::Color logColor;
		Vector2t fadeTime;

		void updateEntities();
		void fitLog() const;

		void draw(sf::RenderTarget& target, sf::RenderStates = sf::RenderStates::Default) const;

	public:
		void setPosition(sf::Vector2f pos);
		void setSize(sf::Uint32 size);
		void setFont(sf::Font& font);

		////////////////////////////////
		/// A fade delay of 0 will make the log stay forever
		/// A fade duration of 0 will make log entries pop instantly after the delay
		////////////////////////////////
		void setFadeTime(sf::Time fadeDelay, sf::Time fadeDuration);

		void append(const std::string& str);
		void clear();


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