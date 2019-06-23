#pragma once
#include "pch.h"
#include <iostream>
#include <string>
#include <string.h>
#include <sstream>
#include <iomanip>

#include <fstream>
#include <vector>
#include "linkList.h"
#include "struct.h"
class linkList;
class xuatNhapFile
{

private:
	
public:
	xuatNhapFile();
	~xuatNhapFile();
	int nhapFile(string duongDanFile, linkList &root, vector< pair<int, string> > &chuc_nhanvien);

};

string trim(const string& str);

void reset(nhanvien &nhan);
string layTen(string nhan);
string tolower(string dauVao);
bool coPhaiLaSo(string dauVao);