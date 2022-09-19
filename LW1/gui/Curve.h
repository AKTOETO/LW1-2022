#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <fstream>
#include <iostream>
#include <memory>

using namespace std;
using namespace sf;

class curve
{
private:
	// line
	vector<Vertex*> m_curve;
	RenderWindow* m_window;
	vector<double> m_y_coords;
	Color m_color;
	string m_filename;

	// constants
	double m_X_STEP;
	double m_X_SCALE;
		   
	double m_Y_SHIFT;
	double m_Y_SCALE;
		   
	double m_Y_BORDERS_OFFSET;

public:
	// coords
	curve(
		RenderWindow* window,
		Color = Color::White,
		string filename = "f1.txt",
		double y_borders_offset = 50);
	~curve();

	// configurate
	void configurate();
	// calculating coords
	void calculate_coords();

	// looking for absolute max value
	double abs_max(vector<double>) const;

	// set methods
	void set_y_scale(double);
	void set_y_border_offset(double);
	void setting();

	// get methods
	double get_y_scale() const;

	// read from file
	void read_data();

	// draw
	void draw() const;

	string info() const;
};

