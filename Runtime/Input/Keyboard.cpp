#include <Keyboard.hpp>

namespace Spore
{
    Keyboard::Keyboard()
    {

    }

    Keyboard::~Keyboard()
    {
    }

    void Keyboard::processInput(Spore::MainWindow* window,
                                Camera& camera, float32 deltaTime)
    {
        if (glfwGetKey(window->window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window->window, true);

        if (glfwGetKey(window->window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
        {
            if (glfwGetKey(window->window, GLFW_KEY_W) == GLFW_PRESS)
                camera.ProcessKeyboard(FORWARD, deltaTime * 2);
            if (glfwGetKey(window->window, GLFW_KEY_S) == GLFW_PRESS)
                camera.ProcessKeyboard(BACKWARD, deltaTime * 2);
            if (glfwGetKey(window->window, GLFW_KEY_A) == GLFW_PRESS)
                camera.ProcessKeyboard(LEFT, deltaTime * 2);
            if (glfwGetKey(window->window, GLFW_KEY_D) == GLFW_PRESS)
                camera.ProcessKeyboard(RIGHT, deltaTime * 2);
            if (glfwGetKey(window->window, GLFW_KEY_E) == GLFW_PRESS)
                camera.ProcessKeyboard(UP, deltaTime * 2);
            if (glfwGetKey(window->window, GLFW_KEY_Q) == GLFW_PRESS)
                camera.ProcessKeyboard(DOWN, deltaTime * 2);
        }
        if (glfwGetKey(window->window, GLFW_KEY_W) == GLFW_PRESS)
            camera.ProcessKeyboard(FORWARD, deltaTime);
        if (glfwGetKey(window->window, GLFW_KEY_S) == GLFW_PRESS)
            camera.ProcessKeyboard(BACKWARD, deltaTime);
        if (glfwGetKey(window->window, GLFW_KEY_A) == GLFW_PRESS)
            camera.ProcessKeyboard(LEFT, deltaTime);
        if (glfwGetKey(window->window, GLFW_KEY_D) == GLFW_PRESS)
            camera.ProcessKeyboard(RIGHT, deltaTime);
        if (glfwGetKey(window->window, GLFW_KEY_E) == GLFW_PRESS)
            camera.ProcessKeyboard(UP, deltaTime);
        if (glfwGetKey(window->window, GLFW_KEY_Q) == GLFW_PRESS)
            camera.ProcessKeyboard(DOWN, deltaTime);

        /*if (glfwGetKey(window->window, GLFW_KEY_LEFT_ALT) == GLFW_PRESS)
        {
            glfwSetInputMode(window->window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            window->cameraLock = true;
        }
        else
        {
            glfwSetInputMode(window->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            window->cameraLock = false;
        }*/
    }
}