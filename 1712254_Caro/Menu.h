#pragma once
#include "Title.h"
#include "Bot.h"

class _Menu
{
private:
	_Title *_title;			//Mảng các tiêu đề
	int _quantity;			//Số lượng
	int _curr;				//Lưu vị trí con trỏ chọn
	int _startPos;			//Vị trí bắt đầu Menu

public:
#pragma region Constructor & Destructor
	_Menu(int);
	~_Menu();
#pragma endregion

#pragma region Getter & Setter
	int getCurr() { return _curr; }
	void setTitle(string, int);
#pragma endregion

#pragma region Main Method
	void displayMenu();			//Hiển thị Menu
	void switchTitle(int &);	//Di chuyển tiêu đề
#pragma endregion

#pragma region Decorate
	void drawFrameTitle(int);								//Tạo khung cho title
	void clearFrameTitle(int);								//Xóa khung cho title
	void drawFrameMenu(int, int, int, int, int, int);		//Vẽ khung cho nội dung menu
	void clearFrameMenu(int, int, int, int, int);			//Xóa khung cho nội dung menu
#pragma endregion

#pragma region Sub-Menu
	int loadGameMenu();				//Menu Load Game
	void tutorialMenu();			//Menu Tutorial
	void aboutMenu();				//Menu About
	void settingsMenu(_Bot *&);		//Menu Settings
#pragma endregion
};