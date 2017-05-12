#include "ExampleApp.h"

using namespace glm;
using namespace std;

namespace basicgraphics {
    
	ExampleApp::ExampleApp(int argc, char** argv, std::string windowName, int windowWidth, int windowHeight) : BaseApp(argc, argv, windowName, windowWidth, windowHeight)
	{
        // Change the background color
        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        
        sphere.reset(new Sphere(vec3(0.0), 1, vec4(1,0,0,1)));
        
        ground.reset(new GroundPlane(vec3(0, -1, 0), vec3(0, 1, 0)));

        dir = vec3(0.0);
        sphereFrame = mat4(1.0);
	}

	ExampleApp::~ExampleApp() {}


    void ExampleApp::onSimulation(double rdt){
		//TODO: Update the sphereFrame matrix to move the ball's position based on the dir variable.
		//Make the ball rotate so that it looks like it is rolling on the table.


    }
    
	void ExampleApp::onRenderGraphics() {
        
        double curTime = glfwGetTime();
        onSimulation(curTime - lastTime);
        lastTime = curTime;
        
		// Setup the view matrix to set where the camera is located
        vec3 ballPos = vec3(column(sphereFrame, 3));
		glm::vec3 eye_world = ballPos + glm::vec3(4,1.5,8);
		glm::mat4 view = glm::lookAt(eye_world, ballPos, glm::vec3(0,1,0));
		
		// Setup the projection matrix so that things are rendered in perspective
		glm::mat4 projection = glm::perspective(glm::radians(45.0f), (GLfloat)_windowWidth / (GLfloat)_windowHeight, 0.01f, 100.0f);
		// Setup the model matrix
		glm::mat4 model = glm::mat4(1.0);

		// Update shader variables
		_shader.setUniform("view_mat", view);
		_shader.setUniform("projection_mat", projection);
		_shader.setUniform("model_mat", model);
		_shader.setUniform("eye_world", eye_world);

        ground->draw(_shader, model);
        
        _shader.setUniform("model_mat", sphereFrame);
        sphere->draw(_shader, sphereFrame);
        
	}

	void ExampleApp::onEvent(shared_ptr<Event> event) {
		string name = event->getName();
        float speed = 0.01;
        
        if (name == "kbd_UP_down") {
            dir = dir + vec3(0,0,-speed);
        }
        else if (name == "kbd_DOWN_down") {
            dir = dir + vec3(0,0,speed);
        }
        else if (name == "kbd_LEFT_down") {
            dir = dir + vec3(-speed,0,0);
        }
        else if (name == "kbd_RIGHT_down") {
            dir = dir + vec3(speed,0,0);
        }
        
        // If the ball rolls off the screen, you can press SPACEBAR to reset its position
        else if (name == "kbd_SPACE_down") {
            dir = vec3(0,0,0);
            sphereFrame = mat4(1.0);
        }
	}
}