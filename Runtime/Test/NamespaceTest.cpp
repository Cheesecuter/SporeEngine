//#include <Types.hpp>
//#include <Shader.hpp>
//#include <Camera.hpp>
//#include <Model.hpp>
//#include <Object.hpp>
//#include <Light.hpp>
//#include <Scene.hpp>
//#include <RenderPipeline.hpp>
//#include <Window.hpp>
//#include <Mouse.hpp>
//#include <Keyboard.hpp>
//#include <AssetsManager.hpp>
//#include <IMGUI_GLFW_OPENGL3.hpp>
//#include <UI.hpp>
//
//using namespace Spore;
//
//void render(MainWindow* window_p, UI* ui_p);
//
//// settings
//uint32 SCR_WIDTH = 1200;
//uint32 SCR_HEIGHT = 900;
//
//// camera
//Camera camera(vec3f(0.0f, 3.0f, 5.0f));
////vec4f backgroungColor = vec4f(0.725f, 0.725f, 0.725f, 1.0f);
//vec4f backgroungColor = vec4f(0.1f, 0.1f, 0.1f, 1.0f);
//
//// timing
//auto currentFrame = static_cast<float32>(glfwGetTime());
//float32 deltaTime = 0.0f;
//float32 lastFrame = 0.0f;
//
//int main()
//{
//    RenderPipeline renderPipeline;
//    MainWindow window(SCR_WIDTH, SCR_HEIGHT, "Spore Engine", &camera, &renderPipeline);
//    Mouse::GetInstance().Update();
//    Keyboard::GetInstance();
//    AssetsManager::GetInstance();
//
//    UI ui(&window);
//    //ui.InitImGui(&window);
//
//    stbi_set_flip_vertically_on_load(false);
//
//    render(&window, &ui);
//
//    ui.UITerminate();
//    window.WindowTerminate();
//
//    return 0;
//}
//
//void render(MainWindow* window_p, UI* ui_p)
//{
//    // build and compile shaders
//    // -------------------------
//    //Shader blendingShader("./Assets/Shaders/BlendingVertex.glsl", "./Assets/Shaders/BlendingFragment.glsl");
//    //Shader gBufferShader("./Assets/Shaders/GBufferVertex.glsl", "./Assets/Shaders/GBufferFragment.glsl");
//    Shader modelShader("./Assets/Shaders/ModelLoadingVertex.glsl", "./Assets/Shaders/ModelLoadingFragment.glsl");
//    //Shader shaderLightingPass("./Assets/Shaders/DeferredShadingVertex.glsl", "./Assets/Shaders/DeferredShadingFragment.glsl");
//    //Shader shaderLightBox("./Assets/Shaders/DeferredLightBoxVertex.glsl", "./Assets/Shaders/DeferredLightBoxFragment.glsl");
//    Shader gridShader("./Assets/Shaders/GridVertex.glsl", "./Assets/Shaders/GridFragment.glsl");
//    //Shader lightingShader("./Assets/Shaders/LightingVertex.glsl", "./Assets/Shaders/LightingFragment.glsl");
//    Shader skyboxShader("./Assets/Shaders/SkyboxVertex.glsl", "./Assets/Shaders/SkyboxFragment.glsl");
//
//    //lightingShader.Use();
//    //lightingShader.SetInt("texture1", 0);
//
//    std::vector<Shader> shaders;
//
//    // load models
//    // -----------
//    std::shared_ptr<Scene> scene = std::make_shared<Scene>("scene1");
//    //std::shared_ptr<Light> light = std::make_shared<Light>("obj_light");
//    //scene->AddObject(light);
//    window_p->renderPipeline->AddScene(scene);
//
//    window_p->renderPipeline->InitSkyBox();
//    //window_p->renderPipeline->InitGBuffer((float32) window_p->GetWindowWidth(), (float32) window_p->GetWindowHeight());
//    glfwPollEvents();
//    glClearColor(backgroungColor.x, backgroungColor.y, backgroungColor.z, backgroungColor.w);
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//    // render loop
//    // -----------
//    while (!glfwWindowShouldClose(window_p->window))
//    {
//        currentFrame = static_cast<float32>(glfwGetTime());
//        deltaTime = currentFrame - lastFrame;
//        lastFrame = currentFrame;
//
//        glClearColor(backgroungColor.x, backgroungColor.y, backgroungColor.z, backgroungColor.w);
//        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//        ImGui_ImplOpenGL3_NewFrame();
//        ImGui_ImplGlfw_NewFrame();
//        ImGui::NewFrame();
//
//        //ui->ShowDemoWindow();
//        ui_p->InitPanels(window_p);
//
//        Keyboard::GetInstance().processInput(window_p, camera, deltaTime);
//        
//        // render
//        // ------
//
//        mat4f projection = glm::perspective(glm::radians(camera.Zoom), 
//                                            (float32) window_p->GetWindowWidth() / (float32) window_p->GetWindowHeight(), 
//                                            0.1f, 10000.0f);
//        mat4f view = camera.GetViewMatrix();
//        mat4f model = mat4f(1.0f);
//
//        window_p->renderPipeline->Render(shaders, &camera,
//                                         (float32) window_p->GetWindowWidth(), (float32) window_p->GetWindowHeight(),
//                                         projection, view, model);
//        window_p->renderPipeline->RenderSkyBox(&camera, projection, view);
//        window_p->renderPipeline->RenderGrid(&camera, projection, view);
//        /*window_p->renderPipeline->DeferredRender(shaders, &camera,
//                                                 (float32) window_p->GetWindowWidth(), (float32) window_p->GetWindowHeight(),
//                                                 projection, view, model);*/
//
//
//        int32 displayW, displayH;
//        glfwGetFramebufferSize(window_p->window, &displayW, &displayH);
//        window_p->SetWindowSize(displayW, displayH);
//        glViewport(displayW / 6, displayH / 3, displayW / 6 * 4, displayH / 3 * 2);
//        ImGui::Render();
//        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
//        glfwSwapBuffers(window_p->window);
//        glfwPollEvents();
//    }
//}
//
