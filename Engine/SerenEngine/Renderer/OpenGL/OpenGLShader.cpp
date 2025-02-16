#include"OpenGLShader.h"
#include"Renderer/Renderer.h"
#include"Resource/ResourceManager.h"
#include"Core/Type/Cast.h"
#include"Core/Logger/Logger.h"

#include<glad/gl.h>
#include<glm/glm.hpp>
#include<glm/gtc/type_ptr.hpp>

namespace SerenEngine {
	DEFINE_RTTI(OpenGLShader, Shader::RunTimeType)

		OpenGLShader::OpenGLShader() : mID(0)
	{
		mName = "";
		mVertexSource = "";
		mFragmentSource = "";
		mGeometrySource = "";
	}

	OpenGLShader::OpenGLShader(const char* name, const char* vertexSource, const char* fragmentSource) :
		OpenGLShader(name, vertexSource, fragmentSource, "")
	{
	}

	OpenGLShader::OpenGLShader(const char* name=nullptr, const char* vertexSource= nullptr, const char* fragmentSource= nullptr,const char* geometrySource= nullptr) :
		mName(name), mVertexSource(vertexSource), mFragmentSource(fragmentSource), mGeometrySource(geometrySource)
	{
		//uint32_t vertexShaderID, fragmentShaderID;
		//// Vertex Shader
		//vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
		//glShaderSource(vertexShaderID, 1, &vertexSource, nullptr);
		//glCompileShader(vertexShaderID);
		//// Fragment Shader
		//fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
		//glShaderSource(fragmentShaderID, 1, &fragmentSource, nullptr);
		//glCompileShader(fragmentShaderID);
		//// Shader Program
		//mID = glCreateProgram();
		//if (
		//	IsValidShader(vertexShaderID, ERendererResource::VertexShader) &&
		//	IsValidShader(fragmentShaderID, ERendererResource::FragmentShader)
		//	) {
		//	glAttachShader(mID, vertexShaderID);
		//	glAttachShader(mID, fragmentShaderID);
		//	glLinkProgram(mID);

		//	if (IsValidShader(mID, ERendererResource::Shader)) {
		//		CORE_LOG_INFO("Shader program {0} with id {1} is loaded!", mName.c_str(), mID);
		//	}
		//}

		//glDeleteShader(vertexShaderID);
		//glDeleteShader(fragmentShaderID);
		uint32_t vertexShaderID, fragmentShaderID, geometryShaderID = 0;
		bool hasGeometry = (geometrySource != nullptr && strlen(geometrySource) > 0);

		// Vertex Shader
		vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShaderID, 1, &vertexSource, nullptr);
		glCompileShader(vertexShaderID);
		// Fragment Shader
		fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShaderID, 1, &fragmentSource, nullptr);
		glCompileShader(fragmentShaderID);

		// Geometry Shader (nếu có)
		if (hasGeometry)
		{
			geometryShaderID = glCreateShader(GL_GEOMETRY_SHADER);
			glShaderSource(geometryShaderID, 1, &geometrySource, nullptr);
			glCompileShader(geometryShaderID);
		}

		// Tạo chương trình shader
		mID = glCreateProgram();
		if (IsValidShader(vertexShaderID, ERendererResource::VertexShader) &&
			IsValidShader(fragmentShaderID, ERendererResource::FragmentShader) &&
			(!hasGeometry || IsValidShader(geometryShaderID, ERendererResource::GeometryShader)))
		{
			glAttachShader(mID, vertexShaderID);
			glAttachShader(mID, fragmentShaderID);
			if (hasGeometry)
			{
				glAttachShader(mID, geometryShaderID);
			}
			glLinkProgram(mID);

			if (IsValidShader(mID, ERendererResource::Shader))
			{
				CORE_LOG_INFO("Shader program {0} with id {1} is loaded!", mName.c_str(), mID);
			}
		}

		glDeleteShader(vertexShaderID);
		glDeleteShader(fragmentShaderID);
		if (hasGeometry)
		{
			glDeleteShader(geometryShaderID);
		}
	}

	OpenGLShader::~OpenGLShader()
	{
	}

	void OpenGLShader::Release() {
		glDeleteShader(mID);
		ResourceManager::Get().FreeShader(this);
	}

	void OpenGLShader::Bind()
	{
		glUseProgram(mID);
	}

	void OpenGLShader::Unbind()
	{
		glUseProgram(0);
	}

	void OpenGLShader::SetBool(const std::string& name, bool value)
	{
		glUniform1i(glGetUniformLocation(mID, name.c_str()), StaticCast<int>(value));
	}

	void OpenGLShader::SetInt(const std::string& name, int32_t value)
	{
		glUniform1i(glGetUniformLocation(mID, name.c_str()), value);
	}

	void OpenGLShader::SetInts(const std::string& name, int32_t* value, uint32_t count)
	{
		glUniform1iv(glGetUniformLocation(mID, name.c_str()), count, value);
	}

	void OpenGLShader::SetFloat(const std::string& name, float value)
	{
		glUniform1f(glGetUniformLocation(mID, name.c_str()), value);
	}

	void OpenGLShader::SetFloats(const std::string& name, float* value, uint32_t count)
	{
		glUniform1fv(glGetUniformLocation(mID, name.c_str()), count, value);
	}

	void OpenGLShader::SetFloats2(const std::string& name, float* value, uint32_t count)
	{
		glUniform2fv(glGetUniformLocation(mID, name.c_str()), count, value);
	}

	void OpenGLShader::SetFloats4(const std::string& name, const glm::vec4& value)
	{
		GLint location = glGetUniformLocation(mID, name.c_str());
		glUniform4f(location, value.x, value.y, value.z, value.w);
	}

	void OpenGLShader::SetVector2(const std::string& name, float x, float y)
	{
		glUniform2f(glGetUniformLocation(mID, name.c_str()), x, y);
	}

	void OpenGLShader::SetVector2(const std::string& name, const glm::vec2& value)
	{
		glUniform2fv(glGetUniformLocation(mID, name.c_str()), 1, glm::value_ptr(value));
	}

	void OpenGLShader::SetVector3(const std::string& name, float x, float y, float z)
	{
		glUniform3f(glGetUniformLocation(mID, name.c_str()), x, y, z);
	}

	void OpenGLShader::SetVector3(const std::string& name, const glm::vec3& value)
	{
		glUniform3fv(glGetUniformLocation(mID, name.c_str()), 1, glm::value_ptr(value));
	}

	void OpenGLShader::SetMatrix4(const std::string& name, const glm::mat4& value)
	{

		glUniformMatrix4fv(glGetUniformLocation(mID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
	}

	bool OpenGLShader::IsValidShader(uint32_t shaderID, ERendererResource resource) {
		int32_t success;
		char info[512];

		switch (resource)
		{
		case SerenEngine::ERendererResource::VertexShader:
			glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
			if (!success) {
				glGetShaderInfoLog(shaderID, 512, nullptr, info);
				CORE_LOG_ERROR("{0} compiled failed: {1}", "Vertex Shader", info);
				return false;
			}
			break;
		case SerenEngine::ERendererResource::FragmentShader:
			glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
			if (!success) {
				glGetShaderInfoLog(shaderID, 512, nullptr, info);
				CORE_LOG_ERROR("{0} compiled failed: {1}", "Fragment Shader", info);
				return false;
			}
			break;
		case SerenEngine::ERendererResource::GeometryShader:
			glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
			if (!success) {
				glGetShaderInfoLog(shaderID, 512, nullptr, info);
				CORE_LOG_ERROR("{0} compiled failed: {1}", "Geometry Shader", info);
				return false;
			}
			break;
		case SerenEngine::ERendererResource::Shader:
			glGetProgramiv(shaderID, GL_LINK_STATUS, &success);
			if (!success) {
				glGetProgramInfoLog(shaderID, 512, nullptr, info);
				CORE_LOG_ERROR("{0} compiled failed: {1}", "Shader Program", info);
				return false;
			}
			break;
		default:
			CORE_LOG_WARN("Invalid resource");
			break;
		}

		return true;
	}
}