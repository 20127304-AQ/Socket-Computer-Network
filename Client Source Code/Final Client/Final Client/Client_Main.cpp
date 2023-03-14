#include "Header.h"

#define DEFAULT_BUFLEN 512

int main()
{
	WSAData wsa_data;
	struct addrinfo* result = NULL, * ptr = NULL, hints;
	string sent_message = "";
	SOCKET client;
	int iResult = 0;
	string message;
	string IP_ADDRESS;
	string port;
	Logo();
	cout << "Connect [ip_address] [port]:";
	getline(cin, IP_ADDRESS, ' ');
	getline(cin, port);

	cout << "Starting Client...\n";

	// Initialize Winsock
	iResult = WSAStartup(MAKEWORD(2, 2), &wsa_data);
	if (iResult != 0) {
		cout << "WSAStartup() failed with error: " << iResult << endl;
		return 1;
	}

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	cout << "Connecting...\n";

	// Resolve the server address and port
	iResult = getaddrinfo(IP_ADDRESS.c_str(), port.c_str(), &hints, &result);
	if (iResult != 0) {
		cout << "getaddrinfo() failed with error: " << iResult << endl;
		WSACleanup();
		system("pause");
		return 1;
	}

	// Attempt to connect to an address until one succeeds
	for (ptr = result; ptr != NULL; ptr = ptr->ai_next) {

		// Create a SOCKET for connecting to server
		client = socket(ptr->ai_family, ptr->ai_socktype,
			ptr->ai_protocol);
		if (client == INVALID_SOCKET) {
			cout << "socket() failed with error: " << WSAGetLastError() << endl;
			WSACleanup();
			system("pause");
			return 1;
		}

		// Connect to server.
		iResult = connect(client, ptr->ai_addr, (int)ptr->ai_addrlen);
		if (iResult == SOCKET_ERROR) {
			closesocket(client);
			client = INVALID_SOCKET;
			continue;
		}
		break;
	}

	freeaddrinfo(result);

	if (client == INVALID_SOCKET) {
		cout << "Unable to connect to server!" << endl;
		WSACleanup();
		system("pause");
		return 1;
	}

	cout << "Successfully Connected" << endl;
	char s[512];
	memset(s, 0, 512);
	//Obtain id from server for this client;
	recv(client, s, DEFAULT_BUFLEN, 0);
	message = string(s);
	Sleep(2000);
	if (message != "Server is full")
	{
		bool isClose = true;
		while (isClose)
		{
			bool isInvited = false;
			string opponent;
			string roomID;
			string board[N + 1][N + 1];
			CreateWhiteBoard(board);
			system("cls");
			Logo();
			thread my_thread(GetInvite, ref(client), ref(isInvited), ref(opponent), ref(roomID));
			string buffer;
			getline(cin, buffer);
			int firstIndex = buffer.find_first_of(" ");
			if (firstIndex == -1)
			{
				if (buffer == "start_game")
				{
					send(client, buffer.c_str(), strlen(buffer.c_str()), 0);
					char tempmsg[512];
					memset(tempmsg, 0, 512);
					int iResult = recv(client, tempmsg, 512, 0);
					if (iResult == SOCKET_ERROR)
					{
						char msg[] = "Can't recieve message.";
						send(client, msg, strlen(msg), 0);
					}
					string flag = string(tempmsg);
					if (flag == "False")
						cout << "You have to login." << endl;
					else
					{
						recv(client, tempmsg, 512, 0);
						cout << tempmsg;
						string request;
						getline(cin, request, ' ');
						send(client, request.c_str(), strlen(request.c_str()), 0);

						getline(cin, roomID, ' ');
						send(client, roomID.c_str(), strlen(roomID.c_str()), 0);

						string temp;
						getline(cin, temp, ' ');

						string username;
						getline(cin, username);
						opponent = username;
						send(client, username.c_str(), strlen(username.c_str()), 0);
						char tempmsg[512];
						memset(tempmsg, 0, 512);
						int iResult = recv(client, tempmsg, 512, 0);
						if (iResult == SOCKET_ERROR)
						{
							char msg[] = "Can't recieve message.";
							send(client, msg, strlen(msg), 0);
						}
						string flag = string(tempmsg);
						if (flag == "Yes")
						{
							system("cls");
							Logo();
							cout << username << " accept your invitation." << endl << "Please ... upload your ships" << endl;
							while (true)
							{
								string upload;
								getline(cin, upload, ' ');
								if (upload == "upload_ships")
								{
									string filename;
									getline(cin, filename);
									cout << "Loading ships....." << endl;
									UploadShips(client, filename, board);
									break;
								}
							}
							Game(client, board, opponent, roomID);
						}
						else cout << username << " reject your invitation." << endl;
					}
				}
				else if (buffer == "change_password")
				{
					send(client, buffer.c_str(), strlen(buffer.c_str()), 0);
					char tempmsg[512];
					memset(tempmsg, 0, 512);
					int iResult = recv(client, tempmsg, 512, 0);
					if (iResult == SOCKET_ERROR)
					{
						char msg[] = "Can't recieve message.";
						send(client, msg, strlen(msg), 0);
					}
					string flag = string(tempmsg);
					if (flag == "True")
						ChangePassword(client);
					else cout << "You have to login." << endl;
				}
				else if (buffer == "logout")
				{
					send(client, buffer.c_str(), strlen(buffer.c_str()), 0);
					char tempmsg[512];
					memset(tempmsg, 0, 512);
					int iResult = recv(client, tempmsg, 512, 0);
					if (iResult == SOCKET_ERROR)
					{
						char msg[] = "Can't recieve message.";
						send(client, msg, strlen(msg), 0);
					}
					string flag = string(tempmsg);
					if (flag == "True")
					{
						cout << "Logout successfully." << endl;
					}
					else cout << "You haven't login yet." << endl;
				}
				else if (buffer == "Yes")
				{
					send(client, buffer.c_str(), strlen(buffer.c_str()), 0);
					Sleep(100);
					send(client, buffer.c_str(), strlen(buffer.c_str()), 0);
					Sleep(100);
					send(client, opponent.c_str(), strlen(opponent.c_str()), 0);
					while (true)
					{
						system("cls");
						Logo();
						cout << "Please ... upload your ships" << endl;
						string upload;
						getline(cin, upload, ' ');
						if (upload == "upload_ships")
						{
							string filename;
							getline(cin, filename);
							cout << "Loading ships....." << endl;
							UploadShips(client, filename, board);
							break;
						}
					}
					Game(client, board, opponent, roomID);
				}
				else if (buffer == "No")
				{
					send(client, buffer.c_str(), strlen(buffer.c_str()), 0);
					Sleep(100);
					send(client, buffer.c_str(), strlen(buffer.c_str()), 0);
					isInvited = false;
					opponent = "";
				}
				else if (buffer == "close" || buffer == "end")
				{
					cout << "End successfully." << endl;
					cout << "Thanks for using our program" << endl;
					isClose = false;
				}
			}
			else
			{
				string request = buffer.substr(0, firstIndex);
				send(client, request.c_str(), strlen(request.c_str()), 0);
				char tempmsg[512];
				memset(tempmsg, 0, 512);
				int iResult = recv(client, tempmsg, 512, 0);
				if (iResult == SOCKET_ERROR)
				{
					char msg[] = "Can't recieve message.";
					send(client, msg, strlen(msg), 0);
				}
				string flag = string(tempmsg);
				if (flag == "True")
				{
					if (request == "login")
					{
						string id = buffer.substr(firstIndex + 1, buffer.length() - 1);
						Login(client, id);
					}
					else if (request == "register")
					{
						string id = buffer.substr(firstIndex + 1, buffer.length() - 1);
						Register(client, id);
					}
					else if (request == "check_user")
					{
						int secondIndex = buffer.find_first_of(" ", firstIndex + 1);
						request = buffer.substr(firstIndex + 1, secondIndex - 1 - firstIndex - 1 + 1);
						string id = buffer.substr(secondIndex + 1, buffer.length() - 1);
						CheckUser(request, id, client);
					}
					else if (request == "setup_info")
					{
						int secondIndex = buffer.find_first_of(" ", firstIndex + 1);
						request = buffer.substr(firstIndex + 1, secondIndex - 1 - firstIndex - 1 + 1);
						string s = buffer.substr(secondIndex + 1, buffer.length() - 1);
						SetupInfo(request, s, client);
					}
				}
			}
			my_thread.detach();
			Sleep(2000);
		}
	}
end:
	cout << "Shutting down socket..." << endl;
	iResult = shutdown(client, SD_SEND);
	if (iResult == SOCKET_ERROR) {
		cout << "shutdown() failed with error: " << WSAGetLastError() << endl;
		closesocket(client);
		WSACleanup();
		system("pause");
		return 1;
	}

	closesocket(client);
	WSACleanup();
	system("pause");
	return 0;
}