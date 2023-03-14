#include "Header.h"
int check_turn = 0;

string string_to_hex(const string& in) {
	stringstream ss;

	ss << hex << setfill('0');
	for (size_t i = 0; in.length() > i; ++i) {
		ss << setw(2) << static_cast<unsigned int>(static_cast<unsigned char>(in[i]));
	}

	return ss.str();
}

string hex_to_string(const string& in) {
	string output;

	if ((in.length() % 2) != 0) {
		throw runtime_error("String is not valid length ...");
	}

	size_t cnt = in.length() / 2;

	for (size_t i = 0; cnt > i; ++i) {
		uint32_t s = 0;
		stringstream ss;
		ss << hex << in.substr(i * 2, 2);
		ss >> s;

		output.push_back(static_cast<unsigned char>(s));
	}

	return output;
}

bool Login(int& pos, SOCKET curClient)
{
	string username, pw;
	string isEncrypt;
	char tempmsg[512];
	memset(tempmsg, 0, 512);
	int iResult = recv(curClient, tempmsg, 512, 0);
	if (iResult == SOCKET_ERROR)
	{
		char msg[] = "Can't recieve message.";
		send(curClient, msg, strlen(msg), 0);
		return false;
	}
	isEncrypt = string(tempmsg);

	memset(tempmsg, 0, 512);
	iResult = recv(curClient, tempmsg, 512, 0);
	if (iResult == SOCKET_ERROR)
	{
		char msg[] = "Can't recieve message.";
		send(curClient, msg, strlen(msg), 0);
		return false;
	}
	username = string(tempmsg);
	memset(tempmsg, 0, 512);
	iResult = recv(curClient, tempmsg, 512, 0);
	if (iResult == SOCKET_ERROR)
	{
		char msg[] = "Can't recieve message.";
		send(curClient, msg, strlen(msg), 0);
		return false;
	}
	pw = string(tempmsg);
	if (isEncrypt == "Y")
	{
		username = hex_to_string(username);
		pw = hex_to_string(pw);
	}
	if (Find(username, pos))
	{
		if (list[pos].password() == pw)
		{
			char msg[] = "Login successfully.";
			send(curClient, msg, strlen(msg), 0);
			list[pos].setIsOnline(true);
			list[pos].setSocketClient(curClient);
			return true;
		}
		else
		{
			char msg[] = "Login failed";
			send(curClient, msg, strlen(msg), 0);
			pos = -1;
		}
	}
	else
	{
		char msg[] = "Username doesn't exist.";
		send(curClient, msg, strlen(msg), 0);
		pos = -1;
	}

	return false;
}

bool Find(string username, int& pos)
{
	for (int i = 0; i < list.size(); i++)
	{
		if (list[i].username() == username)
		{
			pos = i;
			return true;
		}
	}
	return false;
}

void ChangePassword(int& pos, SOCKET curClient)
{
	string cpw;
	string isEncrypt;
	char tempmsg[512];
	memset(tempmsg, 0, 512);
	int iResult = recv(curClient, tempmsg, 512, 0);
	if (iResult == SOCKET_ERROR)
	{
		char msg[] = "Can't recieve message.";
		send(curClient, msg, strlen(msg), 0);
		return;
	}
	isEncrypt = string(tempmsg);
	memset(tempmsg, 0, 512);
	iResult = recv(curClient, tempmsg, 512, 0);
	if (iResult == SOCKET_ERROR)
	{
		char msg[] = "Can't recieve message.";
		send(curClient, msg, strlen(msg), 0);
		return;
	}
	cpw = string(tempmsg);
	if (isEncrypt == "Y")
	{
		cpw = hex_to_string(cpw);
	}

	if (cpw == list[pos].password())
	{
		char msg[] = "true";
		send(curClient, msg, strlen(msg), 0);
		string npw;
		memset(tempmsg, 0, 512);
		int iResult = recv(curClient, tempmsg, 512, 0);
		if (iResult == SOCKET_ERROR)
		{
			char msg[] = "Can't recieve message.";
			send(curClient, msg, strlen(msg), 0);
			return;
		}
		npw = string(tempmsg);
		if (isEncrypt == "Y")
		{
			npw = hex_to_string(npw);
		}
		list[pos].setPassword(npw);
	}
	else
	{
		char msg[] = "Your current password is incorrect.";
		send(curClient, msg, strlen(msg), 0);
	}
}

