#pragma once
#include "Common.h"
#include "Point.h"

class _Board
{
private:
	int _size;			//Kích thước bàn cờ
	int _left, _top;	//Điểm bắt đầu
	_Point** _pArr;		//Mảng kiểu Point

public:
#pragma region Constructor & Destructor
	_Board(int, int, int);
	~_Board();
#pragma endregion

#pragma region Getter & Setter
	int getSize() { return _size; }
	int getLeft() { return _left; }
	int getTop() { return _top; }
	_Point& getPointAt(int i, int j) { return _pArr[i][j]; }
	int getXAt(int, int);
	int getYAt(int, int);
#pragma endregion

#pragma region Check Win/Lose
	int testBoard(int, int, bool);			//Kiểm tra thắng thua
	bool checkDraw();						//Kiểm tra hòa
	bool checkRow(int, int, int);			//Kiểm tra hàng ngang
	bool checkCol(int, int, int);			//Kiểm tra hàng dọc
	bool checkMainDiagonal(int, int, int);	//Kiểm tra đường chéo chính
	bool checkAntiDiagonal(int, int, int);	//Kiểm tra đường chéo phụ
#pragma endregion

#pragma region Others
	void resetData();					//Đưa về bàn cờ mặc định
	void loadBoard(int, int, int);		//Tải lại bàn cờ
	void drawBoard();					//Vẽ bàn cờ
	int checkBoard(int, int, bool);		//Đánh dấu lại nước đã đi
#pragma endregion
};