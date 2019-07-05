#include "Menu.h"

#pragma region Constructor & Destructor

_Menu::_Menu(int quantity)
{
	_quantity = quantity;
	_title = new _Title[_quantity];
	_curr = 1;
}

_Menu::~_Menu()
{
	{ delete _title; }
}

#pragma endregion

#pragma region Getter & Setter

void _Menu::setTitle(string content, int index)
{
	_title[index - 1].setContent(content);
}

#pragma endregion

#pragma region Main Method

void _Menu::displayMenu()
{
	_Common::setColor(8);
	for (int i = 1; i <= _quantity; i++)
	{
		int len = _title[i - 1].getContent().length();
		int _startPos = (110 - len) / 2;
		int titlePos = 2 * (i - 1) + 19;

		_Common::gotoXY(_startPos, titlePos + 1);
		cout << " " << _title[i - 1].getContent() << " " << endl;
	}
}

void _Menu::switchTitle(int &keyPress)
{
	displayMenu();
	drawFrameTitle(_curr);

	do
	{
		keyPress = toupper(_getwch());

		switch (keyPress)
		{
		case 'S':case 80:		//Ấn W hoặc mũi tên xuống
		{
			_Common::switchTitleAudio(_Common::AUDIO_STATUS);
			_curr++;

			if (_curr > _quantity)
			{
				_curr = 1;
				clearFrameTitle(_quantity);
			}
			else
				clearFrameTitle(_curr - 1);

			drawFrameTitle(_curr);
			break;
		}

		case 'W':case 72:		//Ấn W hoặc mũi tên lên
		{
			_Common::switchTitleAudio(_Common::AUDIO_STATUS);
			_curr--;

			if (_curr < 1)
			{
				_curr = _quantity;
				clearFrameTitle(1);
			}
			else
				clearFrameTitle(_curr + 1);

			drawFrameTitle(_curr);
			break;
		}

		case 13:				//Ấn Enter
		{
			_Common::choiceAudio(_Common::AUDIO_STATUS);
			clearFrameTitle(_curr);
			break;
		}
		}
	} while (keyPress != 13);

	_Common::clrscr();
}

#pragma endregion

#pragma region Decorate

void _Menu::drawFrameTitle(int index)
{
	int len = _title[index - 1].getContent().length();
	_startPos = (110 - len) / 2;
	int titlePos = 19 + 2 * (index - 1);

	_Common::setColor(4);
	_Common::drawDelayFrame(2, _startPos - 1, titlePos, len + 4, 3, 13);

	_Common::setColor(244);
	_Common::gotoXY(_startPos, titlePos + 1);
	cout << " " << _title[index - 1].getContent() << " " << endl;
}

void _Menu::clearFrameTitle(int index)
{
	int len = _title[index - 1].getContent().length();
	_startPos = (110 - len) / 2;
	int index_ = 19 + 2 * (index - 1);

	_Common::setColor(15);
	_Common::clearFrame(2, _startPos - 1, index_, len + 4, 3, 0, 0);

	_Common::setColor(8);
	_Common::gotoXY(_startPos, index_ + 1);
	cout << " " << _title[index - 1].getContent() << " " << endl;
}

void _Menu::drawFrameMenu(int style, int col, int row, int length, int amount, int delay)
{
	_Common::drawDelayFrame(2, 15, 18, 82, 17, delay);

	for (int i = 0; i < length - 6; i++)
	{
		_Common::gotoXY(col + 3 + i, row + 4);
		cout << '\xC4';//  ─
		Sleep(delay / 2);
	}
}

void _Menu::clearFrameMenu(int col, int row, int length, int amount, int delay)
{
	_Common::hideCursor();
	string space(length, ' ');
	for (int i = 0; i < amount; i++)
	{
		_Common::gotoXY(col, row + amount - i - 1, space);
		Sleep(delay);
	}
}

#pragma endregion

#pragma region Sub-Menu

int _Menu::loadGameMenu()
{
	_Common::loadedScreen();

	int keyPress = 0;
	_Menu *loadGameMenu = new _Menu(3);
	loadGameMenu->setTitle("Two Players", 1);
	loadGameMenu->setTitle("Single Player", 2);
	loadGameMenu->setTitle("Back", 3);

	while (true)
	{
		_Common::hideCursor();

		loadGameMenu->switchTitle(keyPress);
		switch (loadGameMenu->getCurr())
		{
		case 1:
			return 1;

		case 2:
			return 2;

		case 3:
			return 3;
		}
	}
}

