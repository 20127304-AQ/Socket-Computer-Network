#include "Player.h"

Player::Player()
{

}

void Player::setUsername(string username)
{
    _username = username;
}

void Player::setPassword(string password)
{
    _password = password;
}

void Player::setDOB(string dob)
{
    _dob = dob;
}

void Player::setFullname(string fullname)
{
    _fullname = fullname;
}

void Player::setNote(string note)
{
    _note = note;
}

void Player::setIsOnline(bool isonline)
{
    _isonline = isonline;
}

void Player::setSocketClient(SOCKET player)
{
    _player = player;
}

void Player::updatePoint()
{
    _point++;
}

void Player::setcheckPoint(int value)
{
    _checkpoint = value;
}

int Player::checkPoint()
{
    return _checkpoint;
}

bool Player::isOnline()
{
    return _isonline;
}

int Player::point()
{
    return _point;
}

string Player::username()
{
    return _username;
}

string Player::password()
{
    return _password;
}

string Player::dob()
{
    return _dob;
}

string Player::fullname()
{
    return _fullname;
}

string Player::note()
{
    return _note;
}

SOCKET Player::socketofPlayer()
{
    return _player;
}

Player* Player::partner()
{
    return _partner;
}

void Player::setPartner(Player* partner)
{
    _partner = partner;
}

void Player::CreateWhiteBoard(string WB[N + 1][N + 1])
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