#include "GraphsDrawer.h"

GraphsDrawer::GraphsDrawer()
:m_w_title("Graphs"), m_w_width(800),m_w_hight(600)
{
	m_window = new RenderWindow (
		VideoMode(m_w_width, m_w_hight), m_w_title
	);

	m_curve_manager = new CurveManager(
		m_window, FILENAMES, COLORS
	);
}

GraphsDrawer::~GraphsDrawer()
{
	delete m_window;
	delete m_curve_manager;
}

void GraphsDrawer::run()
{
	while (m_window->isOpen())
	{
		sf::Event event;

		while (m_window->pollEvent(event))
		{

			if (event.type == sf::Event::Closed ||
				event.type == sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				m_window->close();
			}
		}

		m_window->clear();

		m_curve_manager->draw();

		m_window->display();
	}
}
