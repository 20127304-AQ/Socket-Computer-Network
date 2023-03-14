#include "Header.h"

int main()
{
    WSADATA wsaData;
    struct addrinfo hints;
    struct addrinfo* server = NULL;
    SOCKET server_socket = INVALID_SOCKET;
    SOCKET player_socket = INVALID_SOCKET;
    string msg = "";
    SOCKET connected[MAX_CONNECTED];
    int num_connected = 0;
    int temp_id = -1;
    int iResult = 0;
    thread my_thread[MAX_CONNECTED];

    //Initialize Winsock
    cout << "Intializing Winsock..." << endl;
    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);

    //Setup hints
    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;

    //Setup Server
    cout << "Setting up server..." << endl;
    getaddrinfo(IP_ADDRESS, DEFAULT_PORT, &hints, &server);

    //Create a listening socket for connecting to server
    cout << "Creating server socket..." << endl;
    server_socket = socket(server->ai_family, server->ai_socktype, server->ai_protocol);

    //Setup socket options
    setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &OPTION_VALUE, sizeof(int)); //Make it possible to re-bind to a port that was used within the last 2 minutes
    setsockopt(server_socket, IPPROTO_TCP, TCP_NODELAY, &OPTION_VALUE, sizeof(int)); //Used for interactive programs

    //Assign an address to the server socket.
    cout << "Binding socket..." << endl;
    bind(server_socket, server->ai_addr, (int)server->ai_addrlen);
    //Listen for incoming connections.
    cout << "Listening..." << endl;
    listen(server_socket, SOMAXCONN);

    //Initialize the client list
    for (int i = 0; i < MAX_CONNECTED; i++)
    {
        connected[i] = INVALID_SOCKET;
    }
    LoadPlayer();
    while (1)
    {
        player_socket = INVALID_SOCKET;
        player_socket = accept(server_socket, NULL, NULL);

        if (player_socket == INVALID_SOCKET) continue;

        //Reset the number of clients
        num_connected = -1;

        //Create a temporary username for the next client
        temp_id = -1;
        for (int i = 0; i < MAX_CONNECTED; i++)
        {
            if (connected[i] == INVALID_SOCKET && temp_id == -1)
            {
                connected[i] = player_socket;
                temp_id = i;
            }
            if (connected[i] != INVALID_SOCKET)
                num_connected++;
        }

        if (temp_id != -1)
        {
            msg = "True";
            send(player_socket, msg.c_str(), strlen(msg.c_str()), 0);
            //Create a thread process for that client
            my_thread[temp_id] = thread(gameplay, ref(connected[temp_id]), ref(my_thread[temp_id]));
        }
        else
        {
            msg = "Server is full";
            send(player_socket, msg.c_str(), strlen(msg.c_str()), 0);
            cout << msg << endl;
        }
    } //end while


    //Close listening socket
    closesocket(server_socket);

    //Close client socket
    for (int i = 0; i < MAX_CONNECTED; i++)
    {
        my_thread[i].detach();
        closesocket(connected[i]);
    }

    //Clean up Winsock
    WSACleanup();
    cout << "Program has ended successfully" << endl;

    system("pause");
    return 0;
}