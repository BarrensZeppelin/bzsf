
namespace bzsf {
	template<typename ObjectT>
	QuadTree<ObjectT>::QuadTree(sf::FloatRect bounds, Type type, sf::Uint16 maxlevel, sf::Uint16 maxobjects, sf::Uint16 level) :
		bounds(bounds)
		, rects()
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
	bool QuadTree<ObjectT>::isSplit() {
		return nodes[0] != nullptr;
	}

	template<typename ObjectT>
	bool QuadTree<ObjectT>::intersects(const sf::FloatRect& rect) {
		return bounds.intersects(rect);
	}


	template<typename ObjectT>
	void QuadTree<ObjectT>::split() {
		sf::Vector2f halfSize = sf::Vector2f(bounds.width / 2.f, bounds.height / 2.f);
		
		/*
			2 | 1
			-----
			3 | 4
		*/
		nodes[0] = new QuadTree<ObjectT>(sf::FloatRect(sf::Vector2f(bounds.left + halfSize.x, bounds.top), halfSize),				type, MAXLEVEL, MAXNODES, level + 1);
		nodes[1] = new QuadTree<ObjectT>(sf::FloatRect(sf::Vector2f(bounds.left, bounds.top), halfSize),							type, MAXLEVEL, MAXNODES, level + 1);
		nodes[2] = new QuadTree<ObjectT>(sf::FloatRect(sf::Vector2f(bounds.left, bounds.top + halfSize.y), halfSize),				type, MAXLEVEL, MAXNODES, level + 1);
		nodes[3] = new QuadTree<ObjectT>(sf::FloatRect(sf::Vector2f(bounds.left + halfSize.x, bounds.top + halfSize.y), halfSize),	type, MAXLEVEL, MAXNODES, level + 1);
	
		if(type == PRECISE) { // Divide current objects into subnodes
			for(auto o : objects)
				for(QuadTree* q : nodes)
					q->addObject(o, rects[o]);

			objects.clear();
		} // else don't care and proceed to add next objects to subnodes -> creates less accurate collisions, but
		  // gives more performance when splitting
	}


	template<typename ObjectT>
	void QuadTree<ObjectT>::retrieveAllHelper(std::set<std::vector<ObjectT*>>& set) {
		if(!isSplit()) {
			if(objects.size() >= 2)
				set.emplace(objects.begin(), objects.end());
		} else
			for(QuadTree* q : nodes)
				q->retrieveAllHelper(set);
	}


	

	template<typename ObjectT>
	void QuadTree<ObjectT>::clear() {
		if(isSplit()) {
			for(QuadTree* q : nodes)
				delete q;
		}

		nodes = std::array<QuadTree<ObjectT>*, 4>(); // Reinit array to fix nullptr bug
		objects.clear();
		rects.clear();
	}


	template<typename ObjectT>	
	void QuadTree<ObjectT>::addObject(ObjectT* obj, const sf::FloatRect& rect) {
		if(intersects(rect)) {
			if(level == MAXLEVEL || ((!isSplit()) && objects.size() < MAXNODES)) {
				rects.insert(std::make_pair(obj, rect));
				objects.push_back(obj);
			} else { // Direct object into subnodes
				if(!isSplit())
					split();

				for(QuadTree* q : nodes)
					q->addObject(obj, rect);
			}
		}
	}

	
	template<typename ObjectT>
	std::unordered_set<ObjectT*> QuadTree<ObjectT>::retrieve(const sf::FloatRect& rect) {
		std::unordered_set<ObjectT*> _set;

		if(!intersects(rect))
			return _set;
		
		
		if(!isSplit() || type == FAST)
			_set.insert(objects.begin(), objects.end());
		
		if(isSplit()) {
			for(QuadTree* q : nodes) {
				auto s = q->retrieve(rect);
				_set.insert(s.begin(), s.end());
			}
		}

		return _set;
	}


	template<typename ObjectT>
	std::set<std::vector<ObjectT*>> QuadTree<ObjectT>::retrieveAll() {
		assert(("retrieveAll() is undefined with FAST", type == PRECISE));

		std::set<std::vector<ObjectT*>> set;
		retrieveAllHelper(set);
		return set;
	}


	template<typename ObjectT>
	QuadTree<ObjectT>::~QuadTree() {
		clear();
	}
}
