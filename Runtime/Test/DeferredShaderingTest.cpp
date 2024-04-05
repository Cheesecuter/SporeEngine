//#include <glad/glad.h>
//#define GLFW_INCLUDE_NONE
//#include <GLFW/glfw3.h>
//
//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/type_ptr.hpp>
//
//#include <stb_image.h>
//
//#include <SHADER.hpp>
//#include <CAMERA.hpp>
//#include <MODEL.hpp>
//#include <IMGUI_GLFW_OPENGL3.hpp>
//
//#include <iostream>
//
//using namespace Spore;
//
//void framebuffer_size_callback(GLFWwindow* window, int width, int height);
//void mouse_callback(GLFWwindow* window, double xpos, double ypos);
//void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
//static void glfwErrorCallback(int error, const char* description);
//
//void processInput(GLFWwindow* window);
//
//unsigned int loadTexture(const char* path, bool gammaCorrection);
//
//void renderQuad();
//void renderCube();
//void Render(GLFWwindow* window);
//
//GLFWwindow* InitGlfwWindow();
//void InitImguiWindow();
//
//// settings
//const unsigned int SCR_WIDTH = 1200;
//const unsigned int SCR_HEIGHT = 900;
//
//// camera
//Camera camera(glm::vec3(0.0f, 0.0f, 5.0f));
//float lastX = (float) SCR_WIDTH / 2.0;
//float lastY = (float) SCR_HEIGHT / 2.0;
//bool firstMouse = true;
//bool hideCursor = true;
//bool cameraLock = false;
//glm::vec4 backgroungColor = glm::vec4(0.436f, 0.436f, 0.436f, 1.0f);
////ImVec4 backgroungColor = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
//
//// timing
//float deltaTime = 0.0f;
//float lastFrame = 0.0f;
//
//int main()
//{
//    glfwSetErrorCallback(glfwErrorCallback);
//
//    // glfw: initialize and configure
//    // ------------------------------
//    if (!glfwInit())
//        return 1;
//    //glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//    //glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//
//    // Decide GL+GLSL versions
//#if defined(IMGUI_IMPL_OPENGL_ES2)
//    // GL ES 2.0 + GLSL 100
//    const char* glsl_version = "#version 100";
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
//    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
//#elif defined(__APPLE__)
//    // GL 3.2 + GLSL 150
//    const char* glsl_version = "#version 150";
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
//    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
//    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // Required on Mac
//#else
//    // GL 3.0 + GLSL 130
//    const char* glsl_version = "#version 130";
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
//    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
//    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only
//#endif
//
//    GLFWwindow* window = InitGlfwWindow();
//
//    // setup imgui context
//    IMGUI_CHECKVERSION();
//    ImGui::CreateContext();
//    
//    // setup imgui style
//    ImGui::StyleColorsDark();
//
//    // setup platform/renderer backends
//    ImGui_ImplGlfw_InitForOpenGL(window, true);
//#ifdef __EMSCRIPTEN__
//    ImGui_ImplGlfw_InstallEmscriptenCanvasResizeCallback("#canvas");
//#endif
//    ImGui_ImplOpenGL3_Init(glsl_version);
//
//    Render(window);
//
//    ImGui_ImplOpenGL3_Shutdown();
//    ImGui_ImplGlfw_Shutdown();
//    ImGui::DestroyContext();
//    glfwDestroyWindow(window);
//    glfwTerminate();
//
//    return 0;
//}
//
//// renderCube() renders a 1x1 3D cube in NDC.
//// -------------------------------------------------
//unsigned int cubeVAO = 0;
//unsigned int cubeVBO = 0;
//void renderCube()
//{
//    // initialize (if necessary)
//    if (cubeVAO == 0)
//    {
//        float vertices [] = {
//            // back face
//            -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f, // bottom-left
//             1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f, // top-right
//             1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 0.0f, // bottom-right         
//             1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f, // top-right
//            -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f, // bottom-left
//            -1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 1.0f, // top-left
//            // front face
//            -1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f, // bottom-left
//             1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 0.0f, // bottom-right
//             1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f, // top-right
//             1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f, // top-right
//            -1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 1.0f, // top-left
//            -1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f, // bottom-left
//            // left face
//            -1.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-right
//            -1.0f,  1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 1.0f, // top-left
//            -1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-left
//            -1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-left
//            -1.0f, -1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 0.0f, // bottom-right
//            -1.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-right
//            // right face
//             1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-left
//             1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-right
//             1.0f,  1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 1.0f, // top-right         
//             1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-right
//             1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-left
//             1.0f, -1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 0.0f, // bottom-left     
//            // bottom face
//            -1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f, // top-right
//             1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 1.0f, // top-left
//             1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f, // bottom-left
//             1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f, // bottom-left
//            -1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 0.0f, // bottom-right
//            -1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f, // top-right
//            // top face
//            -1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f, // top-left
//             1.0f,  1.0f , 1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f, // bottom-right
//             1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 1.0f, // top-right     
//             1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f, // bottom-right
//            -1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f, // top-left
//            -1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 0.0f  // bottom-left        
//        };
//        glGenVertexArrays(1, &cubeVAO);
//        glGenBuffers(1, &cubeVBO);
//        // fill buffer
//        glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
//        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//        // link vertex attributes
//        glBindVertexArray(cubeVAO);
//        glEnableVertexAttribArray(0);
//        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*) 0);
//        glEnableVertexAttribArray(1);
//        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*) (3 * sizeof(float)));
//        glEnableVertexAttribArray(2);
//        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*) (6 * sizeof(float)));
//        glBindBuffer(GL_ARRAY_BUFFER, 0);
//        glBindVertexArray(0);
//    }
//    // render Cube
//    glBindVertexArray(cubeVAO);
//    glDrawArrays(GL_TRIANGLES, 0, 36);
//    glBindVertexArray(0);
//}
//
//
//// renderQuad() renders a 1x1 XY quad in NDC
//// -----------------------------------------
//unsigned int quadVAO = 0;
//unsigned int quadVBO;
//void renderQuad()
//{
//    if (quadVAO == 0)
//    {
//        float quadVertices [] = {
//            // positions        // texture Coords
//            -1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
//            -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
//             1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
//             1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
//        };
//        // setup plane VAO
//        glGenVertexArrays(1, &quadVAO);
//        glGenBuffers(1, &quadVBO);
//        glBindVertexArray(quadVAO);
//        glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
//        glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
//        glEnableVertexAttribArray(0);
//        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*) 0);
//        glEnableVertexAttribArray(1);
//        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*) (3 * sizeof(float)));
//    }
//    glBindVertexArray(quadVAO);
//    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
//    glBindVertexArray(0);
//}
//
//// glfw: whenever the window size changed (by OS or user resize) this callback function executes
//// ---------------------------------------------------------------------------------------------
//void framebuffer_size_callback(GLFWwindow* window, int width, int height)
//{
//    // make sure the viewport matches the new window dimensions; note that width and 
//    // height will be significantly larger than specified on retina displays.
//    glViewport(0, 0, width, height);
//}
//
//// glfw: whenever the mouse moves, this callback is called
//// -------------------------------------------------------
//void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
//{
//    if (!cameraLock)
//    {
//        float xpos = static_cast<float>(xposIn);
//        float ypos = static_cast<float>(yposIn);
//        if (firstMouse)
//        {
//            lastX = xpos;
//            lastY = ypos;
//            firstMouse = false;
//        }
//
//        float xoffset = xpos - lastX;
//        float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
//
//        lastX = xpos;
//        lastY = ypos;
//
//        camera.ProcessMouseMovement(xoffset, yoffset);
//    }
//}
//
//// glfw: whenever the mouse scroll wheel scrolls, this callback is called
//// ----------------------------------------------------------------------
//void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
//{
//    camera.ProcessMouseScroll(static_cast<float>(yoffset));
//}
//
//static void glfwErrorCallback(int error, const char* description)
//{
//    fprintf(stderr, "GLFW Error %d: %s\n", error, description);
//}
//
//// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
//// ---------------------------------------------------------------------------------------------------------
//void processInput(GLFWwindow* window)
//{
//    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
//        glfwSetWindowShouldClose(window, true);
//
//    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
//    {
//        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
//            camera.ProcessKeyboard(FORWARD, deltaTime * 2);
//        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
//            camera.ProcessKeyboard(BACKWARD, deltaTime * 2);
//        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
//            camera.ProcessKeyboard(LEFT, deltaTime * 2);
//        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
//            camera.ProcessKeyboard(RIGHT, deltaTime * 2);
//        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
//            camera.ProcessKeyboard(UP, deltaTime * 2);
//        if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
//            camera.ProcessKeyboard(DOWN, deltaTime * 2);
//    }
//    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
//        camera.ProcessKeyboard(FORWARD, deltaTime);
//    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
//        camera.ProcessKeyboard(BACKWARD, deltaTime);
//    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
//        camera.ProcessKeyboard(LEFT, deltaTime);
//    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
//        camera.ProcessKeyboard(RIGHT, deltaTime);
//    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
//        camera.ProcessKeyboard(UP, deltaTime);
//    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
//        camera.ProcessKeyboard(DOWN, deltaTime);
//
//    if (glfwGetKey(window, GLFW_KEY_LEFT_ALT) == GLFW_PRESS)
//    {
//        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
//        cameraLock = true;
//    }
//    else
//    {
//        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
//        cameraLock = false;
//    }
//}
//
//// utility function for loading a 2D texture from file
//// ---------------------------------------------------
//unsigned int loadTexture(char const* path)
//{
//    unsigned int textureID;
//    glGenTextures(1, &textureID);
//
//    int width, height, nrComponents;
//    unsigned char* data = stbi_load(path, &width, &height, &nrComponents, 0);
//    if (data)
//    {
//        GLenum format;
//        if (nrComponents == 1)
//            format = GL_RED;
//        else if (nrComponents == 3)
//            format = GL_RGB;
//        else if (nrComponents == 4)
//            format = GL_RGBA;
//
//        glBindTexture(GL_TEXTURE_2D, textureID);
//        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
//        glGenerateMipmap(GL_TEXTURE_2D);
//
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//
//        stbi_image_free(data);
//    }
//    else
//    {
//        std::cout << "Texture failed to load at path: " << path << std::endl;
//        stbi_image_free(data);
//    }
//
//    return textureID;
//}
//
//void Render(GLFWwindow* window)
//{
//    // build and compile shaders
//    // -------------------------
//    Shader shaderGeometryPass("./Assets/Shaders/GBufferVertex.glsl", "./Assets/Shaders/GBufferFragment.glsl");
//    Shader shaderLightingPass("./Assets/Shaders/DeferredShadingVertex.glsl", "./Assets/Shaders/DeferredShadingFragment.glsl");
//    Shader shaderLightBox("./Assets/Shaders/DeferredLightBoxVertex.glsl", "./Assets/Shaders/DeferredLightBoxFragment.glsl");
//
//    // load models
//    // -----------
//    Model backpack(std::filesystem::path("./Assets/Models/plante/Plante_Fbx.gltf"));
//    std::vector<glm::vec3> objectPositions;
//    objectPositions.push_back(glm::vec3(-3.0, -0.5, -3.0));
//    objectPositions.push_back(glm::vec3(0.0, -0.5, -3.0));
//    objectPositions.push_back(glm::vec3(3.0, -0.5, -3.0));
//    objectPositions.push_back(glm::vec3(-3.0, -0.5, 0.0));
//    objectPositions.push_back(glm::vec3(0.0, -0.5, 0.0));
//    objectPositions.push_back(glm::vec3(3.0, -0.5, 0.0));
//    objectPositions.push_back(glm::vec3(-3.0, -0.5, 3.0));
//    objectPositions.push_back(glm::vec3(0.0, -0.5, 3.0));
//    objectPositions.push_back(glm::vec3(3.0, -0.5, 3.0));
//
//
//    // configure g-buffer framebuffer
//    // ------------------------------
//    unsigned int gBuffer;
//    glGenFramebuffers(1, &gBuffer);
//    glBindFramebuffer(GL_FRAMEBUFFER, gBuffer);
//    unsigned int gPosition, gNormal, gAlbedoSpec;
//    // position color buffer
//    glGenTextures(1, &gPosition);
//    glBindTexture(GL_TEXTURE_2D, gPosition);
//    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGBA, GL_FLOAT, NULL);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, gPosition, 0);
//    // normal color buffer
//    glGenTextures(1, &gNormal);
//    glBindTexture(GL_TEXTURE_2D, gNormal);
//    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGBA, GL_FLOAT, NULL);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, gNormal, 0);
//    // color + specular color buffer
//    glGenTextures(1, &gAlbedoSpec);
//    glBindTexture(GL_TEXTURE_2D, gAlbedoSpec);
//    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D, gAlbedoSpec, 0);
//    // tell OpenGL which color attachments we'll use (of this framebuffer) for rendering 
//    unsigned int attachments [3] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2 };
//    glDrawBuffers(3, attachments);
//    // create and attach depth buffer (renderbuffer)
//    unsigned int rboDepth;
//    glGenRenderbuffers(1, &rboDepth);
//    glBindRenderbuffer(GL_RENDERBUFFER, rboDepth);
//    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, SCR_WIDTH, SCR_HEIGHT);
//    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rboDepth);
//    // finally check if framebuffer is complete
//    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
//        std::cout << "Framebuffer not complete!" << std::endl;
//    glBindFramebuffer(GL_FRAMEBUFFER, 0);
//
//    // lighting info
//    // -------------
//    const unsigned int NR_LIGHTS = 40;
//    std::vector<glm::vec3> lightPositions;
//    std::vector<glm::vec3> lightColors;
//    srand(13);
//    for (unsigned int i = 0; i < NR_LIGHTS; i++)
//    {
//        // calculate slightly random offsets
//        float xPos = static_cast<float>(((rand() % 100) / 100.0) * 6.0 - 3.0);
//        float yPos = static_cast<float>(((rand() % 100) / 100.0) * 6.0 - 4.0);
//        float zPos = static_cast<float>(((rand() % 100) / 100.0) * 6.0 - 3.0);
//        lightPositions.push_back(glm::vec3(xPos, yPos, zPos));
//        // also calculate random color
//        float rColor = static_cast<float>(((rand() % 100) / 200.0f) + 0.5); // between 0.5 and 1.)
//        float gColor = static_cast<float>(((rand() % 100) / 200.0f) + 0.5); // between 0.5 and 1.)
//        float bColor = static_cast<float>(((rand() % 100) / 200.0f) + 0.5); // between 0.5 and 1.)
//        lightColors.push_back(glm::vec3(rColor, gColor, bColor));
//    }
//
//    // shader configuration
//    // --------------------
//    shaderLightingPass.Use();
//    shaderLightingPass.SetInt("gPosition", 0);
//    shaderLightingPass.SetInt("gNormal", 1);
//    shaderLightingPass.SetInt("gAlbedoSpec", 2);
//
//    glfwPollEvents();
//    glClearColor(backgroungColor.x, backgroungColor.y, backgroungColor.z, backgroungColor.w);
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//    // render loop
//    // -----------
//    while (!glfwWindowShouldClose(window))
//    {
//        // per-frame time logic
//        // --------------------
//        auto currentFrame = static_cast<float>(glfwGetTime());
//        deltaTime = currentFrame - lastFrame;
//        lastFrame = currentFrame;
//
//        InitImguiWindow();
//
//        // input
//        // -----
//        processInput(window);
//
//        // render
//    // ------
//
//    // 1. geometry pass: render scene's geometry/color data into gbuffer
//    // -----------------------------------------------------------------
//        glBindFramebuffer(GL_FRAMEBUFFER, gBuffer);
//        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float) SCR_WIDTH / (float) SCR_HEIGHT, 0.1f, 100.0f);
//        glm::mat4 view = camera.GetViewMatrix();
//        glm::mat4 model = glm::mat4(1.0f);
//        shaderGeometryPass.Use();
//        shaderGeometryPass.SetMat4("projection", projection);
//        shaderGeometryPass.SetMat4("view", view);
//        for (unsigned int i = 0; i < objectPositions.size(); i++)
//        {
//            model = glm::mat4(1.0f);
//            model = glm::translate(model, objectPositions [i]);
//            model = glm::scale(model, glm::vec3(0.25f));
//            shaderGeometryPass.SetMat4("model", model);
//            backpack.Draw(shaderGeometryPass);
//        }
//        glBindFramebuffer(GL_FRAMEBUFFER, 0);
//
//        // 2. lighting pass: calculate lighting by iterating over a screen filled quad pixel-by-pixel using the gbuffer's content.
//        // -----------------------------------------------------------------------------------------------------------------------
//        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//        shaderLightingPass.Use();
//        glActiveTexture(GL_TEXTURE0);
//        glBindTexture(GL_TEXTURE_2D, gPosition);
//        glActiveTexture(GL_TEXTURE1);
//        glBindTexture(GL_TEXTURE_2D, gNormal);
//        glActiveTexture(GL_TEXTURE2);
//        glBindTexture(GL_TEXTURE_2D, gAlbedoSpec);
//        // send light relevant uniforms
//        for (unsigned int i = 0; i < lightPositions.size(); i++)
//        {
//            shaderLightingPass.SetVec3("lights[" + std::to_string(i) + "].Position", lightPositions [i]);
//            shaderLightingPass.SetVec3("lights[" + std::to_string(i) + "].Color", lightColors [i]);
//            // update attenuation parameters and calculate radius
//            const float constant = 1.0f; // note that we don't send this to the shader, we assume it is always 1.0 (in our case)
//            const float linear = 0.7f;
//            const float quadratic = 1.8f;
//            shaderLightingPass.SetFloat("lights[" + std::to_string(i) + "].Linear", linear);
//            shaderLightingPass.SetFloat("lights[" + std::to_string(i) + "].Quadratic", quadratic);
//            // then calculate radius of light volume/sphere
//            const float maxBrightness = std::fmaxf(std::fmaxf(lightColors [i].r, lightColors [i].g), lightColors [i].b);
//            float radius = (-linear + std::sqrt(linear * linear - 4 * quadratic * (constant - (256.0f / 5.0f) * maxBrightness))) / (2.0f * quadratic);
//            shaderLightingPass.SetFloat("lights[" + std::to_string(i) + "].Radius", radius);
//        }
//        shaderLightingPass.SetVec3("viewPos", camera.Position);
//        // finally render quad
//        renderQuad();
//
//        // 2.5. copy content of geometry's depth buffer to default framebuffer's depth buffer
//        // ----------------------------------------------------------------------------------
//        glBindFramebuffer(GL_READ_FRAMEBUFFER, gBuffer);
//        glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0); // write to default framebuffer
//        // blit to default framebuffer. Note that this may or may not work as the internal formats of both the FBO and default framebuffer have to match.
//        // the internal formats are implementation defined. This works on all of my systems, but if it doesn't on yours you'll likely have to write to the 		
//        // depth buffer in another shader stage (or somehow see to match the default framebuffer's internal format with the FBO's internal format).
//        glBlitFramebuffer(0, 0, SCR_WIDTH, SCR_HEIGHT, 0, 0, SCR_WIDTH, SCR_HEIGHT, GL_DEPTH_BUFFER_BIT, GL_NEAREST);
//        glBindFramebuffer(GL_FRAMEBUFFER, 0);
//
//        // 3. render lights on top of scene
//        // --------------------------------
//        shaderLightBox.Use();
//        shaderLightBox.SetMat4("projection", projection);
//        shaderLightBox.SetMat4("view", view);
//        for (unsigned int i = 0; i < lightPositions.size(); i++)
//        {
//            model = glm::mat4(1.0f);
//            model = glm::translate(model, lightPositions [i]);
//            model = glm::scale(model, glm::vec3(0.125f));
//            shaderLightBox.SetMat4("model", model);
//            shaderLightBox.SetVec3("lightColor", lightColors [i]);
//            renderCube();
//        }
//
//        /*int displayW, displayH;
//        glfwGetFramebufferSize(window, &displayW, &displayH);
//        glViewport(0, 0, displayW, displayH);*/
//
//        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
//        // -------------------------------------------------------------------------------
//        glfwSwapBuffers(window);
//        glfwPollEvents();
//    }
//}
//
//GLFWwindow* InitGlfwWindow()
//{
//    // glfw window creation
//    // --------------------
//    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "RendererDemo", nullptr, nullptr);
//    if (window == nullptr)
//    {
//        std::cout << "Failed to create GLFW window" << std::endl;
//        glfwTerminate();
//        return NULL;
//    }
//    glfwMakeContextCurrent(window);
//    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
//    glfwSetCursorPosCallback(window, mouse_callback);
//    glfwSetScrollCallback(window, scroll_callback);
//
//    // tell GLFW to capture our mouse
//    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
//    //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
//
//    // glad: load all OpenGL function pointers
//    // ---------------------------------------
//    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
//    {
//        std::cout << "Failed to initialize GLAD" << std::endl;
//        return NULL;
//    }
//
//    // tell stb_image.h to flip loaded texture's on the y-axis (before loading model).
//    stbi_set_flip_vertically_on_load(false);
//
//    // configure global opengl state
//    // -----------------------------
//    glEnable(GL_DEPTH_TEST);
//
//    return window;
//}
//
//void InitImguiWindow()
//{
//    ImGuiIO& io = ImGui::GetIO(); (void) io;
//    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;   // enable keyboard controls
//    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;    // enable gamepad controls
//
//    // imgui state
//    bool show_demo_window = false;
//    bool show_another_window = false;
//    bool show_child_window_1 = true;
//    bool show_child_window_2 = true;
//    bool show_renderer_window = true;
//
//    // imgui frame
//    ImGui_ImplOpenGL3_NewFrame();
//    ImGui_ImplGlfw_NewFrame();
//    ImGui::NewFrame();
//
//    // show the demo window
//    if (show_demo_window)
//    {
//        ImGui::ShowDemoWindow(&show_demo_window);
//    }
//
//    // show a simple window
//    {
//        static float f = 0.0f;
//        static int counter = 0;
//
//        ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.
//
//        ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
//        ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
//        ImGui::Checkbox("Another Window", &show_another_window);
//
//        ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
//
//        ImGui::ColorEdit3("clear color", (float*) &backgroungColor); // Edit 3 floats representing a color
//
//        if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
//            counter++;
//        ImGui::SameLine();
//        ImGui::Text("counter = %d", counter);
//
//        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
//        ImGui::End();
//    }
//
//    // 3. Show another simple window.
//    if (show_another_window)
//    {
//        ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
//        ImGui::Text("Hello from another window!");
//        if (ImGui::Button("Close Me"))
//            show_another_window = false;
//        if (ImGui::Begin("child window 1"), &show_child_window_1)
//        {
//            ImGui::Text("child window 1");
//            ImGui::End();
//        }
//        if (ImGui::Begin("child window 2"), &show_child_window_2)
//        {
//            ImGui::Text("child window 2");
//            ImGui::End();
//        }
//        ImGui::End();
//    }
//
//    ImGui::Render();
//
//    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
//}
//
