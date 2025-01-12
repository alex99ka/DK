#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "Item.h"

using namespace std;


// ScreenData is a struct that keeps the positions of all the game items on the screen.
// Each vector is for a specific game symbol, like Mario, barrels, ladders, and so on.
//
// The positions are saved as `pair<int, int>`:
// - The `first` is the row number (Y-coordinate).
// - The `second` is the column number (X-coordinate).
//
// This struct makes it easy to find where each game symbol is on the screen.
struct ScreenData {
    CPoint mario;        // '@'
    CPoint pauline;     // '$'
    CPoint donkeyKong;  // '&'
    CPoint Legend; //'L'
    CPoint hammer;     // 'p'
    vector<CPoint> barrels;     // 'O'
    vector<CPoint> ghosts;      // 'x'
    vector<CPoint > ladders;     // 'H'
    vector<CPoint> walls;       // 'Q'
    vector<CPoint> floor;      // '='
    vector<CPoint> Left;      // '<'
    vector<CPoint> Right;      //  '>'
};

class CFile {
public:
    bool OpenFile(const string& FileName, vector<string>& screen);
    bool ValidateLines(const vector<string>& screen);
    string GetLastError() const;

    bool ParseScreenData(vector<string>& screen, ScreenData& data);

private:
    string lastError;
};

