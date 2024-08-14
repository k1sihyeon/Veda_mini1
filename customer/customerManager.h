#pragma once
#include <unordered_map>
using namespace std;

class Customer;

class customerManager {
private :
	
	static customerManager* instance;

	customerManager() {	}
	customerManager(const customerManager&) = delete;
	customerManager& operator=(const customerManager&) = delete;

	unordered_map<string, Customer> customermap;
	int userCount;

public :
	static customerManager* getInstance() {
		if (instance == nullptr) {
			instance = new customerManager();
		}
		return instance;
	}

	void showManageSystem();

	void addUser(); // txt 파일에서 유저 정보 받아와서 customermap에 저장
	void deleteUser(Customer& customer); // customermap 에서 유저 정보 삭제, txt파일에 업데이트 
	void showUserList(); // customermap 전부 출력 (sorting 기준 (totalpurchase 순, 이름순.. ?) 세울지)
	void showUserInfo(Customer& customer); // user 한명 정보 보기 (id / pw / 이름 / 성별 / 전화번호 / 주소 / 총구매금액 ) 
	void updateUserInfo(Customer& customer); // user 정보 변경 후 txt 파일에 업데이트

	void addUserToGroup(const string& userId, const string& groupName); 
	void removeUserFromGroup(const string& userId, const string& groupName);

};

/* 

1. 옵저버 패턴으로 구매시 고객 정보 / group 업데이트 여부 체크 ->>>>> 도입.
2. 문의내역 조회기능? 혹은 채팅..? ->>>> 나중에..
3. 고객 후기 보기 ->>>>> 나중에 ..
4. 그룹(티어) 관리 -> 알맞게 쿠폰이나 포인트 배부..?  ->>>> getter 넣기 (티어 확인할수있게 멤버변수추가)
5. 고유id 굳이 있어야 하려나..?  -- >>> 빼기

int uniqueId; // manager gives it
	string userId;
	string userPassword;
	string userName;
	bool userGender; // 0 female, 1 male

	string userPhoneNumber;
	string userAddress;

	int totalPurchase;


*/ 