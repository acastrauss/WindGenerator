#include "Keyboard.h"


Keyboard* Keyboard::instance = nullptr;
std::mutex Keyboard::singleton_lock;


Keyboard::Keyboard(){}

bool Keyboard::checkKeySet(int key)
{
	return pressed_keys.find(key) != pressed_keys.end();
}

void Keyboard::handleKeyPress(int key, int action)
{
	if (keys.find(key) == keys.end())
		return;

	if (action == GLFW_PRESS)
		pressed_keys.emplace(key);
	else if (action == GLFW_RELEASE)
		pressed_keys.erase(key);

}

Keyboard* Keyboard::getInstance()
{
	std::lock_guard<std::mutex> lock(singleton_lock);

	if (instance == nullptr)
	{
		instance = new Keyboard();
	}

	return instance;
}