bool Register(SOCKET curClient)
{
	string username, pw;
	string isEncrypt;
	char tempmsg[512];
	memset(tempmsg, 0, 512);
	int iResult = recv(curClient, tempmsg, 512, 0);
	if (iResult == SOCKET_ERROR)
	{
		char msg[] = "Can't recieve message.";
		send(curClient, msg, strlen(msg), 0);
		return false;
	}
	isEncrypt = string(tempmsg);
	memset(tempmsg, 0, 512);
	iResult = recv(curClient, tempmsg, 512, 0);
	if (iResult == SOCKET_ERROR)
	{
		char msg[] = "Can't recieve message.";
		send(curClient, msg, strlen(msg), 0);
		return false;
	}
	username = string(tempmsg);
	memset(tempmsg, 0, 512);
	iResult = recv(curClient, tempmsg, 512, 0);
	if (iResult == SOCKET_ERROR)
	{
		char msg[] = "Can't recieve message.";
		send(curClient, msg, strlen(msg), 0);
		return false;
	}
	pw = string(tempmsg);
	if (isEncrypt == "Y")
	{
		username = hex_to_string(username);
		pw = hex_to_string(pw);
	}
	int temp;
	if (!Find(username, temp))
	{
		Player newPlayer = Player();
		newPlayer.setUsername(username);
		newPlayer.setPassword(pw);
		list.push_back(newPlayer);
		char msg[] = "Register successfully.";
		send(curClient, msg, strlen(msg), 0);
		return true;
	}
	else
	{
		char msg[] = "Username has existed.";
		send(curClient, msg, strlen(msg), 0);
		return false;
	}

}

void CheckUser(SOCKET curClient)
{
	string request, username;
	char tempmsg[512];
	memset(tempmsg, 0, 512);
	int iResult = recv(curClient, tempmsg, 512, 0);
	if (iResult == SOCKET_ERROR)
	{
		char msg[] = "Can't recieve message.";
		send(curClient, msg, strlen(msg), 0);
		return;
	}
	request = string(tempmsg);
	memset(tempmsg, 0, 512);
	iResult = recv(curClient, tempmsg, 512, 0);
	if (iResult == SOCKET_ERROR)
	{
		char msg[] = "Can't recieve message.";
		send(curClient, msg, strlen(msg), 0);
		return;
	}
	username = string(tempmsg);
	int temp;
	if (!Find(username, temp))
	{
		string msg = username + " doesn't exist.";
		send(curClient, msg.c_str(), strlen(msg.c_str()), 0);
		return;
	}
	if (request == "find")
	{
		string msg = username + " exist.";
		send(curClient, msg.c_str(), strlen(msg.c_str()), 0);
		return;
	}
	else if (request == "online")
	{
		if (list[temp].isOnline())
		{
			string msg = username + " is online.";
			send(curClient, msg.c_str(), strlen(msg.c_str()), 0);
			return;
		}
		else
		{
			string msg = username + " is offline.";
			send(curClient, msg.c_str(), strlen(msg.c_str()), 0);
			return;
		}
	}
	else if (request == "show_date")
	{
		string dob = "DOB of " + username + ": " + list[temp].dob();
		send(curClient, dob.c_str(), strlen(dob.c_str()), 0);
		return;
	}
	else if (request == "show_fullname")
	{
		string fullname = "fullname of " + username + ": " + list[temp].fullname();
		send(curClient, fullname.c_str(), strlen(fullname.c_str()), 0);
		return;
	}
	else if (request == "show_note")
	{
		string note = "Note:" + list[temp].note();
		send(curClient, note.c_str(), strlen(note.c_str()), 0);
	}
	else if (request == "show_all")
	{
		if (list[temp].isOnline())
		{
			string msg = username + " is online.";
			send(curClient, msg.c_str(), strlen(msg.c_str()), 0);
		}
		else
		{
			string msg = username + " is offline.";
			send(curClient, msg.c_str(), strlen(msg.c_str()), 0);
		}
		Sleep(100);
		string dob = "DOB of " + username + ": " + list[temp].dob();
		send(curClient, dob.c_str(), strlen(dob.c_str()), 0);
		Sleep(100);
		string fullname = "fullname of " + username + ": " + list[temp].fullname();
		send(curClient, fullname.c_str(), strlen(fullname.c_str()), 0);
		Sleep(100);
		string note = "Note:" + list[temp].note();
		send(curClient, note.c_str(), strlen(note.c_str()), 0);
		Sleep(100);
		int point = list[temp].point();
		string msg = "Point of " + username + ": " + to_string(point);
		send(curClient, msg.c_str(), strlen(msg.c_str()), 0);
	}
	else if (request == "show_point")
	{
		int point = list[temp].point();
		string msg = "Point of " + username + ": " + to_string(point);
		send(curClient, msg.c_str(), strlen(msg.c_str()), 0);
	}
	else
	{
		string msg = "This option is not available";
		send(curClient, msg.c_str(), strlen(msg.c_str()), 0);
		return;
	}
}

