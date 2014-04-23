

#include "particleSystem\particle.hpp"
#include "particleSystem\emitter.hpp"

namespace bzsf {


	class ParticleSystem {
		static std::vector<std::unique_ptr<Emitter>> unownedEmitters;

	public:
		/////////////////////////////////////////
		/// \brief Create a new unowned Emitter
		///
		/// Assign to a bzsf::Emitter ptr and
		/// control with ->Set'ers
		/// Won't display unless without call to
		/// bzsf::ParticleSystem::Draw() and
		/// some Fuel()
		///
		/// \see bzsf::ParticleSystem::Draw
		/////////////////////////////////////////
		static Emitter* NewEmitter();

		static std::vector<std::unique_ptr<Emitter>>& GetUnownedEmitters();
		

		static void Draw(sf::RenderTarget& window, sf::RenderStates = sf::RenderStates::Default);
	};

} //ENDOF NAMESPACE bzsf