#include "File.h"


bool CFile::OpenFile(const string& FileName, vector<string>& screen)
{
    screen.clear(); // Ensure a fresh state
    ifstream inputfile(FileName);

    if (!inputfile.good()) {
        lastError = "Error: Could not open file " + FileName;
        cout << lastError << endl;
        return false;
    }

    string line;
    while (getline(inputfile, line)) 
        screen.push_back(line);

    inputfile.close();
    return true;
}


string CFile::GetLastError() const {
    return lastError;
}

bool CFile::ParseScreenData(vector<string>& screen, ScreenData& data) 
{
    data = {};  // Initialize the ScreenData structure

    for (int i = 0; i < screen.size(); ++i) {
        for (int j = 0; j < screen[i].size(); ++j) {
            char symbol = screen[i][j];

            switch (symbol) {
            case '@': data.mario = CPoint(i, j); break;
            case 'p': data.hammer = CPoint(i, j); break;
            case '$': data.pauline = CPoint(i, j); break;
            case '&': data.donkeyKong = CPoint(i, j); break;
            case 'x': data.ghosts.push_back(CPoint(i, j)); break;
            case 'O': data.barrels.push_back(CPoint(i, j)); break; // from below add to board. 
            case 'H': data.ladders.push_back(CPoint(i, j)); break;
            case 'Q': data.walls.push_back(CPoint(i, j)); break;
            case '=': data.floor.push_back(CPoint(i, j)); break;
            case '<': data.Left.push_back(CPoint(i, j)); break;
            case '>': data.Right.push_back(CPoint(i, j)); break;
            case 'L': data.Legend = CPoint(i, j); break;
            default:
                if (symbol != ' ') { // Ignore spaces
                    lastError = "Unknown symbol '" + string(1, symbol) +
                        "' at (" + to_string(i) + ", " + to_string(j) + ")";
                    screen.clear();
                    return false;
                }
            }
        }
    }
    return true;
}
