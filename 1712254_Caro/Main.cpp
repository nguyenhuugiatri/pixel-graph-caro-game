#include "Game.h"

#pragma region Properties
//Tọa độ bàn cờ
#define LEFT 4						
#define TOP 2

//Kích thước bàn cờ
#define BOARD_SIZE 16

//Âm thanh
bool _Common::AUDIO_STATUS = TRUE;
#pragma endregion

void getChoice(int &keyPress, _Menu *&menu, _Game *&game)
{
	_Common::loadedScreen();
	menu->switchTitle(keyPress);

	switch (menu->getCurr())
	{
	case 1:		//Two Players
	{
		_Common::showCursor();
		game->startGame(false);
		while (game->isContinue())
		{
			if (game->waitForUser(false) == 0)
				break;
		}
		break;
	}

	case 2:		//Single Player
	{
		_Common::showCursor();
		game->startGame(true);
		while (game->isContinue())
		{
			if (game->getTurn() == false)
			{
				if (game->waitForBot() == 0)
					break;
			}

			else
			{
				if (game->waitForUser(true) == 0)
					break;
			}
		}
		break;
	}

	case 3:		//Tutorial
	{
		menu->tutorialMenu();

		_getwch();
		_Common::choiceAudio(_Common::AUDIO_STATUS);
		menu->clearFrameMenu(15, 18, 82, 17, 10);
		break;
	}

	case 4:		//Load Game
	{
		int mode = menu->loadGameMenu();
		if (mode == 1)
		{
			game->loadGame(false);
			while (game->isContinue())
			{
				if (game->waitForUser(false) == 0)
					break;
			}
			break;
		}
		else if (mode == 2)
		{
			game->loadGame(true);
			_Common::showCursor();
			while (game->isContinue())
			{
				if (game->getTurn() == false)
				{
					if (game->waitForBot() == 0)
						break;
				}

				else
				{
					if (game->waitForUser(true) == 0)
						break;
				}
			}
			break;
		}
		else
			break;
	}

	case 5:		//Settings
	{
		menu->settingsMenu(game->getBot());
		break;
	}

	case 6:		//About
	{
		menu->aboutMenu();

		_getwch();
		_Common::choiceAudio(_Common::AUDIO_STATUS);
		menu->clearFrameMenu(15, 18, 82, 17, 10);
		break;
	}

	case 7:		//Quit Game
	{
		_Common::loadedScreen();
		menu->displayMenu();
		_Common::quitGameAudio(_Common::AUDIO_STATUS);
		Sleep(100);
		game->clearScreen(4, 2, 26, 16, 20);
		Sleep(200);
		exit(0);
		break;
	}
	}
}

int main()
{
	_Common::setupConsole();
	_Game *game = new _Game(BOARD_SIZE, LEFT, TOP);

	int keyPress = 0;
	_Menu *menu = new _Menu(7);
	menu->setTitle("Two Players", 1);
	menu->setTitle("Single Player", 2);
	menu->setTitle("Tutorial", 3);
	menu->setTitle("Load Game", 4);
	menu->setTitle("Settings", 5);
	menu->setTitle("About", 6);
	menu->setTitle("Quit Game", 7);
	_Common::loadingScreen();

	while (true)
	{
		_Common::hideCursor();
		getChoice(keyPress, menu, game);
	}

	delete menu;
	delete game;

	system("pause");
	return 0;
}