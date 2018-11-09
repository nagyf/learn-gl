#include <glm/glm.hpp>
#include <boost/scoped_ptr.hpp>
#include <set>
#include <vector>

#include "engine/debug/imgui-debug-window.hpp"
#include "engine/data/texture.hpp"
#include "engine/camera/fps-camera.hpp"
#include "engine/shader/shader.h"
#include "engine/texture/texture-manager.hpp"
#include "engine/object/box.hpp"
#include "engine/object/plane.hpp"
#include "engine/object/skybox.hpp"
#include "engine/window/gl-window.hpp"
#include "engine/light/point-light.hpp"
#include "engine/light/directional-light.hpp"
#include "engine/light/spot-light.hpp"

class GameWindow: public GLWindow {
private:
    boost::scoped_ptr<ImguiDebugWindow> debugWindow;
    boost::scoped_ptr<Shader> shader;
    boost::scoped_ptr<Shader> skyboxShader;
    boost::scoped_ptr<TextureManager> textureManager;
    
    boost::scoped_ptr<Skybox> skybox;
    boost::scoped_ptr<Plane> ground;
    boost::scoped_ptr<Box> box;
    boost::scoped_ptr<FPSCamera> camera;
    boost::scoped_ptr<PointLight> pointLight;
    boost::scoped_ptr<DirectionalLight> dirLight;
    boost::scoped_ptr<SpotLight> spotLight;
    double lastX, lastY;
    bool firstMouse = true;
public:
    GameWindow(): GLWindow() {
        shader.reset(new Shader("/Users/nagyf/dev/home/learn-gl/learn-gl/shader/vertex.glsl", "/Users/nagyf/dev/home/learn-gl/learn-gl/shader/fragment.glsl"));
        skyboxShader.reset(new Shader("/Users/nagyf/dev/home/learn-gl/learn-gl/shader/skybox_vertex.glsl", "/Users/nagyf/dev/home/learn-gl/learn-gl/shader/skybox_fragment.glsl"));
        textureManager.reset(new TextureManager());
        Texture boxTexture = textureManager->load("texture_diffuse", "/Users/nagyf/dev/home/learn-gl/learn-gl/assets/box.png");
        Texture boxSpecularTexture = textureManager->load("texture_specular", "/Users/nagyf/dev/home/learn-gl/learn-gl/assets/box_specular.png");
        Texture pavemantTexture = textureManager->load("texture_diffuse", "/Users/nagyf/dev/home/learn-gl/learn-gl/assets/pavement.jpg");
        
        std::vector<std::string> faces
        {
            "/Users/nagyf/dev/home/learn-gl/learn-gl/assets/skybox/right.jpg",
            "/Users/nagyf/dev/home/learn-gl/learn-gl/assets/skybox/left.jpg",
            "/Users/nagyf/dev/home/learn-gl/learn-gl/assets/skybox/top.jpg",
            "/Users/nagyf/dev/home/learn-gl/learn-gl/assets/skybox/bottom.jpg",
            "/Users/nagyf/dev/home/learn-gl/learn-gl/assets/skybox/front.jpg",
            "/Users/nagyf/dev/home/learn-gl/learn-gl/assets/skybox/back.jpg"
        };
        Texture skyboxCubemap = textureManager->loadCubemap(faces);
        skybox.reset(new Skybox(skyboxCubemap));
        
        camera.reset(new FPSCamera(glm::vec3(0.0, 0.0, 5.0)));
        box.reset(new Box(std::vector<Texture>({boxTexture, boxSpecularTexture})));
        ground.reset(new Plane(100.0f, std::vector<Texture>({pavemantTexture})));
        ground->moveY(-1.0f);
        ground->rotateX(90.0f);
        
        // Point light
        pointLight.reset(new PointLight(glm::vec3(1.2f, 1.0f, 2.0f),
                                        glm::vec3(0.2,0.2,0.2),
                                        glm::vec3(0.5,0.5,0.5),
                                        glm::vec3(1.0,1.0,1.0)));
        // Directional light
        dirLight.reset(new DirectionalLight(glm::vec3(1.2f, 1.0f, 2.0f),
                                        glm::vec3(0.05, 0.05, 0.05),
                                        glm::vec3(0.4, 0.4, 0.4),
                                        glm::vec3(0.5, 0.5, 0.5)));
        
        spotLight.reset(new SpotLight());
        
        debugWindow.reset(new ImguiDebugWindow(window));
    }
protected:
    void preRender() {
        box->rotateY(deltaTime * 25.0);
        debugWindow->preRender();
        projectionMatrix = createProjectionMatrix(camera->zoom, width, height);
        spotLight->setPosition(camera->getPosition());
        spotLight->setDirection(camera->getFront());
    }
    
    void render() {
        shader->use();
        shader->setMat4("projection", projectionMatrix);
        shader->setMat4("view", camera->viewMatrix());
        
        shader->setVec3("pointLight.ambient", pointLight->getAmbient());
        shader->setVec3("pointLight.diffuse", pointLight->getDiffuse());
        shader->setVec3("pointLight.specular", pointLight->getSpecular());
        shader->setFloat("pointLight.constant", pointLight->getConstant());
        shader->setFloat("pointLight.linear", pointLight->getLinear());
        shader->setFloat("pointLight.quadratic", pointLight->getQuadratic());
        shader->setVec3("pointLight.position", pointLight->getPosition());
        
        shader->setVec3("spotLight.ambient", spotLight->getAmbient());
        shader->setVec3("spotLight.diffuse", spotLight->getDiffuse());
        shader->setVec3("spotLight.specular", spotLight->getSpecular());
        shader->setFloat("spotLight.constant", spotLight->getConstant());
        shader->setFloat("spotLight.linear", spotLight->getLinear());
        shader->setFloat("spotLight.quadratic", spotLight->getQuadratic());
        shader->setVec3("spotLight.position", spotLight->getPosition());
        shader->setVec3("spotLight.direction", spotLight->getDirection());
        shader->setFloat("spotLight.cutOff", spotLight->getCutOff());
        shader->setFloat("spotLight.outerCutOff", spotLight->getOuterCutOff());
        
        shader->setVec3("dirLight.ambient", dirLight->getAmbient());
        shader->setVec3("dirLight.diffuse", dirLight->getDiffuse());
        shader->setVec3("dirLight.specular", dirLight->getSpecular());
        shader->setVec3("dirLight.direction", dirLight->getDirection());
        
        shader->setInt("material.diffuse", 0);
        shader->setInt("material.specular", 1);
        shader->setFloat("material.shininess", 64.0f);
        
        shader->setVec3("viewPos", camera->getPosition());
        box->render(*shader);
        
        shader->setInt("material.specular", 0);
        shader->setFloat("material.shininess", 8.0f);
        ground->render(*shader);
        skyboxShader->use();
        skyboxShader->setMat4("projection", projectionMatrix);
        skyboxShader->setMat4("view", glm::mat4(glm::mat3(camera->viewMatrix())));
        skybox->render(*skyboxShader);
    
        debugWindow->render();
    }
    
    void postRender() {
        debugWindow->postRender();
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
