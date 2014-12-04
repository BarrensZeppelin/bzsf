


namespace bzsf {

	template<typename ID, typename Context>
	class StateStack : private sf::NonCopyable {
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


		typename State<ID, Context>::Ptr CreateState(ID stateID);
		void ApplyPendingChanges();

	public:
		explicit StateStack(Context context);

		template<typename StateType>
		void RegisterState(ID stateID);

		void Draw(sf::RenderTarget& window, sf::RenderStates states = sf::RenderStates::Default);
		void Update(sf::Time& dt);
		void HandleEvent(const sf::Event& event);

		void PushState(ID stateID);
		void PopState();
		void ClearStates();

		bool IsEmpty();
	};


}

// Include implementation
#include <BZeps-SFML-Snippets\snippets\stateStack.inl>