namespace bzsf {

	class game {
	public:
		static std::map<sf::Uint16, void (*)()> gameFunctions;
		static sf::Uint16 currentState;
		static bool run;

		static sf::RenderWindow * window; // Remember to assign window
		
		static void addFunc(sf::Uint16 pos, void (*func)());

		static int runGame();
	};

	
	void game_die();

} /// ENDOF NAMESPACE bzsf