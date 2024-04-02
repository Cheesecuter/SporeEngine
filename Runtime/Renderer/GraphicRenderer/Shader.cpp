#include <Shader.hpp>
#include <AssetsManager.hpp>

namespace Spore
{
	Shader::Shader(const char* p_vertex_path, const char* p_fragment_path, const char* p_geometry_path)
	{
		m_alpha_filter_flag = true;
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
			vShaderFile.open(p_vertex_path);
			fShaderFile.open(p_fragment_path);
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
			if (p_geometry_path != nullptr)
			{
				gShaderFile.open(p_geometry_path);
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
		if (p_geometry_path != nullptr)
		{
			const char* gShaderCode = geometryCode.c_str();
			geometry = glCreateShader(GL_GEOMETRY_SHADER);
			glShaderSource(geometry, 1, &gShaderCode, NULL);
			glCompileShader(geometry);
			CheckCompileErrors(geometry, "GEOMETRY");
		}
		// shader program
		m_ID = glCreateProgram();
		glAttachShader(m_ID, vertex);
		glAttachShader(m_ID, fragment);
		if (p_geometry_path != nullptr)
			glAttachShader(m_ID, geometry);
		glLinkProgram(m_ID);
		CheckCompileErrors(m_ID, "PROGRAM");
		// delete the shaders as they're linked into our program now and no longer necessary
		glDeleteShader(vertex);
		glDeleteShader(fragment);
		if (p_geometry_path != nullptr)
			glDeleteShader(geometry);

		std::string vertStr = p_vertex_path;
		std::string fragStr = p_fragment_path;
		std::string nameS = vertStr.substr(vertStr.find_last_of('/') + 1, vertStr.size());
		std::string nameF = fragStr.substr(fragStr.find_last_of('/') + 1, fragStr.size());
		std::string nameG = "null";
		if (p_geometry_path != nullptr)
		{
			std::string geomStr = p_geometry_path;
			nameG = geomStr.substr(geomStr.find_last_of('/') + 1, geomStr.size());

		}
		m_identifier = nameF;
		AssetsManager::GetInstance().m_shader_mapper.insert(std::map<std::string, Shader*>::value_type(m_identifier, this));
	}

	Shader::~Shader()
	{
		AssetsManager::GetInstance().m_shader_mapper.erase(m_identifier);
	}

	void Shader::CheckCompileErrors(uint32 p_shader, std::string p_type)
	{
		int32 success;
		char infoLog [1024];
		if (p_type != "PROGRAM")
		{
			glGetShaderiv(p_shader, GL_COMPILE_STATUS, &success);
			if (!success)
			{
				glGetShaderInfoLog(p_shader, 1024, NULL, infoLog);
				std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << p_type << "\n" << infoLog << std::endl;
			}
		}
		else
		{
			glGetProgramiv(p_shader, GL_LINK_STATUS, &success);
			if (!success)
			{
				glGetProgramInfoLog(p_shader, 1024, NULL, infoLog);
				std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << p_type << "\n" << infoLog << std::endl;
			}
		}
	}

	void Shader::Use() const
	{
		glUseProgram(m_ID);
	}
	// uniform tool functions
	void Shader::SetBool(const std::string& p_name, bool p_value) const
	{
		glUniform1i(glGetUniformLocation(m_ID, p_name.c_str()), (int32) p_value);
	}
	void Shader::SetInt(const std::string& p_name, int32 p_value) const
	{
		glUniform1i(glGetUniformLocation(m_ID, p_name.c_str()), p_value);
	}
	void Shader::SetFloat(const std::string& p_name, float32 p_value) const
	{
		glUniform1f(glGetUniformLocation(m_ID, p_name.c_str()), p_value);
	}
	// vector functions
	void Shader::SetVec2(const std::string& p_name, const vec2f& p_value) const
	{
		glUniform2fv(glGetUniformLocation(m_ID, p_name.c_str()), 1, &p_value [0]);
	}
	void Shader::SetVec2(const std::string& p_name, float32 p_x, float32 p_y) const
	{
		glUniform2f(glGetUniformLocation(m_ID, p_name.c_str()), p_x, p_y);
	}
	void Shader::SetVec3(const std::string& p_name, const vec3f& p_value) const
	{
		glUniform3fv(glGetUniformLocation(m_ID, p_name.c_str()), 1, &p_value [0]);
	}
	void Shader::SetVec3(const std::string& p_name, float32 p_x, float32 p_y, float32 p_z) const
	{
		glUniform3f(glGetUniformLocation(m_ID, p_name.c_str()), p_x, p_y, p_z);
	}
	void Shader::SetVec4(const std::string& p_name, const vec4f& p_value) const
	{
		glUniform4fv(glGetUniformLocation(m_ID, p_name.c_str()), 1, &p_value [0]);
	}
	void Shader::SetVec4(const std::string& p_name, float32 p_x, float32 p_y, float32 p_z, float32 p_w) const
	{
		glUniform4f(glGetUniformLocation(m_ID, p_name.c_str()), p_x, p_y, p_z, p_w);
	}
	// matrix functions
	void Shader::SetMat2(const std::string& p_name, const mat2f& p_mat) const
	{
		glUniformMatrix2fv(glGetUniformLocation(m_ID, p_name.c_str()), 1, GL_FALSE, &p_mat [0][0]);
	}
	void Shader::SetMat3(const std::string& p_name, const mat3f& p_mat) const
	{
		glUniformMatrix3fv(glGetUniformLocation(m_ID, p_name.c_str()), 1, GL_FALSE, &p_mat [0][0]);
	}
	void Shader::SetMat4(const std::string& p_name, const mat4f& p_mat) const
	{
		glUniformMatrix4fv(glGetUniformLocation(m_ID, p_name.c_str()), 1, GL_FALSE, &p_mat [0][0]);
	}
}