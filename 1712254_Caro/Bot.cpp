#include "Bot.h"

#pragma region Constructor & Destructor

_Bot::_Bot(int level)
{
	_level = level;
}

#pragma endregion

#pragma region Calculate Score

int _Bot::attackScoreOfCol(_Board *& b, int currRow, int currCol)
{
	int totalScore = 0;
	int amountEnemy = 0;
	int amountFriend = 0;

	for (int i = 1; i <= 5 && currRow + i < b->getSize(); i++)
	{
		if (b->getPointAt(currRow + i, currCol).getCheck() == 1)
			amountFriend++;

		else if (b->getPointAt(currRow + i, currCol).getCheck() == -1)
		{
			amountEnemy++;
			totalScore -= 9;
			break;
		}
		else
			break;
	}

	for (int i = 1; i <= 5 && currRow - i >= 0; i++)
	{
		if (b->getPointAt(currRow - i, currCol).getCheck() == 1)
			amountFriend++;
		else if (b->getPointAt(currRow - i, currCol).getCheck() == -1)
		{
			amountEnemy++;
			totalScore -= 9;
			break;
		}
		else
			break;
	}

	if (amountEnemy == 2)
		return 0;

	totalScore += attackScoreArray[amountFriend];
	totalScore -= attackScoreArray[amountEnemy];

	return totalScore;
}

int _Bot::attackScoreOfRow(_Board *& b, int currRow, int currCol)
{
	int totalScore = 0;
	int amountEnemy = 0;
	int amountFriend = 0;

	for (int i = 1; i <= 5 && currCol + i < b->getSize(); i++)
	{
		if (b->getPointAt(currRow, currCol + i).getCheck() == 1)
			amountFriend++;

		else if (b->getPointAt(currRow, currCol + i).getCheck() == -1)
		{
			amountEnemy++;
			totalScore -= 9;
			break;
		}
		else
			break;
	}

	for (int i = 1; i <= 5 && currCol - i >= 0; i++)
	{
		if (b->getPointAt(currRow, currCol - i).getCheck() == 1)
			amountFriend++;
		else if (b->getPointAt(currRow, currCol - i).getCheck() == -1)
		{
			amountEnemy++;
			totalScore -= 9;
			break;
		}
		else
			break;
	}

	if (amountEnemy == 2)
		return 0;

	totalScore += attackScoreArray[amountFriend];
	totalScore -= attackScoreArray[amountEnemy];

	return totalScore;
}

int _Bot::attackScoreOfMainDiagonal(_Board *& b, int currRow, int currCol)
{
	int totalScore = 0;
	int amountEnemy = 0;
	int amountFriend = 0;

	for (int i = 1; i <= 5 && currRow + i < b->getSize() && currCol + i < b->getSize(); i++)
	{
		if (b->getPointAt(currRow + i, currCol + i).getCheck() == 1)
			amountFriend++;

		else if (b->getPointAt(currRow + i, currCol + i).getCheck() == -1)
		{
			amountEnemy++;
			totalScore -= 9;
			break;
		}
		else
			break;
	}

	for (int i = 1; i <= 5 && currRow - i >= 0 && currCol - i >= 0; i++)
	{
		if (b->getPointAt(currRow - i, currCol - i).getCheck() == 1)
			amountFriend++;
		else if (b->getPointAt(currRow - i, currCol - i).getCheck() == -1)
		{
			amountEnemy++;
			totalScore -= 9;
			break;
		}
		else
			break;
	}

	if (amountEnemy == 2)
		return 0;

	totalScore += attackScoreArray[amountFriend];
	totalScore -= attackScoreArray[amountEnemy];

	return totalScore;
}

int _Bot::attackScoreOfAntiDiagonal(_Board *& b, int currRow, int currCol)
{
	int totalScore = 0;
	int amountEnemy = 0;
	int amountFriend = 0;

	for (int i = 1; i <= 5 && currRow - i >= 0 && currCol + i < b->getSize(); i++)
	{
		if (b->getPointAt(currRow - i, currCol + i).getCheck() == 1)
			amountFriend++;

		else if (b->getPointAt(currRow - i, currCol + i).getCheck() == -1)
		{
			amountEnemy++;
			totalScore -= 9;
			break;
		}
		else
			break;
	}

	for (int i = 1; i <= 5 && currRow + i < b->getSize() && currCol - i >= 0; i++)
	{
		if (b->getPointAt(currRow + i, currCol - i).getCheck() == 1)
			amountFriend++;
		else if (b->getPointAt(currRow + i, currCol - i).getCheck() == -1)
		{
			amountEnemy++;
			totalScore -= 9;
			break;
		}
		else
			break;
	}

	if (amountEnemy == 2)
		return 0;

	totalScore += attackScoreArray[amountFriend];
	totalScore -= attackScoreArray[amountEnemy];

	return totalScore;
}

int _Bot::defenceScoreOfCol(_Board *& b, int currRow, int currCol)
{
	int totalScore = 0;
	int amountEnemy = 0;
	int amountFriend = 0;

	for (int i = 1; i <= 5 && currRow + i < b->getSize(); i++)
	{
		if (b->getPointAt(currRow + i, currCol).getCheck() == 1)
		{
			amountFriend++;
			break;
		}

		else if (b->getPointAt(currRow + i, currCol).getCheck() == -1)
			amountEnemy++;
		else
			break;
	}

	for (int i = 1; i <= 5 && currRow - i >= 0; i++)
	{
		if (b->getPointAt(currRow - i, currCol).getCheck() == 1)
		{
			amountFriend++;
			break;
		}
		else if (b->getPointAt(currRow - i, currCol).getCheck() == -1)
			amountEnemy++;
		else
			break;
	}

	if (amountFriend == 2)
		return 0;

	totalScore += defenceScoreArray[amountEnemy];
	if (amountEnemy > 0)
		totalScore -= attackScoreArray[amountFriend] * 2;

	return totalScore;
}

