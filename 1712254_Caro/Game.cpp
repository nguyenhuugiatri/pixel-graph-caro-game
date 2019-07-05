#include "Game.h"

#pragma region Constructor & Destructor

_Game::_Game(int pSize, int pLeft, int pTop)
{
	_b = new _Board(pSize, pLeft, pTop);
	_bot = new _Bot(1);						//Mặc định level Easy
	_loop = _turn = _first = true;			//Mặc định người đi đầu là X
	_command = -1;
	_x = pLeft;
	_y = pTop;
	_scoreX = _scoreO = 0;
	_stepX = _stepO = 0;
}

_Game::~_Game()
{
	delete _b;
	delete _bot;
}

#pragma endregion

#pragma region Getter & Setter

char _Game::waitKeyBoard()
{
	_command = toupper(_getwch());
	return _command;
}

#pragma endregion

#pragma region Main Method

void _Game::startGame(bool bot)
{
	_Common::clrscr();

	//Khởi tạo dữ liệu gốc
	_b->resetData();
	resetStep();
	_turn = _first;

	_b->drawBoard();				//Vẽ bàn cờ
	drawMatchInformation(bot);		//Vẽ thông tin ván đấu

	//Điều chỉnh tọa độ con trỏ về ô giữa
	_x = _b->getXAt(_b->getSize() / 2, _b->getSize() / 2);
	_y = _b->getYAt(_b->getSize() / 2, _b->getSize() / 2);
}

int _Game::exitGame(bool bot)
{
	saveTemp();	//Lưu tạm bàn cờ để load lại nếu người dùng back

	_Common::hideCursor();
	clearScreen(4, 2, 26, 16, 7);

	_Common::choiceAudio(_Common::AUDIO_STATUS);
	string question = "DO YOU WANT TO SAVE THIS MATCH ?";
	_Common::gotoXY((110 - question.length()) / 2, 17, question, 4);

	int keyPress = 0;
	_Menu *saveMenu = new _Menu(3);
	saveMenu->setTitle("Yes", 1);
	saveMenu->setTitle("No ", 2);
	saveMenu->setTitle("Back", 3);

	while (true)
	{
		saveMenu->switchTitle(keyPress);
		switch (saveMenu->getCurr())
		{
		case 1:
			if (!bot)
				saveGame(false, false);
			else
				saveGame(false, true);

			resetMatchInformation();
			return 0;
			break;

		case 2:
			resetMatchInformation();
			return 0;
			break;

		case 3:
			if (!bot)
				loadTemp(false);
			else
				loadTemp(true);
			return 1;
			break;
		}

		break;
	}
}

bool _Game::processCheckBoard()
{
	switch (_b->checkBoard(_x, _y, _turn))
	{
	case -1:
		_Common::XChessmanAudio(_Common::AUDIO_STATUS);
		_Common::setColor(12);
		cout << "X";

		//Cập nhật số bước đi
		_stepX++;
		updateStep();
		break;

	case 1:
		_Common::OChessmanAudio(_Common::AUDIO_STATUS);
		_Common::setColor(10);
		cout << "O";

		//Cập nhật số bước đi
		_stepO++;
		updateStep();
		break;

	case 0:
		_Common::accessDeniedAudio(_Common::AUDIO_STATUS);
		return false; //Khi đánh vào ô đã đánh rồi
	}

	return true;
}

