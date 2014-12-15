

namespace bzsf {

	template<typename ID, typename Context>
	class StateStack;

	template<typename ID, typename Context>
	class State : public sf::Drawable {
	public:
		typedef std::unique_ptr<State> Ptr;

	private:
		typename StateStack<ID, Context>* stateStack;
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

}


// Include implementaion
#include <bzsf\snippets\state.inl>