void SetupInfo(int pos, SOCKET curClient)
{
	string request, buffer;
	char tempmsg[512];
	memset(tempmsg, 0, 512);
	int iResult = recv(curClient, tempmsg, 512, 0);
	if (iResult == SOCKET_ERROR)
	{
		char msg[] = "Can't recieve message.";
		send(curClient, msg, strlen(msg), 0);
		return;
	}
	request = string(tempmsg);
	memset(tempmsg, 0, 512);
	iResult = recv(curClient, tempmsg, 512, 0);
	if (iResult == SOCKET_ERROR)
	{
		char msg[] = "Can't recieve message.";
		send(curClient, msg, strlen(msg), 0);
		return;
	}
	buffer = string(tempmsg);

	if (request == "fullname")
	{
		list[pos].setFullname(buffer);
		char msg[] = "True";
		send(curClient, msg, strlen(msg), 0);
		return;
	}
	else if (request == "date")
	{
		list[pos].setDOB(buffer);
		char msg[] = "True";
		send(curClient, msg, strlen(msg), 0);
		return;
	}
	else if (request == "note")
	{
		list[pos].setNote(buffer);
		char msg[] = "True";
		send(curClient, msg, strlen(msg), 0);
		return;
	}
	else
	{
		char msg[] = "False";
		send(curClient, msg, strlen(msg), 0);
		return;
	}
}

void UploadShips(int pos, SOCKET curClient)
{
	int count = 0;
	for (int i = 1; i < N + 1; i++)
	{
		for (int j = 1; j < N + 1; j++)
		{
			char msg[512];
			memset(msg, 0, 512);
			recv(curClient, msg, 512, 0);
			list[pos].board[i][j] = string(msg);
			if (list[pos].board[i][j] == "S") count++;
		}
	}
	list[pos].setcheckPoint(count);
}

