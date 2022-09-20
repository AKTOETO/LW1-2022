#pragma once
#include "CurveManager.h"

class GraphsDrawer
{
private:
	const unsigned int m_w_width;
	const unsigned int m_w_hight;
	const string m_w_title;

	RenderWindow* m_window;
	CurveManager* m_curve_manager;

public:
	GraphsDrawer();
	~GraphsDrawer();

	void window_active(bool);
	void run();
};

