#pragma once
#ifndef struct_h
#define struct_h
#include "string"
#include "string.h"
using namespace std;

struct nhanvien {
	string ho_va_ten;

	string ten;

	double luong;
	//chuc vu theo so 
	int chucvu;
	//chuc vu theo chu
	string chucvu_chu;
	// chia ra  3 loai ngay , thang , nam dua vao mang 
	int ngaythangnamsinh[3];
};

struct tree_node {
	tree_node *left;
	nhanvien data;

};
#endif