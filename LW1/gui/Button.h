#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>

using namespace sf;

class Button
{
private:
	sf::Keyboard::Key  m_keycode;
	bool m_isPressed;
	bool m_isToggled;

public:
	Button(sf::Keyboard::Key keycode);
	~Button();

	int logic();
};

