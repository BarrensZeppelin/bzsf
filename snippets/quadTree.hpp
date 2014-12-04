

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
		QuadTree(sf::FloatRect bounds, sf::Uint16 level, sf::Uint16 maxlevel = 5, sf::Uint16 maxnodes = 4, Type type = PRECISE);
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
