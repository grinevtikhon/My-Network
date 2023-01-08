#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <time.h>
#include <SFML/Graphics.hpp>
#include <chrono>

using namespace std;

class SmartPaint
{

public:

	const int size_of_pixel = 20;

	double r_brush = 25;

	vector<double> chances;

	sf::RenderWindow window;
	vector<vector<double>> mat;
	sf::Event event;
	sf::Font font;

	SmartPaint();

	void draw_answer();

	void draw_chances();

	void next_tick();

	vector<double> get_mat();

	void set_chances(vector<double> _chances);

};

