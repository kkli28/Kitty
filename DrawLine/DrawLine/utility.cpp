#include "Utility.h"
#include "svpng.h"

const int Utility::SCREEN_WIDTH = 640;
const int Utility::SCREEN_HEIGHT = 640;
const int Utility::PIXEL_WIDTH = 2;
const int Utility::LOGIC_WIDTH = SCREEN_WIDTH / PIXEL_WIDTH;
const int Utility::LOGIC_HEIGHT = SCREEN_HEIGHT / PIXEL_WIDTH;
const int Utility::BORDER_WIDTH = 2;

void Utility::save(Image image, std::string fileName) {
	Color* data = new Color[SCREEN_WIDTH * SCREEN_HEIGHT];
	for (int h = 0; h < LOGIC_HEIGHT; ++h) {
		for (int w = 0; w < LOGIC_WIDTH; ++w) {
			Color c = image[h * LOGIC_WIDTH + w];
			for (int i = 0; i < PIXEL_WIDTH; ++i) {
				for (int j = 0; j < PIXEL_WIDTH; ++j) {
					data[(h * PIXEL_WIDTH + i) * SCREEN_WIDTH + w * PIXEL_WIDTH + j] = c;
				}
			}
		}
	}

	// N个像素宽度的白色边框
	for (int i = 0; i < SCREEN_WIDTH; ++i) {
		for (int w = 0; w < BORDER_WIDTH; ++w) {
			data[w * SCREEN_WIDTH + i] = WHITE;
			data[(SCREEN_HEIGHT - 1 - w)*SCREEN_WIDTH + i] = WHITE;
		}
	}
	for (int i = 0; i < SCREEN_HEIGHT; ++i) {
		for (int w = 0; w < BORDER_WIDTH; ++w) {
			data[i * SCREEN_WIDTH + w] = WHITE;
			data[i * SCREEN_WIDTH + SCREEN_HEIGHT - 1 - w] = WHITE;
		}
	}

	FILE* fp = fopen(fileName.c_str(), "wb");
	const unsigned char* pData = reinterpret_cast<const unsigned char*>(data);
	svpng(fp, SCREEN_WIDTH, SCREEN_HEIGHT, pData, 1);
}

void Utility::setColor(Image image, int x, int y, Color c) {
	image[y * LOGIC_WIDTH + x] = c;
}

void Utility::setImage(Image image, Color c) {
	for (int i = 0; i < LOGIC_WIDTH; ++i) {
		for (int j = 0; j < LOGIC_HEIGHT; ++j) {
			image[j * LOGIC_WIDTH + i] = c;
		}
	}
}

void Utility::addLine(Image image, Point beg, Point end, Color c, DrawType type)
{
	switch (type) {
	case DrawType::NORMAL: return addLineNormal(image, beg, end, c);
	case DrawType::DDA: return addLineDDA(image, beg, end, c);
	case DrawType::BRESENHAM: return addLineBresenham(image, beg, end, c);
	}
}

void Utility::addLineNormal(Image image, Point beg, Point end, Color c) {
	// TODO: 增加线段剪裁
	if (beg.x == end.x || beg.y == end.y) {
		return handleVHLine(image, beg, end, c);
	}

	float k = (end.y - beg.y) / (end.x - beg.x);
	float ik = 1 / k;
	float b = beg.y - k * beg.x;
	if (fabs(k) > 1) {
		if (beg.y > end.y) std::swap(beg, end);
		for (int y = beg.y; y <= end.y; ++y) {
			setColor(image, (y - b)*ik, y, c);
		}
	}
	else {
		if (beg.x > end.x) std::swap(beg, end);
		for (int x = beg.x; x <= end.x; ++x) {
			setColor(image, x, k*x + b, c);
		}
	}
}

void Utility::addLineDDA(Image image, Point beg, Point end, Color c) {
	if (beg.x == end.x || beg.y == end.y) {
		return handleVHLine(image, beg, end, c);
	}

	int dx = end.x - beg.x;
	int dy = end.y - beg.y;
	int steps = fabs(dx) > fabs(dy) ? dx : dy;
	float xInc = float(dx) / steps;
	float yInc = float(dy) / steps;
	float x = beg.x;
	float y = beg.y;
	setColor(image, x, y, c);
	for (int i = 0; i < steps; ++i) {
		x += xInc;
		y += yInc;
		setColor(image, x, y, c);
	}
}

