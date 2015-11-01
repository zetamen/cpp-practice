#pragma once

#include <vector>

using namespace std;

enum class Point
{
	BLANK,
	START,
	BLOCK
};

class Map
{
public:
	Map(vector<string> const& matrix);
	vector<vector<Point>> GetMatrix() const;
	Point GetPoint(char const ch) const;
	char GetChar(Point const point) const;
	char GetCharValue(int x, int y) const;
	int GetWidth() const;
	int GetHeight() const;
	~Map();

	static const int WIDTH = 100;
	static const int HEIGHT = 30;
private:
	int m_width;
	int m_height;
	vector<vector<Point>> m_matrix;
};