int _Game::waitForUser(bool bot)
{
	waitKeyBoard();

	if (getCommand() == 27)
	{
		if (!bot)
			return exitGame(false);
		else
			return exitGame(true);
	}

	else
	{
		switch (getCommand())
		{
		case 'A':case 75:	//Ấn A hoặc mũi tên trái
		{
			moveLeft();
			break;
		}

		case 'W':case 72:	//Ấn W hoặc mũi tên lên
		{
			moveUp();
			break;
		}

		case 'S':case 80:	//Ấn S hoặc mũi tên xuống
		{
			moveDown();
			break;
		}

		case 'D':case 77:	//Ấn D hoặc mũi tên phải
		{
			moveRight();
			break;
		}

		case 'L':	//Ấn L
		{
			_Common::choiceAudio(_Common::AUDIO_STATUS);
			clearScreen(4, 2, 26, 16, 7);
			if (!bot)
				return saveGame(true, false);
			else
				return saveGame(true, true);
			break;
		}

		case 'T':	//Ấn T
		{
			_Common::choiceAudio(_Common::AUDIO_STATUS);
			clearScreen(4, 2, 26, 16, 7);
			if (!bot)
				loadGame(false);
			else
				loadGame(true);
			break;
		}

		case 13:	//Ấn Enter
		{
			if (processCheckBoard())
			{
				if (!bot)
					switch (processFinish())
					{
					case -1: case 1: case 0:
						return askForContinue(false);
					}

				else
					switch (processFinish(bot))
					{
					case -1: case 1: case 0:
						return askForContinue(true);
					}
			}
			return 1;
		}
		}
	}
}

int _Game::waitForBot()
{
	_bot->sign(_b);
	_stepO++;
	updateStep();
	switch (processFinish(true))
	{
	case -1: case 1: case 0:
		return askForContinue(true);
	}
	return 1;
}

int _Game::processFinish()
{
	int pWhoWin = _b->testBoard(_x, _y, _turn);
	switch (pWhoWin)
	{
	case -1:
		//Cập nhật tỉ số
		_scoreX++;
		updateScore();

		//Hiệu ứng chiến thắng
		drawXWIN(_b->getLeft() + 12, _b->getTop() + 13);

		//Đổi lượt đánh trước
		_first = !_first;
		break;

	case 1:
		//Cập nhật tỉ số
		_scoreO++;
		updateScore();

		//Hiệu ứng chiến thắng
		drawOWIN(_b->getLeft() + 12, _b->getTop() + 13);

		//Đổi lượt đánh trước
		_first = !_first;
		break;

	case 0:
		//Hiệu ứng hòa
		drawDRAW(_b->getLeft() + 12, _b->getTop() + 13);

		//Đổi lượt đánh trước
		_first = !_first;
		break;

	case 2:
		//Đổi lượt nếu không có gì xảy ra
		_turn = !_turn;
	}
	_Common::gotoXY(_x, _y);	//Trả về vị trí hiện hành của con trỏ màn hình bàn cờ
	return pWhoWin;
}

int _Game::processFinish(bool bot)
{
	if (_turn == false)
	{
		int pWhoWin = _b->testBoard(_b->getXAt(_bot->getMoveCol(), _bot->getMoveRow()), _b->getYAt(_bot->getMoveCol(), _bot->getMoveRow()), false);
		switch (pWhoWin)
		{
		case 1:
			//Cập nhật tỉ số
			_scoreO++;
			updateScore();

			//Hiệu ứng thua
			drawYOULOSE(_b->getLeft() + 17, _b->getTop() + 9);

			//Đổi lượt đánh trước
			_first = !_first;
			break;

		case 0:
			//Hiệu ứng hòa
			drawDRAW(_b->getLeft() + 12, _b->getTop() + 13);

			//Đổi lượt đánh trước
			_first = !_first;
			break;

		case 2:
			//Đổi lượt nếu không có gì xảy ra
			_turn = !_turn;
		}
		_Common::gotoXY(_x, _y);	//Trả về vị trí hiện hành của con trỏ màn hình bàn cờ
		return pWhoWin;
	}

	else
	{
		int pWhoWin = _b->testBoard(_x, _y, _turn);
		switch (pWhoWin)
		{
		case -1:
			//Cập nhật tỉ số
			_scoreX++;
			updateScore();

			//Hiệu ứng chiến thắng
			drawYOUWIN(_b->getLeft() + 17, _b->getTop() + 9);

			//Đổi lượt đánh trước
			_first = !_first;
			break;


		case 0:
			//Hiệu ứng hòa
			drawDRAW(_b->getLeft() + 12, _b->getTop() + 13);

			//Đổi lượt đánh trước
			_first = !_first;
			break;

		case 2:
			//Đổi lượt nếu không có gì xảy ra
			_turn = !_turn;
		}
		_Common::gotoXY(_x, _y);	//Trả về vị trí hiện hành của con trỏ màn hình bàn cờ
		return pWhoWin;
	}
}

