#ifndef BZSF_PARTICLE_SYSTEM
#define BZSF_PARTICLE_SYSTEM

#include <SFML/Graphics.hpp>


#include "particleSystem/emitter.hpp"

namespace bzsf {


	class ParticleSystem : public sf::Drawable {
	private:
		static std::vector<std::unique_ptr<Emitter>> unownedEmitters;

	private:
		void draw(sf::RenderTarget& window, sf::RenderStates = sf::RenderStates::Default) const;


	public:
		/////////////////////////////////////////
		/// \brief Create a new unowned Emitter
		///
		/// Assign to a bzsf::Emitter ptr and
		/// control with ->Set'ers
		/// Won't display without call to
		/// bzsf::ParticleSystem::Draw() and
		/// some Fuel()
		///
		/// \see bzsf::ParticleSystem::Draw
		/////////////////////////////////////////
		static Emitter& newEmitter();

		static std::vector<std::unique_ptr<Emitter>>& getUnownedEmitters();
	};

} //ENDOF NAMESPACE bzsf

#endif
