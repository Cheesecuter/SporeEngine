//#pragma once
//#ifndef InputDevices_hpp
//#define InputDevices_hpp
//
//#include <glad/glad.h>
//#include <GLFW/glfw3.h>
//
//#include "CAMERA.hpp"
//
//class InputDevices
//{
//
//    Camera camera;
//    double lastX, lastY;
//    bool cameraLock = false;
//    bool firstMouse = true;
//    float deltaTime = 0.0f;
//
//public:
//    InputDevices(int scrWidth, int scrHeight, Camera camera)
//    {
//        lastX = scrWidth / 2.0f;
//        lastY = scrHeight / 2.0f;
//    }
//
//    ~InputDevices()
//    { }
//
//    void MouseCallback(GLFWwindow* GLFWwindow, double xPosIn, double yPosIn)
//    {
//        if (!cameraLock)
//        {
//            double xPos = static_cast<float>(xPosIn);
//            double yPos = static_cast<float>(yPosIn);
//            if (firstMouse)
//            {
//                lastX = xPos;
//                lastY = yPos;
//                firstMouse = false;
//            }
//
//            float xOffset = xPos - lastX;
//            float yOffset = yPos - lastY;
//
//            lastX = xPos;
//            lastY = yPos;
//
//            camera.ProcessMouseMovement(xOffset, yOffset);
//        }
//    }
//
//    void ScrollCallBack(GLFWwindow* window, double xOffset, double yOffset)
//    {
//        camera.ProcessMouseScroll(static_cast<float>(yOffset));
//    }
//
//    void KeyboardInput(GLFWwindow* window)
//    {
//        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
//            glfwSetWindowShouldClose(window, true);
//
//        if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
//        {
//            if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
//                camera.ProcessKeyboard(FORWARD, deltaTime * 2);
//            if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
//                camera.ProcessKeyboard(BACKWARD, deltaTime * 2);
//            if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
//                camera.ProcessKeyboard(LEFT, deltaTime * 2);
//            if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
//                camera.ProcessKeyboard(RIGHT, deltaTime * 2);
//            if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
//                camera.ProcessKeyboard(UP, deltaTime * 2);
//            if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
//                camera.ProcessKeyboard(DOWN, deltaTime * 2);
//        }
//        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
//            camera.ProcessKeyboard(FORWARD, deltaTime);
//        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
//            camera.ProcessKeyboard(BACKWARD, deltaTime);
//        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
//            camera.ProcessKeyboard(LEFT, deltaTime);
//        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
//            camera.ProcessKeyboard(RIGHT, deltaTime);
//        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
//            camera.ProcessKeyboard(DOWN, deltaTime);
//        if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
//            camera.ProcessKeyboard(UP, deltaTime);
//
//        if (glfwGetKey(window, GLFW_KEY_LEFT_ALT) == GLFW_PRESS)
//        {
//            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
//            cameraLock = true;
//        }
//        else
//        {
//            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
//            cameraLock = false;
//        }
//    }
//
//private:
//	
//};
//
//#endif
