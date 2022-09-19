#include "Button.h"

Button::Button(sf::Keyboard::Key keycode)
	:m_isPressed(false), m_keycode(keycode)
{
}

Button::~Button()
{
}

int Button::logic()
{
	if (sf::Keyboard::isKeyPressed(m_keycode) && m_isPressed == false)
	{
		m_isPressed = true;
		return 1;
	}
	else if (m_isPressed == true && sf::Keyboard::isKeyPressed(m_keycode) == false)
	{
		m_isPressed = false;
	}
    return 0;
}
