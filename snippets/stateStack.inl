

namespace bzsf {

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
			State<ID, Context>::Ptr ptr(new StateType(*this, context));
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