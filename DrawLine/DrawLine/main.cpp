#define _CRT_SECURE_NO_WARNINGS

#include "Utility.h"
#include "Test.h"

int main() {
	Image image = Utility::newImage();
	Utility::setImage(image, BLACK);
	//Test::drawLine(image, DrawType::DDA);
	//Test::drawCircle(image);
	Test::drawEllipse(image);
	Utility::save(image, "ellipse.png");
	return 0;
}
