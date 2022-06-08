#include "LogErrors.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <stdio.h>
#include <time.h>
#include <stdarg.h>

constexpr const char* GL_LOG_FILE = "gl.log";

#pragma warning(disable:4996)

bool RestartGLlog()
{
    FILE* file = fopen(GL_LOG_FILE, "w");

    if (!file)
    {
        fprintf(
            stderr,
            "ERROR: could not open GL_LOG_FILE log file %s for writing\n",
            GL_LOG_FILE
        );
        return false;
    }

    time_t now = time(NULL);
    char* date = ctime(&now);
    fprintf(file, "GL_LOG_FILE log. Local time: %s\n", date);

    fclose(file);

    return true;
}

bool GLlog(const char* message, ...)
{
    va_list argptr;
    FILE* file = fopen(GL_LOG_FILE, "a");

    if (!file)
    {
        fprintf(
            stderr,
            "ERROR: could not open GL_LOG_FILE log file %s for appending\n",
            GL_LOG_FILE
        );
        return false;
    }

    va_start(argptr, message);
    vfprintf(file, message, argptr);
    va_end(argptr);
    fclose(file);

    return true;
}

bool GLlogError(const char* message, ...)
{
    va_list argptr;
    FILE* file = fopen(GL_LOG_FILE, "a");

    if (!file)
    {
        fprintf(
            stderr,
            "ERROR: could not open GL_LOG_FILE log file %s for appending\n",
            GL_LOG_FILE
        );
        return false;
    }

    va_start(argptr, message);
    vfprintf(file, message, argptr);
    va_end(argptr);
    va_start(argptr, message);
    vfprintf(stderr, message, argptr);
    va_end(argptr);

    fclose(file);

    return true;
}



void LogGLParams()
{
    GLenum params[] = {
        GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS,
        GL_MAX_CUBE_MAP_TEXTURE_SIZE,
        GL_MAX_DRAW_BUFFERS,
        GL_MAX_FRAGMENT_UNIFORM_COMPONENTS,
        GL_MAX_TEXTURE_IMAGE_UNITS,
        GL_MAX_TEXTURE_SIZE,
        GL_MAX_VARYING_FLOATS,
        GL_MAX_VERTEX_ATTRIBS,
        GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS,
        GL_MAX_VERTEX_UNIFORM_COMPONENTS,
        GL_MAX_VIEWPORT_DIMS,
        GL_STEREO
    };

    const char* names[] = {
        "GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS",
        "GL_MAX_CUBE_MAP_TEXTURE_SIZE",
        "GL_MAX_DRAW_BUFFERS",
        "GL_MAX_FRAGMENT_UNIFORM_COMPONENTS",
        "GL_MAX_TEXTURE_IMAGE_UNITS",
        "GL_MAX_TEXTURE_SIZE",
        "GL_MAX_VARYING_FLOATS",
        "GL_MAX_VERTEX_ATTRIBS",
        "GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS",
        "GL_MAX_VERTEX_UNIFORM_COMPONENTS",
        "GL_MAX_VIEWPORT_DIMS",
        "GL_STEREO"
    };

    GLlog("GL Context params:\n");
    char msg[256];

    for (int i = 0; i < 10; i++)
    {
        GLint v = 0;
        glGetIntegerv(params[i], &v);
        GLlog("%s %i\n", names[i], v);
    }

    int v[2];
    v[0] = v[1] = 0;
    glGetIntegerv(params[10], v);
    GLlog("%s %i %i\n", names[10], v[0], v[1]);

    unsigned char s = 0;
    glGetBooleanv(params[11], &s);
    GLlog("%s %u\n", names[11], (unsigned int)s);
    GLlog("-----------------------------------\n");

}


void PrintShaderInfoLog(unsigned int shaderIndex)
{
    int maxLength = 2048;
    int actualLength = 0;
    char log[2048];

    glGetShaderInfoLog(shaderIndex, maxLength, &actualLength, log);
    printf("Shader info log for GL index:%u\n%s\n", shaderIndex, log);
}

void PrintProgramInfoLog(unsigned int program)
{
    int maxLength = 2048;
    int actualLength = 0;
    char log[2048];

    glGetProgramInfoLog(program, maxLength, &actualLength, log);
    printf("Shader info log for GL index:%u\n%s\n", program, log);
}

bool IsProgramValid(unsigned int program)
{
    glValidateProgram(program);
    int params = -1;
    glGetProgramiv(program, GL_VALIDATE_STATUS, &params);
    printf("program %i GL_VALIDATE_STATUS = %i\n", program, params);
    if (params != GL_TRUE) {
        PrintProgramInfoLog(program);
        return false;
    }
    return true;
}