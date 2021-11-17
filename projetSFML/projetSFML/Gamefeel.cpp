#include "Gamefeel.h"

void InitializeArray(float middleScreenX, float middleScreenY) {
	//On commence à gauche du cercle
	int x = middleScreenX - circleRadius;
	int y = middleScreenY;
	bool arcHG = false;
	bool arcHD = false;
	bool arcBD = false;
	bool arcBG = false;

	for (int i = 0; i < 360; i++) {
		sf::Vertex vertexCenter;
		vertexCenter.position = sf::Vector2f(middleScreenX, middleScreenY);
		vertexCenter.color = sf::Color::Black;

		sf::Vertex vertexCircle;
		vertexCircle.position = sf::Vector2f(x, y);
		vertexCircle.color = sf::Color::Red;

		sf::VertexArray line(sf::LineStrip, 2);
		line[0].position = vertexCenter.position;
		line[0].color = vertexCenter.color;
		line[1].position = vertexCircle.position;
		line[1].color = vertexCircle.color;

		if (x == middleScreenX - circleRadius && y == middleScreenY) {
			arcHG = true;
			arcHD = false;
			arcBD = false;
			arcBG = false;
		}
		if (arcHG) {
			x += 1;
			y -= 1;
		}
		if (x == middleScreenX && y == middleScreenY - circleRadius) {
			arcHG = false;
			arcHD = true;
			arcBD = false;
			arcBG = false;
		}
		if (arcHD) {
			x += 1;
			y += 1;
		}
		if (x == middleScreenX && y == middleScreenY - circleRadius) {
			arcHG = false;
			arcHD = false;
			arcBD = true;
			arcBG = false;
		}
		if (arcBD) {
			x -= 1;
			y += 1;
		}
		if (x == middleScreenX && y == middleScreenY - circleRadius) {
			arcHG = false;
			arcHD = false;
			arcBD = false;
			arcBG = true;
		}
		if (arcBG) {
			x -= 1;
			y -= 1;
		}
	}
}