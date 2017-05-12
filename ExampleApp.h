
#include "BaseApp.h"
#include "GroundPlane.h"
#include "glm/glm/gtx/orthonormalize.hpp"

namespace basicgraphics {

	class ExampleApp : public BaseApp {
		public:
			ExampleApp(int argc, char** argv, std::string windowName, int windowWidth, int windowHeight);
			~ExampleApp();

		private:
            void onSimulation(double rdt);
			void onRenderGraphics() override;
			void onEvent(std::shared_ptr<Event> event) override;
        
            std::unique_ptr<Sphere> sphere;
            std::unique_ptr<GroundPlane> ground;
        
            glm::vec3 dir;
            glm::mat4 sphereFrame;
        
            double lastTime;

	};
}