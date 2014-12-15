

namespace bzsf {

	template<typename ID, typename Context>
	State<ID, Context>::State(StateStack<ID, Context>& stack, Context context) : stateStack(&stack), context(context) {}

	template<typename ID, typename Context>
	State<ID, Context>::~State() {}

	template<typename ID, typename Context>
	void State<ID, Context>::requestStackPush(ID stateID) {
		stateStack->pushState(stateID);
	}

	template<typename ID, typename Context>
	void State<ID, Context>::requestStackPop() {
		stateStack->popState();
	}

	template<typename ID, typename Context>
	void State<ID, Context>::requestStackClear() {
		stateStack->clearStates();
	}


	template<typename ID, typename Context>
	Context State<ID, Context>::getContext() const {
		return context;
	}
}