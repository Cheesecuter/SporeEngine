#include <Types.hpp>
#include <Shader.hpp>
#include <Camera.hpp>
#include <Model.hpp>
#include <Object.hpp>
#include <Light.hpp>
#include <Plane.hpp>
#include <Scene.hpp>
#include <RenderPipeline.hpp>
#include <PostProcess.hpp>
#include <Window.hpp>
#include <Mouse.hpp>
#include <Keyboard.hpp>
#include <AssetsManager.hpp>
#include <IMGUI_GLFW_OPENGL3.hpp>
#include <UI.hpp>
#include <PhysicSystem.hpp>

using namespace Spore;

void Runtime(MainWindow* p_window, UI* p_ui, PhysicSystem* p_physic_system);

uint32 SCR_WIDTH = 1200;
uint32 SCR_HEIGHT = 900;
uint32 SCENE_WIDTH = SCR_WIDTH / 6 * 3;
uint32 SCENE_HEIGHT = SCR_HEIGHT / 3 * 2;

Camera editorCamera(vec3f(0.0f, 3.0f, 5.0f));

vec4f backgroungColor = vec4f(0.1f, 0.1f, 0.1f, 1.0f);

auto currentFrame = static_cast<float32>(glfwGetTime());
float32 deltaTime = 0.0f;
float32 lastFrame = 0.0f;

int32 displayW, displayH;

int main()
{
    RenderPipeline m_render_pipeline;
    MainWindow m_window(SCR_WIDTH, SCR_HEIGHT, "Spore Engine", &editorCamera, &m_render_pipeline);
    Mouse::GetInstance().Update();
    Keyboard::GetInstance();
    AssetsManager::GetInstance();
    PhysicSystem physicSystem;
    UI ui(&m_window);

    physicSystem.Init();
    ui.Init();

    stbi_set_flip_vertically_on_load(false);

    Runtime(&m_window, &ui, &physicSystem);

    ui.Terminate();
    physicSystem.Terminate();
    m_window.Terminate();

    return 0;
}

