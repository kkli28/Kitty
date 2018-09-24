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

// ���ֻ�ֱ�ߵ��㷨
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
	// ��Ļ���
	static const int SCREEN_WIDTH;

	// ��Ļ�߶�
	static const int SCREEN_HEIGHT;

	// �߼����
	static const int LOGIC_WIDTH;

	// �߼��߶�
	static const int LOGIC_HEIGHT;

	// һ���߼����ض�Ӧ��ʵ�����ؿ��
	static const int PIXEL_WIDTH;
	
	// �߿���
	static const int BORDER_WIDTH;

public:

	// ��ͼƬ��Ϣ����� image.png
	static void save(Image image, std::string fileName = "image.png");
	
	// ���� image �� (x, y) ���괦����ɫֵΪ c
	static void setColor(Image image, int x, int y, Color c);

	// �� image �����һ�����Ϊ beg���յ�Ϊ end����ɫΪ c ��ֱ�ߣ���ʹ�� type �㷨����
	static void addLine(Image image, Point beg, Point end, Color c, DrawType type = DrawType::NORMAL);

	// �½�һ��ͼƬ
	static Image newImage() { return new Color[LOGIC_WIDTH * LOGIC_HEIGHT]; }

	// ������ͼƬ����Ϊһ����ɫ
	static void setImage(Image image, Color c);

private:
	// �� y = kx + c ��ʽ����
	static void addLineNormal(Image image, Point beg, Point end, Color c);
	
	// �� DDA �㷨
	static void addLineDDA(Image image, Point beg, Point end, Color c);

	// �� Bresenham �㷨
	static void addLineBresenham(Image image, Point beg, Point end, Color c);

	// ֱ�߼���
	static void lineClipping(Point& beg, Point& end); /* TODO */
	
	// ����ˮƽ��ֱ����
	static void handleVHLine(Image image, Point beg, Point end, Color c);
};

/*
TODO:
#. ���� Bresenham �㷨
#. ����ֱ�߼����㷨
#. ����������ϸ����
#. ������ɫ����
*/
