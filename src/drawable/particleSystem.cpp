#include <SFML_Snips.hpp>

namespace bzsf {


	// ParticleSystem ////////
	std::vector<std::unique_ptr<Emitter>> ParticleSystem::unownedEmitters = std::vector<std::unique_ptr<Emitter>>();



	Emitter& ParticleSystem::newEmitter() {
		std::unique_ptr<Emitter> e(new Emitter());
		e->kill(Emitter::SOFT);
		// Kills the emitter in such a way, that it will accept no more than one call to Fuel(),
		// and it will kill itself afterwards

		unownedEmitters.push_back(std::move(e));

		return *unownedEmitters[unownedEmitters.size()-1];
	}


	std::vector<std::unique_ptr<Emitter>>& ParticleSystem::getUnownedEmitters() {
		return unownedEmitters;
	}


	void ParticleSystem::draw(sf::RenderTarget& window, sf::RenderStates states) const {
		unownedEmitters.erase(std::remove_if(unownedEmitters.begin(), unownedEmitters.end(), [] (std::unique_ptr<Emitter>& e) {return e->isDead();}), unownedEmitters.end());

		for(std::unique_ptr<Emitter>& e : unownedEmitters) {
			window.draw(*e, states);
		}
	}
}
