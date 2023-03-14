#pragma once
#include <iostream>
#include <fstream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <string>
#include <thread>
#include <vector>
#include <stdexcept>
#include <sstream>
#include <iomanip>
#include <cstdint>
#include<regex>
#include "Player.h"

#define N 15

//#define IP_ADDRESS "127.0.0.1"
#define IP_ADDRESS "192.168.43.51"
#define DEFAULT_PORT "3504"
#define DEFAULT_BUFLEN 512
static vector<Player> list;
const char OPTION_VALUE = 1;
const int MAX_CONNECTED = 50;

using namespace std;
#pragma comment (lib, "Ws2_32.lib")

string string_to_hex(const string& in);

string hex_to_string(const string& in);

int gameplay(SOCKET curClient, thread& thread);
void LoadPlayer();
bool Login( int& pos, SOCKET curClient);
bool Find(string username, int& pos);
void ChangePassword(int& pos, SOCKET curClient);
bool Register(SOCKET curClient);
void CheckUser(SOCKET curClient);
void SetupInfo(int pos, SOCKET curClient);
void UploadShips(int pos, SOCKET curClient);
void GetRequest(int& pos, SOCKET& curClient, bool& playCheck, bool& uploadShips);
void Game(int pos, bool& uploadShips, string board[N + 1][N + 1]);
void SplitMess(string value, int& x, int& y);
bool isValidFormat(string value);