void GetRequest(int& pos, SOCKET& curClient, bool& playGame, bool& uploadShips)
{
	char tempmsg[512];
	memset(tempmsg, 0, 512);
	int iResult = recv(curClient, tempmsg, 512, 0);
	string request = string(tempmsg);
	if (request == "Yes")
	{
		memset(tempmsg, 0, 512);
		int iResult = recv(curClient, tempmsg, 512, 0);
		string username = string(tempmsg);
		int k;
		if (Find(username, k))
		{
			list[pos].setPartner(&list[k]);
			playGame = true;
		}
		UploadShips(pos, curClient);
		uploadShips = true;
	}
	else if (request == "No")
	{
		return;
	}
	else
	{
		string test = "False";
		send(curClient, test.c_str(), strlen(test.c_str()), 0);
	}
	if (request == "start_game")
	{
		if (pos == -1)
		{
			char msg[] = "False";
			send(curClient, msg, strlen(msg), 0);
			return;
		}
		else
		{
			char msg[] = "True";
			send(curClient, msg, strlen(msg), 0);
			Sleep(500);
			stringstream online;
			online << "List of online account: " << endl;
			for (int i = 0; i < list.size(); i++)
			{
				if (list[i].isOnline() && list[i].username() != list[pos].username()) online << " - " << list[i].username() << endl;
			}
			send(curClient, online.str().c_str(), online.str().size(), 0);
			Sleep(500);
			memset(tempmsg, 0, 512);
			int iResult = recv(curClient, tempmsg, 512, 0);
			string invite = string(tempmsg);
			if (invite == "create_room")
			{
				memset(tempmsg, 0, 512);
				int iResult = recv(curClient, tempmsg, 512, 0);
				string roomid = string(tempmsg);
				memset(tempmsg, 0, 512);
				iResult = recv(curClient, tempmsg, 512, 0);
				string username = string(tempmsg);
				int k;
				if (Find(username, k))
				{
					string test = "True";
					send(list[k].socketofPlayer(), test.c_str(), strlen(test.c_str()), 0);
					Sleep(100);
					send(list[k].socketofPlayer(), list[pos].username().c_str(), strlen(list[pos].username().c_str()), 0);
					Sleep(100);
					send(list[k].socketofPlayer(), roomid.c_str(), strlen(roomid.c_str()), 0);
					memset(tempmsg, 0, 512);
					int iResult = recv(list[k].socketofPlayer(), tempmsg, 512, 0);
					if (string(tempmsg) == "Yes")
					{
						send(curClient, tempmsg, strlen(tempmsg), 0);
						playGame = true;
						Player* temp = &list[k];
						list[pos].setPartner(temp);
						UploadShips(pos, curClient);
						uploadShips = true;
					}
					else
					{
						send(curClient, tempmsg, strlen(tempmsg), 0);
					}
				}
			}
		}
	}

	else if (request == "close" || request == "end")
	{
		cout << "One computer disconnected." << endl;
		closesocket(curClient);
		if (pos != -1)
		{
			list[pos].setIsOnline(false);
			list[pos].setSocketClient(INVALID_SOCKET);
			pos = -1;
		}
		return;
	}
	else if (request == "login")
	{
		if (pos != -1)
		{
			char msg[] = "You have logined already.";
			send(curClient, msg, strlen(msg), 0);
			return;
		}
		else
		{
			char msg[] = "True";
			send(curClient, msg, strlen(msg), 0);
			Login(pos, curClient);
		}
	}
	else if (request == "register")
	{
		if (pos != -1)
		{
			char msg[] = "You have logined already.";
			send(curClient, msg, strlen(msg), 0);
			return;
		}
		else
		{
			char msg[] = "True";
			send(curClient, msg, strlen(msg), 0);
			if (Register(curClient))
			{
				Login(pos, curClient);
			}
		}
	}
	else if (request == "change_password")
	{
		if (pos == -1)
		{
			char msg[] = "You have to login to the game.";
			send(curClient, msg, strlen(msg), 0);
			return;
		}
		else
		{
			char msg[] = "True";
			send(curClient, msg, strlen(msg), 0);
			ChangePassword(pos, curClient);
		}
	}
	else if (request == "check_user")
	{
		if (pos == -1)
		{
			char msg[] = "You have to login to the game.";
			send(curClient, msg, strlen(msg), 0);
			return;
		}
		else
		{
			char msg[] = "True";
			send(curClient, msg, strlen(msg), 0);
			CheckUser(curClient);
		}
	}
	else if (request == "setup_info")
	{
		if (pos == -1)
		{
			char msg[] = "You have to login to the game.";
			send(curClient, msg, strlen(msg), 0);
			return;
		}
		else
		{
			char msg[] = "True";
			send(curClient, msg, strlen(msg), 0);
			SetupInfo(pos, curClient);
		}
	}
	else if (request == "logout")
	{
		if (pos == -1)
		{
			char msg[] = "You have to login to the game.";
			send(curClient, msg, strlen(msg), 0);
			return;
		}
		else
		{
			char msg[] = "True";
			send(curClient, msg, strlen(msg), 0);
			list[pos].setIsOnline(false);
			list[pos].setSocketClient(INVALID_SOCKET);
			pos = -1;
		}
	}
}

