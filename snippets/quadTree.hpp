

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
		std::vector<std::pair<ObjectT*, sf::FloatRect>> objects;
		std::array<QuadTree*, 4> nodes;

	protected:
		inline bool isSplit();

		virtual void split();

		inline bool intersects(const sf::FloatRect& rect);

	public:
		/**
			Constructs a new QuadTree.

			@param bounds The QuadTree's bounds
			@param level Used internally, pass 0 when constructing a new QuadTree
			@param maxlevel The maximum amount of times the QuadTree will split. (Preferably use a value that makes {bounds.size() / maxlevel > average object size})
			@param maxobjects Amount of objects before the QuadTree splits
			@param type FAST makes the QuadTree a lot faster than PRECISE, but less precise.. If you're having perfomance issues, but collision checking isn't expensive, try using FAST.
		*/
		QuadTree(sf::FloatRect bounds, sf::Uint16 level, sf::Uint16 maxlevel, sf::Uint16 maxobjects, Type type = PRECISE);
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
		std::set<ObjectT*> retrieve(const sf::FloatRect& rect);
	};

}


#include "quadTree.inl"
