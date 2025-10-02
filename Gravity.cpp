/*
Configuration Properties :
Debugging - Environment - PATH=C:\Users\marce\OneDrive\Pulpit\cpp\SFML-2.5.1\bin
C / C++ - General - Additional Include Directories - C:\Users\marce\OneDrive\Pulpit\cpp\SFML-2.5.1\include
Linker - General - Additional Library Directories - C:\Users\marce\OneDrive\Pulpit\cpp\SFML-2.5.1\lib
Linker - Input - Additional Dependencies :
1) for Release:
sfml-system.lib
sfml-window.lib
sfml-graphics.lib
2) for Debug:
sfml-system-d.lib
sfml-window-d.lib
sfml-graphics-d.lib

*/

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Planet.h"

using namespace sf;

int main() {
	std::vector<Planet> planets (100);

	RenderWindow window(VideoMode(window_width, window_height), "Gravity");
	window.setFramerateLimit(200);

	main_render_texture.create(window_width, window_height);
	main_sprite.setTexture(main_render_texture.getTexture());
	dot.setRadius(1);
	
	planets_initialization(planets);

	planets[0].setPosition(window_width / 2, 100);
	planets[0].velocity = { -0.900,0.1 };

	planets[1].setPosition(window_width / 2, 800);
	planets[1].velocity = { 0.9,-0.1 };

	planets[2].setPosition(450, 450);
	planets[2].velocity = { 0,1 };

	planets[3].setPosition(350 + window_width / 2, 450);
	planets[3].velocity = { 0,-1 };



	for (int i=0; i<all_planets_number; i++)
		planets[i].center_pos = { planets[i].getPosition().x + planets[i].radius,planets[i].getPosition().y + planets[i].radius };
	

	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed || (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape))
				window.close();
			if (event.type == Event::KeyPressed && event.key.code == Keyboard::Enter)
				start=(start+1)%2;
		}

		if (start) {
			for (int i = 0; i < all_planets_number; i++)
				planets[i].total_force = { 0,0 };

			for (int i = 0; i < all_planets_number; i++)
				for (int j = 0; j < all_planets_number; j++)
					if (i != j)
						planets[i].update_force(planets[j]);

			for (int i = 0; i < all_planets_number; i++)
				planets[i].update_pos();
		}
		
		
		main_render_texture.display();
		window.clear();
		window.draw(main_sprite);
		for (int i = 0; i < all_planets_number; i++)
			window.draw(planets[i]);
		window.display();
	}
}