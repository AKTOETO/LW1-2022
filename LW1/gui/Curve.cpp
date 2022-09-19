#include "Curve.h"

curve::curve(RenderWindow* window, Color color,
	string filename, double y_borders_offset)
	:m_window(window), m_color(color), m_filename(filename),
	m_Y_BORDERS_OFFSET(y_borders_offset), m_visible(true)
{
	configurate();
}

curve::~curve()
{
}

void curve::calculate_coords()
{
	double x_coord = 0.0;
	m_curve.resize(m_y_coords.size());
	for (int i = 0; i < m_y_coords.size(); i++, x_coord += m_X_STEP)
	{
		m_curve[i] = new Vertex[2];
		m_curve[i][0] = { sf::Vertex(sf::Vector2f(
			x_coord * m_X_SCALE,
			-m_y_coords[i] * m_Y_SCALE + m_Y_SHIFT
		))};
		m_curve[i][0].color = m_color;

		m_curve[i][1] = { sf::Vertex(sf::Vector2f(
				(x_coord + (i + 1 < m_y_coords.size() ? m_X_STEP : 0)) * m_X_SCALE,
				-m_y_coords[(i + 1 < m_y_coords.size() ? i + 1 : i)] * m_Y_SCALE + m_Y_SHIFT
		)) };
		m_curve[i][1].color = m_color;
	}
}

void curve::configurate()
{
	// read array of y coords
	read_data();

	// setting constatnts up
	setting();

	// setting coords of line up
	calculate_coords();
}

double curve::abs_max(vector<double> vec) const
{
	transform(vec.begin(), vec.end(), vec.begin(), [](double num) {return abs(num); });
	return *max_element(vec.begin(), vec.end());
}

void curve::read_data()
{
	ifstream fin(m_filename);
	if (!fin.is_open())
		cout << "file \"" << m_filename << "\" didn't open\n";

	// read x_step from file
	fin >> m_X_STEP;
	fin.get();

	//reading datafrom file
	double temp;
	do
	{
		// read number 
		fin >> temp;
		fin.get();
		m_y_coords.push_back(temp);
	} while (fin.peek() != EOF);

	fin.close();
}

void curve::setting()
{
	m_Y_SHIFT = m_window->getSize().y / 2;
	m_X_SCALE = m_window->getSize().x / m_X_STEP / (m_y_coords.size() - 1);
	m_Y_SCALE = (m_window->getSize().y / 2 - m_Y_BORDERS_OFFSET) / abs_max(m_y_coords);
}

void curve::set_y_scale(double scale)
{
	m_Y_SCALE = scale;
	calculate_coords();
}

void curve::set_y_border_offset(double offset)
{
	m_Y_BORDERS_OFFSET = offset;
	setting();
	calculate_coords();
}

void curve::switch_visibility()
{
	m_visible += -1;
}

double curve::get_y_scale() const
{
	return m_Y_SCALE;
}

void curve::draw() const
{
	if (m_visible == 1)
	{
		//cout << "drawing\n";
		for (int i = 0; i < m_curve.size(); i++)
		{
			m_window->draw(m_curve[i], 2, Lines);
		}
	}
}

string curve::info() const
{
	return
		"\tfilename: " + m_filename +
		"\n\tx step:  " + to_string(m_X_STEP) +
		"\n\tx scale: " + to_string(m_X_SCALE) +
		"\n\ty shift: " + to_string(m_Y_SHIFT) +
		"\n\ty scale: " + to_string(m_Y_SCALE) +
		"\n";
}
