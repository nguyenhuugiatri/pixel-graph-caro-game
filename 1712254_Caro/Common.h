#pragma once
#include <iostream>
#include <windows.h>
#include <conio.h>
#include <string>
#include <fstream>
#include <vector>
#include <thread>
#include <iomanip>
#include <MMsystem.h>
#pragma comment(lib, "winmm.lib")
using std::chrono::milliseconds;
using std::this_thread::sleep_for;
using namespace std;

class _Common
{
public:
	static bool AUDIO_STATUS;

public:
#pragma region Console
	static void setConsoleWindow(int, int);	//Điều chỉnh kích thước Console
	static void fixConsoleWindow();			//Cố định Console
	static void removeConsoleScrollbar();	//Bỏ thanh cuộn Console
	static void setConsoleTitle();			//Tiêu đề Console
	static void setupConsole();				//Setup Console (bằng 4 phương thức trên)
	static void clrscr();					//Xóa màn hình
	static void showCursor();				//Hiện con trỏ
	static void hideCursor();				//Ẩn con trỏ
#pragma endregion

#pragma region Moving
	static void gotoXY(int, int);				//Di chuyển đến tọa độ
	static void gotoXY(int, int, char);			//Di chuyển đến tọa độ và viết một kí tự	
	static void gotoXY(int, int, string);		//Di chuyển đến tọa độ và viết một câu
	static void gotoXY(int, int, string, int);	//Di chuyển đến tọa độ và viết một câu có màu
	static void gotoXY(int, int, int, int);		//Di chuyển đến tọa độ và viết một số có màu
#pragma endregion

#pragma region Audio
	static void setAudioStatus(bool);			//Tắt mở toàn bộ âm thanh
	static bool stopAudio(bool &);				//Dừng 1 âm thanh
	static void backgroundAudio(bool &);		//Nhạc nền
	static bool choiceAudio(bool &);			//Âm thanh chọn
	static bool stepAudio(bool &);				//Âm thanh di chuyển con trỏ khi đánh cờ
	static bool switchTitleAudio(bool &);		//Âm thanh di chuyển giữa các title của menu
	static bool winRowAudio(bool &);			//Âm thanh hoàn thành đủ 5 ô cờ
	static bool victoryAudio(bool &);			//Âm thanh chiến thắng
	static bool loseAudio(bool &);				//Âm thanh thua
	static bool typingAudio(bool &);			//Âm thanh đánh phím
	static bool accessDeniedAudio(bool &);		//Âm thanh cảnh báo khi đi vào ô đã đi
	static bool XChessmanAudio(bool &);			//Âm thanh khi đi quân X
	static bool OChessmanAudio(bool &);			//Âm thanh khi đi quân O
	static bool drawDelayFrameAudio(bool &);		//Âm thanh vẽ khung
	static bool quitGameAudio(bool &);			//Âm thanh tắt game
	static bool confirmAudio(bool &);			//Âm thanh xác nhận lưu file thành công
	static bool pressButtonAudio(bool &);		//Âm thanh nhấn 1 phím
#pragma endregion

#pragma region Decorate
	static void setColor(int);									//Set màu
	static void drawFrame(int, int, int, int, int, bool, int);	//Vẽ khung
	static void clearFrame(int, int, int, int, int, bool, int);	//Xóa khung
	static void drawDelayFrame(int, int, int, int, int, int);	//Vẽ khung với hiệu ứng delay
	static void slowPrint(const string&, unsigned int);			//Hiệu ứng viết chữ
	static void drawX(int, int);								//Vẽ chữ X
	static void drawW(int, int);								//Vẽ chữ W
	static void drawI(int, int);								//Vẽ chữ I
	static void drawN(int, int);								//Vẽ chữ N
	static void drawO(int, int);								//Vẽ chữ O
	static void drawD(int, int);								//Vẽ chữ D
	static void drawR(int, int);								//Vẽ chữ R
	static void drawA(int, int);								//Vẽ chữ A
	static void drawY(int, int);								//Vẽ chữ Y
	static void drawU(int, int);								//Vẽ chữ U
	static void drawL(int, int);								//Vẽ chữ L
	static void drawS(int, int);								//Vẽ chữ S
	static void drawE(int, int);								//Vẽ chữ E
	static void loadingScreen();								//Màn hình đang load
	static void loadedScreen();									//Màn hình load xong
#pragma endregion
};