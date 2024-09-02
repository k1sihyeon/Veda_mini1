#pragma once
#include <string>
using namespace std;
class Observer {
public :
	virtual void update(const string& userId, const string& productname, int quantity) = 0;
	virtual ~Observer() = default;
};
