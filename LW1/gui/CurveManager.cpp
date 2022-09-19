#include "CurveManager.h"

CurveManager::CurveManager(RenderWindow* window,
	vector<string> filenames,
	vector<Color> colors)
	:m_window(window),
	m_filenames(filenames),
	m_color(colors)
{
	m_curves.resize(m_filenames.size());
	for (int i = 0; i < m_filenames.size(); i++)
	{
		m_curves[i] = new curve(
			m_window, m_color[i], m_filenames[i], 0.2, 50
		);
	}
}

CurveManager::~CurveManager()
{
	for (int i = 0; i < m_curves.size(); i++)
	{
		delete m_curves[i];
	}
	m_curves.clear();
}

void CurveManager::draw() const
{
	for (int i = 0; i < m_curves.size(); i++)
	{
		m_curves[i]->draw();
	}
}