int _Game::askForContinue(bool bot)
{
	_Common::choiceAudio(_Common::AUDIO_STATUS);
	clearScreen(4, 2, 26, 16, 7);
	string question = "DO YOU WANT TO PLAY NEXT MATCH ?";
	_Common::gotoXY((110 - question.length()) / 2, 17, question, 4);

	_Menu *continueMenu = new _Menu(2);
	int keyPress = 0;

	continueMenu->setTitle("Yes", 1);
	continueMenu->setTitle("No ", 2);

	while (true)
	{
		_Common::hideCursor();
		continueMenu->switchTitle(keyPress);
		switch (continueMenu->getCurr())
		{
		case 1:
			if (!bot)
				startGame(false);
			else
				startGame(true);
			return 1;
			break;

		case 2:
			resetMatchInformation();
			return 0;
			break;
		}
		break;
	}
}

int _Game::askForResume(bool bot)
{
	saveTemp();

	_Common::hideCursor();
	clearScreen(4, 2, 26, 16, 7);
	_Common::choiceAudio(_Common::AUDIO_STATUS);

	string question = "DO YOU WANT RESUME ?";
	_Common::gotoXY((110 - question.length()) / 2, 17, question, 4);

	int keyPress = 0;
	_Menu *saveMenu = new _Menu(2);
	saveMenu->setTitle("Yes", 1);
	saveMenu->setTitle("No ", 2);

	while (true)
	{
		saveMenu->switchTitle(keyPress);

		switch (saveMenu->getCurr())
		{
		case 1:
			if (!bot)
				loadTemp(false);
			else
				loadTemp(true);
			return 1;
			break;

		case 2:
			resetMatchInformation();
			return 0;
			break;
		}

		break;
	}
}

#pragma endregion

#pragma region Moving

void _Game::moveRight()
{
	if (_x < _b->getXAt(_b->getSize() - 1, _b->getSize() - 1))
	{
		_x += 4;
		_Common::stepAudio(_Common::AUDIO_STATUS);
		_Common::gotoXY(_x, _y);

	}
}

void _Game::moveLeft() {
	if (_x > _b->getXAt(0, 0))
	{
		_x -= 4;
		_Common::stepAudio(_Common::AUDIO_STATUS);
		_Common::gotoXY(_x, _y);

	}
}

void _Game::moveUp()
{
	if (_y > _b->getYAt(0, 0))
	{
		_y -= 2;
		_Common::stepAudio(_Common::AUDIO_STATUS);
		_Common::gotoXY(_x, _y);
	}
}

void _Game::moveDown()
{
	if (_y < _b->getYAt(_b->getSize() - 1, _b->getSize() - 1))
	{
		_y += 2;
		_Common::stepAudio(_Common::AUDIO_STATUS);
		_Common::gotoXY(_x, _y);
	}
}

#pragma endregion

#pragma region Save/Load

