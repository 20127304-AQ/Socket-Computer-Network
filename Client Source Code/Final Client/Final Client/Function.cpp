#include "Header.h"

void gotoxy(int x, int y)
{
	static HANDLE h = NULL;
	if (!h)
		h = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD c = { x, y };
	SetConsoleCursorPosition(h, c);
}

void SET_COLOR(int color)
{
	WORD wColor;


	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if (GetConsoleScreenBufferInfo(hStdOut, &csbi))
	{
		wColor = (csbi.wAttributes & 0xF0) + (color & 0x0F);
		SetConsoleTextAttribute(hStdOut, wColor);
	}
}

void Logo()
{
	SET_COLOR(4);
	int i = 0;
	int j = 20;
	//chu B
	gotoxy(j, i++);
	cout << char(220) << char(220) << char(220) << endl;
	gotoxy(j, i++);
	cout << char(219) << "  " << char(219) << endl;
	gotoxy(j, i++);
	cout << char(219) << char(223) << char(223) << char(220) << endl;
	gotoxy(j, i++);
	cout << char(219) << char(220) << char(220) << char(223) << endl;
	//chu A
	i = 0;
	j += 5;
	gotoxy(j, i++);
	cout << " " << char(220) << char(220) << char(220) << endl;
	gotoxy(j, i++);
	cout << char(219) << "   " << char(219) << endl;
	gotoxy(j, i++);
	cout << char(219) << char(220) << char(220) << char(220) << char(219) << endl;
	gotoxy(j, i++);
	cout << char(219) << "   " << char(219) << endl;
	//chu T
	i = 0;
	j += 6;
	gotoxy(j, i++);
	cout << char(220) << char(220) << char(220) << char(220) << char(220) << endl;
	gotoxy(j, i++);
	cout << "  " << char(219) << endl;
	gotoxy(j, i++);
	cout << "  " << char(219) << endl;
	gotoxy(j, i++);
	cout << "  " << char(219);
	//chu T
	i = 0;
	j += 6;
	gotoxy(j, i++);
	cout << char(220) << char(220) << char(220) << char(220) << char(220) << endl;
	gotoxy(j, i++);
	cout << "  " << char(219) << endl;
	gotoxy(j, i++);
	cout << "  " << char(219) << endl;
	gotoxy(j, i++);
	cout << "  " << char(219);
	//chu L
	i = 0;
	j += 6;
	gotoxy(j, i++);
	cout << char(220) << endl;
	gotoxy(j, i++);
	cout << char(219) << endl;
	gotoxy(j, i++);
	cout << char(219) << endl;
	gotoxy(j, i++);
	cout << char(219) << char(220) << char(220) << char(220) << endl;
	//chu E
	i = 0;
	j += 5;
	gotoxy(j, i++);
	cout << char(220) << char(220) << char(220) << char(220) << endl;
	gotoxy(j, i++);
	cout << char(219) << endl;
	gotoxy(j, i++);
	cout << char(219) << char(223) << char(223) << char(223) << endl;
	gotoxy(j, i++);
	cout << char(219) << char(220) << char(220) << char(220) << endl;
	//chu S
	i = 0;
	j += 10;
	gotoxy(j, i++);
	cout << " " << char(220) << char(220) << char(220) << endl;
	gotoxy(j, i++);
	cout << char(219) << endl;
	gotoxy(j, i++);
	cout << " " << char(223) << char(223) << char(220) << endl;
	gotoxy(j, i++);
	cout << char(220) << char(220) << char(220) << char(223) << endl;
	//chu R
	i = 0;
	j += 5;
	gotoxy(j, i++);
	cout << char(220) << "  " << char(220) << endl;
	gotoxy(j, i++);
	cout << char(219) << "  " << char(219) << endl;
	gotoxy(j, i++);
	cout << char(219) << char(223) << char(223) << char(219) << endl;
	gotoxy(j, i++);
	cout << char(219) << "  " << char(219) << endl;
	//chu I
	i = 0;
	j += 5;
	gotoxy(j, i++);
	cout << char(220) << char(220) << char(220) << char(220) << char(220) << endl;
	gotoxy(j, i++);
	cout << "  " << char(219) << endl;
	gotoxy(j, i++);
	cout << "  " << char(219) << endl;
	gotoxy(j, i++);
	cout << char(220) << char(220) << char(219) << char(220) << char(220) << endl;
	//chu P
	i = 0;
	j += 6;
	gotoxy(j, i++);
	cout << char(220) << char(220) << char(220) << char(220) << endl;
	gotoxy(j, i++);
	cout << char(219) << "  " << char(219) << endl;
	gotoxy(j, i++);
	cout << char(219) << char(223) << char(223) << char(223) << endl;
	gotoxy(j, i++);
	cout << char(219) << endl;
	gotoxy(0, 7);
	SET_COLOR(7);
}


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

