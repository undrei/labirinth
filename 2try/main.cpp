#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <conio.h>
#include <iostream>

using namespace std;
using namespace sf;

float heroS = 10.f;
float blockS = 25.f;
float v = 0.3f;


int colCheck(RectangleShape b, RectangleShape hero, float x, float y) //проверка столкновений по ОX
{

	if (x > 0 && int(hero.getPosition().x + heroS + 1) > int(b.getPosition().x) && int(hero.getPosition().x + heroS + 1) < int(b.getPosition().x + blockS))
		return 1;
	else if (x < 0 && int(hero.getPosition().x - 1) < int(b.getPosition().x + blockS) && int(hero.getPosition().x - 1) > int(b.getPosition().x))
		return -1;
	if (y < 0 && int(hero.getPosition().y - 1) < int(b.getPosition().y + blockS) && int(hero.getPosition().y - 1) > int(b.getPosition().y))
		return -2;
	else if (y > 0 && int(hero.getPosition().y + heroS + 1) > int(b.getPosition().y) && int(hero.getPosition().y + heroS + 1) < int(b.getPosition().y + blockS))
		return 2;
	else
		return 0;
}

int yCol(RectangleShape b, RectangleShape hero, float y) //проверка столкновений по ОY
{

	if (y < 0 && int(hero.getPosition().y - 1) < int(b.getPosition().y + blockS) && int(hero.getPosition().y - 1) > int(b.getPosition().y))
		return -1;
	else if (y > 0 && int(hero.getPosition().y + heroS + 1) > int(b.getPosition().y) && int(hero.getPosition().y + heroS + 1) < int(b.getPosition().y + blockS))
		return 1;
	else
		return 0;
}

