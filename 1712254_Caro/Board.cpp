#include "Board.h"

#pragma region Constructor & Destructor

_Board::_Board(int pSize, int pX, int pY)
{
	_size = pSize;
	_left = pX;
	_top = pY;
	_pArr = new _Point*[pSize];
	for (int i = 0; i < pSize; i++)
		_pArr[i] = new _Point[pSize];
}

_Board::~_Board()
{
	for (int i = 0; i < _size; i++)
		delete[] _pArr[i];
	delete[] _pArr;
}

#pragma endregion

#pragma region Getter & Setter

int _Board::getXAt(int i, int j)
{
	return _pArr[i][j].getX();
}

int _Board::getYAt(int i, int j)
{
	return _pArr[i][j].getY();
}

#pragma endregion

#pragma region Check Win/Lose

int _Board::testBoard(int x, int y, bool turn)
{
	//Người chơi X thắng
	if (checkRow(x, y, -1))
		return -1;
	if (checkCol(x, y, -1))
		return -1;
	if (checkMainDiagonal(x, y, -1))
		return -1;
	if (checkAntiDiagonal(x, y, -1))
		return -1;

	//Người chơi O thắng
	if (checkRow(x, y, 1))
		return 1;
	if (checkCol(x, y, 1))
		return 1;
	if (checkMainDiagonal(x, y, 1))
		return 1;
	if (checkAntiDiagonal(x, y, 1))
		return 1;

	//Hòa
	if (checkDraw())
		return 0;

	//Đổi lượt
	return 2;
}

bool _Board::checkDraw()
{
	for (int i = 0; i < _size; i++)
	{
		for (int j = 0; j < _size; j++)
		{
			if (_pArr[i][j].getCheck() == 0)
				return false;
		}
	}
	return true;
}

bool _Board::checkRow(int x, int y, int check)
{
	//Đổi từ tọa độ bàn cờ sang tọa độ mảng
	int row = (x - _left - 2) / 4;
	int col = (y - _top - 1) / 2;

	//Đếm về bên trái và đếm về bên phải
	int countLeft = 0, countRight = 0;

	//Tọa độ điểm đầu cuối
	int head = row, tail = row;

	//Kiểm tra chặn 2 đầu
	bool isBlockHeadTail = false;

	//Vector lưu vị trí check
	vector <_Point*> winRow;

	int i = col, j = row;
	while (_pArr[i][j].getCheck() == check)
	{
		winRow.push_back(new _Point(_pArr[i][j].getX(), _pArr[i][j].getY()));
		countLeft++;
		if (j == 0)
			break;
		j--;
		head = j;
	}

	i = col; j = row;
	while (_pArr[i][j].getCheck() == check)
	{
		winRow.push_back(new _Point(_pArr[i][j].getX(), _pArr[i][j].getY()));
		countRight++;
		if (j == _size - 1)
			break;
		j++;
		tail = j;
	}

	if (_pArr[col][head].getCheck() == -check && _pArr[col][tail].getCheck() == -check)
		isBlockHeadTail = true;

	if ((countLeft + countRight - 1) == 5 && isBlockHeadTail == false)
	{
		char chessman;
		int a = 14, b = 12, c = 13, d = 10;
		if (check == -1)	chessman = 'X';		else chessman = 'O';

		_Common::hideCursor();
		_Common::winRowAudio(_Common::AUDIO_STATUS);

		for (int k = 0; k < 7; k++)
		{
			for (int i = 0; i < winRow.size(); i++)
			{
				_Common::setColor(a);
				_Common::gotoXY(winRow[i]->getX(), winRow[i]->getY(), chessman);
			}

			int temp = d;
			d = c;			c = b;			b = a;			a = temp;
			Sleep(150);
		}
		return true;
	}
	else
	{
		winRow.clear();
		return false;
	}
}

