#include <Keyboard.hpp>

namespace Spore
{
    Keyboard::Keyboard()
    {

    }

    Keyboard::~Keyboard()
    {
    }

    void Keyboard::processInput(Spore::MainWindow* p_window,
                                Camera& p_camera, float32 p_deltaTime)
    {
        if (glfwGetKey(p_window->m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(p_window->m_window, true);

        if (glfwGetKey(p_window->m_window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
        {
            if (glfwGetKey(p_window->m_window, GLFW_KEY_W) == GLFW_PRESS)
                p_camera.ProcessKeyboard(FORWARD, p_deltaTime * 2);
            if (glfwGetKey(p_window->m_window, GLFW_KEY_S) == GLFW_PRESS)
                p_camera.ProcessKeyboard(BACKWARD, p_deltaTime * 2);
            if (glfwGetKey(p_window->m_window, GLFW_KEY_A) == GLFW_PRESS)
                p_camera.ProcessKeyboard(LEFT, p_deltaTime * 2);
            if (glfwGetKey(p_window->m_window, GLFW_KEY_D) == GLFW_PRESS)
                p_camera.ProcessKeyboard(RIGHT, p_deltaTime * 2);
            if (glfwGetKey(p_window->m_window, GLFW_KEY_E) == GLFW_PRESS)
                p_camera.ProcessKeyboard(UP, p_deltaTime * 2);
            if (glfwGetKey(p_window->m_window, GLFW_KEY_Q) == GLFW_PRESS)
                p_camera.ProcessKeyboard(DOWN, p_deltaTime * 2);
        }
        if (glfwGetKey(p_window->m_window, GLFW_KEY_W) == GLFW_PRESS)
            p_camera.ProcessKeyboard(FORWARD, p_deltaTime);
        if (glfwGetKey(p_window->m_window, GLFW_KEY_S) == GLFW_PRESS)
            p_camera.ProcessKeyboard(BACKWARD, p_deltaTime);
        if (glfwGetKey(p_window->m_window, GLFW_KEY_A) == GLFW_PRESS)
            p_camera.ProcessKeyboard(LEFT, p_deltaTime);
        if (glfwGetKey(p_window->m_window, GLFW_KEY_D) == GLFW_PRESS)
            p_camera.ProcessKeyboard(RIGHT, p_deltaTime);
        if (glfwGetKey(p_window->m_window, GLFW_KEY_E) == GLFW_PRESS)
            p_camera.ProcessKeyboard(UP, p_deltaTime);
        if (glfwGetKey(p_window->m_window, GLFW_KEY_Q) == GLFW_PRESS)
            p_camera.ProcessKeyboard(DOWN, p_deltaTime);

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