int _Game::saveGame(bool resume, bool bot)
{
	//Đọc danh sách các ván đã lưu vào vector
	vector<string> fileNames;

	string path;
	if (!bot)
		path = "Save\\List\\PvP.data";
	else
		path = "Save\\List\\PvC.data";

	ifstream inputList(path, ios::in);
	while (!inputList.eof())
	{
		string temp;
		inputList >> temp;
		if (temp.length() > 0)
			fileNames.push_back(temp);
	}
	inputList.close();

	//Nhập tên ván đấu muốn lưu
	_Common::hideCursor();
	_Common::gotoXY(35, 45);
	string request = "ENTER YOUR MATCH'S NAME";
	_Common::gotoXY((110 - request.length()) / 2, 16, request, 4);

	_Common::setColor(15);
	_Common::drawDelayFrame(2, (110 - request.length()) / 2, 18, 23, 3, 7);


	string fileName;

	do
	{
		_Common::showCursor();
		_Common::gotoXY((110 - request.length()) / 2 + 2, 19);
		fileName = inputFileName((110 - request.length()) / 2 + 2, 19, 19);
		if (!checkFileName(fileName) || checkExist(fileName, fileNames))
		{
			_Common::accessDeniedAudio(_Common::AUDIO_STATUS);
			_Common::hideCursor();
			_Common::gotoXY((110 - request.length()) / 2 - 15, 22, "YOUR MATCH'S NAME IS INVALID OR AVAILABLE. PLEASE TRY AGAIN !", 4);
			Sleep(800);
			_Common::gotoXY((110 - request.length()) / 2 - 15, 22, string(65, ' '), 15);
			_Common::gotoXY((110 - request.length()) / 2 + 2, 19, string(19, ' '));
		}
	} while (!checkFileName(fileName) || checkExist(fileName, fileNames));

	_Common::confirmAudio(_Common::AUDIO_STATUS);
	Sleep(500);

	fileNames.push_back(fileName);

	//Kiểm tra nếu số lượng vượt quá 6 thì loại bỏ cái đầu
	while (fileNames.size() > 6)
	{
		string temp;
		if (!bot)
			temp = "Save\\PvP\\" + fileNames[0] + ".data";
		else
			temp = "Save\\PvC\\" + fileNames[0] + ".data";

		char *path = _strdup(temp.c_str());
		DeleteFile(path);
		fileNames.erase(fileNames.begin());
	}

	//File lưu tên các ván đấu đã lưu
	ofstream outputList(path, ios::out);
	for (int i = 0; i < fileNames.size(); i++)
		outputList << fileNames[i] << endl;
	outputList.close();

	//File lưu thông tin game
	fileName += ".data";
	string pathFileName;
	if (!bot)
		pathFileName = "Save\\PvP\\" + fileName;
	else
		pathFileName = "Save\\PvC\\" + fileName;
	ofstream fileOut(pathFileName, ios::out);

	//Lưu thông tin người chơi
	fileOut << _turn << endl;
	fileOut << _scoreX << " " << _scoreO << endl;
	fileOut << _stepX << " " << _stepO << endl;

	//Lưu thông tin tọa độ nháy chuột
	fileOut << _x << " " << _y << endl;

	//Lưu thông tin bàn cờ
	for (int i = 0; i < _b->getSize(); i++)
	{
		for (int j = 0; j < _b->getSize(); j++)
			fileOut << _b->getPointAt(i, j).getCheck() << " ";
		fileOut << endl;
	}
	fileOut.close();

	if (resume)
		return askForResume(bot);
	else
		return 0;
}

void _Game::loadGame(bool bot)
{
	//Lưu danh sách các file đã lưu vào vector
	vector<string> fileNames;

	string path;
	if (!bot)
		path = "Save\\List\\PvP.data";
	else
		path = "Save\\List\\PvC.data";

	ifstream inputList(path, ios::in);
	while (!inputList.eof())
	{
		string temp;
		inputList >> temp;
		if (temp.length() > 0)
			fileNames.push_back(temp);
	}
	inputList.close();

	_Common::setColor(15);
	_Common::drawFrame(2, 0, 0, 112, 37, 0, 4);

	string request = "CHOOSE THE MATCH YOU WANT TO LOAD";
	_Common::gotoXY((110 - request.length()) / 2, 17, request, 4);

	_Menu *loadMenu = new _Menu(fileNames.size());
	int keyPress = 0;

	for (int i = 0; i < fileNames.size(); i++)
		loadMenu->setTitle(fileNames[i], i + 1);

	int selection;

	_Common::hideCursor();
	loadMenu->switchTitle(keyPress);
	selection = loadMenu->getCurr();

	string pathFileName;
	if (!bot)
		pathFileName = "Save\\PvP\\" + fileNames[selection - 1] + ".data";
	else
		pathFileName = "Save\\PvC\\" + fileNames[selection - 1] + ".data";

	ifstream fileIn(pathFileName, ios::in);
	fileIn >> _turn;
	fileIn >> _scoreX >> _scoreO;
	fileIn >> _stepX >> _stepO;
	fileIn >> _x >> _y;

	_b->drawBoard();

	if (!bot)
		drawMatchInformation(false);
	else
		drawMatchInformation(true);

	updateScore();
	updateStep();

	int check;
	for (int i = 0; i < _b->getSize(); i++)
	{
		for (int j = 0; j < _b->getSize(); j++)
		{
			fileIn >> check;
			_b->loadBoard(i, j, check);
		}
	}
	fileIn.close();

	_Common::gotoXY(_x, _y);
	_Common::showCursor();
}

