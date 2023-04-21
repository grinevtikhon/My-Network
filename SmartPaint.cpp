#include "SmartPaint.h"

SmartPaint::SmartPaint()
{
	mat.resize(28, vector<double>(28, 0));

	window.create(sf::VideoMode(size_of_pixel * 28 + 400, size_of_pixel * 28 + 300), "Smart Paint");

	chances.resize(10, 0.5f);

	
	if (!font.loadFromFile("resources/arial.ttf"))
	{
		cout << "OOOOOYYYY!!!!!!(SHRIFT GG)\n";
	}

}

void SmartPaint::draw_answer()
{

	sf::Text text;
	text.setFont(font);
	text.setFillColor(sf::Color::Black);

	text.setString("Answer:");
	text.setPosition(28*size_of_pixel + 120, 150);
	text.setCharacterSize(50);
	
	window.draw(text);

	int ans = 0;

	for (int i = 1; i < 10; ++i)
	{
		if (chances[i] > chances[ans])
		{
			ans = i;
		}
	}

	text.setString((char)(ans + 48));
	text.setPosition(28 * size_of_pixel + 180, 300);
	text.setCharacterSize(60);

	cout << ans << endl;

	window.draw(text);

}

void SmartPaint::draw_chances()
{
	sf::RectangleShape stolb;
	sf::Text text;
	text.setFont(font);

	stolb.setFillColor(sf::Color::Blue);

	for (int i = 0; i < 10; ++i)
	{
		text.setString((char)(i + 48));
		text.setPosition(100 + i * 75, size_of_pixel * 28 + 50 + 210);
		text.setCharacterSize(14);
		text.setFillColor(sf::Color::Black);
		window.draw(text);

		stolb.setPosition(100 + i * 75, size_of_pixel * 28 + 50 + 200 - chances[i] * 200);
		stolb.setSize(sf::Vector2f(10, chances[i] * 200));
		window.draw(stolb);
	}


}


void SmartPaint::next_tick()
{
	window.clear(sf::Color::White);

	draw_chances();

	draw_answer();

	int delta_wheel = 0;

	while (window.pollEvent( event))
	{
		if (event.type == sf::Event::Closed)
			window.close();
		else if (event.type == sf::Event::MouseWheelMoved)
		{
			// display number of ticks mouse wheel has moved
			 delta_wheel = this->event.mouseWheel.delta;
		}
	}



	sf::Vector2i localPosition = sf::Mouse::getPosition(window);

	int x = localPosition.x / size_of_pixel;
	int y = localPosition.y / size_of_pixel;

	

	//cout << delta_wheel << endl;

	r_brush = max(r_brush + delta_wheel * 0.3, 0.0);

	sf::CircleShape brush(r_brush);

	brush.setPosition((x+0.5) * size_of_pixel - brush.getRadius(), (y+0.5) * size_of_pixel - brush.getRadius());
	brush.setFillColor(sf::Color::Green);
	
	int my_radius = brush.getRadius() / size_of_pixel + 1;

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{

		for (int i = y - my_radius; i < y + my_radius; ++i)
		{
			for (int j = x - my_radius; j < x + my_radius; ++j)
			{
				if (pow(i - y, 2) + pow(j - x, 2) < pow(my_radius, 2))
				{
					if (j >= 0 && j < 28 && i >= 0 && i < 28)
					{
						mat[i][j] = min(mat[i][j] + 0.025*(my_radius - sqrt(pow(i - y, 2) + pow(j - x, 2)) / my_radius), 1.0);
					}
				}
			}
		}

		
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
	{
		sf::Vector2i localPosition = sf::Mouse::getPosition(window);

		for (int i = y - my_radius + 1; i < y + my_radius; ++i)
		{
			for (int j = x - my_radius + 1; j < x + my_radius; ++j)
			{
				if (j >= 0 && j < 28 && i >= 0 && i < 28)
				{
					mat[i][j] = 0;
				}
			}
		}
	}

	sf::RectangleShape pixel;

	pixel.setSize(sf::Vector2f(size_of_pixel, size_of_pixel));

	for (int i = 0; i < 28; ++i)
	{
		for (int j = 0; j < 28; ++j)
		{
			pixel.setPosition(j * size_of_pixel, i * size_of_pixel);
			pixel.setFillColor(sf::Color(int(mat[i][j] * 255), int(mat[i][j] * 255), int(mat[i][j] * 255)));
			window.draw(pixel);
			//mat[i][j] = min(1.0, mat[i][j] + 0.0001 * (i+j));
		}
	}

	window.draw(brush);

	window.display();
}

vector<double> SmartPaint::get_mat()
{
	vector<double> ans;

	for (int i = 0; i < 28; ++i)
	{
		for (int j = 0; j < 28; ++j)
		{
			ans.push_back(mat[i][j]);
		}
	}

	return ans;
}

void SmartPaint::set_chances(vector<double> _chances)
{
	chances = _chances;
}
