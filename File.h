#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

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
    vector<pair<int, int>> mario;        // '@'
    vector<pair<int, int>> pauline;     // '$'
    vector<pair<int, int>> donkeyKong;  // '&'
    vector<pair<int, int>> barrels;     // 'O'
    vector<pair<int, int>> ladders;     // 'H'
    vector<pair<int, int>> ghosts;      // 'x'
    vector<pair<int, int>> hammers;     // 'p'
    vector<pair<int, int>> walls;       // 'Q'
    vector<pair<int, int>> floors;      // '=', '<', '>'
};

class CFile {
public:
    bool OpenFile(const string& FileName, vector<string>& screen);
    bool ValidateLines(const vector<string>& screen);
    string GetLastError() const;

    bool ParseScreenData(const vector<string>& screen, ScreenData& data);

private:
    string lastError;
};

