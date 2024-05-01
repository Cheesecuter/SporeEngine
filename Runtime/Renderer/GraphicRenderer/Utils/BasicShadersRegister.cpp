#include <BasicShadersRegister.hpp>

namespace Spore
{
	BasicShadersRegister::BasicShadersRegister()
	{
        Shader* gBufferShader = new Shader("./Assets/Shaders/GBufferVertex.glsl", "./Assets/Shaders/GBufferFragment.glsl");
        Shader* modelShader = new Shader("./Assets/Shaders/ModelLoadingVertex.glsl", "./Assets/Shaders/ModelLoadingFragment.glsl");
        Shader* shaderLightingPassShader = new Shader("./Assets/Shaders/DeferredShadingVertex.glsl", "./Assets/Shaders/DeferredShadingFragment.glsl");
        shaderLightingPassShader->Use();
        shaderLightingPassShader->SetInt("gPosition", 0);
        shaderLightingPassShader->SetInt("gNormal", 1);
        shaderLightingPassShader->SetInt("gAlbedoSpec", 2);
        Shader* shaderLightBoxShader = new Shader("./Assets/Shaders/DeferredLightBoxVertex.glsl", "./Assets/Shaders/DeferredLightBoxFragment.glsl");
        Shader* gridShader = new Shader("./Assets/Shaders/GridVertex.glsl", "./Assets/Shaders/GridFragment.glsl");
        Shader* lightingShader = new Shader("./Assets/Shaders/LightingVertex.glsl", "./Assets/Shaders/LightingFragment.glsl");
        lightingShader->Use();
        lightingShader->SetInt("texture1", 0);
        Shader* multipleLightsShader = new Shader("./Assets/Shaders/MultipleLightsVertex.glsl", "./Assets/Shaders/MultipleLightsFragment.glsl");
        multipleLightsShader->Use();
        multipleLightsShader->SetInt("material.diffuse", 1);
        multipleLightsShader->SetInt("material.specular", 1);
        Shader* skyboxShader = new Shader("./Assets/Shaders/SkyboxVertex.glsl", "./Assets/Shaders/SkyboxFragment.glsl");
        Shader* shadowMappingShader = new Shader("./Assets/Shaders/ShadowMappingVertex.glsl", "./Assets/Shaders/ShadowMappingFragment.glsl");
        Shader* shadowMappingDepthShader = new Shader("./Assets/Shaders/ShadowMappingDepthVertex.glsl", "./Assets/Shaders/ShadowMappingDepthFragment.glsl");
        Shader* debugDepthQuadShader = new Shader("./Assets/Shaders/DebugQuadVertex.glsl", "./Assets/Shaders/DebugQuadFragment.glsl");
        Shader* stencilTestingShader = new Shader("./Assets/Shaders/StencilVertex.glsl", "./Assets/Shaders/StencilFragment.glsl");
        Shader* stencilSingleColorShader = new Shader("./Assets/Shaders/ModelLoadingVertex.glsl", "./Assets/Shaders/StencilSingleColorFragment.glsl");
        Shader* frameBuffersScreenShader = new Shader("./Assets/Shaders/FrameBuffersScreenVertex.glsl", "./Assets/Shaders/FrameBuffersScreenFragment.glsl");
        Shader* normalMappingShader = new Shader("./Assets/Shaders/NormalMappingVertex.glsl", "./Assets/Shaders/NormalMappingFragment.glsl");
        //Shader* voronoiNoiseShader = new Shader("./Assets/Shaders/VoronoiNoiseVertex.glsl", "./Assets/Shaders/VoronoiNoiseFragment.glsl");
        //Shader* sobelEdgeShader = new Shader("./Assets/Shaders/SobelEdgeShadingVertex.glsl", "./Assets/Shaders/SobelEdgeShadingFragment.glsl");
    }

	BasicShadersRegister::~BasicShadersRegister()
	{

	}
}