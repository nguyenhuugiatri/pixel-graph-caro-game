#include "Common.h"

#pragma region Console

void _Common::setConsoleWindow(int w, int h)
{
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);

	MoveWindow(console, r.left, r.top, w, h, TRUE);
}

void _Common::fixConsoleWindow()
{
	HWND consoleWindow = GetConsoleWindow();
	LONG style = GetWindowLong(consoleWindow, GWL_STYLE);
	style = style & ~(WS_MAXIMIZEBOX) & ~(WS_THICKFRAME);
	SetWindowLong(consoleWindow, GWL_STYLE, style);
}

void _Common::removeConsoleScrollbar()
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(handle, &info);
	COORD new_size =
	{
		info.srWindow.Right - info.srWindow.Left + 1,
		info.srWindow.Bottom - info.srWindow.Top + 1
	};
	SetConsoleScreenBufferSize(handle, new_size);
}

void _Common::setConsoleTitle()
{
	SetConsoleTitle("1712254 - NGUYEN HUU GIA TRI");
}

void _Common::setupConsole()
{
	setConsoleWindow(850, 670);
	fixConsoleWindow();
	removeConsoleScrollbar();
	setConsoleTitle();
}

void _Common::clrscr()
{
	CONSOLE_SCREEN_BUFFER_INFO	csbiInfo;
	HANDLE	hConsoleOut;
	COORD	Home = { 0,0 };
	DWORD	dummy;

	hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hConsoleOut, &csbiInfo);

	FillConsoleOutputCharacter(hConsoleOut, ' ', csbiInfo.dwSize.X * csbiInfo.dwSize.Y, Home, &dummy);
	csbiInfo.dwCursorPosition.X = 0;
	csbiInfo.dwCursorPosition.Y = 0;
	SetConsoleCursorPosition(hConsoleOut, csbiInfo.dwCursorPosition);
}

void _Common::showCursor()
{
	HANDLE hstdout = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO *cci = new CONSOLE_CURSOR_INFO;
	cci->dwSize = 1;
	cci->bVisible = TRUE;

	SetConsoleCursorInfo(hstdout, cci);
}

void _Common::hideCursor()
{
	HANDLE hstdout = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO *cci = new CONSOLE_CURSOR_INFO;
	cci->dwSize = 1;
	cci->bVisible = FALSE;

	SetConsoleCursorInfo(hstdout, cci);
}

#pragma endregion

#pragma region Moving

