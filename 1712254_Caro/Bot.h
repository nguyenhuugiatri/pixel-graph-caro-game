#pragma once
#include "Board.h"

class _Bot
{
private:
	int _level;		//1: Ease, 2: Hard
	int _moveRow;	//Tọa độ mà máy sẽ đi
	int _moveCol;
	int attackScoreArray[7] = { 0, 9, 54, 162, 1458, 13112, 118008 };	//Mảng điểm tấn công
	int defenceScoreArray[7] = { 0, 3, 27, 99, 729, 6561, 59049 };		//Mảng điểm tấn công

public:
#pragma region Constructot & Destructor
	_Bot(int);
#pragma endregion

#pragma region Getter & Setter
	int getMoveRow() { return _moveRow; }
	int getMoveCol() { return _moveCol; }
	void setLevel(int level) { _level = level; }
#pragma endregion

#pragma region Calculate Score
	int attackScoreOfCol(_Board *&, int, int);
	int attackScoreOfRow(_Board *&, int, int);
	int attackScoreOfMainDiagonal(_Board *&, int, int);
	int attackScoreOfAntiDiagonal(_Board *&, int, int);
	int defenceScoreOfCol(_Board *&, int, int);
	int defenceScoreOfRow(_Board *&, int, int);
	int defenceScoreOfMainDiagonal(_Board *&, int, int);
	int defenceScoreOfAntiDiagonal(_Board *&, int, int);
#pragma endregion

#pragma region Main Method
	void findRandomMove(_Board *&);
	void findBestMove(_Board *&);
	void sign(_Board *&);
#pragma endregion
};

