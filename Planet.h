#pragma once
using namespace sf;

const int window_height = 1000, window_width = 1600, all_planets_number = 4, planet_radius=10, GMM=400;
RenderTexture main_render_texture;
Sprite main_sprite;
CircleShape dot;
float cos_alf, sin_alf, force, total_distance;
Vector2f distance;
int start = 0;
Color color1(233, 123, 204);
Color color2(178, 102, 255);
Color color3(123, 127, 233);
Color color4(224, 255, 65);

class Planet : public sf::CircleShape {
public:
	Vector2f center_pos, velocity, total_force = { 0,0 };
	int radius;
	Color color;

	void update_force(Planet second_body);
	void update_pos();
};


void planets_initialization(std::vector<Planet>& planets) {
	for (int i = 0; i < all_planets_number; i++) {
		planets[i].setRadius(planet_radius);
		planets[i].radius = planet_radius;
		if (i % 4 == 0)
			planets[i].color = color1;
		else if (i % 4 == 1)
			planets[i].color = color2;
		else if (i % 4 == 2)
			planets[i].color = color3;
		else
			planets[i].color = color4;
		planets[i].setFillColor(planets[i].color);
	}
}



void Planet::update_pos() {
	dot.setPosition(center_pos);
	dot.setFillColor(color);
	main_render_texture.draw(dot);
	velocity.x += total_force.x;
	velocity.y += total_force.y;
	center_pos.x += velocity.x;
	center_pos.y += velocity.y;
	Planet::setPosition(center_pos.x - radius, center_pos.y - radius);
}

void Planet::update_force(Planet second_body) {
	distance.x = center_pos.x-second_body.center_pos.x;
	distance.y = center_pos.y - second_body.center_pos.y;
	
	force = GMM / (distance.x * distance.x + distance.y * distance.y);

	total_distance = sqrt(distance.x * distance.x + distance.y * distance.y);
	cos_alf = distance.x / total_distance;
	sin_alf = distance.y / total_distance;
	
	total_force.x -= cos_alf * force;
	total_force.y -= sin_alf * force;
}