#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;

string num_bin[8];   // 001
string Qn_map[3][2]; // 1x101x
string Qn_JK[3][2];
vector<int> num_x;
int num_q[3][2][6] =
    {
        {{2, 0, 1, 3, 2, 0}, {6, 4, 5, 7, 6, 4}},
        {{4, 0, 1, 5, 4, 0}, {6, 2, 3, 7, 6, 2}},
        {{4, 0, 2, 6, 4, 0}, {5, 1, 3, 7, 5, 1}}};
/*
Qn_map
Q2:
[0]Q2' num_bin[201320][0] QxQy' Qx'Qy' Qx'Qy QxQy QxQy' Qx'Qy' x=1 y=0
[1]Q2  num_bin[201320][0] QxQy' Qx'Qy' Qx'Qy QxQy QxQy' Qx'Qy' x=1 y=0
Q1:
[0]Q1' num_bin[401540][1] QxQy' Qx'Qy' Qx'Qy QxQy QxQy' Qx'Qy' x=2 y=0
[1]Q1  num_bin[623762][1] QxQy' Qx'Qy' Qx'Qy QxQy QxQy' Qx'Qy' x=2 y=0
Q0:
[0]Q1' num_bin[402640][2] QxQy' Qx'Qy' Qx'Qy QxQy QxQy' Qx'Qy' x=2 y=1
[1]Q0  num_bin[513751][2] QxQy' Qx'Qy' Qx'Qy QxQy QxQy' Qx'Qy' x=2 y=1
*/
char char_Qn[3][2] = {{'A', 'a'}, {'B', 'b'}, {'C', 'c'}};
/*
Q2  A
Q2' a
Q1  B
Q1' b
Q0  C
Q0' c
*/
map<char, string> JK_char = {make_pair('A', "Q2"),
                             make_pair('a', "Q2'"),
                             make_pair('B', "Q1"),
                             make_pair('b', "Q1'"),
                             make_pair('C', "Q0"),
                             make_pair('c', "Q0'"),
                             make_pair('1', "1"),
                             make_pair('0', "0"),
                             make_pair('+', "+")};

void GetInput();
void GetQnMap();
void GetJK();
string GetString(int x, int y, int k); // to ABC
char GetString(int x, int y, int m, int n);
bool AllOne(string s);
bool AllZero(string s);
void PrintFirst();
void PrintSecond();
void PrintQn(int n);
void PrintJK();
bool TestSelfSetup();
string ToBinary(int n);

int main()
{
    GetInput();
    while (true)
    {
        PrintFirst();
        PrintQn(2);
        PrintQn(1);
        PrintQn(0);
        GetQnMap();
        GetJK();
        PrintJK();
        PrintSecond();
        if (TestSelfSetup())
        {
            cout << "Self-Setup" << endl;
            break;
        }
        cout << "Un-Self-Setup" << endl; // 3 2 5 1 6 4
        cout << "Please put in 2 number for next state of the xxx:" << endl
             << "$ ";
        int n, m;
        cin >> n >> m; // 7 6
        num_bin[num_x[0]] = ToBinary(n);
        num_bin[num_x[1]] = ToBinary(m);
    }
    int c;
    while (cin >> c)
        ;
    return 0;
}

void GetInput()
{
    cout << "Please enter six numbers:" << endl
         << "$ ";
    for (int i = 0; i < 8; ++i)
    {
        num_bin[i] = "xxx";
    }
    int prev, next, first;
    cin >> prev;
    first = prev;
    for (int i = 0; i < 5; ++i)
    {
        cin >> next;
        num_bin[prev] = ToBinary(next);
        prev = next;
    }
    num_bin[prev] = ToBinary(first);
    for (int i = 0; i < 8; ++i)
    {
        if (num_bin[i][0] == 'x')
        {
            num_x.push_back(i);
        }
    }
}

void GetQnMap()
{
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 2; ++j)
        {
            Qn_map[i][j].clear();
            for (int k = 0; k < 6; ++k)
            {
                Qn_map[i][j] += num_bin[num_q[i][j][k]][i];
            }
        }
    }
}

