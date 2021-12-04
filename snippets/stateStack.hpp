#ifndef BZSF_STATESTACK
#define BZSF_STATESTACK

#include <SFML/Graphics.hpp>

namespace bzsf {
	template<typename ID, typename Context>
	class State;

	template<typename ID, typename Context>
	class StateStack : private sf::NonCopyable, public sf::Drawable {
	public:
		enum Action {
			Push,
			Pop,
			Clear
		};

	private:
		struct PendingChange {
			explicit PendingChange(Action action, ID stateID);
			explicit PendingChange(Action action);

			Action action;
			ID stateID;
		};

		std::vector<typename State<ID, Context>::Ptr>						stack;
		std::vector<PendingChange>											pendingChanges;

		Context																context;
		std::map<ID, std::function<typename State<ID, Context>::Ptr()>>		factory;

	private:
		void draw(sf::RenderTarget& window, sf::RenderStates states = sf::RenderStates::Default) const;

		typename State<ID, Context>::Ptr createState(ID stateID);
		void applyPendingChanges();

	public:
		explicit StateStack(Context context);

		template<typename StateType>
		void registerState(ID stateID);

		
		void update(sf::Time dt);
		void handleEvent(const sf::Event& event);

		void pushState(ID stateID);
		void popState();
		void clearStates();

		bool empty();
	};

	template<typename ID, typename Context>
	StateStack<ID, Context>::PendingChange::PendingChange(Action action, ID stateID) : action(action), stateID(stateID) {}

	template<typename ID, typename Context>
	StateStack<ID, Context>::PendingChange::PendingChange(Action action) : action(action) {}


	template<typename ID, typename Context>
	StateStack<ID, Context>::StateStack(Context context) : stack(), pendingChanges(), context(context), factory() {}


	template<typename ID, typename Context>
	void StateStack<ID, Context>::draw(sf::RenderTarget& window, sf::RenderStates states) const {
		for(auto itr = stack.begin(); itr != stack.end(); ++itr)
			window.draw(**itr, states);
	}


	template<typename ID, typename Context>
	typename State<ID, Context>::Ptr StateStack<ID, Context>::createState(ID stateID) {
		auto found = factory.find(stateID);
		assert(found != factory.end());

		return found->second();
	}

	template<typename ID, typename Context>
	void StateStack<ID, Context>::applyPendingChanges() {
		for(PendingChange change : pendingChanges) {
			switch(change.action) {
			case Push:
				stack.push_back(createState(change.stateID));
				break;

			case Pop:
				stack.pop_back();
				break;

			case Clear:
				stack.clear();
				break;
			}
		}

		pendingChanges.clear();
	}



	template<typename ID, typename Context>
	template<typename StateType>
	void StateStack<ID, Context>::registerState(ID stateID) {
		factory[stateID] = [this]() -> typename State<ID, Context>::Ptr {
			typename State<ID, Context>::Ptr ptr(new StateType(*this, context));
			return std::move(ptr);
		};
	}


	template<typename ID, typename Context>
	void StateStack<ID, Context>::update(sf::Time dt) {
		// Iterate from top to bottom
		for(auto itr = stack.rbegin(); itr != stack.rend(); ++itr) {
			if(!(*itr)->update(dt))
				break;
		}

		applyPendingChanges();
	}

	template<typename ID, typename Context>
	void StateStack<ID, Context>::handleEvent(const sf::Event& event) {
		for(auto itr = stack.rbegin(); itr != stack.rend(); ++itr) {
			if(!(*itr)->handleEvent(event))
				break;
		}

		applyPendingChanges();
	}


	template<typename ID, typename Context>
	void StateStack<ID, Context>::pushState(ID stateID) {
		pendingChanges.emplace_back(Push, stateID);
	}

	template<typename ID, typename Context>
	void StateStack<ID, Context>::popState() {
		pendingChanges.emplace_back(Pop);
	}

	template<typename ID, typename Context>
	void StateStack<ID, Context>::clearStates() {
		pendingChanges.emplace_back(Clear);
	}


	template<typename ID, typename Context>
	bool StateStack<ID, Context>::empty() {
		return stack.empty();
	}
}

#endif
