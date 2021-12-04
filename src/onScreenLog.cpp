#include <SFML_Snips.hpp>

namespace bzsf {
	void OnScreenLog::updateEntities() {
		entities.resize(maxSize);

		for(sf::Uint32 i = 0; i < entities.size(); ++i) {
			if(logFont != nullptr) entities[i].setFont(*logFont);
			entities[i].setCharacterSize(fSize);
			entities[i].setFillColor(logColor);

			entities[i].setPosition(position + sf::Vector2f(0, i * static_cast<float>(fSize + rowOffset)));
		}
	}

	void OnScreenLog::fitLog() const {
		while(log.size() > maxSize) {
			log.pop_back();
		}
	}



	void OnScreenLog::setPosition(sf::Vector2f pos) {
		if(pos != position) {
			position = pos;
			updateEntities();
		}
	}

	void OnScreenLog::setSize(sf::Uint32 size) {
		if(size != maxSize) {
			maxSize = size;
			updateEntities(); // Init new text entities
		}
	}

	void OnScreenLog::setFont(sf::Font& font) {
		if(&font != logFont) {
			logFont = &font;
			updateEntities();
		}
	}

	void OnScreenLog::setFadeTime(sf::Time fadeDelay, sf::Time fadeDuration) {
		if(fadeDelay != fadeTime.x || fadeDuration != fadeTime.y) {
			fadeTime = Vector2t(fadeDelay, fadeDuration);
		}
	}



	void OnScreenLog::append(const std::string& str) {
		log.push_front(std::make_pair(str, sf::Clock()));
	}

	void OnScreenLog::clear() {
		log.clear();
	}



	OnScreenLog::OnScreenLog() : position(0, 0),
		maxSize(5),
		fSize(8),
		logFont(nullptr),
		rowOffset(2),
		logColor(255, 255, 255),
		fadeTime(sf::seconds(5), sf::seconds(0.5)) {}


	OnScreenLog::OnScreenLog(sf::Font& font, sf::Uint32 fontSize, sf::Uint32 size, sf::Uint32 offset, sf::Color color, sf::Vector2f pos, sf::Time fadeDelay, sf::Time fadeDuration) : position(pos),
		maxSize(size),
		fSize(fontSize),
		logFont(&font),
		rowOffset(offset),
		logColor(color),
		fadeTime(fadeDelay, fadeDuration) {

		updateEntities();

	}

	void OnScreenLog::draw(sf::RenderTarget& window, sf::RenderStates states) const {
		if(logFont != nullptr) {

			fitLog();

			for(sf::Uint32 i = 0; i < log.size(); ++i) {
				sf::Uint32 u = maxSize - 1 - i;
				entities[u].setString(log[i].first);

				if(log[i].second.getElapsedTime() > fadeTime.x && fadeTime.x != sf::Time::Zero) {
					float elapsed = (fadeTime.y != sf::Time::Zero ? (log[i].second.getElapsedTime().asSeconds() - fadeTime.x.asSeconds()) / fadeTime.y.asSeconds() : 1.f);
					if(elapsed > 1.f) elapsed = 1.f;

					sf::Color c = logColor; c.a = static_cast<sf::Uint8>(logColor.a - logColor.a * elapsed);
					entities[u].setFillColor(c);
				} else entities[u].setFillColor(logColor);
			}

			for(sf::Text& t : entities) {
				window.draw(t, states);
			}
		}
	}
}
