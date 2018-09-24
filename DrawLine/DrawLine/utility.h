#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <string>

struct Color {
	unsigned char r;
	unsigned char g;
	unsigned char b;
	unsigned char a;
};
typedef Color* Image;

const Color WHITE = Color{ 255, 255, 255, 255 };
const Color RED = Color{ 255, 0, 0, 255 };
const Color GREEN = Color{ 0, 255, 0, 255 };
const Color BLUE = Color{ 0, 0, 255, 255 };
const Color BLACK = Color{ 0, 0, 0, 255 };
const Color TRANS = Color{ 0, 0, 0, 0 };

// 三种画直线的算法
enum class DrawType {
	NORMAL,
	DDA,
	BRESENHAM
};

struct Point {
	float x;
	float y;
};

class Utility {
public:
	// 屏幕宽度
	static const int SCREEN_WIDTH;

	// 屏幕高度
	static const int SCREEN_HEIGHT;

	// 逻辑宽度
	static const int LOGIC_WIDTH;

	// 逻辑高度
	static const int LOGIC_HEIGHT;

	// 一个逻辑像素对应的实际像素宽度
	static const int PIXEL_WIDTH;
	
	// 边框宽度
	static const int BORDER_WIDTH;

public:

	// 将图片信息输出到 image.png
	static void save(Image image, std::string fileName = "image.png");
	
	// 设置 image 中 (x, y) 坐标处的颜色值为 c
	static void setColor(Image image, int x, int y, Color c);

	// 向 image 中添加一条起点为 beg，终点为 end，颜色为 c 的直线，并使用 type 算法绘制
	static void addLine(Image image, Point beg, Point end, Color c, DrawType type = DrawType::NORMAL);

	// 新建一张图片
	static Image newImage() { return new Color[LOGIC_WIDTH * LOGIC_HEIGHT]; }

	// 将整个图片设置为一种颜色
	static void setImage(Image image, Color c);

private:
	// 用 y = kx + c 公式画线
	static void addLineNormal(Image image, Point beg, Point end, Color c);
	
	// 用 DDA 算法
	static void addLineDDA(Image image, Point beg, Point end, Color c);

	// 用 Bresenham 算法
	static void addLineBresenham(Image image, Point beg, Point end, Color c);

	// 直线剪裁
	static void lineClipping(Point& beg, Point& end); /* TODO */
	
	// 处理水平或垂直的线
	static void handleVHLine(Image image, Point beg, Point end, Color c);
};

/*
TODO:
#. 完善 Bresenham 算法
#. 增加直线剪裁算法
#. 增加线条粗细设置
#. 线条颜色渐变
*/
