#define _CRT_SECURE_NO_WARNINGS

#include "Utility.h"
#include "Test.h"

int main() {
	Image image = Utility::newImage();
	//Test::drawLine(image, DrawType::DDA);
	Test::drawCircle(image);
	Utility::save(image, "circle.png");
	return 0;
}