void _Game::saveTemp()
{
	ofstream fileOut("temp.data", ios::out);

	//Lưu thông tin người chơi
	fileOut << _turn << endl;
	fileOut << _scoreX << " " << _scoreO << endl;
	fileOut << _stepX << " " << _stepO << endl;

	//Lưu thông tin tọa độ nháy chuột
	fileOut << _x << " " << _y << endl;

	//Lưu thông tin bàn cờ
	for (int i = 0; i < _b->getSize(); i++)
	{
		for (int j = 0; j < _b->getSize(); j++)
			fileOut << _b->getPointAt(i, j).getCheck() << " ";
		fileOut << endl;
	}
	fileOut.close();
}

void _Game::loadTemp(bool bot)
{
	ifstream fileIn("temp.data", ios::in);
	fileIn >> _turn;
	fileIn >> _scoreX >> _scoreO;
	fileIn >> _stepX >> _stepO;
	fileIn >> _x >> _y;

	_b->drawBoard();
	if (!bot)
		drawMatchInformation(false);
	else
		drawMatchInformation(true);

	updateScore();
	updateStep();

	int check;
	for (int i = 0; i < _b->getSize(); i++)
	{
		for (int j = 0; j < _b->getSize(); j++)
		{
			fileIn >> check;
			_b->loadBoard(i, j, check);
		}
	}
	fileIn.close();

	_Common::showCursor();
	_Common::gotoXY(_x, _y);
}

#pragma endregion

#pragma region Match Information

void _Game::drawFrameMatchInformation()
{
	int style = 2;
	int col = 73;
	int row = 2;
	int length = 35, amount = 33;
	int delay = 5;

	_Common::hideCursor();
	_Common::drawDelayFrame(style, col, row, length, amount, delay);

	for (int i = 0; i < length - 6; i++)
	{
		_Common::gotoXY(col + 3 + i, row + length / 3);
		cout << '\xC4';	//  ─
		_Common::gotoXY(col + length - 4 - i, row + length * 2 / 3 - 1);
		cout << '\xC4';	//  ─
		Sleep(delay / 2);
	}
}

