

namespace bzsf {

	template<typename ID, typename Context>
	State<ID, Context>::State(StateStack<ID, Context>& stack, Context _context) : stateStack(&stack), context(_context) {}

	template<typename ID, typename Context>
	State<ID, Context>::~State() {}

	template<typename ID, typename Context>
	void State<ID, Context>::RequestStackPush(ID stateID) {
		stateStack->PushState(stateID);
	}

	template<typename ID, typename Context>
	void State<ID, Context>::RequestStackPop() {
		stateStack->PopState();
	}

	template<typename ID, typename Context>
	void State<ID, Context>::RequestStateClear() {
		stateStack->ClearStates();
	}


	template<typename ID, typename Context>
	Context State<ID, Context>::GetContext() {
		return context;
	}




	template<typename ID, typename Context>
	void State<ID, Context>::Draw(sf::RenderTarget& window, sf::RenderStates states) {}

	template<typename ID, typename Context>
	bool State<ID, Context>::Update(sf::Time& dt) { return true; }

	template<typename ID, typename Context>
	bool State<ID, Context>::HandleEvent(const sf::Event& event) { return true; }
}