#ifndef BZSF_STATE
#define BZSF_STATE

#include <SFML/Graphics.hpp>

namespace bzsf {

	template<typename ID, typename Context>
	class StateStack;

	template<typename ID, typename Context>
	class State : public sf::Drawable {
	public:
		typedef std::unique_ptr<State> Ptr;

	private:
		typename bzsf::StateStack<ID, Context>* stateStack;
		Context context;

	private:
		virtual void draw(sf::RenderTarget& window, sf::RenderStates states = sf::RenderStates::Default) const = 0;

	protected:
		void requestStackPush(ID stateID);
		void requestStackPop();
		void requestStackClear();

		Context getContext() const;

	public:
		State(StateStack<ID, Context>& stack, Context context);
		virtual ~State();

		virtual bool update(sf::Time dt) = 0;
		virtual bool handleEvent(const sf::Event& event) = 0;
	};


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

#endif
