#pragma once
#include <SFML/Graphics.hpp>

#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <iostream>
#include <cmath>

using namespace std;

#define W_WIDTH 800
#define W_HIGHT 600

// Настроки масштабирования графика
// А - массив с координатами по y
#define X_STEP 0.2										// шаг по оси x (0.2)
#define Y_SHIFT W_HIGHT / 2								// смещение графика по оси y (px)
#define X_SCALE W_WIDTH / X_STEP / y_coords.size()		// множитель по оси x
#define Y_BORDERS 50									// отступ по оси y от рамок (px)
// множитель по оси y
#define Y_SCALE (W_HIGHT / 2 - Y_BORDERS) / abs_max(y_coords)

namespace GUI
{
	//	=============================
	//			DECLARATIONS
	//	=============================

	// printing vector into console
	template<typename T>
	inline void vect_out(vector<T> vec);

	// reading data from file
	inline vector<double> read_arr(string filename = "out.txt");

	// drawing graphs
	inline void draw_graphs();

	//	=============================
	//			DEFINITIONS
	//	=============================

	// printing vector into console
	template<typename T>
	inline void vect_out(vector<T> vec)
	{
		for_each(vec.begin(), vec.end(), [](T el) {
			cout << el << endl;
			});
	}

	// reading data from file
	inline vector<double> read_arr(string filename)
	{
		// filepath "../" + filename
		ifstream fin(filename);
		if (!fin.is_open()) cout << "file \"" << filename << "\" didn't open\n";

		// out vector
		vector<double> out;

		//reading datafrom file
		double temp;
		do
		{
			// read number 
			fin >> temp;
			fin.get();
			// converting temp from string to int
			// and pushing it into vector
			out.push_back(temp);
		} while (fin.peek() != EOF);

		//cout << "size: " << out.size() << '\n';
		//vect_out(out);

		fin.close();
		return out;
	}

	// looking for absolute max value
	inline double abs_max(vector<double> vec)
	{
		transform(vec.begin(), vec.end(), vec.begin(), [](double num) {return abs(num); });
		return *max_element(vec.begin(), vec.end());
	}

	// drawing graphs
	inline void draw_graphs()
	{
		// settings for window
		sf::ContextSettings set;
		set.antialiasingLevel = 9;

		// creating window
		sf::RenderWindow window(sf::VideoMode(W_WIDTH, W_HIGHT), "Graphs", sf::Style::Default, set);

		// reading data from file
		vector<double> y_coords = read_arr("out.txt");

		// creating line
		vector<sf::Vertex*> line(y_coords.size());

		double xcoord = 0.0;
		for (int i = 0; i < y_coords.size() - 1; i++, xcoord += X_STEP)
		{
			line[i] = new sf::Vertex[2];
			// координаты начала отрезка
			line[i][0] = sf::Vertex(
				sf::Vector2f(xcoord * X_SCALE, - y_coords[i] * Y_SCALE + Y_SHIFT),
				sf::Color::White
			);
			// координаты конца отрезка отрезка
			line[i][1] = sf::Vertex(
				sf::Vector2f((xcoord + X_STEP) * X_SCALE, - y_coords[i + 1] * Y_SCALE + Y_SHIFT),
				sf::Color::White
			);
		};

		// print coords of points of line in console
		/*for_each(line.begin(), line.end() - 1, [](sf::Vertex* line) {
			cout << line[0].position.x << " " << line[0].position.y << endl;
			});*/

		// run the program as long as the window is open
		while (window.isOpen())
		{
			// check all the window's events that were triggered since the last iteration of the loop
			sf::Event event;
			while (window.pollEvent(event))
			{
				// "close requested" event: we close the window
				if (event.type == sf::Event::Closed ||
					sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
					window.close();
			}
			window.clear();

			// draw
			for (int i = 0; i < y_coords.size(); i++)
			{
				window.draw(line[i], 2, sf::Lines);
			}

			window.display();
		}
	}
}
