#pragma once
#include "Curve.h"
#include "Button.h"
const vector<string> FILENAMES =
{
	"files/f1.txt",
	"files/f2.txt",
	"files/f3.txt",
	"files/f4.txt",
	"files/f5.txt",
	"files/f6.txt"
};

const vector<Color> COLORS =
{
	Color::White,
	Color::Magenta,
	Color::Red,
	Color::Green,
	Color::Blue,
	Color::Yellow
};

class CurveManager
{
private:
	RenderWindow* m_window;
	vector<curve*> m_curves;
	vector<Button*> m_buttons;

	vector<Color> m_color;
	vector<string> m_filenames;

public:
	CurveManager(
		RenderWindow*,
		vector<string> filenames,
		vector<Color> colors
	);

	~CurveManager();

	//set methods
	void set_all_y_scale(double);
	void set_all_y_border_offset(double);
	
	// get method
	double get_min_y_scale() const;

	void draw() const;

	void logic();

	void info() const;
};

