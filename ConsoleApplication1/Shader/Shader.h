#pragma once

#include <string>

#include <GL/glew.h>

struct MaterialLocations {
	GLuint SpecularIntesityLocation;
	GLuint ShininessLocation;
};

struct LightLocations {
	GLuint ColorLocation;
	GLuint AmbientIntesityLocation;
	GLuint DiffuseIntesityLocation;
};

struct DirectionalLightLocations {
	LightLocations ULightLocations;
	GLuint DirectionLocation;
};

struct PointLightLocation {
	LightLocations ULightLocations;
	GLuint PositionLocation;
	GLuint ConstantLocation;
	GLuint LinearLocation;
	GLuint ExponentLocation;
};

struct UniformLocations
{
	UniformLocations() = default;
	UniformLocations(const UniformLocations& ref);
	~UniformLocations() = default;

	GLuint ModelMatrixLocation;
	GLuint ProjectionMatrixLocation;
	GLuint ViewMatrixLocation;

	MaterialLocations UMaterialLocations;
	DirectionalLightLocations UDirLightLocs;
	PointLightLocation UPointLightLocs;

	GLuint EyePositionLocation;
};

class Shader
{
public:
	Shader();
	~Shader() = default;

	void CreateShaderFromFiles(
		const char* vShader,
		const char* fShader
	);

	void UseShader();

	const UniformLocations& GetUniformLocations() const;

	GLuint GetUniformColorLocation() const;
	GLuint getID() const { return m_ShaderProgram; }
private:
	GLuint m_ShaderProgram;

	UniformLocations m_UniformLocations;

	std::string ReadShaderCodeFromFile(const char* shaderPath);
	void AddShader(GLuint program, const char* shaderCode, GLenum shaderType);
	void CompileShaders(const char* vShaderCode, const char* fShaderCode);
};