void Game(int pos, bool& uploadShips, string board[N + 1][N + 1])
{
jump:
	int x = 0, y = 0;
	string turn = "It's your turn";
	string start_game = "Game is starting now";
	string win_game = "You're the winner";
	string lose_game = "You're the loser";
	Sleep(1000);
	send(list[pos].socketofPlayer(), start_game.c_str(), start_game.size(), 0);
	Sleep(1000);
	if (check_turn % 2 == 0) send(list[pos].socketofPlayer(), turn.c_str(), turn.size(), 0);
	check_turn++;
	char position[100];
	while (1)
	{
		memset(position, 0, 100);
		int Result = recv(list[pos].socketofPlayer(), position, 100, 0);
		if (Result != SOCKET_ERROR)
		{
			if (isValidFormat(position))
			{
				SplitMess(position, x, y);
				if (x == 20 && y == 20)
				{
					break;
				}
				if (list[pos].partner()->board[x][y] == "S")
				{
					stringstream out;
					string tmp1 = "Attack successfully";
					string tmp2 = "You're being attacked";
					out << tmp1 << x << " " << y;
					tmp1 = out.str();
					list[pos].partner()->setcheckPoint(list[pos].partner()->checkPoint() - 1);
					send(list[pos].socketofPlayer(), tmp1.c_str(), tmp1.size(), 0);
					Sleep(1000);
					if (isValidFormat(position)) send(list[pos].partner()->socketofPlayer(), position, 100, 0);
					send(list[pos].partner()->socketofPlayer(), tmp2.c_str(), tmp2.size(), 0);
					if (list[pos].partner()->checkPoint() == 0)
					{
						Sleep(1000);
						string end = "20 20";
						send(list[pos].partner()->socketofPlayer(), lose_game.c_str(), lose_game.size(), 0);
						Sleep(1000);
						list[pos].updatePoint();
						send(list[pos].socketofPlayer(), win_game.c_str(), win_game.size(), 0);
						break;
					}
					send(list[pos].socketofPlayer(), turn.c_str(), turn.size(), 0);
				}
				if (list[pos].partner()->board[x][y] == "O")
				{
					string tmp1 = "Attack failingly";
					string tmp2 = "You're not being attacked";
					send(list[pos].socketofPlayer(), tmp1.c_str(), tmp1.size(), 0);
					Sleep(1000);
					send(list[pos].partner()->socketofPlayer(), tmp2.c_str(), tmp2.size(), 0);
					Sleep(1000);
					send(list[pos].partner()->socketofPlayer(), turn.c_str(), turn.size(), 0);
					continue;
				}
			}
		}
		else
		{
			string disconnected = "Please enter the position";
			send(list[pos].socketofPlayer(), disconnected.c_str(), disconnected.size(), 0);
		}
	}
	string again = "Do you want to play again ?(YES/NO)";
	uploadShips = false;
	Sleep(1000);
	send(list[pos].socketofPlayer(), again.c_str(), again.size(), 0);
	//send(list[pos].partner()->socketofPlayer(), again.c_str(), again.size(), 0);

	//Asking for playing again
	char ask_again[100];
	int count = 0;
	while (1)
	{
		memset(ask_again, 0, 100);
		int Result = recv(list[pos].socketofPlayer(), ask_again, 100, 0);
		string temp = ask_again;
		if (Result != SOCKET_ERROR)
		{
			if (temp == "YES")
			{
				Sleep(1000);
				send(list[pos].partner()->socketofPlayer(), temp.c_str(), temp.size(), 0);
				count++;
				if (count == 2)
				{
					count = 0;
					//gui tin nhan tam ra hieu 2 ben dong y
					string upload = "okupload";
					send(list[pos].socketofPlayer(), upload.c_str(), upload.size(), 0);
					Sleep(500);
					UploadShips(pos, list[pos].socketofPlayer());
					goto jump;
				}
			}
			else if (temp == "Again")
			{
				Sleep(1000);
				count++;
				if (count == 2)
				{
					count = 0;
					//gui tin nhan tam ra hieu 2 ben dong y
					string upload = "okupload";
					send(list[pos].socketofPlayer(), upload.c_str(), upload.size(), 0);
					Sleep(500);
					UploadShips(pos, list[pos].socketofPlayer());
					goto jump;
				}
			}
			else if (temp == "NO")
			{
				string end_game = "Game is ending now";
				send(list[pos].partner()->socketofPlayer(), temp.c_str(), temp.size(), 0);
				Sleep(500);
				send(list[pos].socketofPlayer(), end_game.c_str(), end_game.size(), 0);
				list[pos].setPartner(nullptr);
				cout << "Player " << list[pos].username() << " return." << endl;
				return;
			}
		}
	}
}

int gameplay(SOCKET curClient, thread& thread)
{
	SOCKET temp = curClient;
	while (true)
	{
		bool uploadShips = false;
		int pos = -1;
		bool playCheck = false;
		while (true)
		{
			if (!playCheck || !uploadShips)
			{
				GetRequest(pos, curClient, playCheck, uploadShips);
			}
			if (playCheck && uploadShips)
			{
				Game(pos, uploadShips, list[pos].board);
				uploadShips = false;
				playCheck = false;
			}
		}
	}
	cout << "Client: " << temp << " disconnected." << endl;
	return 0;
}

void SplitMess(string value, int& x, int& y)
{
	int pos = value.find_first_of(" ");

	string tmp_x = value.substr(0, pos);
	string tmp_y = value.substr(pos + 1, value.size() - pos - 1);

	x = stoi(tmp_x);
	y = stoi(tmp_y);
}

bool isValidFormat(string value)
{
	const regex DigitsPattern("\\b\\d+\\ \\d+\\b");

	bool result = regex_match(value, DigitsPattern);
	return result;
}

void LoadPlayer()
{
	ifstream read;
	read.open("Player.txt");
	while (!read.eof())
	{
		Player newplayer = Player();
		string buffer;
		getline(read, buffer);
		newplayer.setUsername(buffer);
		getline(read, buffer);
		newplayer.setPassword(buffer);
		getline(read, buffer);
		newplayer.setDOB(buffer);
		getline(read, buffer);
		newplayer.setFullname(buffer);
		getline(read, buffer);
		newplayer.setNote(buffer);
		newplayer.setIsOnline(false);
		newplayer.setcheckPoint(0);
		newplayer.setPartner(nullptr);
		newplayer.setSocketClient(INVALID_SOCKET);
		list.push_back(newplayer);
	}
}