bool _Board::checkCol(int x, int y, int check)
{
	//Đổi từ tọa độ bàn cờ sang tọa độ mảng
	int row = (x - _left - 2) / 4;
	int col = (y - _top - 1) / 2;

	//Đếm về bên trái và đếm về bên phải
	int countLeft = 0, countRight = 0;

	//Tọa độ điểm đầu cuối
	int head = col, tail = col;

	//Kiểm tra chặn 2 đầu
	bool isBlockHeadTail = false;

	//Vector lưu vị trí check
	vector <_Point*> winRow;

	int i = col, j = row;
	while (_pArr[i][j].getCheck() == check)
	{
		winRow.push_back(new _Point(_pArr[i][j].getX(), _pArr[i][j].getY()));
		countLeft++;
		if (i == 0)
			break;
		i--;
		head = i;
	}

	i = col; j = row;
	while (_pArr[i][j].getCheck() == check)
	{
		winRow.push_back(new _Point(_pArr[i][j].getX(), _pArr[i][j].getY()));
		countRight++;
		if (i == _size - 1)
			break;
		i++;
		tail = i;
	}

	if (_pArr[head][row].getCheck() == -check && _pArr[tail][row].getCheck() == -check)
		isBlockHeadTail = true;

	if ((countLeft + countRight - 1) == 5 && isBlockHeadTail == false)
	{
		char chessman;
		int a = 14, b = 12, c = 13, d = 10;
		if (check == -1)	chessman = 'X';		else chessman = 'O';

		_Common::hideCursor();
		_Common::winRowAudio(_Common::AUDIO_STATUS);

		for (int k = 0; k < 7; k++)
		{
			for (int i = 0; i < winRow.size(); i++)
			{
				_Common::setColor(a);
				_Common::gotoXY(winRow[i]->getX(), winRow[i]->getY(), chessman);
			}

			int temp = d;
			d = c;			c = b;			b = a;			a = temp;
			Sleep(150);
		}
		return true;
	}
	else
	{
		winRow.clear();
		return false;
	}
}

bool _Board::checkMainDiagonal(int x, int y, int check)
{
	//Đổi từ tọa độ bàn cờ sang tọa độ mảng
	int row = (x - _left - 2) / 4;
	int col = (y - _top - 1) / 2;

	//Đếm về bên trái và đếm về bên phải
	int countLeft = 0, countRight = 0;

	//Tọa độ điểm đầu cuối
	int head = col, tail = col;

	//Kiểm tra chặn 2 đầu
	bool isBlockHeadTail = false;

	//Vector lưu vị trí check
	vector <_Point*> winRow;

	int i = col, j = row;
	while (_pArr[i][j].getCheck() == check)
	{
		winRow.push_back(new _Point(_pArr[i][j].getX(), _pArr[i][j].getY()));
		countLeft++;
		if (i == 0 || j == 0)
			break;
		i--;
		j--;
		head = i;
	}

	i = col; j = row;
	while (_pArr[i][j].getCheck() == check)
	{
		winRow.push_back(new _Point(_pArr[i][j].getX(), _pArr[i][j].getY()));
		countRight++;
		if (i == _size - 1 || j == _size - 1)
			break;
		i++;
		j++;
		tail = i;
	}

	if (_pArr[head][head].getCheck() == -check && _pArr[tail][tail].getCheck() == -check)
		isBlockHeadTail = true;

	if ((countLeft + countRight - 1) == 5 && isBlockHeadTail == false)
	{
		char chessman;
		int a = 14, b = 12, c = 13, d = 10;
		if (check == -1)	chessman = 'X';		else chessman = 'O';

		_Common::hideCursor();
		_Common::winRowAudio(_Common::AUDIO_STATUS);

		for (int k = 0; k < 7; k++)
		{
			for (int i = 0; i < winRow.size(); i++)
			{
				_Common::setColor(a);
				_Common::gotoXY(winRow[i]->getX(), winRow[i]->getY(), chessman);
			}

			int temp = d;
			d = c;			c = b;			b = a;			a = temp;
			Sleep(150);
		}
		return true;
	}
	else
	{
		winRow.clear();
		return false;
	}
}