int _Bot::defenceScoreOfRow(_Board *& b, int currRow, int currCol)
{
	int totalScore = 0;
	int amountEnemy = 0;
	int amountFriend = 0;

	for (int i = 1; i <= 5 && currCol + i < b->getSize(); i++)
	{
		if (b->getPointAt(currRow, currCol + i).getCheck() == 1)
		{
			amountFriend++;
			break;
		}

		else if (b->getPointAt(currRow, currCol + i).getCheck() == -1)
			amountEnemy++;
		else
			break;
	}

	for (int i = 1; i <= 5 && currCol - i >= 0; i++)
	{
		if (b->getPointAt(currRow, currCol - i).getCheck() == 1)
		{
			amountFriend++;
			break;
		}
		else if (b->getPointAt(currRow, currCol - i).getCheck() == -1)
			amountEnemy++;
		else
			break;
	}

	if (amountFriend == 2)
		return 0;

	totalScore += defenceScoreArray[amountEnemy];
	if (amountEnemy > 0)
		totalScore -= attackScoreArray[amountFriend] * 2;

	return totalScore;
}

int _Bot::defenceScoreOfMainDiagonal(_Board *& b, int currRow, int currCol)
{
	int totalScore = 0;
	int amountEnemy = 0;
	int amountFriend = 0;

	for (int i = 1; i <= 5 && currRow + i < b->getSize() && currCol + i < b->getSize(); i++)
	{
		if (b->getPointAt(currRow + i, currCol + i).getCheck() == 1)
		{
			amountFriend++;
			break;
		}

		else if (b->getPointAt(currRow + i, currCol + i).getCheck() == -1)
			amountEnemy++;
		else
			break;
	}

	for (int i = 1; i <= 5 && currRow - i >= 0 && currCol - i >= 0; i++)
	{
		if (b->getPointAt(currRow - i, currCol - i).getCheck() == 1)
		{
			amountFriend++;
			break;
		}

		else if (b->getPointAt(currRow - i, currCol - i).getCheck() == -1)
			amountEnemy++;
		else
			break;
	}

	if (amountFriend == 2)
		return 0;

	totalScore += defenceScoreArray[amountEnemy];
	if (amountEnemy > 0)
		totalScore -= attackScoreArray[amountFriend] * 2;

	return totalScore;
}

int _Bot::defenceScoreOfAntiDiagonal(_Board *& b, int currRow, int currCol)
{
	int totalScore = 0;
	int amountEnemy = 0;
	int amountFriend = 0;

	for (int i = 1; i <= 5 && currRow - i >= 0 && currCol + i < b->getSize(); i++)
	{
		if (b->getPointAt(currRow - i, currCol + i).getCheck() == 1)
		{
			amountFriend++;
			break;
		}

		else if (b->getPointAt(currRow - i, currCol + i).getCheck() == -1)
			amountEnemy++;
		else
			break;
	}

	for (int i = 1; i <= 5 && currRow + i < b->getSize() && currCol - i >= 0; i++)
	{
		if (b->getPointAt(currRow + i, currCol - i).getCheck() == 1)
		{
			amountFriend++;
			break;
		}

		else if (b->getPointAt(currRow + i, currCol - i).getCheck() == -1)
			amountEnemy++;
		else
			break;
	}

	if (amountFriend == 2)
		return 0;

	totalScore += defenceScoreArray[amountEnemy];
	if (amountEnemy > 0)
		totalScore -= attackScoreArray[amountFriend] * 2;

	return totalScore;
}

#pragma endregion

#pragma region Main Method

void _Bot::findRandomMove(_Board *&b)
{
	srand(time(NULL));
	do
	{
		_moveRow = rand() % b->getSize();
		_moveCol = rand() % b->getSize();
	} while (b->getPointAt(_moveCol, _moveRow).getCheck() != 0);
}

void _Bot::findBestMove(_Board *&b)
{
	int maxScore = 0;
	for (int i = 0; i < b->getSize(); i++)
	{
		for (int j = 0; j < b->getSize(); j++)
		{
			if (b->getPointAt(i, j).getCheck() == 0)
			{
				int attackScore = attackScoreOfRow(b, i, j) + attackScoreOfCol(b, i, j) + attackScoreOfMainDiagonal(b, i, j) + attackScoreOfAntiDiagonal(b, i, j);
				int defenceScore = defenceScoreOfRow(b, i, j) + defenceScoreOfCol(b, i, j) + defenceScoreOfMainDiagonal(b, i, j) + defenceScoreOfAntiDiagonal(b, i, j);

				int temp = attackScore > defenceScore ? attackScore : defenceScore;

				if (temp > maxScore)
				{
					maxScore = temp;
					_moveRow = j;
					_moveCol = i;
				}
			}
		}
	}
	if (maxScore == 0)
	{
		_moveRow = b->getSize() / 2;
		_moveCol = b->getSize() / 2;
	}
}

void _Bot::sign(_Board *&b)
{
	if (_level == 1)
		findRandomMove(b);
	else
		if (_level == 2)
			findBestMove(b);

	b->getPointAt(_moveCol, _moveRow).setCheck(1);
	_Common::hideCursor();
	_Common::gotoXY(b->getXAt(_moveCol, _moveRow), b->getYAt(_moveCol, _moveRow));
	Sleep(200);
	_Common::OChessmanAudio(_Common::AUDIO_STATUS);
	_Common::setColor(10);
	cout << "O";
	_Common::showCursor();
}

#pragma endregion

