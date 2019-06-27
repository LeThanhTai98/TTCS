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
	//tong so luong phan tu 
	int tongSoLuonPhanTu;
	//so ky tu toi da cua tong so luong phan tu 
	int max_tongSoLuonPhanTu;
	// cai nay xai ben trong in file 
	void show_2(tree_node *item, ofstream &myfile);

	// ham cua merger sort
	tree_node* SortedMerge(tree_node* a, tree_node* b, int type_sort);

	// merge sort hop vs link list theo tim hieu la vay 
	void  MergeSort(tree_node** headRef);

public:
	~linkList();
	linkList();


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

	//xoa link list 
	void deleteList(tree_node** headRef);
	// show nhan vien ra
	void show_1();
	//show ra khung
	void show_khung();
	//show ra 1 bộ và vị trí
	void show_3(tree_node *prt, int dem);


	// goi sort 1 de sort theo luong , 2 chuc vu , 3 ngay thang nam sinh 
	void  Sort(const int&);





	int getMax_Ten() { return max_ten; }
	int getMax_Luong() { return max_luong; }
	//tìm kiếm theo hệ số lương
	void searchLuong(double cv);
	//tìm kiếm theo chức vụ
	void searchChucVu(string cv);
	// tìm kiếm theo họ và tên
	void searchHoTen(string cv);
	// tìm kiếm theo ngày tháng năm sinh
	void searchNTN(int ngay, int thang, int nam);
	//void badCharHeuristic(string str, int size, int badchar[255]);
	int search(string txt, string pat);


	// chức năng xóa
	void removeHead(linkList &l);
	void removeTail(linkList &l);
	void removeAfter(linkList &l, tree_node *t);
	void RemoveKey(linkList &l, string key);
	void RemoveDupNode(linkList &l, string cv);
	void deleteChucvu(string cv);

	friend class xuatNhapFile;
	
	
};

int sosanhten(string ten1, string ten2, string hoten1, string hoten2);