void Login(SOCKET client, string id)
{

	string pw;
	cout << "Password: ";
	FillPassword(pw, 1, 11);
	cout << endl;
	cout << "Do you want to encrypt message before sending?" << endl << "(Y/N): ";
	string temp;
	getline(cin, temp);
	if (temp == "Y")
	{
		id = string_to_hex(id);
		pw = string_to_hex(pw);
	}
	send(client, temp.c_str(), strlen(temp.c_str()), 0);
	Sleep(500);
	send(client, id.c_str(), strlen(id.c_str()), 0);
	Sleep(500);
	send(client, pw.c_str(), strlen(pw.c_str()), 0);
	string result;
	char tempmsg[512];
	memset(tempmsg, 0, 512);
	int iResult = recv(client, tempmsg, 512, 0);
	if (iResult == SOCKET_ERROR)
	{
		char msg[] = "Can't recieve message.";
		send(client, msg, strlen(msg), 0);
		return;
	}
	result = string(tempmsg);
	cout << result << endl;
}

void Register(SOCKET client, string id)
{
	string pw;
	cout << "Password: ";
	FillPassword(pw, 1, 11);
	cout << endl;
	cout << "Do you want to encrypt message before sending?" << endl << "(Y/N): ";
	string temp;
	getline(cin, temp);
	if (temp == "Y")
	{
		id = string_to_hex(id);
		pw = string_to_hex(pw);
	}
	send(client, temp.c_str(), strlen(temp.c_str()), 0);
	Sleep(500);
	send(client, id.c_str(), strlen(id.c_str()), 0);
	Sleep(500);
	send(client, pw.c_str(), strlen(pw.c_str()), 0);
	string result;
	char tempmsg[512];
	memset(tempmsg, 0, 512);
	int iResult = recv(client, tempmsg, 512, 0);
	if (iResult == SOCKET_ERROR)
	{
		char msg[] = "Can't recieve message.";
		send(client, msg, strlen(msg), 0);
		return;
	}
	result = string(tempmsg);
	cout << result << endl;
	Sleep(1000);
	system("cls");
	Logo();
	if (result == "Register successfully.")
	{
		string id;
		cout << "Username: ";
		getline(cin, id);
		Login(client, id);
	}
}

void ChangePassword(SOCKET client)
{
	string cpw;
	cout << "Current Password: ";
	FillPassword(cpw, 1, 19);
	cout << endl;
	string temp;
	cout << "Do you want to encrypt message before sending?" << endl << "(Y/N): ";
	getline(cin, temp);
	if (temp == "Y")
	{
		cpw = string_to_hex(cpw);
	}
	send(client, temp.c_str(), strlen(temp.c_str()), 0);
	Sleep(500);
	send(client, cpw.c_str(), strlen(cpw.c_str()), 0);
	string result;
	char tempmsg[512];
	memset(tempmsg, 0, 512);
	int iResult = recv(client, tempmsg, 512, 0);
	if (iResult == SOCKET_ERROR)
	{
		char msg[] = "Can't recieve message.";
		send(client, msg, strlen(msg), 0);
		return;
	}
	result = string(tempmsg);
	if (result == "true")
	{
		string npw;
		cout << "New Password: ";
		FillPassword(npw, 4, 15);
		cout << endl;
		if (temp == "Y")
		{
			npw = string_to_hex(npw);
		}
		send(client, npw.c_str(), strlen(npw.c_str()), 0);
		cout << "Your password has been changed." << endl;
	}
	else
	{
		cout << result << endl;
	}

}

