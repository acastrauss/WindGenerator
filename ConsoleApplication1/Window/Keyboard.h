#pragma once

#include <GLFW/glfw3.h>
#include <unordered_set>
#include <mutex>
#include <iostream>


class MainWindow;


class Keyboard
{

	friend class MainWindow;

private:
	static Keyboard* instance;
	static std::mutex singleton_lock;

private:

	std::unordered_set<int> keys{
		GLFW_KEY_W,
		GLFW_KEY_A,
		GLFW_KEY_S,
		GLFW_KEY_D,
		GLFW_KEY_UP,
		GLFW_KEY_DOWN,
		GLFW_KEY_ESCAPE,
	};


	std::unordered_set<int> pressed_keys;
	void handleKeyPress(int key, int action);
	Keyboard();

public:
	bool checkKeySet(int key);
	

public:
	Keyboard(Keyboard const&) = delete;
	void operator=(Keyboard const&) = delete;
	static Keyboard* getInstance();
};

