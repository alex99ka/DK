#include "File.h"

bool CFile::OpenFile(const string& FileName, vector<string>& screen) {
    screen.clear(); // Ensure a fresh state
    ifstream inputfile(FileName);

    if (!inputfile) {
        lastError = "Error: Could not open file " + FileName;
        cerr << lastError << endl;
        return false;
    }

    string line;
    while (getline(inputfile, line)) {
        if (line.size() != 80) { // Validate line length
            lastError = "Error: Invalid line length (" + to_string(line.size()) + ") in file.";
            cerr << lastError << endl;
            return false;
        }
        screen.push_back(line);
    }

    inputfile.close();
    return true;
}

bool CFile::ValidateLines(const vector<string>& screen) {
    if (screen.size() != 25) {
        lastError = "Error: Invalid number of lines in file (" + to_string(screen.size()) + ")";
        cerr << lastError << endl;
        return false;
    }
    return true;
}

string CFile::GetLastError() const {
    return lastError;
}

bool CFile::ParseScreenData(const vector<string>& screen, ScreenData& data) {
    data = {};

    for (int i = 0; i < screen.size(); ++i) {
        for (int j = 0; j < screen[i].size(); ++j) {
            char symbol = screen[i][j];
            pair<int, int> position = { i, j };

            switch (symbol) {
            case '@': data.mario = CPoint(position.first, position.second); break;
            case 'p': data.hammer = CPoint(position.first, position.second); break;
            case '$': data.pauline = CPoint(position.first, position.second); break;
            case '&': data.donkeyKong = CPoint(position.first, position.second); break;
            case 'x': data.ghosts.push_back(CPoint(position.first, position.second)); break;
            case 'O': data.barrels.push_back(CPoint(position.first, position.second)); break;
            case 'H': data.ladders.push_back(CPoint(position.first, position.second)); break;
            case 'Q': data.walls.push_back(CPoint(position.first, position.second)); break;
            case '=':data.floor.push_back(CPoint(position.first, position.second)); break;
            case '<':data.Left.push_back(CPoint(position.first, position.second)); break;
            case '>': data.Right.push_back(CPoint(position.first, position.second)); break;
            case 'L': data.Legend = CPoint(position.first, position.second); break;
            default:
                if (symbol != ' ') { // Ignore spaces
                    lastError = "Unknown symbol '" + string(1, symbol) +
                        "' at (" + to_string(i) + ", " + to_string(j) + ")";
                    return false;
                }
            }
        }
    }
    return true;
}