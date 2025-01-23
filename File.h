#pragma once
#include <iostream>
#include <vector>
#include <filesystem>
#include <string>
#include <fstream>
#include "Item.h"
namespace fs = std::filesystem;
using namespace std;

class CFile {
public:
    bool OpenFile(const string& FileName, vector<string>& screen);
    string GetLastError() const {return lastError;}

private:
    string lastError;
};

