#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <winsock.h>
#include <sstream>
using namespace std;

#define N 15
class Player
{
private:
	string _username = "";
	string _password = "";
	string _dob = "";
	string _fullname = "";
	string _note = "";
	int _point = 0;
	bool _isonline;
	SOCKET _player;
	Player* _partner;
	int _checkpoint = 0;
public:
	string board[N + 1][N + 1];
	void setUsername(string);
	void setPassword(string);
	void setDOB(string);
	void setFullname(string);
	void setNote(string);
	void setIsOnline(bool);
	void setSocketClient(SOCKET);
	void setPartner(Player*);
	void updatePoint();
	void setcheckPoint(int);
	bool isOnline();
	int point();
	int checkPoint();
	string username();
	string password();
	string dob();
	string fullname();
	string note();
	SOCKET socketofPlayer();
	Player* partner();
public:
	Player();
	void CreateWhiteBoard(string WB[N + 1][N + 1]);
};