void _Common::gotoXY(int pX, int pY)
{
	COORD coord;
	coord.X = pX;
	coord.Y = pY;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void _Common::gotoXY(int pX, int pY, char ch)
{
	gotoXY(pX, pY);
	cout.put(char(ch)).flush();
}

void _Common::gotoXY(int pX, int pY, string text)
{
	gotoXY(pX, pY);
	cout << text;
}

void _Common::gotoXY(int pX, int pY, string text, int color)
{
	gotoXY(pX, pY);
	setColor(color);
	cout << text;
}

void _Common::gotoXY(int pX, int pY, int number, int color)
{
	gotoXY(pX, pY);
	setColor(color);
	cout << number;
}

#pragma endregion

#pragma region Audio

void _Common::setAudioStatus(bool status)
{
	AUDIO_STATUS = status;
	if (AUDIO_STATUS)
		mciSendString("resume Audio\\Background.mp3", NULL, 0, NULL);
	else
		mciSendString("pause Audio\\Background.mp3", NULL, 0, NULL);
}

bool _Common::stopAudio(bool &status)
{
	if (status)
		return PlaySound(NULL, NULL, SND_ASYNC);
	else return false;
}

void _Common::backgroundAudio(bool &status)
{
	if (status)
		mciSendString("play Audio\\Background.mp3 repeat", NULL, 0, NULL);
}

bool _Common::choiceAudio(bool &status)
{
	if (status)
		return PlaySound(TEXT("Audio\\Choice.wav"), NULL, SND_ASYNC);
	else return false;
}

bool _Common::stepAudio(bool &status)
{
	if (status)
		return PlaySound(TEXT("Audio\\Step.wav"), NULL, SND_ASYNC);
	else return false;
}

bool _Common::switchTitleAudio(bool &status)
{
	if (status)
		return PlaySound(TEXT("Audio\\SwitchTitle.wav"), NULL, SND_ASYNC);
	else return false;
}

bool _Common::winRowAudio(bool &status)
{
	if (status)
		return PlaySound(TEXT("Audio\\WinRow.wav"), NULL, SND_ASYNC);
	else return false;
}

bool _Common::victoryAudio(bool &status)
{
	if (status)
		return PlaySound(TEXT("Audio\\Victory.wav"), NULL, SND_ASYNC);
	else return false;
}

bool _Common::loseAudio(bool &status)
{
	if (status)
		return PlaySound(TEXT("Audio\\Lose.wav"), NULL, SND_ASYNC);
	else return false;
}

bool _Common::typingAudio(bool &status)
{
	if (status)
		return PlaySound(TEXT("Audio\\Typing.wav"), NULL, SND_ASYNC);
	else return false;
}

bool _Common::accessDeniedAudio(bool &status)
{
	if (status)
		return PlaySound(TEXT("Audio\\AccessDenied.wav"), NULL, SND_ASYNC);
	else return false;
}

bool _Common::XChessmanAudio(bool &status)
{
	if (status)
		return PlaySound(TEXT("Audio\\XChessman.wav"), NULL, SND_ASYNC);
	else return false;
}

bool _Common::OChessmanAudio(bool &status)
{
	if (status)
		return PlaySound(TEXT("Audio\\OChessman.wav"), NULL, SND_ASYNC);
	else return false;
}

bool _Common::drawDelayFrameAudio(bool &status)
{
	if (status)
		return PlaySound(TEXT("Audio\\DrawDelayFrame.wav"), NULL, SND_ASYNC);
	else return false;
}

bool _Common::quitGameAudio(bool &status)
{
	if (status)
		return PlaySound(TEXT("Audio\\QuitGame.wav"), NULL, SND_ASYNC);
	else return false;
}

bool _Common::confirmAudio(bool &status)
{
	if (status)
		return PlaySound(TEXT("Audio\\Confirm.wav"), NULL, SND_ASYNC);
	else return false;
}

bool _Common::pressButtonAudio(bool &status)
{
	if (status)
		return PlaySound(TEXT("Audio\\PressButton.wav"), NULL, SND_ASYNC);
	else return false;
}

#pragma endregion

#pragma region Decorate

void _Common::setColor(int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void _Common::drawFrame(int style, int col, int row, int width, int hight, bool fill, int sw)
{
	int a;
	if (sw > 4)
		sw = 4;
	style = (style - 1) * 6;
	char box[12];
	char shdw[5];
	box[0] = '\xDA';//  ┌
	box[1] = '\xBF';//  ┐
	box[2] = '\xC0';//  └
	box[3] = '\xD9';//  ┘
	box[4] = '\xB3';//  │ 
	box[5] = '\xC4';//  ─
	box[6] = '\xC9';//  ╔ 
	box[7] = '\xBB';//  ╗
	box[8] = '\xC8';//  ╚
	box[9] = '\xBC';//  ╝
	box[10] = '\xBA';// ║
	box[11] = '\xCD';// ═
	shdw[1] = '\xB0';// ░
	shdw[2] = '\xB1';// ▒
	shdw[3] = '\xB2';// ▓
	shdw[4] = '\xDB';// █
	char tl, tr, bl, br, side, edge, shadow;
	tl = box[style];
	tr = box[style + 1];
	bl = box[style + 2];
	br = box[style + 3];
	side = box[style + 4];
	edge = box[style + 5];
	shadow = shdw[sw];
	string Line(width - 2, edge);
	string Shadow(width, shadow);
	string Fill(width - 2, ' ');

	gotoXY(col, row);
	cout << tl << Line << tr;

	for (a = 1; a < hight - 1; a++)
	{
		gotoXY(col, row + a);
		cout << side;
		if (fill)
			cout << Fill;
		else
			gotoXY(col + width - 1, row + a);
		cout << side;
		if (sw)
			cout << shadow;
	}

	gotoXY(col, (hight + row) - 1);
	cout << bl << Line << br;

	if (sw)
	{
		cout << shadow;
		gotoXY(col + 1, row + hight, Shadow);
	}
}

void _Common::drawDelayFrame(int style, int col, int row, int length, int amount, int delay)
{
	style = (style - 1) * 6;
	char box[12];
	box[0] = '\xDA';//  ┌
	box[1] = '\xBF';//  ┐
	box[2] = '\xC0';//  └
	box[3] = '\xD9';//  ┘
	box[4] = '\xB3';//  │ 
	box[5] = '\xC4';//  ─
	box[6] = '\xC9';//  ╔ 
	box[7] = '\xBB';//  ╗
	box[8] = '\xC8';//  ╚
	box[9] = '\xBC';//  ╝
	box[10] = '\xBA';// ║
	box[11] = '\xCD';// ═
	char tl, tr, bl, br, side, edge;
	tl = box[style];
	tr = box[style + 1];
	bl = box[style + 2];
	br = box[style + 3];
	side = box[style + 4];
	edge = box[style + 5];
	string Line(length - 2, edge);

	for (int i = 1; i < amount - 1; i++)
	{
		gotoXY(col, row + i);
		cout << side;
		gotoXY(col + length - 1, amount + row - 1 - i);
		cout << side;
		Sleep(delay);
	}

	gotoXY(col + length - 1, row);
	cout << tr;
	gotoXY(col, amount + row - 1);
	cout << bl;

	for (int i = 0; i < Line.length(); i++)
	{
		gotoXY(col + length - 2 - i, row);
		cout << Line[i];
		gotoXY(col + 1 + i, amount + row - 1);
		cout << Line[i];
		Sleep(delay);
	}

	gotoXY(col, row);
	cout << tl;
	gotoXY(col + length - 1, row + amount - 1);
	cout << br;
}

void _Common::clearFrame(int style, int col, int row, int width, int hight, bool fill, int sw)
{
	int a;
	if (sw > 4)
		sw = 4;
	style = (style - 1) * 6;
	char box[12];
	char shdw[5];
	box[0] = ' ';
	box[1] = ' ';
	box[2] = ' ';
	box[3] = ' ';
	box[4] = ' ';
	box[5] = ' ';
	box[6] = ' ';
	box[7] = ' ';
	box[8] = ' ';
	box[9] = ' ';
	box[10] = ' ';
	box[11] = ' ';
	shdw[1] = ' ';
	shdw[2] = ' ';
	shdw[3] = ' ';
	shdw[4] = ' ';
	char tl, tr, bl, br, side, edge, shadow;
	tl = box[style];
	tr = box[style + 1];
	bl = box[style + 2];
	br = box[style + 3];
	side = box[style + 4];
	edge = box[style + 5];
	shadow = shdw[sw];
	string Line(width - 2, edge);
	string Shadow(width, shadow);
	string Fill(width - 2, ' ');

	gotoXY(col, row);
	cout << tl << Line << tr;
	for (a = 1; a < hight - 1; a++)
	{
		gotoXY(col, row + a);
		cout << side;
		if (fill)
			cout << Fill;
		else
			gotoXY(col + width - 1, row + a);
		cout << side;
		if (sw)
			cout << shadow;
	}
	gotoXY(col, (hight + row) - 1);
	cout << bl << Line << br;
	if (sw)
	{
		cout << shadow;
		gotoXY(col + 1, row + hight, Shadow);
	}
}

void _Common::slowPrint(const string & message, unsigned int millis_per_char)
{
	for (const char c : message)
	{
		cout << c << flush;
		sleep_for(milliseconds(millis_per_char));
	}
}

void _Common::drawX(int left, int top)
{
	char a = char(219);
	gotoXY(left, top);
	cout << a << a << char(187); gotoXY(left + 5, top); cout << a << a << char(187);
	gotoXY(left, top + 1);
	cout << char(200) << a << a << char(187) << a << a << char(201) << char(188);
	gotoXY(left + 1, top + 2);
	cout << char(200) << a << a << a << char(201) << char(188);
	gotoXY(left + 1, top + 3);
	cout << a << a << char(201) << a << a << char(187);
	gotoXY(left, top + 4);
	cout << a << a << char(201) << char(188); gotoXY(left + 5, top + 4); cout << a << a << char(187);
	gotoXY(left, top + 5);
	cout << char(200) << char(205) << char(188); gotoXY(left + 5, top + 5); cout << char(200) << char(205) << char(188);
}

void _Common::drawW(int left, int top)
{
	char a = char(219);
	gotoXY(left, top);
	cout << a << a << char(187); gotoXY(left + 7, top); cout << a << a << char(187);
	gotoXY(left, top + 1);
	cout << a << a << char(186); gotoXY(left + 7, top + 1); cout << a << a << char(186);
	gotoXY(left, top + 2);
	cout << a << a << char(186); gotoXY(left + 4, top + 2); cout << a << char(187); gotoXY(left + 7, top + 2); cout << a << a << char(186);
	gotoXY(left, top + 3);
	cout << a << a << char(186) << a << a << a << char(187) << a << a << char(186);
	gotoXY(left, top + 4);
	cout << char(200) << a << a << a << char(201) << a << a << a << char(201) << char(188);
	gotoXY(left + 1, top + 5);
	cout << char(200) << char(205) << char(205) << char(188) << char(200) << char(205) << char(205) << char(188);
}

void _Common::drawI(int left, int top)
{
	char a = char(219);
	gotoXY(left, top);
	cout << a << a << char(187);
	gotoXY(left, top + 1);
	cout << a << a << char(186);
	gotoXY(left, top + 2);
	cout << a << a << char(186);
	gotoXY(left, top + 3);
	cout << a << a << char(186);
	gotoXY(left, top + 4);
	cout << a << a << char(186);
	gotoXY(left, top + 5);
	cout << char(200) << char(205) << char(188);
}

void _Common::drawN(int left, int top)
{
	char a = char(219);
	gotoXY(left, top);
	cout << a << a << a << char(187);	gotoXY(left + 7, top); cout << a << a << char(187);
	gotoXY(left, top + 1);
	cout << a << a << a << a << char(187); gotoXY(left + 7, top + 1); cout << a << a << char(186);
	gotoXY(left, top + 2);
	cout << a << a << char(201) << a << a << char(187); gotoXY(left + 7, top + 2); cout << a << a << char(186);
	gotoXY(left, top + 3);
	cout << a << a << char(186) << char(200) << a << a << char(187) << a << a << char(186);
	gotoXY(left, top + 4);
	cout << a << a << char(186); gotoXY(left + 4, top + 4); cout << char(200) << a << a << a << a << char(186);
	gotoXY(left, top + 5);
	cout << char(200) << char(205) << char(188); gotoXY(left + 5, top + 5); cout << char(200) << char(205) << char(205) << char(205) << char(188);
}

void _Common::drawO(int left, int top)
{
	char a = char(219);
	gotoXY(left + 1, top);
	cout << a << a << a << a << a << a << char(187);
	gotoXY(left, top + 1);
	cout << a << a << char(201) << char(205) << char(205) << char(205) << a << a << char(187);
	gotoXY(left, top + 2);
	cout << a << a << char(186); gotoXY(left + 6, top + 2); cout << a << a << char(186);
	gotoXY(left, top + 3);
	cout << a << a << char(186); gotoXY(left + 6, top + 3); cout << a << a << char(186);
	gotoXY(left, top + 4);
	cout << char(200) << a << a << a << a << a << a << char(201) << char(188);
	gotoXY(left + 1, top + 5);
	cout << char(200) << char(205) << char(205) << char(205) << char(205) << char(205) << char(188);
}

void _Common::drawD(int left, int top)
{
	char a = char(219);
	gotoXY(left, top);
	cout << a << a << a << a << a << a << char(187);
	gotoXY(left, top + 1);
	cout << a << a << char(201) << char(205) << char(205) << a << a << char(187);
	gotoXY(left, top + 2);
	cout << a << a << char(186); gotoXY(left + 5, top + 2); cout << a << a << char(186);
	gotoXY(left, top + 3);
	cout << a << a << char(186); gotoXY(left + 5, top + 3); cout << a << a << char(186);
	gotoXY(left, top + 4);
	cout << a << a << a << a << a << a << char(201) << char(188);
	gotoXY(left, top + 5);
	cout << char(200) << char(205) << char(205) << char(205) << char(205) << char(205) << char(188);
}

void _Common::drawR(int left, int top)
{
	char a = char(219);
	gotoXY(left, top);
	cout << a << a << a << a << a << a << a << char(187);
	gotoXY(left, top + 1);
	cout << a << a << char(201) << char(205) << char(205) << a << a << a << char(187);
	gotoXY(left, top + 2);
	cout << a << a << a << a << a << a << a << char(201) << char(188);
	gotoXY(left, top + 3);
	cout << a << a << char(201) << char(205) << char(205) << char(205) << a << a << char(187);
	gotoXY(left, top + 4);
	cout << a << a << char(186); gotoXY(left + 6, top + 4); cout << a << a << char(186);
	gotoXY(left, top + 5);
	cout << char(200) << char(205) << char(188); gotoXY(left + 6, top + 5); cout << char(200) << char(205) << char(188);
}

void _Common::drawA(int left, int top)
{
	{
		char a = char(219);
		gotoXY(left + 1, top);
		cout << a << a << a << a << a << a << char(187);
		gotoXY(left, top + 1);
		cout << a << a << char(201) << char(205) << char(205) << char(205) << a << a << char(187);
		gotoXY(left, top + 2);
		cout << a << a << a << a << a << a << a << a << char(186);
		gotoXY(left, top + 3);
		cout << a << a << char(201) << char(205) << char(205) << char(205) << a << a << char(186);
		gotoXY(left, top + 4);
		cout << a << a << char(186); gotoXY(left + 6, top + 4); cout << a << a << char(186);
		gotoXY(left, top + 5);
		cout << char(200) << char(205) << char(188); gotoXY(left + 6, top + 5); cout << char(200) << char(205) << char(188);
	}
}

void _Common::drawY(int left, int top)
{
	char a = char(219);
	gotoXY(left, top);
	cout << a << a << char(187); gotoXY(left + 6, top); cout << a << a << char(187) << endl;
	gotoXY(left, top + 1);
	cout << char(200) << a << a << char(187); gotoXY(left + 5, top + 1); cout << a << a << char(201) << char(188) << endl;
	gotoXY(left + 1, top + 2);
	cout << char(200) << a << a << a << a << char(201) << char(188) << endl;
	gotoXY(left + 2, top + 3);
	cout << char(200) << a << a << char(201) << char(188) << endl;
	gotoXY(left + 3, top + 4);
	cout << a << a << char(186) << endl;
	gotoXY(left + 3, top + 5);
	cout << char(200) << char(205) << char(188) << endl;
}

void _Common::drawU(int left, int top)
{
	char a = char(219);
	gotoXY(left, top);
	cout << a << a << char(187); gotoXY(left + 6, top); cout << a << a << char(187) << endl;
	gotoXY(left, top + 1);
	cout << a << a << char(186); gotoXY(left + 6, top + 1); cout << a << a << char(186) << endl;
	gotoXY(left, top + 2);
	cout << a << a << char(186); gotoXY(left + 6, top + 2); cout << a << a << char(186) << endl;
	gotoXY(left, top + 3);
	cout << a << a << char(186); gotoXY(left + 6, top + 3); cout << a << a << char(186) << endl;
	gotoXY(left, top + 4);
	cout << char(200) << a << a << a << a << a << a << char(201) << char(188) << endl;
	gotoXY(left + 1, top + 5);
	cout << char(200) << char(205) << char(205) << char(205) << char(205) << char(205) << char(188) << endl;
}

void _Common::drawL(int left, int top)
{
	char a = char(219);
	gotoXY(left, top);
	cout << a << a << char(187) << endl;
	gotoXY(left, top + 1);
	cout << a << a << char(186) << endl;
	gotoXY(left, top + 2);
	cout << a << a << char(186) << endl;
	gotoXY(left, top + 3);
	cout << a << a << char(186) << endl;
	gotoXY(left, top + 4);
	cout << a << a << a << a << a << a << a << char(187) << endl;
	gotoXY(left, top + 5);
	cout << char(200) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(188) << endl;
}

void _Common::drawS(int left, int top)
{
	char a = char(219);
	gotoXY(left, top);
	cout << a << a << a << a << a << a << a << char(187) << endl;
	gotoXY(left, top + 1);
	cout << a << a << char(201) << char(205) << char(205) << char(205) << char(205) << char(188) << endl;
	gotoXY(left, top + 2);
	cout << a << a << a << a << a << a << a << char(187) << endl;
	gotoXY(left, top + 3);
	cout << char(200) << char(205) << char(205) << char(205) << char(205) << a << a << char(186) << endl;
	gotoXY(left, top + 4);
	cout << a << a << a << a << a << a << a << char(186) << endl;
	gotoXY(left, top + 5);
	cout << char(200) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(188) << endl;
}

void _Common::drawE(int left, int top)
{
	char a = char(219);
	gotoXY(left, top);
	cout << a << a << a << a << a << a << a << char(187) << endl;
	gotoXY(left, top + 1);
	cout << a << a << char(201) << char(205) << char(205) << char(205) << char(205) << char(188) << endl;
	gotoXY(left, top + 2);
	cout << a << a << a << a << a << char(187) << endl;
	gotoXY(left, top + 3);
	cout << a << a << char(201) << char(205) << char(205) << char(188) << endl;
	gotoXY(left, top + 4);
	cout << a << a << a << a << a << a << a << char(187) << endl;
	gotoXY(left, top + 5);
	cout << char(200) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(188) << endl;
}

void _Common::loadingScreen()
{
	backgroundAudio(AUDIO_STATUS);

	hideCursor();
	setColor(15);
	drawFrame(2, 0, 0, 112, 37, 0, 4);

	//Tọa độ loading bar
	const int x_loadingBar = 50;
	const int y_loadingBar = 20;

	int x = 15, y = 5;					//Tọa độ chữ CARO
	int a = 6, b = 2, c = 1, d = 4;		//Màu

	for (int i = 0; i < 9; i++)
	{
		x = 15;
		setColor(a);
		gotoXY(x, y);cout << "       @@@@@@@@@@@@@" << endl;
		gotoXY(x, y + 1); cout << "     @@@@@@@@@@@@@@" << endl;
		gotoXY(x, y + 2); cout << "   @@@@@@@@@        " << endl;
		gotoXY(x, y + 3); cout << "  @@@@@@@@          " << endl;
		gotoXY(x, y + 4); cout << " @@@@@@@@           " << endl;
		gotoXY(x, y + 5); cout << " @@@@@@@            " << endl;
		gotoXY(x, y + 6); cout << " @@@@@@@            " << endl;
		gotoXY(x, y + 7); cout << " @@@@@@@@           " << endl;
		gotoXY(x, y + 8); cout << "  @@@@@@@@@     @@@@" << endl;
		gotoXY(x, y + 9); cout << "    @@@@@@@@@@@@@@@@" << endl;
		gotoXY(x, y + 10); cout << "      @@@@@@@@@@@@ " << endl;
		Sleep(60);

		x = 35;
		setColor(b);
		gotoXY(x, y + 3); cout << "      @@@@@@@@@@@@@" << endl;
		gotoXY(x, y + 4); cout << "     @@@    @@@@@@@" << endl;
		gotoXY(x, y + 5); cout << "            @@@@@@@" << endl;
		gotoXY(x, y + 6); cout << "     @@@@@@@@@@@@@@" << endl;
		gotoXY(x, y + 7); cout << "   @@@@@@@@@@@@@@@@" << endl;
		gotoXY(x, y + 8); cout << "  @@@@@@@    @@@@@@" << endl;
		gotoXY(x, y + 9); cout << "  @@@@@@@@@@@@@@@@@" << endl;
		gotoXY(x, y + 10); cout << "   @@@@@@@@@@@@@@@@" << endl;
		Sleep(20);

		x = 54;
		setColor(c);
		gotoXY(x, y + 3); cout << "   @@@@@@@@@@@@" << endl;
		gotoXY(x, y + 4); cout << "   @@@@@@@@@@@@" << endl;
		gotoXY(x, y + 5); cout << "   @@@@@@@@    " << endl;
		gotoXY(x, y + 6); cout << "   @@@@@@@     " << endl;
		gotoXY(x, y + 7); cout << "   @@@@@@      " << endl;
		gotoXY(x, y + 8); cout << "   @@@@@@      " << endl;
		gotoXY(x, y + 9); cout << "   @@@@@@      " << endl;
		gotoXY(x, y + 10); cout << "   @@@@@@      " << endl;
		Sleep(10);

		x = 70;
		setColor(d);
		gotoXY(x, y + 0); cout << "       @@@@@@@@@@@@@@" << endl;
		gotoXY(x, y + 1); cout << "    @@@@@@@@@@@@@@@@@@@@" << endl;
		gotoXY(x, y + 2); cout << "  @@@@@@@@@      @@@@@@@@" << endl;
		gotoXY(x, y + 3); cout << " @@@@@@@@         @@@@@@@@" << endl;
		gotoXY(x, y + 4); cout << " @@@@@@@           @@@@@@@" << endl;
		gotoXY(x, y + 5); cout << " @@@@@@@           @@@@@@@" << endl;
		gotoXY(x, y + 6); cout << " @@@@@@@           @@@@@@@" << endl;
		gotoXY(x, y + 7); cout << " @@@@@@@@         @@@@@@@@" << endl;
		gotoXY(x, y + 8); cout << "  @@@@@@@@@     @@@@@@@@@" << endl;
		gotoXY(x, y + 9); cout << "    @@@@@@@@@@@@@@@@@@@" << endl;
		gotoXY(x, y + 10); cout << "      @@@@@@@@@@@@@@" << endl;

		//Hoán vị các màu
		int temp = d;
		d = c;		c = b;		b = a;		a = temp;

		setColor(14);
		gotoXY(x_loadingBar, y_loadingBar);
		if (i == 0)
			cout << "LOADING";
		else
			cout << "LOADING" << setw(2) << i << "0%";

		gotoXY(x_loadingBar - 4, y_loadingBar + 2);
		for (int k = 0; k < 18; k++)
			cout << char(176);

		gotoXY(x_loadingBar - 4, y_loadingBar + 2);
		for (int j = 0; j < i; j++)
			cout << char(219) << char(219);

		Sleep(430);
	}

	//Xóa loading bar
	gotoXY(x_loadingBar, y_loadingBar);
	cout << "       ";
	gotoXY(x_loadingBar - 5, y_loadingBar + 2);
	for (int k = 0; k < 17; k++)
		cout << ' ';

	choiceAudio(AUDIO_STATUS);
}

void _Common::loadedScreen()
{
	clrscr();
	hideCursor();
	setColor(15);
	drawFrame(2, 0, 0, 112, 37, 0, 4);

	int x = 15, y = 5;
	for (int i = 0; i < 2; i++)
	{
		setColor(4);
		gotoXY(x, y); cout << "       @@@@@@@@@@@@@" << endl;
		gotoXY(x, y + 1); cout << "     @@@@@@@@@@@@@@" << endl;
		gotoXY(x, y + 2); cout << "   @@@@@@@@@        " << endl;
		gotoXY(x, y + 3); cout << "  @@@@@@@@          " << endl;
		gotoXY(x, y + 4); cout << " @@@@@@@@           " << endl;
		gotoXY(x, y + 5); cout << " @@@@@@@            " << endl;
		gotoXY(x, y + 6); cout << " @@@@@@@            " << endl;
		gotoXY(x, y + 7); cout << " @@@@@@@@           " << endl;
		gotoXY(x, y + 8); cout << "  @@@@@@@@@     @@@@" << endl;
		gotoXY(x, y + 9); cout << "    @@@@@@@@@@@@@@@@" << endl;
		gotoXY(x, y + 10); cout << "      @@@@@@@@@@@@ " << endl;


		x = 35;
		setColor(6);
		gotoXY(x, y + 3); cout << "      @@@@@@@@@@@@@" << endl;
		gotoXY(x, y + 4); cout << "     @@@    @@@@@@@" << endl;
		gotoXY(x, y + 5); cout << "            @@@@@@@" << endl;
		gotoXY(x, y + 6); cout << "     @@@@@@@@@@@@@@" << endl;
		gotoXY(x, y + 7); cout << "   @@@@@@@@@@@@@@@@" << endl;
		gotoXY(x, y + 8); cout << "  @@@@@@@    @@@@@@" << endl;
		gotoXY(x, y + 9); cout << "  @@@@@@@@@@@@@@@@@" << endl;
		gotoXY(x, y + 10); cout << "   @@@@@@@@@@@@@@@@" << endl;


		x = 54;
		setColor(2);
		gotoXY(x, y + 3); cout << "   @@@@@@@@@@@@" << endl;
		gotoXY(x, y + 4); cout << "   @@@@@@@@@@@@" << endl;
		gotoXY(x, y + 5); cout << "   @@@@@@@@    " << endl;
		gotoXY(x, y + 6); cout << "   @@@@@@@     " << endl;
		gotoXY(x, y + 7); cout << "   @@@@@@      " << endl;
		gotoXY(x, y + 8); cout << "   @@@@@@      " << endl;
		gotoXY(x, y + 9); cout << "   @@@@@@      " << endl;
		gotoXY(x, y + 10); cout << "   @@@@@@      " << endl;

		x = 70;
		setColor(1);
		gotoXY(x, y + 0); cout << "       @@@@@@@@@@@@@@" << endl;
		gotoXY(x, y + 1); cout << "    @@@@@@@@@@@@@@@@@@@@" << endl;
		gotoXY(x, y + 2); cout << "  @@@@@@@@@      @@@@@@@@" << endl;
		gotoXY(x, y + 3); cout << " @@@@@@@@         @@@@@@@@" << endl;
		gotoXY(x, y + 4); cout << " @@@@@@@           @@@@@@@" << endl;
		gotoXY(x, y + 5); cout << " @@@@@@@           @@@@@@@" << endl;
		gotoXY(x, y + 6); cout << " @@@@@@@           @@@@@@@" << endl;
		gotoXY(x, y + 7); cout << " @@@@@@@@         @@@@@@@@" << endl;
		gotoXY(x, y + 8); cout << "  @@@@@@@@@     @@@@@@@@@" << endl;
		gotoXY(x, y + 9); cout << "    @@@@@@@@@@@@@@@@@@@" << endl;
		gotoXY(x, y + 10); cout << "      @@@@@@@@@@@@@@" << endl;
	}
}

#pragma endregion