#include "Shader/Shader.h"

#include <fstream>
#include <sstream>
#include <iostream>

UniformLocations::UniformLocations(const UniformLocations& ref):
	ModelMatrixLocation(ref.ModelMatrixLocation),
	ProjectionMatrixLocation(ref.ProjectionMatrixLocation),
	ViewMatrixLocation(ref.ViewMatrixLocation)
{
}

Shader::Shader():
	m_ShaderProgram(0),
	m_UniformLocations()
{
}

const UniformLocations& Shader::GetUniformLocations() const
{
	return m_UniformLocations;
}

void Shader::CreateShaderFromFiles(
	const char* vShader, const char* fShader)
{
	std::string vShaderCode = ReadShaderCodeFromFile(vShader);
	std::string fShaderCode = ReadShaderCodeFromFile(fShader);

	CompileShaders(
		vShaderCode.c_str(),
		fShaderCode.c_str()
	);
}

void Shader::UseShader()
{
	glUseProgram(m_ShaderProgram);
}

std::string Shader::ReadShaderCodeFromFile(const char* shaderPath)
{
	std::string code;
	std::ifstream shaderFile;

	shaderFile.exceptions(
		std::ifstream::badbit
	);

	try
	{
		shaderFile.open(shaderPath);
		std::stringstream sstream;

		sstream << shaderFile.rdbuf();
		shaderFile.close();

		code = sstream.str();
	}
	catch (const std::ifstream::failure&)
	{
		std::cout << "Shader file:\"" << shaderPath << "\" cannot be read." << std::endl;
	}

	return code;
}

void Shader::AddShader(GLuint program, const char* shaderCode, GLenum shaderType)
{
	GLuint concreteShader = glCreateShader(shaderType);

	const GLchar* theCode[1];
	theCode[0] = shaderCode;

	GLint codeLength[1];
	codeLength[0] = strlen(shaderCode);

	glShaderSource(concreteShader, 1, theCode, codeLength);
	glCompileShader(concreteShader);

	GLint result = 0;
	GLchar errLog[1024] = { 0 };

	// get shader compiling result
	glGetShaderiv(concreteShader, GL_COMPILE_STATUS, &result);

	if (!result)
	{
		glGetShaderInfoLog(
			concreteShader, sizeof(errLog), NULL, errLog
		);
		std::cerr << "Error compiling the " << shaderType << " shader:" << errLog << std::endl;
		return;
	}

	glAttachShader(program, concreteShader);
}

void Shader::CompileShaders(const char* vShaderCode, const char* fShaderCode)
{
	m_ShaderProgram = glCreateProgram();

	if (!m_ShaderProgram)
	{
		std::cerr << "Error creating shader program" << std::endl;
		return;
	}

	AddShader(m_ShaderProgram, vShaderCode, GL_VERTEX_SHADER);
	AddShader(m_ShaderProgram, fShaderCode, GL_FRAGMENT_SHADER);

	GLint result = 0;
	GLchar errLog[1024] = { 0 };

	// check shader linking
	glLinkProgram(m_ShaderProgram);
	glGetProgramiv(
		m_ShaderProgram, GL_LINK_STATUS, &result
	);

	if (!result)
	{
		glGetProgramInfoLog(m_ShaderProgram, sizeof(errLog), NULL, errLog);
		std::cerr << "Error linking program:" << errLog << std::endl;
		return;
	}

	// validate shader program
	glValidateProgram(m_ShaderProgram);
	glGetProgramiv(m_ShaderProgram, GL_VALIDATE_STATUS, &result);

	if (!result)
	{
		glGetProgramInfoLog(m_ShaderProgram, sizeof(errLog), NULL, errLog);
		std::cerr << "Erro validating program:" << errLog << std::endl;
		return;
	}

	// get uniform locations here
	m_UniformLocations.ProjectionMatrixLocation = glGetUniformLocation(m_ShaderProgram, "projection");
	m_UniformLocations.ModelMatrixLocation = glGetUniformLocation(m_ShaderProgram, "model");
	m_UniformLocations.ViewMatrixLocation = glGetUniformLocation(m_ShaderProgram, "view");
	
	MaterialLocations mLocs;
	mLocs.SpecularIntesityLocation = glGetUniformLocation(m_ShaderProgram, "material.specularIntesity");
	mLocs.ShininessLocation = glGetUniformLocation(m_ShaderProgram, "material.shininess");
	m_UniformLocations.UMaterialLocations = mLocs;

	LightLocations dirLightLocs;
	dirLightLocs.ColorLocation = glGetUniformLocation(m_ShaderProgram, "directionalLight.base.colour");
	dirLightLocs.AmbientIntesityLocation = glGetUniformLocation(m_ShaderProgram, "directionalLight.base.ambientIntensity");
	dirLightLocs.DiffuseIntesityLocation = glGetUniformLocation(m_ShaderProgram, "directionalLight.base.diffuseIntesity");

	DirectionalLightLocations dlLocs;
	dlLocs.ULightLocations = dirLightLocs;
	dlLocs.DirectionLocation =
		glGetUniformLocation(m_ShaderProgram, "directionalLight.direction");

	m_UniformLocations.UDirLightLocs = dlLocs;

	LightLocations pointLightLocs;
	pointLightLocs.ColorLocation = glGetUniformLocation(m_ShaderProgram, "pointLight.base.colour");
	pointLightLocs.AmbientIntesityLocation = glGetUniformLocation(m_ShaderProgram, "pointLight.base.ambientIntensity");
	pointLightLocs.DiffuseIntesityLocation = glGetUniformLocation(m_ShaderProgram, "pointLight.base.diffuseIntesity");

	PointLightLocation plLocs;
	plLocs.ULightLocations = pointLightLocs;
	plLocs.PositionLocation = glGetUniformLocation(m_ShaderProgram, "pointLight.position");
	plLocs.ConstantLocation = glGetUniformLocation(m_ShaderProgram, "pointLight.constant");
	plLocs.LinearLocation = glGetUniformLocation(m_ShaderProgram, "pointLight.linear");
	plLocs.ExponentLocation = glGetUniformLocation(m_ShaderProgram, "pointLight.exponent");
	m_UniformLocations.UPointLightLocs = plLocs;

	m_UniformLocations.EyePositionLocation = glGetUniformLocation(m_ShaderProgram, "eyePosition");
}

GLuint Shader::GetUniformColorLocation() const
{
	return glGetUniformLocation(m_ShaderProgram, "uColor");
}