void _Game::drawMatchInformation(bool bot)
{
	Sleep(200);
	_Common::drawDelayFrameAudio(_Common::AUDIO_STATUS);

	_Common::hideCursor();
	drawFrameMatchInformation();

	string score = "SCORE";
	_Common::gotoXY((182 - score.length()) / 2, 5, score, 15);
	_Common::gotoXY((182 - score.length()) / 2 - 3, 5);
	cout << char(175) << char(175);
	_Common::gotoXY((182 - score.length()) / 2 + score.length() + 1, 5);
	cout << char(174) << char(174);

	if (!bot)
		_Common::gotoXY((182 - score.length()) / 2 - 8, 8, "PLAYER X", 12);
	else
		_Common::gotoXY((182 - score.length()) / 2 - 8, 8, "  PLAYER", 12);

	_Common::gotoXY((182 - score.length()) / 2 + 2, 8, "VS", 15);

	if (!bot)
		_Common::gotoXY((182 - score.length()) / 2 + 6, 8, "PLAYER O", 10);
	else
		_Common::gotoXY((182 - score.length()) / 2 + 6, 8, "COMPUTER", 10);

	_Common::gotoXY((182 - 2) / 2, 10, "--", 15);
	_Common::gotoXY((182 - 2) / 2 - 5, 10, _scoreX, 12);
	_Common::gotoXY((182 - 2) / 2 + 5, 10, _scoreO, 10);

	string step = "STEP";
	_Common::gotoXY((182 - step.length()) / 2, 16, step, 15);
	_Common::gotoXY((182 - step.length()) / 2 - 3, 16);
	cout << char(175) << char(175);
	_Common::gotoXY((182 - step.length()) / 2 + step.length() + 1, 16);
	cout << char(174) << char(174);

	if (!bot)
		_Common::gotoXY((182 - step.length()) / 2 - 9, 19, "PLAYER X", 12);
	else
		_Common::gotoXY((182 - step.length()) / 2 - 9, 19, "  PLAYER", 12);

	_Common::gotoXY((182 - step.length()) / 2 + 1, 19, "VS", 15);
	if (!bot)
		_Common::gotoXY((182 - step.length()) / 2 + 5, 19, "PLAYER O", 10);
	else
		_Common::gotoXY((182 - step.length()) / 2 + 5, 19, "COMPUTER", 10);

	_Common::gotoXY((182 - 2) / 2, 21, "--", 15);
	_Common::gotoXY((182 - 2) / 2 - 5, 21, _stepX, 12);
	_Common::gotoXY((182 - 2) / 2 + 5, 21, _stepO, 10);

	string tutorial = "TUTORIAL";
	_Common::gotoXY((182 - tutorial.length()) / 2, 26, tutorial, 15);
	_Common::gotoXY((182 - tutorial.length()) / 2 - 3, 26);
	cout << char(175) << char(175);
	_Common::gotoXY((182 - tutorial.length()) / 2 + tutorial.length() + 1, 26);
	cout << char(174) << char(174);

	_Common::gotoXY(76, 28, "Press [A] [D] [S] [W] to move", 8);
	_Common::gotoXY(76, 29, "Press [Enter] to sign", 8);
	_Common::gotoXY(76, 30, "Press [L] to save this match", 8);
	_Common::gotoXY(76, 31, "Press [T] to load other match", 8);
	_Common::gotoXY(76, 32, "Press [ESC] to quit", 8);

	//Di chuyển con trỏ đến ô giữa
	_Common::gotoXY(_b->getXAt(_b->getSize() / 2, _b->getSize() / 2), _b->getYAt(_b->getSize() / 2, _b->getSize() / 2));
	_Common::showCursor();
}

void _Game::clearScreen(int col, int row, int length, int amount, int delay)
{
	string Line(length * 4 + 1, ' ');
	for (int i = 0; i < row + 2 * amount; i++)
	{
		_Common::gotoXY(col, row + i);
		cout << Line;
		_Common::gotoXY(col, row + row + 2 * amount - 1 - i);
		cout << Line;
		Sleep(delay);
	}
}

void _Game::updateStep()
{
	_Common::gotoXY((182 - 2) / 2 - 5, 21, _stepX, 12);
	_Common::gotoXY((182 - 2) / 2 + 5, 21, _stepO, 10);
}

void _Game::updateScore()
{
	_Common::gotoXY((182 - 2) / 2 - 5, 10, _scoreX, 12);
	_Common::gotoXY((182 - 2) / 2 + 5, 10, _scoreO, 10);
}

void _Game::resetScore()
{
	_scoreX = _scoreO = 0;
}

void _Game::resetStep()
{
	_stepX = _stepO = 0;
}

void _Game::resetFirst()
{
	_first = true;
}

void _Game::resetMatchInformation()
{
	resetScore();
	resetStep();
	resetFirst();
}

#pragma endregion

#pragma region Decorate

void _Game::drawXWIN(int left, int top)
{
	_Common::victoryAudio(_Common::AUDIO_STATUS);
	_Common::hideCursor();

	int a = 14, b = 12, c = 13, d = 10;
	for (int k = 0; k < 60; k++)
	{
		_Common::setColor(a);

		_Common::drawX(left, top);
		_Common::drawW(left + 14, top);
		_Common::drawI(left + 26, top);
		_Common::drawN(left + 30, top);

		int temp = d;
		d = c;			c = b;			b = a;			a = temp;
		Sleep(90);
	}
	Sleep(200);
}

