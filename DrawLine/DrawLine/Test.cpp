#include "Test.h"

void Test::drawLine(Image image, DrawType type) {
	Utility::setImage(image, BLACK);
	Color colors[] = { WHITE, RED, GREEN, BLUE };
	for (int i = 0; i < 100; ++i) {
		Point beg;
		beg.x = rand() % Utility::LOGIC_WIDTH;
		beg.y = rand() % Utility::LOGIC_HEIGHT;
		Point end;
		end.x = rand() % Utility::LOGIC_WIDTH;
		end.y = rand() % Utility::LOGIC_HEIGHT;
		Utility::addLine(image, beg, end, colors[rand() % 4], type);
	}
	/*
	Utility::addLine(image, Point{ 10, 10 }, Point{ 140, 40 }, colors[0], DrawType::BRESENHAM);
	Utility::addLine(image, Point{ 10, 10 }, Point{ 100, 80 }, colors[1], DrawType::BRESENHAM);
	//*/
}

void Test::drawCircle(Image image) {
	Color colors[] = { WHITE, RED, GREEN, BLUE };
	for (int i = 0; i < 100; ++i) {
		Point center;
		center.x = rand() % Utility::LOGIC_WIDTH;
		center.y = rand() % Utility::LOGIC_HEIGHT;
		Utility::addCircle(image, center, rand() % Utility::LOGIC_WIDTH / 2, colors[rand() % 4]);
	}
}
