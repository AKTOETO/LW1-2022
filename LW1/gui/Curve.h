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
	curve(RenderWindow*, Color = Color::White,
		string = "f1.txt", double = 0.2, double = 50);
	~curve();

	// configurate
	void configurate();

	// looking for absolute max value
	double abs_max(vector<double>) const;

	// set methods
	void set_coords();
	void setting();

	// read from file
	void read_data();

	// draw
	void draw() const;
};