void _Game::drawOWIN(int left, int top)
{
	_Common::victoryAudio(_Common::AUDIO_STATUS);
	_Common::hideCursor();

	int a = 14, b = 12, c = 13, d = 10;
	for (int k = 0; k < 60; k++)
	{
		_Common::setColor(a);

		_Common::drawO(left, top);
		_Common::drawW(left + 14, top);
		_Common::drawI(left + 26, top);
		_Common::drawN(left + 30, top);

		int temp = d;
		d = c;			c = b;			b = a;			a = temp;
		Sleep(90);
	}
	Sleep(200);
}

void _Game::drawDRAW(int left, int top)
{
	_Common::victoryAudio(_Common::AUDIO_STATUS);
	_Common::hideCursor();

	int a = 14, b = 12, c = 13, d = 10;
	for (int k = 0; k < 60; k++)
	{
		_Common::setColor(a);

		_Common::drawD(left, top);
		_Common::drawR(left + 9, top);
		_Common::drawA(left + 19, top);
		_Common::drawW(left + 29, top);

		int temp = d;
		d = c;			c = b;			b = a;			a = temp;
		Sleep(90);
	}
	Sleep(200);
}

void _Game::drawYOUWIN(int left, int top)
{
	_Common::victoryAudio(_Common::AUDIO_STATUS);
	_Common::hideCursor();

	int a = 14, b = 12, c = 13, d = 10;
	for (int k = 0; k < 60; k++)
	{
		_Common::setColor(a);

		_Common::drawY(left, top);
		_Common::drawO(left + 10, top);
		_Common::drawU(left + 20, top);

		_Common::drawW(left + 2, top + 7);
		_Common::drawI(left + 13, top + 7);
		_Common::drawN(left + 17, top + 7);

		int temp = d;
		d = c;			c = b;			b = a;			a = temp;
		Sleep(90);
	}
	Sleep(200);
}

void _Game::drawYOULOSE(int left, int top)
{
	_Common::loseAudio(_Common::AUDIO_STATUS);
	_Common::hideCursor();

	int a = 7, b = 8, c = 15;
	for (int k = 0; k < 25; k++)
	{
		_Common::setColor(a);

		_Common::drawY(left + 3, top);
		_Common::drawO(left + 13, top);
		_Common::drawU(left + 23, top);

		_Common::drawL(left, top + 7);
		_Common::drawO(left + 9, top + 7);
		_Common::drawS(left + 19, top + 7);
		_Common::drawE(left + 28, top + 7);

		int temp = c;
		c = b;			b = a;			a = temp;
		Sleep(150);
	}
	Sleep(200);
}

#pragma endregion

#pragma region Others


string _Game::inputFileName(int left, int top, int max)
{
	string fileName;
	while (true)
	{
		if (_kbhit())
		{
			_Common::pressButtonAudio(_Common::AUDIO_STATUS);
			char c = _getwch();
			if (c == 13)
				break;
			//Quy định đặt tên
			if (c != 32 && c != '/' && c != '\\' && c != ':' && c != '*' && c != '?' && c != '"' && c != '<' && c != '>' && c != '|')
			{
				if (c == 8)	//Backspace
				{
					if (fileName.size() != 0)
					{
						left--;
						_Common::gotoXY(left, top);
						cout << ' ';
						_Common::gotoXY(left, top);
						fileName.pop_back();
					}
				}
				else
				{
					if (fileName.size() < max)
					{
						fileName.push_back(c);
						_Common::gotoXY(left, top);
						cout << c;
						left++;
					}
				}
			}
		}

	}
	return fileName;
}

bool _Game::checkFileName(string fileName)
{
	if (fileName.length() == 0)
		return false;
	for (char c : fileName)
	{
		if (c < 32 || c>126)
			return false;
	}
	return true;
}

bool _Game::checkExist(string &fileName, vector<string>& fileNames)
{
	for (int i = 0; i < fileNames.size(); i++)
	{
		if (isEquals(fileName, fileNames[i]))
			return true;
	}
	return false;
}

bool _Game::isEquals(const string & a, const string & b)
{
	unsigned int sz = a.size();
	if (b.size() != sz)
		return false;
	for (unsigned int i = 0; i < sz; ++i)
		if (tolower(a[i]) != tolower(b[i]))
			return false;
	return true;
}

#pragma endregion
