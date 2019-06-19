#pragma once
#include "pch.h"

#include <string>
#include <string.h>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <vector>
#include "struct.h"
#include "xuatNhapFile.h"
using namespace std;

class xuatNhapFile;
class linkList
{
public:
private:
	//phan tu dau list
	
	tree_node *roots;
	//phan tu cuoi list
	tree_node *last;
	//tieu chi sap xep 
	int type_sort;
	//so ky tu toi da cua ten 
	int max_ten;
	//so ky tu toi da cua luong 
	int max_luong;
	// so ky tu toi da cua chuc vu CHU (string)
	int max_chucvu;
	//so ky tu toi da cua ngay thang nam sinh 
	int max_ngay;
	// cai nay xai ben trong in file 
	void show_2(tree_node *item, ofstream &myfile);

public:
	~linkList();
	linkList();
	// thang duoi nay chua kip viet 
	linkList(const tree_node &);

	// kiem tra rong
	int is_empty() {
		return (roots == NULL);
	}
	// them bt * chu y sau khi sort xong tu dong them dung vi tri theo sort
	void insert(nhanvien item);
	// them theo vi tri 
	void insert(nhanvien item, int loca);

	tree_node * getRoots();

	tree_node * getLast();
	// cai nay de in file 
	void in_file();
	// chua kip viet xuong main chuong trinh coi 
	void nhapfile(string file);
	//xoa link list 
	void deleteList(tree_node** headRef);
	// show nhan vien ra
	void show_1();

	// merge sort hop vs link list theo tim hieu la vay 
	void  MergeSort(tree_node** headRef);

	// goi sort 1 de sort theo luong , 2 chuc vu , 3 ngay thang nam sinh 
	void  Sort(const int&);

	// ham cua merger sort
	tree_node* SortedMerge(tree_node* a, tree_node* b, int type_sort);

	// lay thang nhan vien cuoi list 
	void setLast();

	int getMax_Ten() { return max_ten; }
	int getMax_Luong() { return max_luong; }
	
	friend class xuatNhapFile;
	friend  void  xuatFile(linkList roots);
	
};

int sosanhten(string str1, string str2);