void Runtime(MainWindow* p_window, UI* p_ui, PhysicSystem* p_physic_system)
{

    uint32 step = 0;

    p_physic_system->Tick(step);

    //Shader blendingShader("./Assets/Shaders/BlendingVertex.glsl", "./Assets/Shaders/BlendingFragment.glsl");
    //Shader gBufferShader("./Assets/Shaders/GBufferVertex.glsl", "./Assets/Shaders/GBufferFragment.glsl");
    Shader modelShader("./Assets/Shaders/ModelLoadingVertex.glsl", "./Assets/Shaders/ModelLoadingFragment.glsl");
    //Shader shaderLightingPass("./Assets/Shaders/DeferredShadingVertex.glsl", "./Assets/Shaders/DeferredShadingFragment.glsl");
    //Shader shaderLightBox("./Assets/Shaders/DeferredLightBoxVertex.glsl", "./Assets/Shaders/DeferredLightBoxFragment.glsl");
    Shader gridShader("./Assets/Shaders/GridVertex.glsl", "./Assets/Shaders/GridFragment.glsl");
    Shader lightingShader("./Assets/Shaders/LightingVertex.glsl", "./Assets/Shaders/LightingFragment.glsl");
    Shader skyboxShader("./Assets/Shaders/SkyboxVertex.glsl", "./Assets/Shaders/SkyboxFragment.glsl");
    Shader shadowMappingShader("./Assets/Shaders/ShadowMappingVertex.glsl", "./Assets/Shaders/ShadowMappingFragment.glsl");
    Shader shadowMappingDepthShader("./Assets/Shaders/ShadowMappingDepthVertex.glsl", "./Assets/Shaders/ShadowMappingDepthFragment.glsl");
    Shader debugDepthQuadShader("./Assets/Shaders/DebugQuadVertex.glsl", "./Assets/Shaders/DebugQuadFragment.glsl");
    Shader stencilTestingShader("./Assets/Shaders/StencilVertex.glsl", "./Assets/Shaders/StencilFragment.glsl");
    Shader stencilSingleColorShader("./Assets/Shaders/ModelLoadingVertex.glsl", "./Assets/Shaders/StencilSingleColorFragment.glsl");
    Shader frameBuffersScreenShader("./Assets/Shaders/FrameBuffersScreenVertex.glsl", "./Assets/Shaders/FrameBuffersScreenFragment.glsl");

    Shader postProcessDefaultShader("./Assets/Shaders/FrameBuffersScreenVertex.glsl", "./Assets/Shaders/PostProcesses/DefaultPostProcessFS.glsl");
    Shader postProcessInversionShader("./Assets/Shaders/FrameBuffersScreenVertex.glsl", "./Assets/Shaders/PostProcesses/InversionPostProcessFS.glsl");
    Shader postProcessGrayscaleShader("./Assets/Shaders/FrameBuffersScreenVertex.glsl", "./Assets/Shaders/PostProcesses/GrayscalePostProcessFS.glsl");
    Shader postProcessSharpenShader("./Assets/Shaders/FrameBuffersScreenVertex.glsl", "./Assets/Shaders/PostProcesses/SharpenPostProcessFS.glsl");
    Shader postProcessBlurShader("./Assets/Shaders/FrameBuffersScreenVertex.glsl", "./Assets/Shaders/PostProcesses/BlurPostProcessFS.glsl");
    Shader postProcessEdgeDetectionShader("./Assets/Shaders/FrameBuffersScreenVertex.glsl", "./Assets/Shaders/PostProcesses/EdgeDetectionPostProcessFS.glsl");

    shadowMappingShader.Use();
    shadowMappingShader.SetInt("diffuseTexture", 0);
    shadowMappingShader.SetInt("shadowMap", 1);
    debugDepthQuadShader.Use();
    debugDepthQuadShader.SetInt("depthMap", 0);

    lightingShader.Use();
    lightingShader.SetInt("texture1", 0);

    Texture floorTexture = Texture("./Assets/Textures/default.png");
    
    float32 nearPlane = 1.0f, farPlane = 100.0f;
    mat4x4f lightProjection, lightView, lightSpaceMatrix;

    const uint32 SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;
    unsigned int depthMapFBO;
    glGenFramebuffers(1, &depthMapFBO);
    // create depth texture
    unsigned int depthMap;
    glGenTextures(1, &depthMap);
    glBindTexture(GL_TEXTURE_2D, depthMap);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    float borderColor [] = { 1.0, 1.0, 1.0, 1.0 };
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
    // attach depth texture as FBO's depth buffer
    glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    std::vector<Shader*> shaders;
    Scene* scene1 = new Scene("scene_1");
    Scene* scene2 = new Scene("scene_2");
    Light* light = new Light("obj_light");
    Plane* plane = new Plane("obj_plane");
    scene1->AddObject(light);
    scene1->AddObject(plane);

    p_physic_system->AddScene(scene1);

    p_window->m_render_pipeline->AddScene(scene1);
    p_window->m_render_pipeline->AddScene(scene2);

    p_window->m_render_pipeline->InitGrid();
    p_window->m_render_pipeline->InitSkyBox();
    p_window->m_render_pipeline->InitShadowMap();

    PostProcess* postProcessDefault = new PostProcess("Default", &postProcessDefaultShader);
    p_window->m_render_pipeline->InitPostProcesser(p_window->m_width / 6 * 4, p_window->m_height / 3 * 2, postProcessDefault);

    p_window->m_render_pipeline->GetPostProcesser()->AddPostProcess(postProcessDefault);
    PostProcess* postProcessInversion = new PostProcess("Inversion", &postProcessInversionShader);
    p_window->m_render_pipeline->GetPostProcesser()->AddPostProcess(postProcessInversion);
    PostProcess* postProcessGrayscale = new PostProcess("Grayscale", &postProcessGrayscaleShader);
    p_window->m_render_pipeline->GetPostProcesser()->AddPostProcess(postProcessGrayscale);
    PostProcess* postProcessSharpen = new PostProcess("Sharpen", &postProcessSharpenShader);
    p_window->m_render_pipeline->GetPostProcesser()->AddPostProcess(postProcessSharpen);
    PostProcess* postProcessBlur = new PostProcess("Blur", &postProcessBlurShader);
    p_window->m_render_pipeline->GetPostProcesser()->AddPostProcess(postProcessBlur);
    PostProcess* postProcessEdgeDetection = new PostProcess("Edge Detection", &postProcessEdgeDetectionShader);
    p_window->m_render_pipeline->GetPostProcesser()->AddPostProcess(postProcessEdgeDetection);

    //window_p->renderPipeline->InitGBuffer((float32) window_p->GetWindowWidth(), (float32) window_p->GetWindowHeight());
    glfwPollEvents();
    glClearColor(backgroungColor.x, backgroungColor.y, backgroungColor.z, backgroungColor.w);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    while (!glfwWindowShouldClose(p_window->m_window))
    {
        currentFrame = static_cast<float32>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        glClearColor(backgroungColor.x, backgroungColor.y, backgroungColor.z, backgroungColor.w);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        p_ui->RenderPanels(p_window);

        Keyboard::GetInstance().processInput(p_window, editorCamera, deltaTime);

        mat4f projection = glm::perspective(glm::radians(editorCamera.m_zoom),
                                            (float32) p_window->GetWindowWidth() / (float32) p_window->GetWindowHeight(),
                                            0.1f, 10000.0f);
        mat4f view = editorCamera.GetViewMatrix();
        mat4f model = mat4f(1.0f);
        p_window->m_render_pipeline->PreRender();

        /*shaders.clear();
        shaders.push_back(&shadowMappingDepthShader);
        shaders.push_back(&shadowMappingShader);
        window_p->renderPipeline->ShadowMapRender(light, shaders, &camera,
                                                  (uint32) window_p->GetWindowWidth(), (uint32) window_p->GetWindowHeight(),
                                                  projection, view, model);*/

        p_window->m_render_pipeline->SetScenePos(displayW / 6, displayH / 3);
        p_window->m_render_pipeline->SetSceneSize(displayW / 6 * 4, displayH / 3 * 2);

        if (p_window->m_render_pipeline->m_post_process_on)
        {
            p_window->m_render_pipeline->PostProcessRenderToFBO();
        }

        
        if (p_window->m_render_pipeline->m_shadow_map_on)
        {
            lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, nearPlane, farPlane);
            //lightProjection = glm::ortho(glm::radians(45.0f), (float32)SHADOW_WIDTH / (float32)SHADOW_HEIGHT, nearPlane, farPlane);
            lightView = glm::lookAt(light->GetPosition(), vec3f(0.0f), vec3f(0.0f, 1.0f, 0.0f));
            //vec3f cameraPos = camera.Position;
            //lightView = glm::lookAt(-light->GetFront() * vec3f(50) + cameraPos, vec3f(0.0f), vec3f(0.0f, 1.0f, 0.0f));
            lightSpaceMatrix = lightProjection * lightView;
            shadowMappingDepthShader.Use();
            shadowMappingDepthShader.SetMat4("lightSpaceMatrix", lightSpaceMatrix);
            //glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
            glfwGetFramebufferSize(p_window->m_window, &displayW, &displayH);
            p_window->SetWindowSize(displayW, displayH);
            glViewport(displayW / 6, displayH / 3, displayW / 6 * 4, displayH / 3 * 2);
            glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
            glClear(GL_DEPTH_BUFFER_BIT);
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, floorTexture.m_ID);
            shaders.clear();
            shaders.push_back(&shadowMappingDepthShader);
            plane->Render(shaders, &floorTexture, model);
            p_window->m_render_pipeline->Render(shaders, &editorCamera,
                                             (uint32) p_window->GetWindowWidth(), (uint32) p_window->GetWindowHeight(),
                                             projection, view, model);
            glBindFramebuffer(GL_FRAMEBUFFER, 0);

            glfwGetFramebufferSize(p_window->m_window, &displayW, &displayH);
            p_window->SetWindowSize(displayW, displayH);
            glViewport(displayW / 6, displayH / 3, displayW / 6 * 4, displayH / 3 * 2);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            shadowMappingShader.Use();
            shadowMappingShader.SetMat4("projection", projection);
            shadowMappingShader.SetMat4("view", view);
            shadowMappingShader.SetVec3("viewPos", editorCamera.m_position);
            shadowMappingShader.SetVec3("lightPos", light->GetPosition());
            shadowMappingShader.SetMat4("lightSpaceMatrix", lightSpaceMatrix);
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, floorTexture.m_ID);
            glActiveTexture(GL_TEXTURE1);
            glBindTexture(GL_TEXTURE_2D, depthMap);
            shaders.clear();
            shaders.push_back(&shadowMappingShader);
            plane->Render(shaders, &floorTexture, model);
            p_window->m_render_pipeline->Render(shaders, &editorCamera,
                                             (uint32) p_window->GetWindowWidth(), (uint32) p_window->GetWindowHeight(),
                                             projection, view, model);
            debugDepthQuadShader.Use();
            debugDepthQuadShader.SetFloat("near_plane", nearPlane);
            debugDepthQuadShader.SetFloat("far_plane", farPlane);
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, depthMap);
        }
        

        p_window->m_render_pipeline->Render(shaders, &editorCamera,
                                         (uint32) p_window->GetWindowWidth(), (uint32) p_window->GetWindowHeight(),
                                         projection, view, model);
        p_window->m_render_pipeline->RenderSkyBox(&editorCamera, projection, view);
        p_window->m_render_pipeline->RenderGrid(&editorCamera, projection, view);
        
        if (p_window->m_render_pipeline->m_post_process_on)
        {
            p_window->m_render_pipeline->UpdateSceneFBO();
            p_window->m_render_pipeline->UpdateSceneRBO();
            p_window->m_render_pipeline->PostProcessFBO();
        }

        glViewport(displayW / 6, displayH / 3, displayW / 6 * 4, displayH / 3 * 2);

        /*window_p->renderPipeline->DeferredRender(shaders, &camera,
                                                 (float32) window_p->GetWindowWidth(), (float32) window_p->GetWindowHeight(),
                                                 projection, view, model);*/


        //glfwGetFramebufferSize(window_p->window, &displayW, &displayH);
        glfwGetWindowSize(p_window->m_window, &displayW, &displayH);
        p_window->SetWindowSize(displayW, displayH);

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        
        glfwSwapBuffers(p_window->m_window);
        glfwPollEvents();
    }
}
