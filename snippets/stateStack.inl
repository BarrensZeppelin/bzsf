

namespace bzsf {

	template<typename ID, typename Context>
	StateStack<ID, Context>::PendingChange::PendingChange(Action action, ID stateID) : action(action), stateID(stateID) {}

	template<typename ID, typename Context>
	StateStack<ID, Context>::PendingChange::PendingChange(Action action) : action(action) {}


	template<typename ID, typename Context>
	StateStack<ID, Context>::StateStack(Context context) : stack(), pendingChanges(), context(context), factory() {}

	template<typename ID, typename Context>
	void StateStack<ID, Context>::Update(sf::Time& dt) {
		// Iterate from top to bottom
		for(auto itr = stack.rbegin(); itr != stack.rend(); ++itr) {
			if(!(*itr)->Update(dt))
				break;
		}

		ApplyPendingChanges();
	}

	template<typename ID, typename Context>
	void StateStack<ID, Context>::Draw(sf::RenderTarget& window, sf::RenderStates states) {
		for(auto itr = stack.begin(); itr != stack.end(); ++itr) {
			(*itr)->Draw(window, states);
		}
	}

	template<typename ID, typename Context>
	void StateStack<ID, Context>::HandleEvent(const sf::Event& event) {
		for(auto itr = stack.rbegin(); itr != stack.rend(); ++itr) {
			if(!(*itr)->HandleEvent(event))
				break;
		}

		ApplyPendingChanges();
	}


	template<typename ID, typename Context>
	void StateStack<ID, Context>::PushState(ID stateID) {
		pendingChanges.push_back(PendingChange(Push, stateID));
	}

	template<typename ID, typename Context>
	void StateStack<ID, Context>::PopState() {
		pendingChanges.push_back(PendingChange(Pop));
	}

	template<typename ID, typename Context>
	void StateStack<ID, Context>::ClearStates() {
		pendingChanges.push_back(PendingChange(Clear));
	}


	template<typename ID, typename Context>
	bool StateStack<ID, Context>::IsEmpty() {
		return stack.empty();
	}

	template<typename ID, typename Context>
	typename State<ID, Context>::Ptr StateStack<ID, Context>::CreateState(ID stateID) {
		auto found = factory.find(stateID);
		assert(found != factory.end());

		return found->second();
	}


	
	template<typename ID, typename Context>
	void StateStack<ID, Context>::ApplyPendingChanges() {
		for(PendingChange change : pendingChanges) {
			switch(change.action) {
				case Push:
					stack.push_back(CreateState(change.stateID));
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
	void StateStack<ID, Context>::RegisterState(ID stateID) {
		factory[stateID] = [this] () {
			return typename State<ID, Context>::Ptr(new StateType(*this, context));
		};
	}


}