void Utility::addLineBresenham(Image image, Point beg, Point end, Color c) {
	if (beg.x == end.x || beg.y == end.y) {
		return handleVHLine(image, beg, end, c);
	}
	
	int dx = end.x - beg.x;
	int dy = end.y - beg.y;
	int d1 = 2 * dy;
	int d2 = 2 * dy - 2 * dx;
	int err = 2 * dy - dx;
	setColor(image, beg.x, beg.y, c);
	int x = beg.x;
	int y = beg.y;
	while (x <= end.x) {
		++x;
		if (err > 0) {
			err += d2;
			++y;
		}
		else {
			err += d1;
		}
		setColor(image, x, y, c);
	}
}

void Utility::handleVHLine(Image image, Point beg, Point end, Color c) {
	if (beg.x == end.x && beg.y == end.y) {
		setColor(image, beg.x, beg.y, c);
	}
	else if (beg.x == end.x) {
		for (int y = std::min(beg.y, end.y); y <= std::max(beg.y, end.y); ++y) {
			setColor(image, beg.x, y, c);
		}
	}
	else if (beg.y == end.y) {
		for (int x = std::min(beg.x, end.x); x <= std::max(beg.x, end.x); ++x) {
			setColor(image, x, beg.y, c);
		}
	}
}

void Utility::safeSet(Image image, int x, int y, Color c) {
	if (x < 0 || x >= LOGIC_WIDTH || y < 0 || y >= LOGIC_HEIGHT) return;
	image[x * LOGIC_WIDTH + y] = c;
}

void Utility::addCircle(Image image, Point center, int r, Color c) {
	// 半径小于等于1，画一个点
	if (r < 1) {
		setColor(image, center.x, center.y, c);
		return;
	}

	auto setColorForCircle = [image, center, c](int x, int y) {
		safeSet(image, center.x + x, center.y + y, c);
		safeSet(image, center.x + x, center.y - y, c);
		safeSet(image, center.x - x, center.y + y, c);
		safeSet(image, center.x - x, center.y - y, c);
		safeSet(image, center.x + y, center.y + x, c);
		safeSet(image, center.x + y, center.y - x, c);
		safeSet(image, center.x - y, center.y + x, c);
		safeSet(image, center.x - y, center.y - x, c);
	};
	
	int x = 0;
	int y = r;
	int p = 1 - r;
	setColorForCircle(x, y);
	while (x <= y) {
		++x;
		if (p < 0) {
			p += 2 * x + 1;
		}
		else {
			--y;
			p += 2 * x + 1 - 2 * y;
		}
		setColorForCircle(x, y);
	}
}

void Utility::addEllipse(Image image, Point center, int rx, int ry, Color c)
{
	if (rx < 0 || ry < 0) {
		setColor(image, center.x, center.y, c);
		return;
	}

	auto setColorForEllipse = [image, center, c](int x, int y) {
		safeSet(image, center.x + x, center.y + y, c);
		safeSet(image, center.x + x, center.y - y, c);
		safeSet(image, center.x - x, center.y + y, c);
		safeSet(image, center.x - x, center.y - y, c);
	};

	int rx2 = rx * rx;
	int ry2 = ry * ry;
	int twoRx2 = 2 * rx2;
	int twoRy2 = 2 * ry2;
	int px = 0;
	int py = twoRx2 * ry;
	int x = 0;
	int y = ry;
	setColorForEllipse(x, y);

	// region 1: |k| < 1
	int p = ry2 - rx2 * ry + rx2 * 0.25;
	while (px < py) {
		++x;
		px += twoRy2;
		if (p < 0) {
			p += ry2 + px;
		}
		else {
			--y;
			py -= twoRx2;
			p += ry2 + px - py;
		}
		setColorForEllipse(x, y);
	}

	// region 2: |k| >= 1
	p = ry2 * (x + 0.5) * (x + 0.5) + rx2 * (y - 1) * (y - 1) - rx2 * ry2;
	while (y > 0) {
		--y;
		py -= twoRx2;
		if (p > 0) {
			p += rx2 - py;
		}
		else {
			++x;
			px += twoRy2;
			p += rx2 - py + px;
		}
		setColorForEllipse(x, y);
	}
}
