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