void _Menu::tutorialMenu()
{
	_Common::loadedScreen();
	Sleep(200);

	_Common::drawDelayFrameAudio(_Common::AUDIO_STATUS);
	_Common::setColor(15);
	drawFrameMenu(2, 15, 18, 82, 17, 3);

	string tutorial = "TUTORIAL";
	_Common::gotoXY((110 - tutorial.length()) / 2, 20, tutorial, 4);
	_Common::gotoXY((110 - tutorial.length()) / 2 - 3, 20);
	cout << char(175) << char(175);
	_Common::gotoXY((110 - tutorial.length()) / 2 + tutorial.length() + 1, 20);
	cout << char(174) << char(174);

	Sleep(400);
	_Common::typingAudio(_Common::AUDIO_STATUS);
	_Common::gotoXY(20, 24);
	_Common::setColor(8);
	_Common::showCursor();
	_Common::slowPrint("-	In first match, player X will take the first turn.", 25);
	_Common::gotoXY(20, 26);
	_Common::slowPrint("-	The first turn will be change after next match.", 25);
	_Common::gotoXY(20, 28);
	_Common::slowPrint("-	The winner is the first one who take 5 chessmans continuously", 25);
	_Common::gotoXY(20, 29);
	_Common::slowPrint("	without being blocked head and tail.", 25);
	_Common::gotoXY(20, 31);
	_Common::slowPrint("-	Press [A] [S] [D] [W] to move and press [Enter] to sign.", 25);
	_Common::stopAudio(_Common::AUDIO_STATUS);
}

void _Menu::aboutMenu()
{
	_Common::loadedScreen();
	Sleep(200);

	_Common::drawDelayFrameAudio(_Common::AUDIO_STATUS);
	_Common::setColor(15);
	drawFrameMenu(2, 15, 18, 82, 17, 3);

	string tutorial = "ABOUT";
	_Common::gotoXY((110 - tutorial.length()) / 2, 20, tutorial, 4);
	_Common::gotoXY((110 - tutorial.length()) / 2 - 3, 20);
	cout << char(175) << char(175);
	_Common::gotoXY((110 - tutorial.length()) / 2 + tutorial.length() + 1, 20);
	cout << char(174) << char(174);

	Sleep(400);
	_Common::typingAudio(_Common::AUDIO_STATUS);
	string title = "* FINAL PROJECT OOP - GAME CARO *";
	_Common::gotoXY((110 - title.length()) / 2, 25);
	_Common::setColor(5);
	_Common::showCursor();
	_Common::slowPrint(title, 25);

	_Common::setColor(8);
	_Common::gotoXY(20, 27);
	_Common::slowPrint("-	Full name: \tNguyen Huu Gia Tri", 25);
	_Common::gotoXY(20, 29);
	_Common::slowPrint("-	Student ID: \t1712254", 25);
	_Common::gotoXY(20, 31);
	_Common::slowPrint("-	Contact: \thttps://www.facebook.com/o0liebeo0o", 25);
	_Common::stopAudio(_Common::AUDIO_STATUS);
}

void _Menu::settingsMenu(_Bot *&bot)
{
	_Common::loadedScreen();

	int keyPress = 0;
	_Menu *settingsMenu = new _Menu(3);
	settingsMenu->setTitle("Audio", 1);
	settingsMenu->setTitle("Computer Level", 2);
	settingsMenu->setTitle("Back", 3);

	while (true)
	{
		_Common::hideCursor();

		int wantToContinue = 1;
		settingsMenu->switchTitle(keyPress);
		switch (settingsMenu->getCurr())
		{
		case 1:
		{
			_Menu *audioSettingsMenu = new _Menu(2);
			int keyPress = 0;

			audioSettingsMenu->setTitle("On ", 1);
			audioSettingsMenu->setTitle("Off", 2);

			while (true)
			{
				_Common::loadedScreen();
				_Common::hideCursor();
				audioSettingsMenu->switchTitle(keyPress);
				switch (audioSettingsMenu->getCurr())
				{
				case 1:
					_Common::setAudioStatus(true);
					_Common::confirmAudio(_Common::AUDIO_STATUS);
					break;

				case 2:
					_Common::setAudioStatus(false);
					_Common::confirmAudio(_Common::AUDIO_STATUS);
					break;
				}
				break;
			}

			break;
		}

		case 2:
		{
			_Menu *levelSettingsMenu = new _Menu(2);
			int keyPress = 0;

			levelSettingsMenu->setTitle("Easy", 1);
			levelSettingsMenu->setTitle("Hard", 2);

			while (true)
			{
				_Common::loadedScreen();
				_Common::hideCursor();
				levelSettingsMenu->switchTitle(keyPress);
				switch (levelSettingsMenu->getCurr())
				{
				case 1:
					bot->setLevel(1);
					_Common::confirmAudio(_Common::AUDIO_STATUS);
					break;

				case 2:
					bot->setLevel(2);
					_Common::confirmAudio(_Common::AUDIO_STATUS);
					break;
				}
				break;
			}

			break;
		}

		case 3:
			wantToContinue = 0;
			break;
		}
		_Common::loadedScreen();
		if (wantToContinue == 0)
			break;
	}
}

#pragma endregion