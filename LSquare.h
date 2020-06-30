#pragma once

class LSquare
{
private:
	int vertical;
	int horizontal;
	int color;
	int state;

public:
	LSquare(int vertical, int horizontal, int color);

	int getVertical();
	int getHorizontal();
	int getColor();
	int getState();

	void setState(int state);
	void setPosition(int vertical, int horizontal);

	void draw(bool reverse);

};

