#include <Keyboard.hpp>
#include <Window.hpp>

namespace Spore
{
    Keyboard::Keyboard()
    {

    }

    Keyboard::~Keyboard()
    {

    }

    void Keyboard::SetWindow(MainWindow* p_window)
    {
        m_window = p_window;
    }

    MainWindow* Keyboard::GetWindow()
    {
        return m_window;
    }

    int32 Keyboard::processInput(MainWindow* p_window,
                                Camera& p_camera, float32 p_deltaTime)
    {
        if (glfwGetKey(p_window->GetWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
        {
            glfwSetWindowShouldClose(p_window->GetWindow(), true);
            return KEY_ESC;
        }

        if (glfwGetKey(p_window->GetWindow(), GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
        {
            if (glfwGetKey(p_window->GetWindow(), GLFW_KEY_W) == GLFW_PRESS)
            {
                p_camera.ProcessKeyboard(FORWARD, p_deltaTime * 2);
                return KEY_W;
            }
            if (glfwGetKey(p_window->GetWindow(), GLFW_KEY_S) == GLFW_PRESS)
            {
                p_camera.ProcessKeyboard(BACKWARD, p_deltaTime * 2);
                return KEY_S;
            }
            if (glfwGetKey(p_window->GetWindow(), GLFW_KEY_A) == GLFW_PRESS)
            {
                p_camera.ProcessKeyboard(LEFT, p_deltaTime * 2);
                return KEY_A;
            }
            if (glfwGetKey(p_window->GetWindow(), GLFW_KEY_D) == GLFW_PRESS)
            {
                p_camera.ProcessKeyboard(RIGHT, p_deltaTime * 2);
                return KEY_D;
            }
            if (glfwGetKey(p_window->GetWindow(), GLFW_KEY_E) == GLFW_PRESS)
            {
                p_camera.ProcessKeyboard(UP, p_deltaTime * 2);
                return KEY_E;
            }
            if (glfwGetKey(p_window->GetWindow(), GLFW_KEY_Q) == GLFW_PRESS)
            {
                p_camera.ProcessKeyboard(DOWN, p_deltaTime * 2);
                return KEY_Q;
            }
        }
        if (glfwGetKey(p_window->GetWindow(), GLFW_KEY_W) == GLFW_PRESS)
            p_camera.ProcessKeyboard(FORWARD, p_deltaTime);
        if (glfwGetKey(p_window->GetWindow(), GLFW_KEY_S) == GLFW_PRESS)
            p_camera.ProcessKeyboard(BACKWARD, p_deltaTime);
        if (glfwGetKey(p_window->GetWindow(), GLFW_KEY_A) == GLFW_PRESS)
            p_camera.ProcessKeyboard(LEFT, p_deltaTime);
        if (glfwGetKey(p_window->GetWindow(), GLFW_KEY_D) == GLFW_PRESS)
            p_camera.ProcessKeyboard(RIGHT, p_deltaTime);
        if (glfwGetKey(p_window->GetWindow(), GLFW_KEY_E) == GLFW_PRESS)
            p_camera.ProcessKeyboard(UP, p_deltaTime);
        if (glfwGetKey(p_window->GetWindow(), GLFW_KEY_Q) == GLFW_PRESS)
            p_camera.ProcessKeyboard(DOWN, p_deltaTime);
        return -1;
    }

    int32 Keyboard::GetKey(MainWindow* p_window)
    {
        if (glfwGetKey(m_window->GetWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
        {
            return KEY_ESC;
        }
        if (glfwGetKey(m_window->GetWindow(), GLFW_KEY_F1) == GLFW_PRESS)
        {
            return KEY_F1;
        }
        if (glfwGetKey(m_window->GetWindow(), GLFW_KEY_F2) == GLFW_PRESS)
        {
            return KEY_F2;
        }
        if (glfwGetKey(m_window->GetWindow(), GLFW_KEY_F3) == GLFW_PRESS)
        {
            return KEY_F3;
        }
        if (glfwGetKey(m_window->GetWindow(), GLFW_KEY_F4) == GLFW_PRESS)
        {
            return KEY_F4;
        }
        if (glfwGetKey(m_window->GetWindow(), GLFW_KEY_F5) == GLFW_PRESS)
        {
            return KEY_F5;
        }
        if (glfwGetKey(m_window->GetWindow(), GLFW_KEY_F6) == GLFW_PRESS)
        {
            return KEY_F6;
        }
        if (glfwGetKey(m_window->GetWindow(), GLFW_KEY_F7) == GLFW_PRESS)
        {
            return KEY_F7;
        }
        if (glfwGetKey(m_window->GetWindow(), GLFW_KEY_F8) == GLFW_PRESS)
        {
            return KEY_F8;
        }
        if (glfwGetKey(m_window->GetWindow(), GLFW_KEY_F9) == GLFW_PRESS)
        {
            return KEY_F9;
        }
        if (glfwGetKey(m_window->GetWindow(), GLFW_KEY_F10) == GLFW_PRESS)
        {
            return KEY_F10;
        }
        if (glfwGetKey(m_window->GetWindow(), GLFW_KEY_F11) == GLFW_PRESS)
        {
            return KEY_F11;
        }
        if (glfwGetKey(m_window->GetWindow(), GLFW_KEY_F12) == GLFW_PRESS)
        {
            return KEY_F12;
        }
        if (glfwGetKey(m_window->GetWindow(), GLFW_KEY_GRAVE_ACCENT) == GLFW_PRESS)
        {
            return KEY_GRAVE_ACCENT;
        }
        if (glfwGetKey(m_window->GetWindow(), GLFW_KEY_1) == GLFW_PRESS)
        {
            return KEY_1;
        }
        if (glfwGetKey(m_window->GetWindow(), GLFW_KEY_2) == GLFW_PRESS)
        {
            return KEY_2;
        }
        if (glfwGetKey(m_window->GetWindow(), GLFW_KEY_3) == GLFW_PRESS)
        {
            return KEY_3;
        }
        if (glfwGetKey(m_window->GetWindow(), GLFW_KEY_4) == GLFW_PRESS)
        {
            return KEY_4;
        }
        if (glfwGetKey(m_window->GetWindow(), GLFW_KEY_5) == GLFW_PRESS)
        {
            return KEY_5;
        }
        if (glfwGetKey(m_window->GetWindow(), GLFW_KEY_6) == GLFW_PRESS)
        {
            return KEY_6;
        }
        if (glfwGetKey(m_window->GetWindow(), GLFW_KEY_7) == GLFW_PRESS)
        {
            return KEY_7;
        }
        if (glfwGetKey(m_window->GetWindow(), GLFW_KEY_8) == GLFW_PRESS)
        {
            return KEY_8;
        }
        if (glfwGetKey(m_window->GetWindow(), GLFW_KEY_9) == GLFW_PRESS)
        {
            return KEY_9;
        }
        if (glfwGetKey(m_window->GetWindow(), GLFW_KEY_0) == GLFW_PRESS)
        {
            return KEY_0;
        }
        if (glfwGetKey(m_window->GetWindow(), GLFW_KEY_MINUS) == GLFW_PRESS)
        {
            return KEY_MINUS;
        }
        if (glfwGetKey(m_window->GetWindow(), GLFW_KEY_EQUAL) == GLFW_PRESS)
        {
            return KEY_EQUAL;
        }
        if (glfwGetKey(m_window->GetWindow(), GLFW_KEY_BACKSPACE) == GLFW_PRESS)
        {
            return KEY_BACKSPACE;
        }
        if (glfwGetKey(m_window->GetWindow(), GLFW_KEY_TAB) == GLFW_PRESS)
        {
            return KEY_TAB;
        }
        if (glfwGetKey(m_window->GetWindow(), GLFW_KEY_Q) == GLFW_PRESS)
        {
            return KEY_Q;
        }
        if (glfwGetKey(m_window->GetWindow(), GLFW_KEY_W) == GLFW_PRESS)
        {
            return KEY_W;
        }
        if (glfwGetKey(m_window->GetWindow(), GLFW_KEY_E) == GLFW_PRESS)
        {
            return KEY_E;
        }
        if (glfwGetKey(m_window->GetWindow(), GLFW_KEY_R) == GLFW_PRESS)
        {
            return KEY_R;
        }
        if (glfwGetKey(m_window->GetWindow(), GLFW_KEY_T) == GLFW_PRESS)
        {
            return KEY_T;
        }
        if (glfwGetKey(m_window->GetWindow(), GLFW_KEY_Y) == GLFW_PRESS)
        {
            return KEY_Y;
        }
        if (glfwGetKey(m_window->GetWindow(), GLFW_KEY_U) == GLFW_PRESS)
        {
            return KEY_U;
        }
        if (glfwGetKey(m_window->GetWindow(), GLFW_KEY_I) == GLFW_PRESS)
        {
            return KEY_I;
        }
        if (glfwGetKey(m_window->GetWindow(), GLFW_KEY_O) == GLFW_PRESS)
        {
            return KEY_O;
        }
        if (glfwGetKey(m_window->GetWindow(), GLFW_KEY_P) == GLFW_PRESS)
        {
            return KEY_P;
        }
        if (glfwGetKey(m_window->GetWindow(), GLFW_KEY_LEFT_BRACKET) == GLFW_PRESS)
        {
            return KEY_LEFT_BRACKET;
        }
        if (glfwGetKey(m_window->GetWindow(), GLFW_KEY_RIGHT_BRACKET) == GLFW_PRESS)
        {
            return KEY_RIGHT_BRACKET;
        }
        if (glfwGetKey(m_window->GetWindow(), GLFW_KEY_BACKSLASH) == GLFW_PRESS)
        {
            return KEY_RIGHT_BACKSLASH;
        }
        if (glfwGetKey(m_window->GetWindow(), GLFW_KEY_CAPS_LOCK) == GLFW_PRESS)
        {
            return KEY_CAPS_LOCK;
        }
        if (glfwGetKey(m_window->GetWindow(), GLFW_KEY_A) == GLFW_PRESS)
        {
            return KEY_A;
        }
        if (glfwGetKey(m_window->GetWindow(), GLFW_KEY_S) == GLFW_PRESS)
        {
            return KEY_S;
        }
        if (glfwGetKey(m_window->GetWindow(), GLFW_KEY_D) == GLFW_PRESS)
        {
            return KEY_D;
        }
        if (glfwGetKey(m_window->GetWindow(), GLFW_KEY_F) == GLFW_PRESS)
        {
            return KEY_F;
        }
        if (glfwGetKey(m_window->GetWindow(), GLFW_KEY_G) == GLFW_PRESS)
        {
            return KEY_G;
        }
        if (glfwGetKey(m_window->GetWindow(), GLFW_KEY_H) == GLFW_PRESS)
        {
            return KEY_H;
        }
        if (glfwGetKey(m_window->GetWindow(), GLFW_KEY_J) == GLFW_PRESS)
        {
            return KEY_J;
        }
        if (glfwGetKey(m_window->GetWindow(), GLFW_KEY_K) == GLFW_PRESS)
        {
            return KEY_K;
        }
        if (glfwGetKey(m_window->GetWindow(), GLFW_KEY_L) == GLFW_PRESS)
        {
            return KEY_L;
        }
        if (glfwGetKey(m_window->GetWindow(), GLFW_KEY_SEMICOLON) == GLFW_PRESS)
        {
            return KEY_SEMICOLON;
        }
        if (glfwGetKey(m_window->GetWindow(), GLFW_KEY_APOSTROPHE) == GLFW_PRESS)
        {
            return KEY_APOSTROPHE;
        }
        if (glfwGetKey(m_window->GetWindow(), GLFW_KEY_ENTER) == GLFW_PRESS)
        {
            return KEY_ENTER;
        }
        if (glfwGetKey(m_window->GetWindow(), GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        {
            return KEY_LEFT_SHIFT;
        }
        if (glfwGetKey(m_window->GetWindow(), GLFW_KEY_Z) == GLFW_PRESS)
        {
            return KEY_Z;
        }
        if (glfwGetKey(m_window->GetWindow(), GLFW_KEY_X) == GLFW_PRESS)
        {
            return KEY_X;
        }
        if (glfwGetKey(m_window->GetWindow(), GLFW_KEY_C) == GLFW_PRESS)
        {
            return KEY_C;
        }
        if (glfwGetKey(m_window->GetWindow(), GLFW_KEY_V) == GLFW_PRESS)
        {
            return KEY_V;
        }
        if (glfwGetKey(m_window->GetWindow(), GLFW_KEY_B) == GLFW_PRESS)
        {
            return KEY_B;
        }
        if (glfwGetKey(m_window->GetWindow(), GLFW_KEY_N) == GLFW_PRESS)
        {
            return KEY_N;
        }
        if (glfwGetKey(m_window->GetWindow(), GLFW_KEY_M) == GLFW_PRESS)
        {
            return KEY_M;
        }
        if (glfwGetKey(m_window->GetWindow(), GLFW_KEY_COMMA) == GLFW_PRESS)
        {
            return KEY_COMMA;
        }
        if (glfwGetKey(m_window->GetWindow(), GLFW_KEY_PERIOD) == GLFW_PRESS)
        {
            return KEY_PERIOD;
        }
        if (glfwGetKey(m_window->GetWindow(), GLFW_KEY_SLASH) == GLFW_PRESS)
        {
            return KEY_SLASH;
        }
        if (glfwGetKey(m_window->GetWindow(), GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS)
        {
            return KEY_RIGHT_SHIFT;
        }
        if (glfwGetKey(m_window->GetWindow(), GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
        {
            return KEY_LEFT_CONTROL;
        }
        if (glfwGetKey(m_window->GetWindow(), GLFW_KEY_LEFT_ALT) == GLFW_PRESS)
        {
            return KEY_LEFT_ALT;
        }
        if (glfwGetKey(m_window->GetWindow(), GLFW_KEY_SPACE) == GLFW_PRESS)
        {
            return KEY_SPACE;
        }
        if (glfwGetKey(m_window->GetWindow(), GLFW_KEY_RIGHT_ALT) == GLFW_PRESS)
        {
            return KEY_RIGHT_ALT;
        }
        if (glfwGetKey(m_window->GetWindow(), GLFW_KEY_RIGHT_CONTROL) == GLFW_PRESS)
        {
            return KEY_RIGHT_CONTROL;
        }
        return KEY_UNKNOWN;
    }
}