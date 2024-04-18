//#include <glad/glad.h>
//#include <GLFW/glfw3.h>
//
//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/type_ptr.hpp>
//
//#include <stb_image.h>
//#include <Shader.hpp>
//#include <Camera.hpp>
//#include <Model.hpp>
//#include <IMGUI_GLFW_OPENGL3.hpp>
//
//#include <iostream>
//
//using namespace Spore;
//
//void framebuffer_size_callback(GLFWwindow* window, int width, int height);
//void mouse_callback(GLFWwindow* window, double xpos, double ypos);
//void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
//
//void processInput(GLFWwindow* window);
//
//unsigned int loadTexture(const char* path);
//void render(Shader lightingShader, Shader lightCubeShader,
//            unsigned int diffuseMap, unsigned int specularMap);
//
//// settings
//const unsigned int SCR_WIDTH = 1200;
//const unsigned int SCR_HEIGHT = 900;
//
//// camera
//Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
//float lastX = SCR_WIDTH / 2.0f;
//float lastY = SCR_HEIGHT / 2.0f;
//bool firstMouse = true;
//bool hideCursor = true;
//bool cameraLock = false;
//
//// timing
//float deltaTime = 0.0f;
//float lastFrame = 0.0f;
//
//// lighting
//glm::vec3 lightPos(1.2f, 1.0f, 2.0f);
//
//unsigned int VBO, cubeVAO, lightCubeVAO;
//
//// set up vertex data (and buffer(s)) and configure vertex attributes
//    // ------------------------------------------------------------------
//float vertices [] = {
//    // positions          // normals           // texture coords
//    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
//     0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
//     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
//     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
//    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
//    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
//
//    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
//     0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
//     0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
//     0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
//    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
//    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
//
//    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
//    -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
//    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
//    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
//    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
//    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
//
//     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
//     0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
//     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
//     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
//     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
//     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
//
//    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
//     0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
//     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
//     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
//    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
//    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
//
//    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
//     0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
//     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
//     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
//    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
//    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
//};
//
//int main()
//{
//    // glfw: initialize and configure
//    // ------------------------------
//    glfwInit();
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//
//#ifdef __APPLE__
//    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
//#endif
//
//    // glfw window creation
//    // --------------------
//    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "RendererDemo", NULL, NULL);
//    if (window == NULL)
//    {
//        std::cout << "Failed to create GLFW window" << std::endl;
//        glfwTerminate();
//        return -1;
//    }
//    glfwMakeContextCurrent(window);
//    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
//    glfwSetCursorPosCallback(window, mouse_callback);
//    glfwSetScrollCallback(window, scroll_callback);
//
//    // tell GLFW to capture our mouse
//    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
//
//    // glad: load all OpenGL function pointers
//    // ---------------------------------------
//    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
//    {
//        std::cout << "Failed to initialize GLAD" << std::endl;
//        return -1;
//    }
//
//    /*ImGui::CreateContext();
//    ImGui_ImplGlfw_InitForOpenGL(window, true);
//    ImGui_ImplOpenGL3_Init("#version 130");*/
//
//    // configure global opengl state
//    // -----------------------------
//    glEnable(GL_DEPTH_TEST);
//    //glDisable(GL_DEPTH_TEST);
//
//    Shader lightingShader("./Assets/Shaders/MultipleLightsVertex.glsl", "./Assets/Shaders/MultipleLightsFragment.glsl");
//    Shader lightCubeShader("./Assets/Shaders/LightCubeVertex.glsl", "./Assets/Shaders/LightCubeFragment.glsl");
//
//    unsigned int diffuseMap = loadTexture("./Assets/Textures/plank1.png");
//    unsigned int specularMap = loadTexture("./Assets/Textures/plank1.png");
//
//    // shader configuration
//    // --------------------
//    lightingShader.Use();
//    lightingShader.SetInt("material.diffuse", 1);
//    lightingShader.SetInt("material.specular", 1);
//
//    unsigned int framebuffer;
//    unsigned int textureColorBuffer;
//
//    glGenFramebuffers(1, &framebuffer);
//    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
//
//    glGenTextures(1, &textureColorBuffer);
//    glBindTexture(GL_TEXTURE_2D, textureColorBuffer);
//    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureColorBuffer, 0);
//    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
//        std::cerr << "Framebuffer is not complete!" << std::endl;
//
//    glBindFramebuffer(GL_FRAMEBUFFER, 0);
//
//    // render loop
//    // -----------
//    while (!glfwWindowShouldClose(window))
//    {
//        // per-frame time logic
//        // --------------------
//        float currentFrame = static_cast<float>(glfwGetTime());
//        deltaTime = currentFrame - lastFrame;
//        lastFrame = currentFrame;
//
//        // input
//        // -----
//        processInput(window);
//
//        //glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
//
//        // render
//        // ------
//        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
//        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//        render(lightingShader, lightCubeShader, diffuseMap, specularMap);
//
//        //glBindFramebuffer(GL_FRAMEBUFFER, 0);
//
//        /*ImGui_ImplOpenGL3_NewFrame();
//        ImGui_ImplGlfw_NewFrame();
//        ImGui::NewFrame();
//
//        ImGui::Begin("renderer window");
//        ImGui::Image((void*) (intptr_t) textureColorBuffer, ImVec2(SCR_WIDTH, SCR_HEIGHT));
//        ImGui::End();
//
//        ImGui::Render();
//        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());*/
//
//        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
//        // -------------------------------------------------------------------------------
//        glfwSwapBuffers(window);
//        glfwPollEvents();
//    }
//
//    /*ImGui_ImplOpenGL3_Shutdown();
//    ImGui_ImplGlfw_Shutdown();
//    ImGui::DestroyContext();*/
//
//    // optional: de-allocate all resources once they've outlived their purpose:
//    // ------------------------------------------------------------------------
//    glDeleteVertexArrays(1, &cubeVAO);
//    glDeleteVertexArrays(1, &lightCubeVAO);
//    glDeleteBuffers(1, &VBO);
//
//    // glfw: terminate, clearing all previously allocated GLFW resources.
//    // ------------------------------------------------------------------
//    glfwTerminate();
//    return 0;
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
//        camera.ProcessKeyboard(DOWN, deltaTime);
//    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
//        camera.ProcessKeyboard(UP, deltaTime);
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
//        //float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
//        float yoffset = ypos - lastY; // reversed since y-coordinates go from bottom to top
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
//void render(Shader lightingShader, Shader lightCubeShader,
//            unsigned int diffuseMap, unsigned int specularMap)
//{
//    
//    // positions all containers
//    glm::vec3 cubePositions [] = {
//        glm::vec3(0.0f,  0.0f,  0.0f),
//        glm::vec3(2.0f,  5.0f, -15.0f),
//        glm::vec3(-1.5f, -2.2f, -2.5f),
//        glm::vec3(-3.8f, -2.0f, -12.3f),
//        glm::vec3(2.4f, -0.4f, -3.5f),
//        glm::vec3(-1.7f,  3.0f, -7.5f),
//        glm::vec3(1.3f, -2.0f, -2.5f),
//        glm::vec3(1.5f,  2.0f, -2.5f),
//        glm::vec3(1.5f,  0.2f, -1.5f),
//        glm::vec3(-1.3f,  1.0f, -1.5f)
//    };
//    // positions of the point lights
//    glm::vec3 pointLightPositions [] = {
//        glm::vec3(0.7f,  0.2f,  2.0f),
//        glm::vec3(0.7f,  0.2f,  20.0f),
//        glm::vec3(0.7f,  0.2f,  20.0f),
//        glm::vec3(0.7f,  0.2f,  20.0f)
//        /*glm::vec3(2.3f, -3.3f, -4.0f),
//        glm::vec3(-4.0f,  2.0f, -12.0f),
//        glm::vec3(0.0f,  0.0f, -3.0f)*/
//    };
//    // first, configure the cube's VAO (and VBO)
//    glGenVertexArrays(1, &cubeVAO);
//    glGenBuffers(1, &VBO);
//
//    glBindBuffer(GL_ARRAY_BUFFER, VBO);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//
//    glBindVertexArray(cubeVAO);
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*) 0);
//    glEnableVertexAttribArray(0);
//    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*) (3 * sizeof(float)));
//    glEnableVertexAttribArray(1);
//    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*) (6 * sizeof(float)));
//    glEnableVertexAttribArray(2);
//
//    // second, configure the light's VAO (VBO stays the same; the vertices are the same for the light object which is also a 3D cube)
//    glGenVertexArrays(1, &lightCubeVAO);
//    glBindVertexArray(lightCubeVAO);
//
//    glBindBuffer(GL_ARRAY_BUFFER, VBO);
//    // note that we update the lamp's position attribute's stride to reflect the updated buffer data
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*) 0);
//    glEnableVertexAttribArray(0);
//
//    // be sure to activate shader when setting uniforms/drawing objects
//    lightingShader.Use();
//    lightingShader.SetVec3("viewPos", camera.m_position);
//    lightingShader.SetFloat("material.shininess", 32.0f);
//
//    /*
//       Here we set all the uniforms for the 5/6 types of lights we have. We have to set them manually and index
//       the proper PointLight struct in the array to set each uniform variable. This can be done more code-friendly
//       by defining light types as classes and set their values in there, or by using a more efficient uniform approach
//       by using 'Uniform buffer objects', but that is something we'll discuss in the 'Advanced GLSL' tutorial.
//    */
//    // directional light
//    lightingShader.SetVec3("dirLight.direction", -0.2f, -1.0f, -0.3f);
//    lightingShader.SetVec3("dirLight.ambient", 0.05f, 0.05f, 0.05f);
//    lightingShader.SetVec3("dirLight.diffuse", 0.4f, 0.4f, 0.4f);
//    lightingShader.SetVec3("dirLight.specular", 0.5f, 0.5f, 0.5f);
//    // point light 1
//    lightingShader.SetVec3("pointLights[0].position", pointLightPositions [0]);
//    lightingShader.SetVec3("pointLights[0].ambient", 0.05f, 0.05f, 0.05f);
//    lightingShader.SetVec3("pointLights[0].diffuse", 0.8f, 0.8f, 0.8f);
//    lightingShader.SetVec3("pointLights[0].specular", 1.0f, 1.0f, 1.0f);
//    lightingShader.SetFloat("pointLights[0].constant", 1.0f);
//    lightingShader.SetFloat("pointLights[0].linear", 0.09f);
//    lightingShader.SetFloat("pointLights[0].quadratic", 0.032f);
//    // point light 2
//    lightingShader.SetVec3("pointLights[1].position", pointLightPositions [1]);
//    lightingShader.SetVec3("pointLights[1].ambient", 0.05f, 0.05f, 0.05f);
//    lightingShader.SetVec3("pointLights[1].diffuse", 0.8f, 0.8f, 0.8f);
//    lightingShader.SetVec3("pointLights[1].specular", 1.0f, 1.0f, 1.0f);
//    lightingShader.SetFloat("pointLights[1].constant", 1.0f);
//    lightingShader.SetFloat("pointLights[1].linear", 0.09f);
//    lightingShader.SetFloat("pointLights[1].quadratic", 0.032f);
//    // point light 3
//    lightingShader.SetVec3("pointLights[2].position", pointLightPositions [2]);
//    lightingShader.SetVec3("pointLights[2].ambient", 0.05f, 0.05f, 0.05f);
//    lightingShader.SetVec3("pointLights[2].diffuse", 0.8f, 0.8f, 0.8f);
//    lightingShader.SetVec3("pointLights[2].specular", 1.0f, 1.0f, 1.0f);
//    lightingShader.SetFloat("pointLights[2].constant", 1.0f);
//    lightingShader.SetFloat("pointLights[2].linear", 0.09f);
//    lightingShader.SetFloat("pointLights[2].quadratic", 0.032f);
//    // point light 4
//    lightingShader.SetVec3("pointLights[3].position", pointLightPositions [3]);
//    lightingShader.SetVec3("pointLights[3].ambient", 0.05f, 0.05f, 0.05f);
//    lightingShader.SetVec3("pointLights[3].diffuse", 0.8f, 0.8f, 0.8f);
//    lightingShader.SetVec3("pointLights[3].specular", 1.0f, 1.0f, 1.0f);
//    lightingShader.SetFloat("pointLights[3].constant", 1.0f);
//    lightingShader.SetFloat("pointLights[3].linear", 0.09f);
//    lightingShader.SetFloat("pointLights[3].quadratic", 0.032f);
//    // spotLight
//    lightingShader.SetVec3("spotLight.position", camera.m_position);
//    lightingShader.SetVec3("spotLight.direction", camera.m_front);
//    lightingShader.SetVec3("spotLight.ambient", 0.0f, 0.0f, 0.0f);
//    lightingShader.SetVec3("spotLight.diffuse", 1.0f, 1.0f, 1.0f);
//    lightingShader.SetVec3("spotLight.specular", 1.0f, 1.0f, 1.0f);
//    lightingShader.SetFloat("spotLight.constant", 1.0f);
//    lightingShader.SetFloat("spotLight.linear", 0.09f);
//    lightingShader.SetFloat("spotLight.quadratic", 0.032f);
//    lightingShader.SetFloat("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
//    lightingShader.SetFloat("spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));
//
//    // view/projection transformations
//    glm::mat4 projection = glm::perspective(glm::radians(camera.m_zoom), (float) SCR_WIDTH / (float) SCR_HEIGHT, 0.1f, 100.0f);
//    glm::mat4 view = camera.GetViewMatrix();
//    lightingShader.SetMat4("projection", projection);
//    lightingShader.SetMat4("view", view);
//
//    // world transformation
//    glm::mat4 model = glm::mat4(1.0f);
//    lightingShader.SetMat4("model", model);
//
//    // bind diffuse map
//    glActiveTexture(GL_TEXTURE0);
//    glBindTexture(GL_TEXTURE_2D, diffuseMap);
//    // bind specular map
//    glActiveTexture(GL_TEXTURE1);
//    glBindTexture(GL_TEXTURE_2D, specularMap);
//
//    // render containers
//    glBindVertexArray(cubeVAO);
//    for (unsigned int i = 0; i < 1; i++)
//    {
//        // calculate the model matrix for each object and pass it to shader before drawing
//        glm::mat4 model = glm::mat4(1.0f);
//        model = glm::translate(model, cubePositions [i]);
//        float angle = 20.0f * i;
//        model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
//        lightingShader.SetMat4("model", model);
//
//        glDrawArrays(GL_TRIANGLES, 0, 36);
//    }
//
//    // also draw the lamp object(s)
//    lightCubeShader.Use();
//    lightCubeShader.SetMat4("projection", projection);
//    lightCubeShader.SetMat4("view", view);
//
//    // we now draw as many light bulbs as we have point lights.
//    //glBindVertexArray(lightCubeVAO);
//    //for (unsigned int i = 0; i < 4; i++)
//    //{
//    //    model = glm::mat4(1.0f);
//    //    model = glm::translate(model, pointLightPositions [i]);
//    //    model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
//    //    lightCubeShader.SetMat4("model", model);
//    //    glDrawArrays(GL_TRIANGLES, 0, 36);
//    //}
//}
//