void CheckUser(string request, string id, SOCKET client)
{
	send(client, request.c_str(), strlen(request.c_str()), 0);
	Sleep(100);
	send(client, id.c_str(), strlen(id.c_str()), 0);
	int times = 1;
	if (request == "show_all") times = 5;
	for (int i = 0; i < times; i++)
	{
		string result;
		char tempmsg[512];
		memset(tempmsg, 0, 512);
		int iResult = recv(client, tempmsg, 512, 0);
		if (iResult == SOCKET_ERROR)
		{
			char msg[] = "Can't recieve message.";
			send(client, msg, strlen(msg), 0);
			return;
		}
		result = string(tempmsg);
		cout << result << endl;
	}
	Sleep(2000);
}

void SetupInfo(string request, string s, SOCKET client)
{
	send(client, request.c_str(), strlen(request.c_str()), 0);
	Sleep(100);
	send(client, s.c_str(), strlen(s.c_str()), 0);
	string result;
	char tempmsg[512];
	memset(tempmsg, 0, 512);
	int iResult = recv(client, tempmsg, 512, 0);
	if (iResult == SOCKET_ERROR)
	{
		char msg[] = "Can't recieve message.";
		send(client, msg, strlen(msg), 0);
		return;
	}
	result = string(tempmsg);
	if (result == "True")
	{
		cout << "Change " << request << " successfully." << endl;
	}
	else
	{
		cout << "This option is not available." << endl;
	}
}

