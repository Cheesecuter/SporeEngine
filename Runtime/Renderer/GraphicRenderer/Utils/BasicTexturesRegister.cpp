#include <BasicTexturesRegister.hpp>
#include <Texture.hpp>

namespace Spore
{
	BasicTexturesRegister::BasicTexturesRegister()
	{
		Texture* imageEmptyFileTexture		= new Texture("./Assets/Utils/Textures/Images/empty_file.png");
		Texture* imageFileTexture			= new Texture("./Assets/Utils/Textures/Images/file.png");
		Texture* imageFolderTexture			= new Texture("./Assets/Utils/Textures/Images/folder.png");
		Texture* imageFolderCloseTexture	= new Texture("./Assets/Utils/Textures/Images/folder_close.png");
		Texture* imageDeleteTexture			= new Texture("./Assets/Utils/Textures/Images/delete.png");
		Texture* imagePauseTexture			= new Texture("./Assets/Utils/Textures/Images/pause.png");
		Texture* imagePlayTexture			= new Texture("./Assets/Utils/Textures/Images/play.png");
		Texture* imageResetTexture			= new Texture("./Assets/Utils/Textures/Images/reset.png");
		Texture* imageSettingsTexture		= new Texture("./Assets/Utils/Textures/Images/settings.png");
		Texture* imageStopTexture			= new Texture("./Assets/Utils/Textures/Images/stop.png");
		Texture* imageAudioTexture			= new Texture("./Assets/Utils/Textures/Images/audio.png");
		Texture* imageModelTexture			= new Texture("./Assets/Utils/Textures/Images/model.png");
		Texture* defaultModelTexture		= new Texture("./Assets/Utils/Textures/default.png");

		imageEmptyFileTexture->m_utility_image		= true;
		imageFileTexture->m_utility_image			= true;
		imageFolderTexture->m_utility_image			= true;
		imageFolderCloseTexture->m_utility_image	= true;
		imageDeleteTexture->m_utility_image			= true;
		imagePauseTexture->m_utility_image			= true;
		imagePlayTexture->m_utility_image			= true;
		imageResetTexture->m_utility_image			= true;
		imageSettingsTexture->m_utility_image		= true;
		imageStopTexture->m_utility_image			= true;
		imageAudioTexture->m_utility_image			= true;
		imageModelTexture->m_utility_image			= true;
		defaultModelTexture->m_utility_image		= true;
	}

	BasicTexturesRegister::~BasicTexturesRegister()
	{

	}
}