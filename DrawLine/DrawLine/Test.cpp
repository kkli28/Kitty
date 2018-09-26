#include "Test.h"

const Color Test::COLORS[4] = { WHITE, RED, GREEN, BLUE };

void Test::drawLine(Image image, DrawType type) {
	for (int i = 0; i < 100; ++i) {
		Point beg;
		beg.x = rand() % Utility::LOGIC_WIDTH;
		beg.y = rand() % Utility::LOGIC_HEIGHT;
		Point end;
		end.x = rand() % Utility::LOGIC_WIDTH;
		end.y = rand() % Utility::LOGIC_HEIGHT;
		Utility::addLine(image, beg, end, COLORS[rand() % 4], type);
	}
	/*
	Utility::addLine(image, Point{ 10, 10 }, Point{ 140, 40 }, colors[0], DrawType::BRESENHAM);
	Utility::addLine(image, Point{ 10, 10 }, Point{ 100, 80 }, colors[1], DrawType::BRESENHAM);
	//*/
}

void Test::drawCircle(Image image) {
	for (int i = 0; i < 100; ++i) {
		Point center;
		center.x = rand() % Utility::LOGIC_WIDTH;
		center.y = rand() % Utility::LOGIC_HEIGHT;
		Utility::addCircle(image, center, rand() % Utility::LOGIC_WIDTH / 2, COLORS[rand() % 4]);
	}
}

void Test::drawEllipse(Image image) {
	for (int i = 0; i < 40; ++i) {
		Point center;
		center.x = rand() % Utility::LOGIC_WIDTH;
		center.y = rand() % Utility::LOGIC_HEIGHT;
		Utility::addEllipse(image, center, rand() % (Utility::LOGIC_WIDTH / 2), rand() % (Utility::LOGIC_HEIGHT / 2), COLORS[rand() % 4]);
	}
}
