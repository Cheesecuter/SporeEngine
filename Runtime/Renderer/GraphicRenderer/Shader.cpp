#include <Shader.hpp>
#include <AssetsManager.hpp>

namespace Spore
{
	Shader::Shader(const char* vertexPath, const char* fragmentPath, const char* geometryPath)
	{
		// get vertex/fragment shader from the path
		std::string vertexCode;
		std::string fragmentCode;
		std::string geometryCode;
		std::ifstream vShaderFile;
		std::ifstream fShaderFile;
		std::ifstream gShaderFile;
		// ensure ifstream objects can throw exceptions
		vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		gShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		try
		{
			// open files
			vShaderFile.open(vertexPath);
			fShaderFile.open(fragmentPath);
			std::stringstream vShaderStream, fShaderStream;
			// read file's buffer contents into streams
			vShaderStream << vShaderFile.rdbuf();
			fShaderStream << fShaderFile.rdbuf();
			// close file handlers
			vShaderFile.close();
			fShaderFile.close();
			// convert stream into string
			vertexCode = vShaderStream.str();
			fragmentCode = fShaderStream.str();
			// if geometry shader path is present, also load a geometry shader
			if (geometryPath != nullptr)
			{
				gShaderFile.open(geometryPath);
				std::stringstream gShaderStream;
				gShaderStream << gShaderFile.rdbuf();
				gShaderFile.close();
				geometryCode = gShaderStream.str();
			}
		}
		catch (std::ifstream::failure e)
		{
			std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
		}
		const char* vShaderCode = vertexCode.c_str();
		const char* fShaderCode = fragmentCode.c_str();
		// compile shaders
		uint32 vertex, fragment;
		// vertex shader
		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vShaderCode, NULL);
		glCompileShader(vertex);
		CheckCompileErrors(vertex, "VERTEX");
		// fragment shader
		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fShaderCode, NULL);
		glCompileShader(fragment);
		CheckCompileErrors(fragment, "FRAGMENT");
		// if geometry shader is given, compile geometry shader
		uint32 geometry;
		if (geometryPath != nullptr)
		{
			const char* gShaderCode = geometryCode.c_str();
			geometry = glCreateShader(GL_GEOMETRY_SHADER);
			glShaderSource(geometry, 1, &gShaderCode, NULL);
			glCompileShader(geometry);
			CheckCompileErrors(geometry, "GEOMETRY");
		}
		// shader program
		ID = glCreateProgram();
		glAttachShader(ID, vertex);
		glAttachShader(ID, fragment);
		if (geometryPath != nullptr)
			glAttachShader(ID, geometry);
		glLinkProgram(ID);
		CheckCompileErrors(ID, "PROGRAM");
		// delete the shaders as they're linked into our program now and no longer necessary
		glDeleteShader(vertex);
		glDeleteShader(fragment);
		if (geometryPath != nullptr)
			glDeleteShader(geometry);

		std::string vertStr = vertexPath;
		std::string fragStr = fragmentPath;
		std::string nameS = vertStr.substr(vertStr.find_last_of('/') + 1, vertStr.size());
		std::string nameF = fragStr.substr(fragStr.find_last_of('/') + 1, fragStr.size());
		std::string nameG = "null";
		if (geometryPath != nullptr)
		{
			std::string geomStr = geometryPath;
			nameG = geomStr.substr(geomStr.find_last_of('/') + 1, geomStr.size());

		}
		identifier = nameF;
		AssetsManager::GetInstance().shaderMapper.insert(std::map<std::string, Shader*>::value_type(identifier, this));
	}

	Shader::~Shader()
	{
		AssetsManager::GetInstance().shaderMapper.erase(identifier);
	}

	void Shader::CheckCompileErrors(uint32 shader, std::string type)
	{
		int32 success;
		char infoLog [1024];
		if (type != "PROGRAM")
		{
			glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
			if (!success)
			{
				glGetShaderInfoLog(shader, 1024, NULL, infoLog);
				std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << std::endl;
			}
		}
		else
		{
			glGetProgramiv(shader, GL_LINK_STATUS, &success);
			if (!success)
			{
				glGetProgramInfoLog(shader, 1024, NULL, infoLog);
				std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << std::endl;
			}
		}
	}

	void Shader::Use() const
	{
		glUseProgram(ID);
	}
	// uniform tool functions
	void Shader::SetBool(const std::string& name, bool value) const
	{
		glUniform1i(glGetUniformLocation(ID, name.c_str()), (int32) value);
	}
	void Shader::SetInt(const std::string& name, int32 value) const
	{
		glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
	}
	void Shader::SetFloat(const std::string& name, float32 value) const
	{
		glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
	}
	// vector functions
	void Shader::SetVec2(const std::string& name, const vec2f& value) const
	{
		glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, &value [0]);
	}
	void Shader::SetVec2(const std::string& name, float32 x, float32 y) const
	{
		glUniform2f(glGetUniformLocation(ID, name.c_str()), x, y);
	}
	void Shader::SetVec3(const std::string& name, const vec3f& value) const
	{
		glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value [0]);
	}
	void Shader::SetVec3(const std::string& name, float32 x, float32 y, float32 z) const
	{
		glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
	}
	void Shader::SetVec4(const std::string& name, const vec4f& value) const
	{
		glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &value [0]);
	}
	void Shader::SetVec4(const std::string& name, float32 x, float32 y, float32 z, float32 w) const
	{
		glUniform4f(glGetUniformLocation(ID, name.c_str()), x, y, z, w);
	}
	// matrix functions
	void Shader::SetMat2(const std::string& name, const mat2f& mat) const
	{
		glUniformMatrix2fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat [0][0]);
	}
	void Shader::SetMat3(const std::string& name, const mat3f& mat) const
	{
		glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat [0][0]);
	}
	void Shader::SetMat4(const std::string& name, const mat4f& mat) const
	{
		glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat [0][0]);
	}
}