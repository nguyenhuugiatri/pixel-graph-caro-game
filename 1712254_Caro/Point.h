#pragma once

class _Point
{
	int _x, _y;
	int _check;

public:
#pragma region Constructor & Destructor

	_Point()
	{
		_x = _y = 0;
		_check = 0;
	}

	_Point(int pX, int pY)
	{
		_x = pX;
		_y = pY;
		_check = 0;
	}

#pragma endregion

#pragma region Getter & Setter

	int getX() { return _x; }
	int getY() { return _y; }
	void setX(int pX) { _x = pX; }
	void setY(int pY) { _y = pY; }
	int getCheck() { return _check; }

	bool setCheck(int pCheck)
	{
		if (pCheck == -1 || pCheck == 1 || pCheck == 0)
		{
			_check = pCheck;
			return true;
		}
		return false;
	}

#pragma endregion
};