void GetJK()
{
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 2; ++j)
        {
            string tmp = Qn_map[i][j];
            if (AllZero(tmp))
            {
                Qn_JK[i][j] = "0";
                continue;
            }
            if (AllOne(tmp))
            {
                Qn_JK[i][j] = "1";
                for (int k = 1; k < 5; ++k)
                {
                    if (tmp[k] == 'x')
                    {
                        num_bin[num_q[i][j][k]][i] = '1';
                    }
                }
                continue;
            }
            int x = i == 0 ? 1 : 0;
            int y = i == 2 ? 1 : 2;
            string s;
            bool used[6] = {false};
            for (int k = 1; k < 5; ++k)
            {
                if (tmp[k] == '1' && !used[k])
                {
                    if (!s.empty())
                    {
                        s.push_back('+');
                    }
                    if (tmp[k + 1] == '1')
                    {
                        s += GetString(x, y, k, k + 1);
                        int n = k + 1 == 5 ? 1 : k + 1;
                        used[n] = true;
                        continue;
                    }
                    if (tmp[k - 1] == '1')
                    {
                        s += GetString(x, y, k, k - 1);
                        int n = k - 1 == 0 ? 4 : k - 1;
                        used[n] = true;
                        continue;
                    }
                    if (tmp[k + 1] == 'x')
                    {
                        s += GetString(x, y, k, k + 1);
                        num_bin[num_q[i][j][k + 1]][i] = '1';
                        continue;
                    }
                    if (tmp[k - 1] == 'x')
                    {
                        s += GetString(x, y, k, k - 1);
                        num_bin[num_q[i][j][k - 1]][i] = '1';
                        continue;
                    }
                    s += GetString(x, y, k);
                }
            }
            Qn_JK[i][j] = s;
        }
    }
}

// single one
string GetString(int x, int y, int k)
{
    int a = (k == 1 || k == 2 || k == 5) ? 1 : 0;
    int b = (k == 2 || k == 3) ? 0 : 1;
    string s;
    s.push_back(char_Qn[x][a]);
    s.push_back(char_Qn[y][b]);
    return s;
}

// combine two
char GetString(int x, int y, int m, int n)
{
    string s1 = GetString(x, y, m);
    string s2 = GetString(x, y, n);
    char c = (s1[0] == s2[0]) ? s1[0] : s1[1];
    return c;
}

void PrintFirst()
{
    cout << endl
         << "Karnaugh map:" << endl
         << "   00  01  11  10"
         << endl;
    for (int i = 0; i < 2; ++i)
    {
        cout << i << "  "
             << num_bin[i * 4] << " "
             << num_bin[i * 4 + 1] << " "
             << num_bin[i * 4 + 3] << " "
             << num_bin[i * 4 + 2] << endl;
    }
}

void PrintQn(int n)
{
    cout << endl
         << "Karnaugh map Q" << n << ":" << endl
         << "   00  01  11  10"
         << endl;
    n = 2 - n;
    for (int i = 0; i < 2; ++i)
    {
        cout << i << "  "
             << num_bin[i * 4][n] << "   "
             << num_bin[i * 4 + 1][n] << "   "
             << num_bin[i * 4 + 3][n] << "   "
             << num_bin[i * 4 + 2][n] << endl;
    }
}

void PrintJK()
{
    cout << endl;
    for (int i = 0; i < 3; ++i)
    {
        string jk[2] = {"J", "K"};
        for (int j = 0; j < 2; ++j)
        {
            cout << jk[j] << 2 - i
                 << (j == 0 ? ' ' : '\'')
                 << " = ";
            for (char c : Qn_JK[i][j])
            {
                cout << JK_char[c];
            }
            cout << endl;
        }
    }
}

void PrintSecond()
{
    for (int i = 0; i < 8; ++i)
    {
        for (char &c : num_bin[i])
        {
            c = (c == 'x') ? '0' : c;
        }
    }
    PrintFirst();
    cout << endl;
}

bool TestSelfSetup()
{
    int num1 = num_x[0];
    int num2 = num_x[1];
    string s1 = ToBinary(num1);
    string s2 = ToBinary(num2);
    string b1 = num_bin[num1];
    string b2 = num_bin[num2];
    return !(b1 == s1 || b2 == s2 || (b1 == s2 && b2 == s1));
}

bool AllOne(string s)
{
    return s.find('0') == -1;
}

bool AllZero(string s)
{
    return s.find('1') == -1;
}

string ToBinary(int n)
{
    string s;
    s.push_back((n >> 2) + 48);
    s.push_back(((n >> 1) & 1) + 48);
    s.push_back((n & 1) + 48);
    return s;
}