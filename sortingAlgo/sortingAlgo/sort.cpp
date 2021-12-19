#include <SFML/Graphics.hpp>

#define ARR_SIZE 5
#define WIDTH 800
#define HEIGHT 500
#define SCALE WIDTH/ARR_SIZE
using namespace sf;

int randomh = 0, part = 1;
int itera = 0;
int max = 0, cont = 0, lims = ARR_SIZE - 1;
char str[HEIGHT];

struct data
{
	int height;
	int posx;
}line[ARR_SIZE];

int main()
{
	RenderWindow window(VideoMode(WIDTH, HEIGHT), "Bubble sort!");
	Event appEvent;


	Texture fondot;
	fondot.loadFromFile("fondo1.png");
	Sprite fondos(fondot);


	Text t;
	RectangleShape rectangle(Vector2f(2, 178));
	rectangle.setFillColor(Color(235, 149, 13));

	srand(time(NULL));

	while (window.isOpen())
	{
		
		while (window.pollEvent(appEvent))
		{
			if (appEvent.type == Event::Closed)
				window.close();
		}

		if (part == 2)
			if (line[itera].height < line[itera + 1].height)
			{
				max = line[itera].height;
				line[itera].height = line[itera + 1].height;
				line[itera + 1].height = max;
			}

		if (part == 1)
		{
			for (int i = 0; i < ARR_SIZE; i++)
			{
				randomh = 1 + rand() % (HEIGHT);
				line[i].posx = (i+1)*SCALE;
				line[i].height = randomh;
				if (i == ARR_SIZE - 1)
				{
					part = 2;
				}
			}
		}
		window.clear(Color::Black);
		window.draw(fondos);
		for (int i = 0; i < ARR_SIZE; i++)
		{
			rectangle.setFillColor(Color(235, 149, 13));
			if (i == itera)
				rectangle.setFillColor(Color(255, 0, 0));
			t.setString(std::to_string(line[i].height));
			t.setOrigin(15, 15);
			t.setPosition(rectangle.getPosition());
			rectangle.setPosition(line[i].posx, HEIGHT);
			rectangle.setSize(Vector2f(SCALE, line[i].height));
			rectangle.setRotation(180);
			window.draw(rectangle);
			window.draw(t);
		} 
		window.display();
		itera++;
		if (itera >= lims)
		{
			itera = 0;
			cont++;
			lims--;
		}
	}
	return 0;
}