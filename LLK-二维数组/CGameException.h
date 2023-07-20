#pragma once
#include"string"
class CGameException
{
private:
	std::string message;
public:
	std::string getMessage() {
		return message;
	}
	CGameException(std::string _message) :message(_message){}

};