void PrintBoard(string Mine[N + 1][N + 1], string Attacking[N + 1][N + 1], string opponent, string roomID)
{
	int offset = 0;
	int x = 52 + offset;  // change size of input
	int y = 17;
	for (int i = 0 + offset; i < x; i++) // tao dong ngang
	{
		gotoxy(i, 7); printf("%c", 205); // dong ngang tren
		gotoxy(i, y+7); printf("%c", 205);  // dong ngang duoi
	}
	for (int i = 1; i < y; i++)  // dong ke thang dung
	{
		gotoxy(0 + offset, i+7); printf("%c", 186); // dong thang ben trai
		gotoxy(x, i+7); printf("%c", 186); // dong thang ben phai
	}
	gotoxy(x, 0 + 7); printf("%c", 187); // cai moc cau ben phai ben tre^n
	gotoxy(x, y + 7); printf("%c", 188); // cai moc cau ben phai ben duoi
	gotoxy(0 + offset, 0 + 7); printf("%c", 201); // cai moc cau ben trai tren
	gotoxy(0 + offset, y + 7); printf("%c", 200); // moc cau ben trai duoi
	gotoxy(20 + offset, 0 + 7); cout << "  MY BOARD  ";



	offset = 53;
	x = 51 + offset;
	for (int i = 0 + offset; i < x; i++) // tao dong ngang
	{
		gotoxy(i, 0 + 7); printf("%c", 205); // dong ngang tren
		gotoxy(i, y + 7); printf("%c", 205);  // dong ngang duoi
	}
	for (int i = 1; i < y; i++)  // dong ke thang dung
	{
		gotoxy(0 + offset, i + 7); printf("%c", 186); // dong thang ben trai
		gotoxy(x, i + 7); printf("%c", 186); // dong thang ben phai
	}
	gotoxy(x, 0 + 7); printf("%c", 187); // cai moc cau ben phai ben tre^n
	gotoxy(x, y + 7); printf("%c", 188); // cai moc cau ben phai ben duoi
	gotoxy(0 + offset, 0 + 7); printf("%c", 201); // cai moc cau ben trai tren
	gotoxy(0 + offset, y + 7); printf("%c", 200); // moc cau ben trai duoi
	gotoxy(17 + offset, 0 + 7); cout << "  ATTACKING BOARD  ";


	for (int i = 0; i <= N; i++)
	{
		gotoxy(0 + 2, i + 1 + 7);
		for (int j = 0; j <= N; j++)
		{

			if (i == 0 && j == 0)
			{
				cout << setw(3) << " ";
				continue;
			}
			cout << setw(3) << Mine[i][j];

		}
		gotoxy(52 + 2, i + 1 + 7);
		for (int k = 0; k <= N; k++)
		{
			if (i == 0 && k == 0)
			{
				cout << setw(3) << " ";
				continue;
			}
			cout << setw(3) << Attacking[i][k];

		}
		cout << endl;
	}
	gotoxy(0, 18 + 7);
	cout << "Room ID: " << roomID << " - My opponent: " << opponent << endl;
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

void CreateWhiteBoard(string WB[N + 1][N + 1])
{
	stringstream out;
	WB[0][0] = "";
	int number1 = 1;
	int number2 = 1;
	for (int i = 0; i <= N; i++)
	{
		for (int j = 0; j <= N; j++)
		{
			out.str("");
			if (j == 0 && i != 0)
			{
				out << number1;
				WB[i][j] = out.str();
				number1++;
			}
			else if (i != 0 && j != 0)
			{
				WB[i][j] = "O";
			}
			else if (i == 0 && j != 0)
			{
				out << number2;
				WB[i][j] = out.str();
				number2++;
			}
		}
	}
}

int GetInvite(SOCKET client, bool& isInvited, string& opponent, string& roomID)
{
	char tempmsg[512];
	memset(tempmsg, 0, 512);
	recv(client, tempmsg, 512, 0);
	if (string(tempmsg) == "True")
	{
		memset(tempmsg, 0, 512);
		recv(client, tempmsg, 512, 0);
		opponent = string(tempmsg);
		memset(tempmsg, 0, 512);
		recv(client, tempmsg, 512, 0);
		roomID = string(tempmsg);
		isInvited = true;
		cout << "Do you want to play with " << opponent << " ?(Yes/No)" << endl;
	}
	return 0;
}

void Game(SOCKET client, string board[N + 1][N + 1], string opponent, string roomID)
{
	string attacking_board[N + 1][N + 1];
	while (true)
	{
		char tempmsg[512];
		memset(tempmsg, 0, 512);
		recv(client, tempmsg, 512, 0);
		string message = string(tempmsg);
		Sleep(500);
		if (message == "Game is starting now")
		{
			system("cls");
			Logo();
			cout << message << endl;
			CreateWhiteBoard(attacking_board);
			PrintBoard(board, attacking_board, opponent, roomID);
			cout << endl;
			continue;
		}
		//Notice for partner to break out of the game
		if (message == "You're the loser")
		{
			string check_lose = "20 20";
			cout << message << endl;
			send(client, check_lose.c_str(), check_lose.size(), 0);
			Sleep(2000);
			continue;
		}
		if (message =="You're the winner")
		{
			cout << message << endl;
			Sleep(2000);
			continue;
		}
		if (message == "YES")
		{
			string y = "Again";
			send(client, y.c_str(), y.size(), 0);
			continue;
		}
		if (message == "NO")
		{
			system("cls");
			Logo();
			send(client, message.c_str(), message.size(), 0);
			cout << "Game is ending now...";
			Sleep(3000);
			system("cls");
			Logo();
			return;
		}
		if (message == "Game is ending now ...")
		{
			cout << message << endl;
			Sleep(3000);
			system("cls");
			Logo();
			return;
		}
		if (message.size() >= 19)
		{
			if (message.substr(0, 19) == "Attack successfully")
			{
				system("cls");
				Logo();
				int tmp_x = 0, tmp_y = 0;
				SplitMess(message.substr(19, message.size() - 18), tmp_x, tmp_y);
				attacking_board[tmp_x][tmp_y] = "X";
				PrintBoard(board, attacking_board, opponent, roomID);
				string result = message.substr(0, 19);
				cout << result << endl;
				continue;
			}
		}
		if (message == "Attack failingly")
		{
			system("cls");
			Logo();
			PrintBoard(board, attacking_board, opponent, roomID);
			cout << message << endl;
			continue;
		}
		if (isValidFormat(message))
		{
			system("cls");
			Logo();
			int x = 0, y = 0;
			SplitMess(message, x, y);
			board[x][y] = "O";
			PrintBoard(board, attacking_board, opponent, roomID);
			continue;
		}
		if (message == "It's your turn")
		{
			system("cls");
			Logo();
			PrintBoard(board, attacking_board, opponent, roomID);
			cout << message << endl;
			string buffer;
			getline(cin, buffer);
			int x = 0, y = 0;
			SplitMess(buffer, x, y);
			attacking_board[x][y] = "M";
			send(client, buffer.c_str(), buffer.size(), 0);
			continue;
		}
		if (message == "Do you want to play again ?(YES/NO)")
		{
			system("cls");
			Logo();
			cout << message << endl;
			string buffer;
			getline(cin, buffer);
			send(client, buffer.c_str(), buffer.size(), 0);
			if (buffer == "NO")
			{
				system("CLS");
				Logo();
				cout << "Game is ending now ...";
				Sleep(3000);
				system("cls");
				Logo();
				return;
			}
			continue;
		}
		if (message == "okupload")
		{
			cout << "Please ... upload your ships" << endl;
			Sleep(1000);
			while (true)
			{
				string upload;
				getline(cin, upload, ' ');
				if (upload == "upload_ships")
				{
					string filename;
					getline(cin, filename);
					UploadShips(client, filename, board);
					break;
				}
			}
			continue;
		}
		cout << message << endl;
	}
}

void UploadShips(SOCKET client, string filename, string board[N + 1][N + 1])
{
	SET_COLOR(2);
	int a = 1;
	int b = 5;
	ifstream read;
	read.open(filename);
	for (int i = 1; i < N + 1; i++)
	{
		gotoxy(a, b + 7);
		cout << char(219);
		gotoxy(25, b + 7);
		cout << a * 5 << "%";
		gotoxy(0, 0);
		a++;
		for (int j = 1; j < N; j++)
		{
			getline(read, board[i][j], ' ');
			send(client, board[i][j].c_str(), strlen(board[i][j].c_str()), 0);
			Sleep(100);
		}
		getline(read, board[i][N]);
		send(client, board[i][N].c_str(), strlen(board[i][N].c_str()), 0);
		Sleep(100);
	}
	for (; a < 21; a++)
	{
		gotoxy(a, b + 7);
		cout << char(219);
		gotoxy(25, b + 7);
		cout << a * 5 << "%";
		Sleep(200);
		gotoxy(0, 0);
	}
	SET_COLOR(7);
}

void FillPassword(string& password, int k, int m)
{
	char keycap;
	int i = m;
	while (true)
	{
		gotoxy(m, k + 7);
		for (int i = 0; i < password.length(); i++) cout << "*";
		gotoxy(i, k + 7);
		keycap = getch();
		if (keycap == 13) break;
		if (keycap == -32)
		{
			keycap = getch();
			if (keycap == 75 && i > m) i--;
			else if (keycap == 77 && i - m < password.length()) i++;
		}
		else if (keycap == 8)
		{
			if (i == m) continue;
			gotoxy(m + password.length() - 1, k + 7);
			cout << " ";
			password.erase(i - m - 1, 1);
			i--;
		}
		else
		{
			cout << keycap;
			Sleep(300);
			password += keycap;
			int k = i - m;
			while (k != password.length())
			{
				swap(password[k], password[password.length() - 1]);
				k++;
			}
			i++;
		}
	}
}