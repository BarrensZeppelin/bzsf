
namespace bzsf {

	template<typename ObjectT>
	bool QuadTree<ObjectT>::isSplit() {
		return nodes[0] != nullptr;
	}


	template<typename ObjectT>
	void QuadTree<ObjectT>::split() {
		sf::Vector2f halfSize = sf::Vector2f(bounds.width / 2.f, bounds.height / 2.f);
		
		/*
			2 | 1
			-----
			3 | 4
		*/
		nodes[0] = new QuadTree<ObjectT>(sf::FloatRect(sf::Vector2f(bounds.left + halfSize.x, bounds.top), halfSize), level + 1, MAXLEVEL, MAXNODES, type);
		nodes[1] = new QuadTree<ObjectT>(sf::FloatRect(sf::Vector2f(bounds.left, bounds.top), halfSize), level + 1, MAXLEVEL, MAXNODES, type);
		nodes[2] = new QuadTree<ObjectT>(sf::FloatRect(sf::Vector2f(bounds.left, bounds.top + halfSize.y), halfSize), level + 1, MAXLEVEL, MAXNODES, type);
		nodes[3] = new QuadTree<ObjectT>(sf::FloatRect(sf::Vector2f(bounds.left + halfSize.x, bounds.top + halfSize.y), halfSize), level + 1, MAXLEVEL, MAXNODES, type);
	
		if(type == PRECISE) { // Divide current objects into subnodes
			for(auto o : objects)
				for(QuadTree* q : nodes)
					q->addObject(o.first, o.second);

			objects.clear();
		} // else don't care and proceed to add next objects to subnodes -> creates less accurate collisions, but
		  // gives more performance when splitting
	}


	template<typename ObjectT>
	bool QuadTree<ObjectT>::intersects(const sf::FloatRect& rect) {
		return bounds.intersects(rect);
	}



	template<typename ObjectT>
	QuadTree<ObjectT>::QuadTree(sf::FloatRect bounds, sf::Uint16 level, sf::Uint16 maxlevel, sf::Uint16 maxobjects, Type type) :
	bounds(bounds)
	, objects()
	, nodes()
	, level(level)
	, MAXLEVEL(maxlevel)
	, MAXNODES(maxobjects)
	, type(type) {
		for(QuadTree* q : nodes)
			q = nullptr;
	}

	template<typename ObjectT>
	QuadTree<ObjectT>::~QuadTree() {
		clear();
	}

	template<typename ObjectT>
	void QuadTree<ObjectT>::clear() {
		if(isSplit()) {
			for(QuadTree* q : nodes)
				delete q;
		}

		nodes = std::array<QuadTree<ObjectT>*, 4>(); // Reinit array to fix nullptr bug
		objects.clear();
	}


	template<typename ObjectT>	
	void QuadTree<ObjectT>::addObject(ObjectT* obj, const sf::FloatRect& rect) {
		if(intersects(rect)) {
			if(level == MAXLEVEL || ((!isSplit()) && objects.size() < MAXNODES))
				objects.push_back(std::pair<ObjectT*, sf::FloatRect>(obj, rect));
			else { // Direct object into subnodes
				if(!isSplit())
					split();

				for(QuadTree* q : nodes)
					q->addObject(obj, rect);
			}
		}
	}

	
	template<typename ObjectT>
	std::set<ObjectT*> QuadTree<ObjectT>::retrieve(const sf::FloatRect& rect) {
		std::set<ObjectT*> _set;

		if(!intersects(rect))
			return _set;
		
		
		if(!isSplit() || type == FAST)
			for(auto p : objects)
				_set.insert(p.first);
		
		if(isSplit()) {
			for(QuadTree* q : nodes) {
				auto s = q->retrieve(rect);
				_set.insert(s.begin(), s.end());
			}
		}

		return _set;
	}
}