int main()
{
	RenderWindow window(VideoMode(900, 500), "Game");
	//Shapes
	RectangleShape hero(Vector2f(heroS,heroS));
	
	RectangleShape block = RectangleShape();
	vector<RectangleShape> blocks(800, RectangleShape(block));

	bool right = true;
	bool left = true;
	bool up = true;
	bool down = true;


	int i, j, l = 0;
	
	int map[33][20] =	{{ 1,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, }, 
						{ 1,2,1,0,0,1,0,1,2,2,2,1,1,1,1,0,0,0,0,1, },
						{ 1,2,1,1,0,1,0,1,2,1,2,2,2,2,1,0,1,1,0,1, },
						{ 1,2,2,2,2,2,2,1,2,1,1,1,1,2,1,0,0,1,0,1, },
						{ 1,1,1,1,1,1,2,1,2,1,0,0,1,2,1,1,0,1,0,1, },
						{ 1,0,0,1,0,0,2,2,2,1,1,0,0,2,0,0,0,1,0,1, },
						{ 1,0,1,1,0,1,1,1,1,1,0,0,1,2,1,1,1,1,0,1, },
						{ 1,0,0,0,0,0,0,0,0,1,1,1,1,2,1,0,0,0,0,1, },
						{ 1,1,1,1,1,1,0,1,1,1,2,2,2,2,1,0,1,1,1,1, },
						{ 1,1,0,0,0,1,0,0,1,1,2,1,1,1,1,0,0,0,0,1, },
						{ 1,0,0,1,0,0,0,0,0,1,2,2,2,2,1,1,1,1,0,1, },
						{ 1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,0,0,0,0,1, },
						{ 1,2,2,2,2,2,2,2,2,2,2,2,2,2,1,0,1,1,1,1, },
						{ 1,2,1,1,0,1,1,1,1,1,1,1,1,1,1,0,0,0,0,1, },
						{ 1,2,1,0,0,0,1,2,2,2,1,0,0,0,0,0,1,1,0,1, },
						{ 1,2,1,1,1,1,1,2,1,2,1,1,1,0,1,0,0,0,0,1, },
						{ 1,2,1,2,2,2,1,2,1,2,2,2,1,1,1,1,1,1,1,1, },
						{ 1,2,1,2,1,2,1,2,1,0,1,2,2,2,2,2,2,2,2,1, },
						{ 1,2,1,2,1,2,1,2,1,0,1,1,1,1,1,1,1,1,2,1, },
						{ 1,2,1,2,1,2,1,2,1,0,0,0,0,0,0,0,0,0,2,1, },
						{ 1,2,1,2,1,2,2,2,1,0,1,1,1,1,1,1,0,1,2,1, },
						{ 1,2,1,2,1,1,1,1,1,0,0,0,1,0,1,0,0,1,2,1, },
						{ 1,2,1,2,2,1,0,0,1,1,1,0,0,0,1,0,1,1,2,1, },
						{ 1,2,1,1,2,1,1,0,0,0,0,0,1,0,1,0,0,1,2,1, },
						{ 1,2,1,1,2,1,0,0,1,1,1,1,1,1,1,1,1,1,2,1, },
						{ 1,2,1,1,2,1,1,0,1,2,2,2,2,2,2,2,2,2,2,1, },
						{ 1,2,1,1,2,1,0,0,1,2,1,1,1,1,1,1,1,1,1,1, },
						{ 1,2,1,1,2,1,0,1,1,2,1,1,1,1,1,1,1,1,2,2, },
						{ 1,2,1,1,2,1,0,0,1,2,1,1,2,2,2,2,2,2,2,1, },
						{ 1,2,1,1,2,1,0,1,1,2,1,1,2,1,1,1,1,1,1,1, },
						{ 1,2,1,1,2,1,0,0,1,2,1,1,2,1,0,0,0,1,0,1, },
						{ 1,2,2,2,2,1,0,1,1,2,2,2,2,0,0,1,0,0,0,1, },
						{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, } };

	for (i = 0; i < 33; i++)
		for (j = 0; j < 20; j++)
		{
			if (map[i][j] == 1)
			{
				blocks[l].setPosition(i * blockS, j * blockS);
				blocks[l].setSize(Vector2f(blockS, blockS));
				blocks[l].setFillColor(Color(100, 100, 100));
				l++;
			}
		}


	//(x,y) for hero
	float x = 0.f;
	float y = 0.f;


	hero.setPosition(0, 27);
	Vector2f heroPos = hero.getPosition();

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();

			if (event.type == Event::KeyPressed)
				switch (event.key.code)
				{
				case Keyboard::D:
					if (right)
						x = v;
				break;

				case Keyboard::A:
					if (left)
						x = -v;
				break;

				case Keyboard::W:
					if (up)
						y = -v;
				break;

				case Keyboard::S:
					if (down)
						y = v;
				break;
				}

			if (event.type == Event::KeyReleased)
				switch (event.key.code)
				{
				case Keyboard::A: 
					x = 0;
					break;
				case Keyboard::D: 
					x = 0;
					break;
				case Keyboard::W:
					y = 0;
					break;
				case Keyboard::S: 
					y = 0;
					break;
				}
		}

		window.clear();

		for (i = 0; i < blocks.size(); i++)
		{	
			if (hero.getGlobalBounds().intersects(blocks[i].getGlobalBounds()))
			{
				if (colCheck(blocks[i], hero, x, y) == 1)
				{
					x = 0;
					cout << "\nright";
					right = false;
				}
				else right = true;

				if (colCheck(blocks[i], hero, x, y) == -1)
				{
					x = 0;
					cout << "\nleft";
					left = false;
				}
				else left = true;

				if (colCheck(blocks[i], hero, x, y) == -2)
				{
					y = 0;
					cout << "\nup";
					up = false;
				}
				else up = true;

				if (colCheck(blocks[i], hero, x, y) == 2)
				{
					y = 0;
					cout << "\ndown";
					down = false;
				}
				else down = true;
			}
			else
			{
				right = left = true;
				up = down = true;
			}

			window.draw(blocks[i]);
		}

		hero.move(x, y);
		window.draw(hero);
		window.display();
	}

	return 0;
}

