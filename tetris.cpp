// tetris.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <stdio.h>
#include "windows.h"
#include <cstdlib>
#include<time.h>
#include <conio.h>

using namespace std;
using std::string;

//#define TEST

#define mp make_pair 
#define uc unsigned char

const int width = 120;
const int high = 30;
const int screen_size = high * (width + 1);
char buff[screen_size];

string colors = " @#.O*o0";

const int fild_w = 10;
const int fild_h = 20;
const int fild_begin = 40;
 
enum {
    NONE = 0,
    RIGHT = 1,
    LEFT = 2,
    DOWN = 4
};

class Domino {
private:
    uc type;
    uc color;
    vector <pair<int, int>> pos;
    bool fall(vector <vector <uc>>& fild) {
        bool ans = true;
        for (int i = 0; i < 4; i++)if (pos[i].second == 0)ans = false;

        if (ans) {
            for (int i = 0; i < 4; i++)
                if ((fild[pos[i].first][pos[i].second - 1]) && ((fild[pos[i].first][pos[i].second - 1] >> 4) == 0))ans = false;
        }

        if (!ans) {
            for (int i = 0; i < 4; i++)fild[pos[i].first][pos[i].second] = (color & 15);
        }
        return ans;
    }

public:
      
    Domino(uc input) {
        pos.resize(4);
        type = input;
        color = type + 17;

        if (type == 0)pos = { mp(fild_w/2-1, fild_h - 1), mp(fild_w / 2 - 2, fild_h - 1), mp(fild_w / 2, fild_h - 1), mp(fild_w / 2 + 1, fild_h - 1) };
        else if (type == 1)pos = { mp(fild_w / 2 - 1, fild_h - 1), mp(fild_w / 2 - 2, fild_h - 1),  mp(fild_w / 2, fild_h - 1), mp(fild_w / 2 - 1, fild_h - 2) };
        else if (type == 2)pos = { mp(fild_w / 2 - 1, fild_h - 1), mp(fild_w / 2 - 1, fild_h - 2),  mp(fild_w / 2, fild_h - 1), mp(fild_w / 2, fild_h - 2) };
        else if (type == 3)pos = { mp(fild_w / 2 - 1, fild_h - 1), mp(fild_w / 2 + 1, fild_h - 1),  mp(fild_w / 2, fild_h - 1), mp(fild_w / 2 + 1, fild_h - 2) };
        else if (type == 4)pos = { mp(fild_w / 2 - 1, fild_h - 1), mp(fild_w / 2 - 2, fild_h - 1),  mp(fild_w / 2, fild_h - 1), mp(fild_w / 2 - 2, fild_h - 2) };
        else if (type == 5)pos = { mp(fild_w / 2 - 1, fild_h - 1), mp(fild_w / 2 - 2, fild_h - 2),  mp(fild_w / 2, fild_h - 1), mp(fild_w / 2 - 1, fild_h - 2) };
        else if (type == 6)pos = { mp(fild_w / 2 - 1, fild_h - 1), mp(fild_w / 2, fild_h - 2),      mp(fild_w / 2, fild_h - 1), mp(fild_w / 2 + 1, fild_h - 2) };

    }

    void redraw(vector <vector<uc>>& fild, uc dir) {
        for (int i = 0; i < 4; i++)fild[pos[i].first][pos[i].second] = 0;
        if (dir & 1)for (int i = 0; i < 4; i++)pos[i] = mp(pos[i].first + 1,pos[i].second);
        if ((dir >> 1) & 1)for (int i = 0; i < 4; i++)pos[i] = mp(pos[i].first - 1, pos[i].second);
        if ((dir >> 2) & 1)for (int i = 0; i < 4; i++)pos[i] = mp(pos[i].first, pos[i].second - 1);

        for (int i = 0; i < 4; i++)fild[pos[i].first][pos[i].second] = color;
        
    }
    bool end_game() {
        if (pos[0].second == 29)return true;
        else return false;
    }
    bool empty(vector <vector<uc>>& fild, uc dir) {
        if (dir == DOWN)return fall(fild);

        if (dir == LEFT) {
            
            bool ans = true;
            for (int i = 0; i < 4; i++)if (pos[i].first <= 0)ans = false;

            if (ans) {
                for (int i = 0; i < 4; i++)
                    if ((fild[pos[i].first -1 ][pos[i].second]) && ((fild[pos[i].first - 1][pos[i].second] >> 4) == 0))ans = false;
            }

            return ans;
        }

        if (dir == RIGHT) {
            bool ans = true;
            for (int i = 0; i < 4; i++)if (pos[i].first == fild_w - 1)ans = false;

            if (ans) {
                for (int i = 0; i < 4; i++)
                    if ((fild[pos[i].first + 1][pos[i].second]) && ((fild[pos[i].first + 1][pos[i].second] >> 4) == 0))ans = false;
            }
            return ans;
        }
    }
    void clean(vector <vector <uc>>& fild) {
        for (int i = 0; i < 4; i++)fild[pos[i].first][pos[i].second] = 0;
    }
    void rotate(vector <vector <uc>>& fild) {
        if (type == 2)return; // 1 state
        else {
            clean(fild);
            for (int i = 1; i < 4; i++) {

                int x = pos[i].second + pos[0].first - pos[0].second;
                int y = pos[0].first + pos[0].second - pos[i].first;
                pos[i] = mp(x, y);
            }
            redraw(fild, NONE);
        }
    }
};


