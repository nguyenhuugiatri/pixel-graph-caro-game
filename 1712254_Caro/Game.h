#pragma once
#include "Common.h"
#include "Board.h"
#include "Bot.h"
#include "Menu.h"

class _Game
{
private:
	_Board *_b;				//Một bàn cờ
	_Bot *_bot;				//Máy
	bool _turn;				//Lượt chơi: true lượt X & false lượt O
	int _x, _y;				//Tọa độ hiện hành nháy chuột
	int _command;			//Phím gõ từ người dùng
	bool _loop;				//Biến quyết định thoát game hay không
	int _scoreX, _scoreO;	//Điểm người chơi
	int _stepX, _stepO;		//Số bước đi
	bool _first;			//Người đánh trước, đổi lượt sau mỗi ván

public:
#pragma region Constructor & Destructor
	_Game(int, int, int);
	~_Game();
#pragma endregion

#pragma region Getter & Setter
	bool getTurn() { return _turn; }
	_Bot*&getBot() { return _bot; }
	int getCommand() { return _command; }
	bool isContinue() { return _loop; }
	char waitKeyBoard();
#pragma endregion

#pragma region Main Method
	void startGame(bool);				//Bắt đầu game
	int exitGame(bool);					//Kết thúc game
	bool processCheckBoard();			//Kiểm tra để đánh cờ nào
	int waitForUser(bool);				//Người đánh
	int waitForBot();					//Máy đánh
	int processFinish();				//Kiểm tra thắng/thua/hòa người vs người
	int processFinish(bool);			//Kiểm tra thắng/thua/hòa người vs máy
	int askForContinue(bool);			//Hỏi người chơi có muốn chơi tiếp ván mới
	int askForResume(bool);				//Hỏi người chơi có muốn chơi tiếp ván đang chơi
#pragma endregion

#pragma region Moving
	void moveRight();	//Di chuyển con trỏ qua phải
	void moveLeft();	//Di chuyển con trỏ qua trái
	void moveUp();		//Di chuyển con trỏ đi lên
	void moveDown();	//Di chuyển con trỏ đi xuống
#pragma endregion

#pragma region Save/Load
	int saveGame(bool, bool);						//Lưu game (true: hỏi có tiếp tục không, flase: không hỏi)
	void loadGame(bool);							//Tải game
	void saveTemp();								//Lưu bàn cờ tạm thời
	void loadTemp(bool);							//Tải lại bàn cờ tạm thời
#pragma endregion

#pragma region Match Information
	void drawFrameMatchInformation();			//Vẽ khung thông tin màn chơi
	void drawMatchInformation(bool);			//Xuất thông tin màn chơi ban đầu
	void updateStep();							//Cập nhật số bước đi
	void updateScore();							//Cập nhật tỉ số
	void resetScore();							//Reset tỉ số
	void resetStep();							//Reset bước đi
	void resetFirst();							//Reset người đánh trước
	void resetMatchInformation();				//Reset tất cả thông tin
#pragma endregion

#pragma region Decorate
	void clearScreen(int, int, int, int, int);	//Xóa màn hình có hiệu ứng

	//Hiệu ứng thắng/thua
	void drawXWIN(int, int);
	void drawOWIN(int, int);
	void drawDRAW(int, int);
	void drawYOUWIN(int, int);
	void drawYOULOSE(int, int);
#pragma endregion

#pragma region Others
	string inputFileName(int, int, int);			//Nhập tên file giới hạn số lượng
	bool checkFileName(string);						//Kiểm tra tên file
	bool checkExist(string&, vector<string>&);		//Kiểm tra tên có tồn tại
	bool isEquals(const string&, const string&);	//So sánh 2 chuỗi
#pragma endregion
};