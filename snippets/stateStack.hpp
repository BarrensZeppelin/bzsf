


namespace bzsf {

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
}

// Include implementation
#include <bzsf\snippets\stateStack.inl>