void view(vector<vector <uc>>& fild);
void clean();
uc get_com();
void clean_rows(vector <vector <uc>>& fild);
void delete_row(vector <vector <uc>>& fild, int index);
void rotate(Domino* domino, vector <vector <uc>>& fild);

int main()
{
    srand(time(0));
    //emptys creen
    for (int i = 0; i < screen_size; i++) {
        if (i % (width + 1) == 0)buff[i] = '\n';
        else buff[i] = ' ';  
    }

    vector<vector <uc>> fild(fild_w);
    for (int i = 0; i < fild_w; i++)fild[i].resize(fild_h);

    //make fild & grid 
    for (int i = 0; i < screen_size; i++) {
        if ((i/(width + 1) < fild_h) && ((((i % (width + 1)) >= fild_begin) && (((i % (width + 1)) <= fild_begin + 2 * fild_w) && ((i % (width + 1)) % 2 == 0)))))buff[i] = '|';

    }



    Domino* domino = new Domino(rand() % 7);
    domino->redraw(fild, NONE);

#ifdef TEST
    //tets rotation 
    int t = 10;
    while (t--)domino->redraw(fild, DOWN);

    while (1) {

        //domino->clean(fild);
        view(fild);
        printf(buff);
        rotate(domino, fild);
    }

#endif
    //game
    while (1) {

        //read buttons
        int count = 5;
        while (count--){
            rotate(domino, fild);
            uc command = get_com();
            if (domino->empty(fild, command))domino->redraw(fild, command);
            Sleep(10);
        }

        // move falling domino down
        if (domino->empty(fild,DOWN))domino->redraw(fild, DOWN);
        else {
            if (domino->end_game()) {
                clean();
                printf(buff);
                cout << "\t Game over \n";
                return 0;
            }
            clean_rows(fild);
            domino = new Domino(rand() % 7);
        }
        view(fild);
        printf(buff);
        Sleep(80);
    }
}

// help function 
void view(vector<vector <uc>>& fild) {
    for (int i = 0; i < fild_w; i++) {
        for (int j = 0; j < fild_h; j++) {
            buff[((fild_h - 1 - j) * (width + 1)) + (fild_begin + (2 * i) + 1)] = colors[fild[i][j]&15];
        }
    }
}

void clean() {
    for (int i = 0; i < screen_size; i++)buff[i] = ' ';
}

uc get_com() {
    uc com = NONE;
    if (_kbhit()) {
        uc code = _getch();
        //code = static_cast<int>(code);
        if (code == 75)com = LEFT;
        if (code == 77)com = RIGHT;
        if (code == 80)com = DOWN;
    }
    return com;
}

void clean_rows(vector <vector <uc>>& fild) {
    for (int i = 0; i < fild_h; i++) {
        bool all_row = true;
        for (int j = 0; j < fild_w; j++) {
            if (fild[j][i] == 0) {
                all_row = false;
                break;
            }
        }
        if (all_row) {
            delete_row(fild, i);
            i--;
        }
    }
}

void delete_row(vector <vector <uc>>&fild, int index) {
    for (int i = 0; i < fild_w; i++)fild[i][index] = 0;
    //down all fild
    for (int i = index + 1; i < fild_h; i++) {
        for (int j = 0; j < fild_w; j++) {
            fild[j][i-1] = fild[j][i];
            fild[j][i] = 0;
        }
    }  
}

void rotate(Domino* domino, vector <vector <uc>>& fild) {
    if (_kbhit()) {
        uc code = _getch();
        if (code == 32) {
            domino->rotate(fild);
        }
    }
}