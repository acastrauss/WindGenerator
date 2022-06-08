#pragma once


bool RestartGLlog();
bool GLlog(const char* message, ...);
bool GLlogError(const char* message, ...);
void LogGLParams();

void PrintShaderInfoLog(unsigned int shaderIndex);
void PrintProgramInfoLog(unsigned int program);

// Only call in development, operation is expensive
bool IsProgramValid(unsigned int program);