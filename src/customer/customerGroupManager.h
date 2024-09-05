#pragma once
#include <iostream>
#include "customer.h"
using namespace std;

class customerGroupManager{
	static customerGroupManager* instance;

public :
	static customerGroupManager* getInstance();

	void showGroupManageSystem();
	bool viewGroup();
	void changeUserGroup();
};