bool _Board::checkAntiDiagonal(int x, int y, int check)
{
	//Đổi từ tọa độ bàn cờ sang tọa độ mảng
	int row = (x - _left - 2) / 4;
	int col = (y - _top - 1) / 2;

	//Đếm về bên trái và đếm về bên phải
	int countLeft = 0, countRight = 0;

	//Tọa độ điểm đầu cuối
	int head_x = col, head_y = row;
	int tail_x = col, tail_y = row;

	//Kiểm tra chặn 2 đầu
	bool isBlockHeadTail = false;

	//Vector lưu vị trí check
	vector <_Point*> winRow;

	int i = col, j = row;
	while (_pArr[i][j].getCheck() == check)
	{
		winRow.push_back(new _Point(_pArr[i][j].getX(), _pArr[i][j].getY()));
		countLeft++;
		if (i == 0 || j == _size - 1)
			break;
		i--;
		j++;
		head_x = i;
		head_y = j;
	}

	i = col; j = row;
	while (_pArr[i][j].getCheck() == check)
	{
		winRow.push_back(new _Point(_pArr[i][j].getX(), _pArr[i][j].getY()));
		countRight++;
		if (i == _size - 1 || j == 0)
			break;
		i++;
		j--;
		tail_x = i;
		tail_y = j;
	}

	if (_pArr[head_x][head_y].getCheck() == -check && _pArr[tail_x][tail_y].getCheck() == -check)
		isBlockHeadTail = true;

	if ((countLeft + countRight - 1) == 5 && isBlockHeadTail == false)
	{
		char chessman;
		int a = 14, b = 12, c = 13, d = 10;
		if (check == -1)	chessman = 'X';		else chessman = 'O';

		_Common::hideCursor();
		_Common::winRowAudio(_Common::AUDIO_STATUS);

		for (int k = 0; k < 7; k++)
		{
			for (int i = 0; i < winRow.size(); i++)
			{
				_Common::setColor(a);
				_Common::gotoXY(winRow[i]->getX(), winRow[i]->getY(), chessman);
			}

			int temp = d;
			d = c;			c = b;			b = a;			a = temp;
			Sleep(150);
		}
		return true;
	}
	else
	{
		winRow.clear();
		return false;
	}
}

#pragma endregion

#pragma region Others

void _Board::resetData()
{
	if (_size == 0)
		return;

	for (int i = 0; i < _size; i++)
	{
		for (int j = 0; j < _size; j++)
		{
			_pArr[i][j].setX(4 * j + _left + 2);	//Trùng với hoành độ màn hình bàn cờ
			_pArr[i][j].setY(2 * i + _top + 1);		//Trùng với tung độ màn hình bàn cờ
			_pArr[i][j].setCheck(0);
		}
	}
}

void _Board::loadBoard(int i, int j, int check)
{
	_pArr[i][j].setX(4 * j + _left + 2);
	_pArr[i][j].setY(2 * i + _top + 1);
	_pArr[i][j].setCheck(check);

	if (check == -1)
		_Common::gotoXY(4 * j + _left + 2, 2 * i + _top + 1, "X", 12);

	if (check == 1)
		_Common::gotoXY(4 * j + _left + 2, 2 * i + _top + 1, "O", 10);
}

void _Board::drawBoard()
{
	//Vẽ khung
	_Common::hideCursor();
	_Common::setColor(15);
	_Common::drawFrame(2, 0, 0, 112, 37, 0, 4);

	//Vẽ bàn cờ
	_Common::gotoXY(_left, _top);
	cout << char(218);
	for (int i = 0; i < _size - 1; i++)
		cout << char(196) << char(196) << char(196) << char(194);
	cout << char(196) << char(196) << char(196) << char(191);

	for (int i = 0; i < _size; i++) {
		_Common::gotoXY(_left, _top + 2 * i + 1);

		for (int j = 0; j <= _size; j++)
			cout << char(179) << "   ";

		if (i != _size - 1) {
			_Common::gotoXY(_left, _top + 2 * i + 2);
			cout << char(195);

			for (int j = 0; j < _size - 1; j++)
				cout << char(196) << char(196) << char(196) << char(197);

			cout << char(196) << char(196) << char(196) << char(180);
		}
	}

	_Common::gotoXY(_left, _top + 2 * _size);
	cout << char(192);
	for (int i = 0; i < _size - 1; i++)
		cout << char(196) << char(196) << char(196) << char(193);
	cout << char(196) << char(196) << char(196) << char(217);
}

int _Board::checkBoard(int pX, int pY, bool pTurn)
{
	for (int i = 0; i < _size; i++)
	{
		for (int j = 0; j < _size; j++)
		{
			if (_pArr[i][j].getX() == pX && _pArr[i][j].getY() == pY && _pArr[i][j].getCheck() == 0)
			{
				if (pTurn)
					_pArr[i][j].setCheck(-1);	//Nếu lượt hiện hành là true: check = -1
				else
					_pArr[i][j].setCheck(1);	//Nếu lượt hiện hành là false: check = 1
				return _pArr[i][j].getCheck();
			}
		}
	}
	return 0;
}

#pragma endregion