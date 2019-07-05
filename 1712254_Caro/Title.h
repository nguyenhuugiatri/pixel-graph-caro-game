#pragma once
#include "Common.h"

class _Title
{
private:
	string _content;	//Nội dung title

public:
#pragma region Constructor & Destructor
	_Title() {}
	_Title(string content) { _content = content; }
#pragma endregion

#pragma region Getter & Setter
	string getContent() { return _content; }
	void setContent(string content) { _content = content; }
#pragma endregion
};