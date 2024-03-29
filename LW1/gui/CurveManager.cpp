﻿#include "CurveManager.h"

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
			m_window,		// window
			m_color[i],		// color
			m_filenames[i],	// filename
			20				// y borders offset
		);
	}
	set_all_y_scale(get_min_y_scale());

	m_buttons.resize(m_filenames.size() + 1);
	// 26 - is 1
	for (int i = 0; i < m_filenames.size(); i++)
	{
		m_buttons[i] = new Button(Keyboard::Key(i + 26 + 1));
	}
	// 0 - is A
	m_buttons[m_buttons.size() - 1] = new Button(Keyboard::Key(0));

	//info();
}

CurveManager::~CurveManager()
{
	for (int i = 0; i < m_curves.size(); i++)
	{
		delete m_curves[i];
	}
	m_curves.clear();
}

void CurveManager::set_all_y_scale(double scale)
{
	for (int i = 0; i < m_curves.size(); i++)
	{
		m_curves[i]->set_y_scale(scale);
	}
}

void CurveManager::set_all_y_border_offset(double offset)
{
	for (int i = 0; i < m_curves.size(); i++)
	{
		m_curves[i]->set_y_border_offset(offset);
	}
}

double CurveManager::get_min_y_scale() const
{
	return (*min_element(m_curves.begin(), m_curves.end(),
		[](curve* cur1, curve* cur2)
		{
			return cur1->get_y_scale() < cur2->get_y_scale();
		}))->get_y_scale();
}

void CurveManager::draw() const
{
	for (int i = 0; i < m_curves.size(); i++)
	{
		m_curves[i]->draw();
	}
}

void CurveManager::logic()
{
	// change i visibility
	for (int i = 0; i < m_curves.size(); i++)
	{
		if (m_buttons[i]->logic() == 1)
		{
			m_curves[i]->switch_visibility();
		}
	}

	// change all visibility
	if (m_buttons[m_buttons.size() - 1]->logic() == 1)
	{
		for (int i = 0; i < m_curves.size(); i++)
		{
			m_curves[i]->switch_visibility();
		}
	}
}

void CurveManager::info() const
{
	cout << "=== INFO ===\n";
	for (int i = 0; i < m_curves.size(); i++)
	{
		cout << "curve #" << i + 1 << endl;
		cout << m_curves[i]->info();
	};
}
