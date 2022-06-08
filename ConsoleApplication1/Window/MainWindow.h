#pragma once

#include <GL/glew.h>
#include <iostream>
#include <GLFW/glfw3.h>
#include <string>
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "LogErrors/LogErrors.h"

#include "Keyboard.h"



static const int default_width = 1700;
static const int default_heigth = 800;



void glfw_error_callback(int error, const char* desc);


class MainWindow
{

private:
	GLint width, height;
	GLint buffer_width, buffer_height;
	std::string title;
	Keyboard* keyboard;

	float last_x;
	float last_y;
	float x_change;
	float y_change;

	bool is_initial_movement = true;
	bool is_right_down = false;

private:
	bool initialize();
	void attachCallbacks();

private:
	
	static MainWindow* getCurrentWindowHandle(GLFWwindow* window);
	static void handleKeyPressCallback(GLFWwindow* window, int key, int code, int action, int mode);
	static void handleMouseClickCallback(GLFWwindow* window, int button,int action,int mode);
	static void handleMouseMovementCallback(GLFWwindow* window, double xPos, double yPos);
	static void handleWindowSizeChangedCallback(GLFWwindow* window, int width, int height);



public:
	GLFWwindow* glfw_window_handle;
	ImGuiContext* imguiContext;

	MainWindow(const std::string& title, GLint width = default_width, GLint height = default_heigth);
	void swapBuffers() { glfwSwapBuffers(glfw_window_handle); }
	bool getShouldClose() { return glfwWindowShouldClose(glfw_window_handle); }
	void setShouldClose(GLboolean value) { glfwSetWindowShouldClose(glfw_window_handle, value); }
	GLfloat getBufferWidth() const { return buffer_width; }
	GLfloat getBufferHeight() const { return buffer_height; }

	float getXChange();
	float getYChange();
	
	~MainWindow();
};

