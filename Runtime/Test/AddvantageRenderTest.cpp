//#include <glad/glad.h>
//#define GLFW_INCLUDE_NONE
//#include <GLFW/glfw3.h>
//
//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/type_ptr.hpp>
//
//#include <stb_image.h>
//#include <Shader.hpp>
//#include <Model.hpp>
//#include <Camera.hpp>
//
//#include <iostream>
//
//using namespace Spore;
//
//void framebuffer_size_callback(GLFWwindow* window, int width, int height);
//void processInput(GLFWwindow* window);
//void mouse_callback(GLFWwindow* window, double xposIn, double yposIn);
//void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
//unsigned int loadTexture(const char* path);
//unsigned int loadCubemap(std::vector<std::string> faces);
//
//// settings
//const unsigned int SCR_WIDTH = 800;
//const unsigned int SCR_HEIGHT = 600;
//
//// camera
//Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
//float lastX = SCR_WIDTH / 2.0f;
//float lastY = SCR_HEIGHT / 2.0f;
//bool firstMouse = true;
//
//// timing
//float deltaTime = 0.0f;
//float lastFrame = 0.0f;
//
//// matrix
//glm::mat4 model;
//glm::mat4 view;
//glm::mat4 projection;
//
//// lighting
//glm::vec3 lightPos(1.2f, 1.0f, 2.0f);
//
//unsigned int EBO;
//unsigned int cubeVBO, planeVBO, transparentVBO, quadVBO, skyboxVBO;
//unsigned int cubeVAO, planeVAO, transparentVAO, quadVAO, skyboxVAO;
//
///*
//	Remember: to specify vertices in a counter-clockwise winding order you need to visualize the triangle
//	as if you're in front of the triangle and from that point of view, is where you set their order.
//
//	To define the order of a triangle on the right side of the cube for example, you'd imagine yourself looking
//	straight at the right side of the cube, and then visualize the triangle and make sure their order is specified
//	in a counter-clockwise order. This takes some practice, but try visualizing this yourself and see that this
//	is correct.
//*/
//
//float cubeVertices [] = {
//	// Back face
//	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, // Bottom-left
//	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right
//	 0.5f, -0.5f, -0.5f,  1.0f, 0.0f, // bottom-right         
//	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right
//	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, // bottom-left
//	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // top-left
//	// Front face
//	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-left
//	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // bottom-right
//	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f, // top-right
//	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f, // top-right
//	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f, // top-left
//	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-left
//	// Left face
//	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-right
//	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-left
//	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-left
//	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-left
//	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-right
//	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-right
//	// Right face
//	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-left
//	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-right
//	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right         
//	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-right
//	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-left
//	 0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-left     
//	// Bottom face
//	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // top-right
//	 0.5f, -0.5f, -0.5f,  1.0f, 1.0f, // top-left
//	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // bottom-left
//	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // bottom-left
//	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-right
//	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // top-right
//	// Top face
//	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // top-left
//	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // bottom-right
//	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right     
//	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // bottom-right
//	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // top-left
//	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f  // bottom-left        
//};
//
//float planeVertices [] = {
//	// positions          // texture Coords (note we set these higher than 1 (together with GL_REPEAT as texture wrapping mode). this will cause the floor texture to repeat)
//	 5.0f, -0.5f,  5.0f,  2.0f, 0.0f,
//	-5.0f, -0.5f, -5.0f,  0.0f, 2.0f,
//	-5.0f, -0.5f,  5.0f,  0.0f, 0.0f,
//
//	 5.0f, -0.5f,  5.0f,  2.0f, 0.0f,
//	 5.0f, -0.5f, -5.0f,  2.0f, 2.0f,
//	-5.0f, -0.5f, -5.0f,  0.0f, 2.0f
//};
//
//float transparentVertices [] = {
//	// positions         // texture Coords (swapped y coordinates because texture is flipped upside down)
//	0.0f,  0.5f,  0.0f,  0.0f,  0.0f,
//	0.0f, -0.5f,  0.0f,  0.0f,  1.0f,
//	1.0f, -0.5f,  0.0f,  1.0f,  1.0f,
//
//	0.0f,  0.5f,  0.0f,  0.0f,  0.0f,
//	1.0f, -0.5f,  0.0f,  1.0f,  1.0f,
//	0.0f, -0.5f,  0.0f,  0.0f,  1.0f,
//
//	0.0f,  0.5f,  0.0f,  0.0f,  0.0f,
//	1.0f,  0.5f,  0.0f,  1.0f,  0.0f,
//	1.0f, -0.5f,  0.0f,  1.0f,  1.0f,
//
//	0.0f,  0.5f,  0.0f,  0.0f,  0.0f,
//	1.0f, -0.5f,  0.0f,  1.0f,  1.0f,
//	1.0f,  0.5f,  0.0f,  1.0f,  0.0f
//};
//
//float quadVertices [] = { // vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
//	// positions   // texCoords
//	-1.0f,  1.0f,  0.0f, 1.0f,
//	-1.0f, -1.0f,  0.0f, 0.0f,
//	 1.0f, -1.0f,  1.0f, 0.0f,
//
//	-1.0f,  1.0f,  0.0f, 1.0f,
//	 1.0f, -1.0f,  1.0f, 0.0f,
//	 1.0f,  1.0f,  1.0f, 1.0f
//};
//
//float skyboxVertices [] = {
//	// positions          
//	-1.0f,  1.0f, -1.0f,
//	-1.0f, -1.0f, -1.0f,
//	 1.0f, -1.0f, -1.0f,
//	 1.0f, -1.0f, -1.0f,
//	 1.0f,  1.0f, -1.0f,
//	-1.0f,  1.0f, -1.0f,
//
//	-1.0f, -1.0f,  1.0f,
//	-1.0f, -1.0f, -1.0f,
//	-1.0f,  1.0f, -1.0f,
//	-1.0f,  1.0f, -1.0f,
//	-1.0f,  1.0f,  1.0f,
//	-1.0f, -1.0f,  1.0f,
//
//	 1.0f, -1.0f, -1.0f,
//	 1.0f, -1.0f,  1.0f,
//	 1.0f,  1.0f,  1.0f,
//	 1.0f,  1.0f,  1.0f,
//	 1.0f,  1.0f, -1.0f,
//	 1.0f, -1.0f, -1.0f,
//
//	-1.0f, -1.0f,  1.0f,
//	-1.0f,  1.0f,  1.0f,
//	 1.0f,  1.0f,  1.0f,
//	 1.0f,  1.0f,  1.0f,
//	 1.0f, -1.0f,  1.0f,
//	-1.0f, -1.0f,  1.0f,
//
//	-1.0f,  1.0f, -1.0f,
//	 1.0f,  1.0f, -1.0f,
//	 1.0f,  1.0f,  1.0f,
//	 1.0f,  1.0f,  1.0f,
//	-1.0f,  1.0f,  1.0f,
//	-1.0f,  1.0f, -1.0f,
//
//	-1.0f, -1.0f, -1.0f,
//	-1.0f, -1.0f,  1.0f,
//	 1.0f, -1.0f, -1.0f,
//	 1.0f, -1.0f, -1.0f,
//	-1.0f, -1.0f,  1.0f,
//	 1.0f, -1.0f,  1.0f
//};
//
//// transparent window locations
//  // --------------------------------
//std::vector<glm::vec3> windows
//{
//	glm::vec3(-0.5f, 0.0f, -0.5f),
//	glm::vec3(-0.5f, 0.0f, 0.5f),
//	glm::vec3(0.5f, 0.0f, -0.5f),
//	glm::vec3(0.5f, 0.0f, 0.5f)
//};
//
//int main()
//{
//	// glfw: initialize and configure
//	// ------------------------------
//	glfwInit();
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//
//#ifdef __APPLE__
//	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
//#endif
//
//	// glfw window creation
//	// --------------------
//	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "RendererDemo", NULL, NULL);
//	if (window == NULL)
//	{
//		std::cout << "Failed to create GLFW window" << std::endl;
//		glfwTerminate();
//		return -1;
//	}
//	glfwMakeContextCurrent(window);
//	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
//	glfwSetCursorPosCallback(window, mouse_callback);
//	glfwSetScrollCallback(window, scroll_callback);
//	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
//
//	// glad: load all OpenGL function pointers
//	// ---------------------------------------
//	if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
//	{
//		std::cout << "Failed to initialize GLAD" << std::endl;
//		return -1;
//	}
//
//	// configure global opengl state
//	glEnable(GL_DEPTH_TEST);
//	glEnable(GL_BLEND);
//	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//	glEnable(GL_CULL_FACE);
//	// always pass the depth test (same effect as glDisable(GL_DEPTH_TEST))))
//	//glDepthFunc(GL_ALWAYS);
//	glDepthFunc(GL_LESS);
//	//glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
//	//glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
//
//	// build and compile our shader program
//	// ------------------------------------
//	Shader shader("./Assets/Shaders/FrameBuffersVertex.glsl", "./Assets/Shaders/FrameBuffersFragment.glsl");
//	Shader screenShader("./Assets/Shaders/FrameBuffersScreenVertex.glsl", "./Assets/Shaders/FrameBuffersScreenFragment.glsl");
//	Shader skyboxShader("./Assets/Shaders/SkyboxVertex.glsl", "./Assets/Shaders/SkyboxFragment.glsl");
//
//	glm::vec3 translations [100];
//	int index = 0;
//	float offsetX = 5.0f, offsetY, offsetZ;
//	for (int y = -10; y < 10; y += 2)
//	{
//		offsetY = (float) y / 10.0f + offsetX;
//		offsetZ = (float) y / 10.0f + offsetX;
//		for (int x = -10; x < 10; x += 2)
//		{
//			glm::vec3 translation;
//			translation.x = (float) x / 10.0f + offsetX;
//			translation.y = (float) y / 10.0f + offsetX;
//			translation.z = (float) offsetZ / 10.0f + offsetX;
//			translations [index++] = translation;
//			offsetZ++;
//		}
//	}
//
//	// cube VAO
//	glGenVertexArrays(1, &cubeVAO);
//	glGenBuffers(1, &cubeVBO);
//	glBindVertexArray(cubeVAO);
//	glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), &cubeVertices, GL_STATIC_DRAW);
//	glEnableVertexAttribArray(0);
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*) 0);
//	glEnableVertexAttribArray(1);
//	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*) (3 * sizeof(float)));
//	glBindVertexArray(0);
//	// plane VAO
//	glGenVertexArrays(1, &planeVAO);
//	glGenBuffers(1, &planeVBO);
//	glBindVertexArray(planeVAO);
//	glBindBuffer(GL_ARRAY_BUFFER, planeVBO);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices), &planeVertices, GL_STATIC_DRAW);
//	glEnableVertexAttribArray(0);
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*) 0);
//	glEnableVertexAttribArray(1);
//	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*) (3 * sizeof(float)));
//	glBindVertexArray(0);
//	// transparent VAO
//	glGenVertexArrays(1, &transparentVAO);
//	glGenBuffers(1, &transparentVBO);
//	glBindVertexArray(transparentVAO);
//	glBindBuffer(GL_ARRAY_BUFFER, transparentVBO);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(transparentVertices), transparentVertices, GL_STATIC_DRAW);
//	glEnableVertexAttribArray(0);
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*) 0);
//	glEnableVertexAttribArray(1);
//	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*) (3 * sizeof(float)));
//	glBindVertexArray(0);
//	// screen quad VAO
//	glGenVertexArrays(1, &quadVAO);
//	glGenBuffers(1, &quadVBO);
//	glBindVertexArray(quadVAO);
//	glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
//	glEnableVertexAttribArray(0);
//	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*) 0);
//	glEnableVertexAttribArray(1);
//	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*) (2 * sizeof(float)));
//	// skybox VAO
//	glGenVertexArrays(1, &skyboxVAO);
//	glGenBuffers(1, &skyboxVBO);
//	glBindVertexArray(skyboxVAO);
//	glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
//	glEnableVertexAttribArray(0);
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*) 0);
//
//	// load textures
//	unsigned int cubeTexture = loadTexture("./Assets/Textures/elem2.png");
//	unsigned int floorTexture = loadTexture("./Assets/Textures/cobblestone.png");
//	unsigned int transparentTexture = loadTexture("./Assets/Textures/sapling_oak.png");
//	std::vector<std::string> faces {
//		"./Assets/Textures/sky/right1.jpg",
//		"./Assets/Textures/sky/left1.jpg",
//		"./Assets/Textures/sky/top1.jpg",
//		"./Assets/Textures/sky/bottom1.jpg",
//		"./Assets/Textures/sky/front1.jpg",
//		"./Assets/Textures/sky/back1.jpg",
//	};
//	/*std::vector<std::string> faces {
//		"./assets/textures/skybox/right.jpg",
//		"./assets/textures/skybox/left.jpg",
//		"./assets/textures/skybox/top.jpg",
//		"./assets/textures/skybox/bottom.jpg",
//		"./assets/textures/skybox/front.jpg",
//		"./assets/textures/skybox/back.jpg",
//	};*/
//	unsigned int cubemapTexture = loadCubemap(faces);
//
//	// render container
//	shader.Use();
//	shader.SetInt("texture1", 0);
//	for (unsigned int i = 0; i < 100; i++)
//	{
//		std::stringstream ss;
//		std::string index;
//		ss << i;
//		index = ss.str();
//		shader.SetVec3(("offsets[" + index + "]").c_str(), translations [i]);
//	}
//
//	screenShader.Use();
//	screenShader.SetInt("screenTexture", 0);
//
//	skyboxShader.Use();
//	skyboxShader.SetInt("skybox", 0);
//
//	unsigned int framebuffer;
//	glGenFramebuffers(1, &framebuffer);
//	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
//	unsigned int textureColorBuffer;
//	glGenTextures(1, &textureColorBuffer);
//	glBindTexture(GL_TEXTURE_2D, textureColorBuffer);
//
//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 800, 600, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//
//	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureColorBuffer, 0);
//
//	unsigned int RBO;
//	glGenRenderbuffers(1, &RBO);
//	glBindRenderbuffer(GL_RENDERBUFFER, RBO);
//	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, 800, 600);
//	glBindRenderbuffer(GL_RENDERBUFFER, 0);
//	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, RBO);
//	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
//		std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete! " << std::endl;
//	glBindFramebuffer(GL_FRAMEBUFFER, 0);
//
//	// render loop
//	// -----------
//	while (!glfwWindowShouldClose(window))
//	{
//		// per-frame time logic
//		float currentFrame = glfwGetTime();
//		deltaTime = currentFrame - lastFrame;
//		lastFrame = currentFrame;
//
//		// input
//		// -----
//		processInput(window);
//
//		std::map<float, glm::vec3> sorted;
//		for (unsigned int i = 0; i < windows.size(); i++)
//		{
//			float distance = glm::length(camera.Position - windows [i]);
//			sorted [distance] = windows [i];
//		}
//
//		// render
//		// ------
//		
//		glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
//		glEnable(GL_DEPTH_TEST);
//
//		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
//		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//		// draw objects
//		shader.Use();
//		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float) SCR_WIDTH / (float) SCR_HEIGHT, 0.1f, 100.0f);
//		glm::mat4 view = camera.GetViewMatrix();
//		glm::mat4 model = glm::mat4(1.0f);
//		shader.SetMat4("projection", projection);
//		shader.SetMat4("view", view);
//		// cubes
//		glBindVertexArray(cubeVAO);
//		glActiveTexture(GL_TEXTURE0);
//		glBindTexture(GL_TEXTURE_2D, cubeTexture);
//		model = glm::translate(model, glm::vec3(-1.0f, 3.0f, -1.0f));
//		//model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
//		shader.SetMat4("model", model);
//		//glDrawArrays(GL_TRIANGLES, 0, 36);
//		glDrawArraysInstanced(GL_TRIANGLES, 0, 36, 100);
//		/*model = glm::mat4(1.0f);
//		model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
//		shader.setMat4("model", model);
//		glDrawArrays(GL_TRIANGLES, 0, 36);*/
//		// floor
//		glBindVertexArray(planeVAO);
//		glBindTexture(GL_TEXTURE_2D, floorTexture);
//		model = glm::mat4(1.0f);
//		shader.SetMat4("model", model);
//		glDrawArrays(GL_TRIANGLES, 0, 6);
//		// windows (from furthest to nearest)
//		glBindVertexArray(transparentVAO);
//		glBindTexture(GL_TEXTURE_2D, transparentTexture);
//		/*for (std::map<float, glm::vec3>::reverse_iterator it = sorted.rbegin(); it != sorted.rend(); ++it)
//		{
//			model = glm::mat4(1.0f);
//			model = glm::translate(model, it->second);
//			shader.setMat4("model", model);
//			glDrawArrays(GL_TRIANGLES, 0, 12);
//		}*/
//		/*model = glm::mat4(1.0f);
//		shader.setMat4("model", model);
//		glDrawArraysInstanced(GL_TRIANGLES, 0, 6, 100);*/
//
//		//draw skybox at last
//		// change depth function so depth test passes when values are equal to depth buffer's content
//		glDepthFunc(GL_LEQUAL);
//		skyboxShader.Use();
//		// remove translation from the view matrix
//		view = glm::mat4(glm::mat3(camera.GetViewMatrix()));
//		skyboxShader.SetMat4("view", view);
//		skyboxShader.SetMat4("projection", projection);
//		//skybox cube
//		glBindVertexArray(skyboxVAO);
//		glActiveTexture(GL_TEXTURE0);
//		glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
//		glDrawArrays(GL_TRIANGLES, 0, 36);
//		glBindVertexArray(0);
//		// set depth function back to default
//		glDepthFunc(GL_LESS);
//
//		glBindFramebuffer(GL_FRAMEBUFFER, 0);
//		glDisable(GL_DEPTH_TEST);
//
//		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
//		glClear(GL_COLOR_BUFFER_BIT);
//
//		screenShader.Use();
//		glBindVertexArray(quadVAO);
//		glBindTexture(GL_TEXTURE_2D, textureColorBuffer);
//		glDrawArrays(GL_TRIANGLES, 0, 6);
//
//		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
//		// -------------------------------------------------------------------------------
//		glfwSwapBuffers(window);
//		glfwPollEvents();
//	}
//
//	// optional: de-allocate all resources once they've outlived their purpose
//	// -----------------------------------------------------------------------
//	glDeleteVertexArrays(1, &cubeVAO);
//	glDeleteVertexArrays(1, &planeVAO);
//	glDeleteVertexArrays(1, &transparentVAO);
//	glDeleteVertexArrays(1, &quadVAO);
//	glDeleteVertexArrays(1, &skyboxVAO);
//	glDeleteBuffers(1, &cubeVBO);
//	glDeleteBuffers(1, &planeVBO);
//	glDeleteBuffers(1, &transparentVBO);
//	glDeleteBuffers(1, &quadVBO);
//	glDeleteBuffers(1, &skyboxVBO);
//	glDeleteRenderbuffers(1, &RBO);
//	glDeleteFramebuffers(1, &framebuffer);
//
//	// glfw: terminate, clearing all previously allocated GLFW resources.
//	// ------------------------------------------------------------------
//	glfwTerminate();
//	return 0;
//}
//
//// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
//// ---------------------------------------------------------------------------------------------------------
//void processInput(GLFWwindow* window)
//{
//	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
//		glfwSetWindowShouldClose(window, true);
//
//	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
//	{
//		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
//			camera.ProcessKeyboard(FORWARD, deltaTime * 2);
//		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
//			camera.ProcessKeyboard(BACKWARD, deltaTime * 2);
//		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
//			camera.ProcessKeyboard(LEFT, deltaTime * 2);
//		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
//			camera.ProcessKeyboard(RIGHT, deltaTime * 2);
//		if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
//			camera.ProcessKeyboard(UP, deltaTime * 2);
//		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
//			camera.ProcessKeyboard(DOWN, deltaTime * 2);
//	}
//	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
//		camera.ProcessKeyboard(FORWARD, deltaTime);
//	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
//		camera.ProcessKeyboard(BACKWARD, deltaTime);
//	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
//		camera.ProcessKeyboard(LEFT, deltaTime);
//	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
//		camera.ProcessKeyboard(RIGHT, deltaTime);
//	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
//		camera.ProcessKeyboard(UP, deltaTime);
//	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
//		camera.ProcessKeyboard(DOWN, deltaTime);
//}
//
//// glfw: whenever the window size changed (by OS or user resize) this callback function executes
//// ---------------------------------------------------------------------------------------------
//void framebuffer_size_callback(GLFWwindow* window, int width, int height)
//{
//	// make sure the viewport matches the new window dimensions; note that width and 
//	// height will be significantly larger than specified on retina displays.
//	glViewport(0, 0, width, height);
//}
//
//void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
//{
//	float xpos = static_cast<float>(xposIn);
//	float ypos = static_cast<float>(yposIn);
//
//	if (firstMouse)
//	{
//		lastX = xpos;
//		lastY = ypos;
//		firstMouse = false;
//	}
//
//	float xoffset = xpos - lastX;
//	float yoffset = lastY - ypos;
//	lastX = xpos;
//	lastY = ypos;
//
//	camera.ProcessMouseMovement(xoffset, yoffset);
//}
//
//void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
//{
//	camera.ProcessMouseScroll(static_cast<float>(yoffset));
//}
//
//unsigned int loadTexture(const char* path)
//{
//	unsigned int textureID;
//	glGenTextures(1, &textureID);
//
//	int width, height, nrComponents;
//	unsigned char* data = stbi_load(path, &width, &height, &nrComponents, 0);
//	if (data)
//	{
//		GLenum format = GL_RED;
//		if (nrComponents == 1)
//			format = GL_RED;
//		else if (nrComponents == 3)
//			format = GL_RGB;
//		else if (nrComponents == 4)
//			format = GL_RGBA;
//
//		glBindTexture(GL_TEXTURE_2D, textureID);
//		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
//		glGenerateMipmap(GL_TEXTURE_2D);
//
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//
//		stbi_image_free(data);
//	}
//	else
//	{
//		std::cout << "Texture failed to load at path: " << path << std::endl;
//		stbi_image_free(data);
//	}
//
//	return textureID;
//}
//
//// loads a cubemap texture from 6 individual texture faces
//// order:
//// +X (right)
//// -X (left)
//// +Y (top)
//// -Y (bottom)
//// +Z (front)
//// -Z (back)
//// -------------------------------------------------------
//unsigned int loadCubemap(std::vector<std::string> faces)
//{
//	unsigned int textureID;
//	glGenTextures(1, &textureID);
//	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
//
//	int width, height, nrComponents;
//	for (unsigned int i = 0; i < faces.size(); i++)
//	{
//		unsigned char* data = stbi_load(faces [i].c_str(), &width, &height, &nrComponents, 0);
//		if (data)
//		{
//			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
//			stbi_image_free(data);
//		}
//		else
//		{
//			std::cout << "Cubemap texture failed to load at path: " << faces [i] << std::endl;
//			stbi_image_free(data);
//		}
//	}
//	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
//	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
//	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
//
//	return textureID;
//}