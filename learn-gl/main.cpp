#include <glm/glm.hpp>
#include <boost/scoped_ptr.hpp>
#include <set>
#include <vector>

#include "engine/data/texture.hpp"
#include "engine/camera/fps-camera.hpp"
#include "engine/shader/shader.h"
#include "engine/texture/texture-manager.hpp"
#include "engine/object/box.hpp"
#include "engine/window/gl-window.hpp"
#include "engine/light/point-light.hpp"

class GameWindow: public GLWindow {
private:
    boost::scoped_ptr<Shader> shader;
    boost::scoped_ptr<TextureManager> textureManager;
    
    boost::scoped_ptr<Box> box;
    boost::scoped_ptr<FPSCamera> camera;
    boost::scoped_ptr<PointLight> pointLight;
    double lastX, lastY;
    bool firstMouse = true;
public:
    GameWindow(): GLWindow(1024, 768) {
        shader.reset(new Shader("/Users/nagyf/dev/home/learn-gl/learn-gl/shader/vertex.glsl", "/Users/nagyf/dev/home/learn-gl/learn-gl/shader/fragment.glsl"));
        textureManager.reset(new TextureManager());
        Texture boxTexture = textureManager->load("texture_diffuse", "/Users/nagyf/dev/home/learn-gl/learn-gl/assets/box.png");
        Texture boxSpecularTexture = textureManager->load("texture_specular", "/Users/nagyf/dev/home/learn-gl/learn-gl/assets/box_specular.png");
        
        camera.reset(new FPSCamera(glm::vec3(0.0, 0.0, 3.0)));
        box.reset(new Box(std::vector<Texture>({boxTexture, boxSpecularTexture})));
        pointLight.reset(new PointLight(glm::vec3(1.2f, 1.0f, 2.0f),
                                        glm::vec3(0.2,0.2,0.2),
                                        glm::vec3(0.5,0.5,0.5),
                                        glm::vec3(1.0,1.0,1.0)));
    }
protected:
    void preRender() {
        box->rotateY(deltaTime * 25.0);
    }
    
    void render() {
        shader->use();
        projectionMatrix = createProjectionMatrix(camera->zoom, width, height);
        shader->setMat4("projection", projectionMatrix);
        shader->setMat4("view", camera->viewMatrix());
        
        shader->setVec3("light.ambient", pointLight->getAmbient());
        shader->setVec3("light.diffuse", pointLight->getDiffuse());
        shader->setVec3("light.specular", pointLight->getSpecular());
        shader->setVec3("light.position", pointLight->getPosition());
        
        shader->setInt("material.diffuse", 0);
        shader->setInt("material.specular", 1);
        shader->setFloat("material.shininess", 64.0f);
        
        shader->setVec3("viewPos", camera->getPosition());
        box->render(*shader);
    }
    
    void processInput() {
        GLWindow::processInput();
        
        if (isAnyKeysPressed(std::set<int>({GLFW_KEY_W, GLFW_KEY_UP})))
            camera->processKeyboard(FORWARD, deltaTime);
        if (isAnyKeysPressed(std::set<int>({GLFW_KEY_S, GLFW_KEY_DOWN})))
            camera->processKeyboard(BACKWARD, deltaTime);
        if (isAnyKeysPressed(std::set<int>({GLFW_KEY_A, GLFW_KEY_LEFT})))
            camera->processKeyboard(LEFT, deltaTime);
        if (isAnyKeysPressed(std::set<int>({GLFW_KEY_D, GLFW_KEY_RIGHT})))
            camera->processKeyboard(RIGHT, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
            camera->processKeyboard(UP, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
            camera->processKeyboard(DOWN, deltaTime);
    }
    
    bool isAnyKeysPressed(const std::set<int> &keys) {
        std::set<int>::iterator it;
        for (it = keys.begin(); it != keys.end(); ++it){
            if(glfwGetKey(window, *it) == GLFW_PRESS) {
                return true;
            }
        }
        return false;
    }
    
    void mouseMoved(const double x, const double y) {
        if (firstMouse) {
            lastX = x;
            lastY = y;
            firstMouse = false;
        }
        
        float xoffset = x - lastX;
        float yoffset = lastY - y; // reversed since y-coordinates go from bottom to top
        
        lastX = x;
        lastY = y;
        
        camera->processMouseMovement(xoffset, yoffset);
    }
    
    void mouseScrolled(const double xOffset, const double yOffset) {
        camera->processMouseScroll(yOffset);
    }
};

int main(int argc, const char * argv[]) {
    boost::scoped_ptr<GameWindow> window(new GameWindow());
    return window->run();
}
