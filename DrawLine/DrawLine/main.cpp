#define _CRT_SECURE_NO_WARNINGS

#include "utility.h"

int main() {
	Image image = Utility::newImage();
	Utility::setImage(image, BLACK);
	Color colors[] = { WHITE, RED, GREEN, BLUE };
	///*
	for (int i = 0; i < 100; ++i) {
		Point beg;
		beg.x = rand() % Utility::LOGIC_WIDTH;
		beg.y = rand() % Utility::LOGIC_HEIGHT;
		Point end;
		end.x = rand() % Utility::LOGIC_WIDTH;
		end.y = rand() % Utility::LOGIC_HEIGHT;
		Utility::addLine(image, beg, end, colors[rand() % 4], DrawType::DDA);
	}
	//*/
	/*
	Utility::addLine(image, Point{ 10, 10 }, Point{ 140, 40 }, colors[0], DrawType::BRESENHAM);
	Utility::addLine(image, Point{ 10, 10 }, Point{ 100, 80 }, colors[1], DrawType::BRESENHAM);
	//*/
	Utility::save(image);
	return 0;
}
