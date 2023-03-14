#pragma once
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include <string>
#include <thread>
#include <stdexcept>
#include <sstream>
#include <iomanip>
#include <cstdint>
#include <stdio.h>
#include <windows.h>
#include <regex>
#include <fstream>
#include <conio.h>
#pragma warning(disable : 4996)

using namespace std;
#define N 15

#pragma comment (lib, "Ws2_32.lib")

//void GetRequest(SOCKET client);
string string_to_hex(const string& in);

string hex_to_string(const string& in);
void Login(SOCKET client, string id);
void Register(SOCKET client, string id);
void ChangePassword(SOCKET client);
void CheckUser(string request, string id, SOCKET client);
void SetupInfo(string request, string s, SOCKET client);
int GetInvite(SOCKET client, bool& isInvited, string& opponent, string& roomID);
void Game(SOCKET client, string board[N + 1][N + 1], string opponent, string roomID);

void UploadShips(SOCKET curClient, string filename, string board[N + 1][N + 1]);

void PrintBoard(string Mine[N + 1][N + 1], string Attacking[N + 1][N + 1], string opponent, string roomID);

void CreateWhiteBoard(string WB[N + 1][N + 1]);

void gotoxy(int x, int y);

void SET_COLOR(int color);

void Logo();

void SplitMess(string value, int& x, int& y);

bool isValidFormat(string value);

void FillPassword(string& password, int k, int m);
