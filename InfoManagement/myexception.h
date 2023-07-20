#ifndef MYEXCEPTION_H
#define MYEXCEPTION_H
#include<string>
class MyException {
public:
	MyException(const std::string message ):message_(message){}
	const std::string & getMessage() const{
		return message_;
	}
private:
	std::string message_;
};

#endif
