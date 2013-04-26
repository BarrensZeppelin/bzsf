using namespace std;

class game {
public:
	static map<unsigned int, void (*)()> gameFunctions;
	static unsigned int currentState;
	static bool run;

	static sf::RenderWindow * window; // Remember to assign window
	
	static void addFunc(unsigned int pos, void (*func)()) {
		gameFunctions.insert(pair<unsigned int, void (*)()>(pos, func));
	}

	static int runGame() {
		window->setMouseCursorVisible(0);
		window->setVerticalSyncEnabled(0);
		while(run && window->isOpen()) {
			if(gameFunctions.find(currentState) != gameFunctions.end()) {
				gameFunctions[currentState]();
			} else {
				cerr << "Fatal error: Function with key: " << currentState << " was not found." << endl << "Exiting..." << endl;
				return 1;
			}
		}

		return 0;
	}
};

unsigned int game::currentState = 0;
bool game::run = true;
map<unsigned int, void (*)()> game::gameFunctions = map<unsigned int, void (*)()>();