#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <conio.h>
#include <iostream>

using namespace std;
using namespace sf;

float heroS = 10.f;
float blockS = 25.f;




int main()
{
	RenderWindow window(VideoMode(900, 500), "SFMLworks");
	//Shapes
	RectangleShape hero(Vector2f(heroS,heroS));
	//RectangleShape heroHB(Vector2f(heroS+2, heroS+2));
	vector<RectangleShape*> blocks;
	RectangleShape block = RectangleShape();
	block.setSize(Vector2f(blockS, blockS));
	
	block.setFillColor(Color(100,100,100));

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
												
	int i, j;
	bool col;
	
	//(x,y) for hero
	float x = 0.f;
	float y = 0.f;

	bool upFlag = false;
	bool leftFlag = false;
	bool rightFlag = false;
	bool downFlag = false;


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
				switch (event.key.code)s
				{
				case Keyboard::D:
					if (!rightFlag)
						x = 0.2f;
					else
						x = 0;
				break;

				case Keyboard::A: 
					if (!leftFlag)
						x = -0.2f;
					else
						x = 0;
				break;

				case Keyboard::W:
					if (!upFlag)
						y = -0.2f;
					else
						y = 0;
				break;

				case Keyboard::S:
					if (!downFlag)
						y = 0.2f;
					else
						y = 0;
				break;

				case Keyboard::Space:
					cout << "\n\nup: " << upFlag;
					cout << "\ndown: " << downFlag;
					cout << "\nright: " << rightFlag;
					cout << "\nleft: " << leftFlag;
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

		for(i = 0; i < 33; i++)
			for (j = 0; j < 20; j++)
			{
				if (map[i][j] == 1)
				{
					block.setPosition(i * blockS, j * blockS);
					
					if (hero.getGlobalBounds().intersects(block.getGlobalBounds()))
					{
						if (int(hero.getPosition().x + heroS) == int(block.getPosition().x))
							rightFlag = true;
						else
							rightFlag = false;

						if (int(hero.getPosition().x + 1) == int(block.getPosition().x + blockS))
							leftFlag = true;
						else 
							leftFlag = false;

						if (int(hero.getPosition().y + 1) == int(block.getPosition().y + blockS))
							upFlag = true;
						else
							upFlag = false;

						if (int(hero.getPosition().y + heroS) == int(block.getPosition().y))
							downFlag = true;
						else
							downFlag = false;

					}
						//cout << " " << int(hero.getGlobalBounds().top); 
					
					blocks.push_back(&block);
					window.draw(block);
				}
			}

		
		hero.move(x, y);
		window.draw(hero);
		window.display();
	}

	return 0;
}

/*void blockcheck(int * arr[][])
{
	for (int i = 0; i < 33; i++)
		for (int j = 0; j < 20; j++)
		{
			if (arr[i][j] == 1)
				Vector2f 
		}
}*/