#pragma once
#include <unordered_map>
#include "Observer.h"
#include "customer.h"
#include <vector> 
using namespace std;


class customerManager : public Observer{
private :
	
	static customerManager* instance;

	customerManager() : userCount(0) {};
	customerManager(const customerManager&) = delete;
	customerManager& operator=(const customerManager&) = delete;

	unordered_map<string, Customer> customermap;

	int userCount;

	const string filepath = "./data/customersList.csv";

public :
	static customerManager* getInstance();
	void getRegisteredUsers();
	int getuserCount() { return userCount;}

	Customer* getCustomer(string id) {
		return &customermap[id];
	}
	void update(const string& userId, const string& productname, int quantity) override {
		auto it = customermap.find(userId);
		if (it != customermap.end()) {
			it->second.updateTotalPurchase(quantity);
			int total = it->second.getTotalPurchase();

			if (total >= 5000000 && it->second.getGroup() != Customer::Group::platinum)
				it->second.updateGroup(3);
			else if (total >= 1000000 && it->second.getGroup() != Customer::Group::gold)
				it->second.updateGroup(2);
			else if (total >= 100000 && it->second.getGroup() != Customer::Group::silver)
				it->second.updateGroup(1);

			updateChangedUserInfo(it->second);
		}
	}

	void showManageSystem();

	bool Login(const string& id, const string& pwd);
	bool registerUser(); // 회원가입
	void deleteUser(Customer& customer); // customermap 에서 유저 정보 삭제, txt파일에 업데이트 
	void addUser(Customer& customer);

	void showUserList(); // customermap 전부 출력 (sorting 기준 (totalpurchase 순, 이름순.. ?) 세울지)
	void showUserInfo(Customer& customer); // user 한명 정보 보기 (id / pw / 이름 / 성별 / 전화번호 / 주소 / 총구매금액 ) 
	void updateUserInfo(Customer& customer); // change ui + user 정보 변경 후 txt 파일에 업데이트 
	void updateChangedUserInfo(Customer& customer); // user 정보 변경후 txt 파일에 업데이트 

	vector<Customer> getGroupList(Customer::Group group);

};

/* 

1. 옵저버 패턴으로 구매시 고객 정보 / group 업데이트 여부 체크 ->>>>> 도입.

4. 그룹(티어) 관리 -> 알맞게 쿠폰이나 포인트 배부..?  ->>>> getter 넣기 (티어 확인할수있게 멤버변수추가)
*/ 