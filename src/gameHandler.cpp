#include <SFML_Snips.hpp>

namespace bzsf {
	
	// game ///
	sf::Uint16 game::currentState = 0;
	bool game::run = true;
	std::map<sf::Uint16, void (*)()> game::gameFunctions = std::map<sf::Uint16, void (*)()>();
	
	sf::RenderWindow * game::window = nullptr;

	void game::addFunc(sf::Uint16 pos, void (*func)()) {
		gameFunctions.insert(std::pair<sf::Uint16, void (*)()>(pos, func));
	}

	int game::runGame() {
		assert(window != nullptr);

		window->setMouseCursorVisible(true);
		window->setVerticalSyncEnabled(false);
		window->setKeyRepeatEnabled(false);
		while(run && window->isOpen()) {
			if(gameFunctions.find(currentState) != gameFunctions.end()) {
				gameFunctions[currentState]();
			} else {
				std::cerr << "Fatal error: Function with key: " << currentState << " was not found." << std::endl << "Exiting..." << std::endl;
				return 1;
			}
		}

		return 0;
	}
	////////


	void game_die() {
		game::run = false;
	}
}