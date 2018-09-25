#pragma once
#include "Utility.h"

class Test {
public:
	static void drawLine(Image image, DrawType type = DrawType::DDA);
	static void drawCircle(Image image);
	static void drawEllipse(Image image);

public:
	static const Color COLORS[4];
};
