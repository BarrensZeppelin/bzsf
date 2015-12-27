

namespace bzsf {
	
	template<typename ObjectT>
	class QuadTree {
	public:
		enum Type {
			PRECISE, // Minimize collision pairs
			FAST // Maximize QuadTree speed
		};

	protected:
		const sf::Uint16 MAXLEVEL;
		const sf::Uint16 MAXNODES;

		const Type type;

		sf::Uint16 level;
		sf::FloatRect bounds;
		std::unordered_map<ObjectT*, const sf::FloatRect> rects;
		std::vector<ObjectT*> objects;
		std::array<QuadTree*, 4> nodes;

	protected:
		inline bool isSplit();
		inline bool intersects(const sf::FloatRect& rect);

		virtual void split();

		void retrieveAllHelper(std::set<std::vector<ObjectT*>>& set);

	public:
		/**
			Constructs a new QuadTree.

			@param bounds The QuadTree's bounds
			@param type FAST makes the QuadTree a lot faster than PRECISE, but less precise.. If you're having perfomance issues, but collision checking isn't expensive, try using FAST.
			@param maxlevel The maximum amount of times the QuadTree will split. (Preferably use a value that makes {bounds.size() / maxlevel > average object size})
			@param maxobjects Amount of objects before the QuadTree splits
			@param level Used internally, pass 0 when constructing a new QuadTree
		*/
		QuadTree(sf::FloatRect bounds, Type type = Type::PRECISE, sf::Uint16 maxlevel = 6, sf::Uint16 maxobjects = 4, sf::Uint16 level = 0);
		virtual ~QuadTree();

		void clear();

		/**
			Adds the object of given type ObjectT to the QuadTree.
			Since the QuadTree has no way of determining how to get
			boundary data from the object, you have to supply the 
			object's bounding rectangle.

			@param obj Pointer to the object to insert
			@param rect Bounding rectangle of the object
		*/
		void addObject(ObjectT* obj, const sf::FloatRect& rect);
		std::unordered_set<ObjectT*> retrieve(const sf::FloatRect& rect);

		std::set<std::vector<ObjectT*>> retrieveAll();
	};

}

#include "quadTree.inl"
