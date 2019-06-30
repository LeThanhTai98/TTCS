#include "pch.h"

#include <string>
#include <string.h>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <fstream>
#include "linkList.h"
#include "struct.h"
using namespace std;
int doDaiCuaSoInt(int so) {
	int dem = 0;
	if (so == 0) return 1;
	while (so != 0 ) {
		so = so / 10;
		dem++;
	}
	return dem;
}
int sosanhten(string ten1, string ten2,string hoten1 , string hoten2) {
	int doDaiStr1 = ten1.size();
	int doDaiStr2 = ten2.size();
	int dem;
	if (doDaiStr2 < doDaiStr1)
		dem = doDaiStr2;
	else  dem = doDaiStr1;
	for (int i = 0;i < dem;i++) {
		if (ten1[i] > ten2[i]) return 1;
		else if (ten1[i] < ten2[i]) return 0;
	}
	if (doDaiStr1 > doDaiStr2) return 1;

	if (doDaiStr1 == doDaiStr2) {
	
		int doDai1 = hoten1.size();
		int doDai2 = hoten2.size();
		int dem;
		if (doDai2 < doDai1)
			dem = doDai2;
		else  dem = doDai1;
		for (int i = 0;i < dem;i++) {
			if (hoten1[i] > hoten2[i]) return 1;
			else if (hoten1[i] < hoten2[i]) return 0;
		}
		if (doDaiStr1 > doDaiStr2) return 1;
		return 0;
	}
	return 0;
}

bool linkList::soSanhNgayThangNam(nhanvien data1, nhanvien data2) {

	if (data1.ngaythangnamsinh[2] < data2.ngaythangnamsinh[2]) {
		return true;
	}
	else if (data1.ngaythangnamsinh[2] > data2.ngaythangnamsinh[2]) {
		return false;

	}
	else if (data1.ngaythangnamsinh[1] < data2.ngaythangnamsinh[1]) {
		return true;
	}
	else if (data1.ngaythangnamsinh[1] > data2.ngaythangnamsinh[1]) {
		return false;
	}
	else if (data1.ngaythangnamsinh[0] < data2.ngaythangnamsinh[0]) {
		return true;
	}
	else if (data1.ngaythangnamsinh[0] > data2.ngaythangnamsinh[0]) {
		return false;
	}
	else if (sosanhten(data1.ten, data2.ten, data1.ho_va_ten, data2.ho_va_ten) <= 0) {
		if (thuTu_sort == 1)return true;
		else return false;
	}
	if (thuTu_sort == 1) return false;
	else return true;
}

bool linkList::soSanhNhanVien(tree_node *a, tree_node *b) {
	bool ketQua;
	switch (type_sort)
	{
	case 1: {
		if (a->data.luong == b->data.luong) {
			string ten1 = a->data.ten;
			string ten2 = b->data.ten;
			string hoten1 = a->data.ho_va_ten;
			string hoten2 = b->data.ho_va_ten;

			if (sosanhten(ten1, ten2, hoten1, hoten2) <= 0) {
				if (thuTu_sort == 1)	ketQua = true;
				else ketQua = false;
			}
			else {
				if (thuTu_sort == 1)ketQua = false;
				else ketQua = true;
			}
		}
		else
			if (a->data.luong > b->data.luong) {
				ketQua = true;
			}
			else {
				ketQua = false;
			}
	}
			break;
			// sort theo chuc vu so neu bang bang nhau sort theo ten
	case 2: {
		if (a->data.chucvu == b->data.chucvu) {
			string ten1 = a->data.ten;
			string ten2 = b->data.ten;
			string hoten1 = a->data.ho_va_ten;
			string hoten2 = b->data.ho_va_ten;

			if (sosanhten(ten1, ten2, hoten1, hoten2) <= 0) {
				if (thuTu_sort == 1)	ketQua = true;
				else ketQua = false;
			}
			else {
				if (thuTu_sort == 1)ketQua = false;
				else ketQua = true;
			}
		}
		else
			if (a->data.chucvu > b->data.chucvu) {
				ketQua = true;
			}
			else {
				ketQua = false;
			}
	}
			break;
			// sort theo ngay thang nam sinh neu bang bang nhau sort theo ten
	case 3: {

		if (soSanhNgayThangNam(a->data, b->data))
		{
			ketQua = true;
		}
		else {
			ketQua = false;
		}

	}
			break;
	case 4: {
		string ten1 = a->data.ten;
		string ten2 = b->data.ten;
		string hoten1 = a->data.ho_va_ten;
		string hoten2 = b->data.ho_va_ten;

		if (sosanhten(ten1, ten2, hoten1, hoten2) <= 0)
		{
			ketQua = true;
		}
		else {
			ketQua = false;
		}
	}
			break;
	default:
		ketQua = true;
		break;
	}
	if (thuTu_sort == 1) return ketQua;
	else if (thuTu_sort == 2) {
		ketQua = !ketQua;
		return ketQua;
	}
}


void FrontBackSplit(tree_node* source, tree_node** frontRef, tree_node** backRef);

ostream& operator<<(ostream& os, const nhanvien& item);

linkList::linkList() { roots = NULL;type_sort = 0;max_ten = 11; max_luong = 13;max_chucvu = 11;max_ngay = 21;max_tongSoLuonPhanTu = 5; }

linkList::~linkList() {
	deleteList(&roots);
}

void linkList::insert(nhanvien item) {
	// so sanh de tim chuoi dai nhat 
	int doDaiHoTen = item.ho_va_ten.size();
	if (max_ten < doDaiHoTen) max_ten = doDaiHoTen;

	//convert so sang string de so sanh 

	ostringstream a;
	a << item.luong;
	int doDaiLuong = a.str().size();
	if (max_luong < doDaiLuong) max_luong = doDaiLuong;

	int doDaiChucVu = item.chucvu_chu.size();
	if (max_chucvu < doDaiChucVu) max_chucvu = doDaiChucVu;



	tree_node *p = new tree_node;
	p->left = NULL;

	p->data = item;


	if (type_sort == 0) {
		tree_node *last = getLast();
		tree_node *parent = NULL;
		if (is_empty()) {
			roots = p;
			last = p;
			return;
		}
		tree_node *ptr = roots;

		last->left = p;
		last = last->left;

	}
	else {
		tree_node *parent = NULL;
		tree_node *ptr = getRoots();

		if (ptr != NULL) {
			do {
				if (soSanhNhanVien(ptr, p)) {
				parent = ptr;
				ptr = ptr->left;
			}
			else {
				break;
			}

		} while (ptr != NULL);
	
		}
		if (parent != NULL) {
			tree_node *tem_node = parent->left;
			parent->left = p;
			p->left = tem_node;
		}
		else {
			p->left = roots;
			roots = p;
		}
		tongSoLuonPhanTu++;
	}
}



void linkList::insert(nhanvien item, int loca) {
	tree_node *p = new tree_node;
	p->left = NULL;

	p->data = item;
	tree_node *parent = NULL;
	if (is_empty()) {
		roots = p;
		return;
	}
	tree_node *ptr = roots;
	int count = 0;
	parent = ptr;
	while (ptr != NULL and count < loca - 1) {
		parent = ptr;
		ptr = ptr->left;
		count++;
	}
	tree_node *tem_node = parent->left;
	parent->left = p;
	p->left = tem_node;
}


tree_node* linkList::getRoots() {
	return roots;
}


tree_node* linkList::getLast() {
	
	tree_node *last = roots;
	if (last != NULL) {
		while (last->left != NULL)
			last = last->left;

		return last;
	}
	return last;
}
string taoKhoangTrong(int soKhoantrong) {
	string traVe;
	for (int i = 0;i < soKhoantrong;i++)
		traVe += ' ';
	return traVe;
}

void linkList::in_file() {

	ofstream myfile;
	myfile.open("example_1.txt");
	
	const char separator = ' ';
	const char separator_2 = '|';
	if (myfile.is_open())
	{
		string hoTen, chuc, ngaythang, heSoLuong;
		
		hoTen = "ho va ten";
		chuc = "chuc vu";
		ngaythang = "ngay thang nam sinh";
		heSoLuong = "he so luong";
		

		myfile << '+' << string( max_ten + max_luong + max_ngay + max_chucvu + 3, '-') << '+' << "\n";

		
		myfile << separator_2 << hoTen << taoKhoangTrong(max_ten - hoTen.size()) << separator_2 << chuc << taoKhoangTrong(max_chucvu - chuc.size()) << separator_2
			<< ngaythang << taoKhoangTrong(max_ngay - ngaythang.size()) << separator_2 << heSoLuong << taoKhoangTrong(max_luong - heSoLuong.size()) << separator_2 << "\n";
		// in duong ket thuc
		myfile << '+' << string(max_ten + max_luong + max_ngay + max_chucvu + 3, '-') << '+' << "\n";
		show_2(roots, myfile);
	}
	myfile.close();
}

void linkList::show_2(tree_node *ptr, ofstream &myfile) {
	if (ptr != NULL) {
		const char separator = ' ';
		const char separator_2 = '|';
		// noi ngay thang nam sinh lai thanh ngay/thang/nam
		ostringstream ss, luong;
		ss << ptr->data.ngaythangnamsinh[0] << '/' << ptr->data.ngaythangnamsinh[1] << '/' << ptr->data.ngaythangnamsinh[2];
		luong << ptr->data.luong;


		//left canh le trai / right canh le phai 
		myfile << separator_2 << ptr->data.ho_va_ten << taoKhoangTrong(max_ten - ptr->data.ho_va_ten.size()) << separator_2 << ptr->data.chucvu_chu << taoKhoangTrong(max_chucvu - ptr->data.chucvu_chu.size()) << separator_2
			<< ss.str() << taoKhoangTrong(max_ngay - ss.str().size()) << separator_2 << ptr->data.luong << taoKhoangTrong(max_luong - luong.str().size()) << separator_2 << "\n";
		// in duong ket thuc 1 bo 
		myfile << '+' << string(max_ten + max_luong + max_ngay + max_chucvu + 3, '-') << '+' << "\n";
		show_2(ptr->left, myfile);
	}
}

//in bt thuong
void linkList::show_1() {
	
	tree_node *ptr = roots;

	const char separator = ' ';
	const char separator_2 = '|';
	// noi ngay thang nam sinh lai thanh ngay/thang/nam
	string hoTen, chuc, ngaythang, heSoLuong, stt;
	stt = "STT";
	hoTen = "ho va ten";
	chuc = "chuc vu";
	ngaythang = "ngay thang nam sinh";
	heSoLuong = "he so luong";
	if (max_tongSoLuonPhanTu < doDaiCuaSoInt(tongSoLuonPhanTu)) max_tongSoLuonPhanTu = doDaiCuaSoInt(tongSoLuonPhanTu);

	cout << separator_2 << stt << taoKhoangTrong(max_tongSoLuonPhanTu - stt.size()) << separator_2 << hoTen << taoKhoangTrong(max_ten - hoTen.size()) << separator_2 << chuc << taoKhoangTrong(max_chucvu - chuc.size()) << separator_2
		<< ngaythang << taoKhoangTrong(max_ngay - ngaythang.size()) << separator_2 << heSoLuong << taoKhoangTrong(max_luong - heSoLuong.size()) << separator_2 << "\n";
	// in duong ket thuc 1 bo 
	cout << '+' << string(max_tongSoLuonPhanTu + max_ten + max_luong + max_ngay + max_chucvu + 4, '-') << '+' << "\n";
	 
	int dem = 1;
	while (ptr != NULL) {
		ostringstream ss,luong;
		ss << ptr->data.ngaythangnamsinh[0] << '/' << ptr->data.ngaythangnamsinh[1] << '/' << ptr->data.ngaythangnamsinh[2];
		luong << ptr->data.luong;
		
		int doDaiDem = doDaiCuaSoInt(dem);

		cout << separator_2 << dem << taoKhoangTrong(max_tongSoLuonPhanTu - doDaiDem) << separator_2 << ptr->data.ho_va_ten << taoKhoangTrong(max_ten - ptr->data.ho_va_ten.size())  << separator_2<< ptr->data.chucvu_chu << taoKhoangTrong(max_chucvu - ptr->data.chucvu_chu.size()) <<separator_2
	<< ss.str() << taoKhoangTrong(max_ngay - ss.str().size())  << separator_2  << ptr->data.luong << taoKhoangTrong(max_luong - luong.str().size()) << separator_2 << "\n";
		// in duong ket thuc 1 bo 
		cout << '+' << string(max_tongSoLuonPhanTu + max_ten + max_luong + max_ngay + max_chucvu + 4, '-') << '+' << "\n";

		ptr = ptr->left;
		dem++;
	}
}

//show ra 1 nhân viên
void linkList::show_3(tree_node *ptr,int dem) {
	const char separator = ' ';
	const char separator_2 = '|';
	// nối ngày tháng năm
		ostringstream ss, luong;
		ss << ptr->data.ngaythangnamsinh[0] << '/' << ptr->data.ngaythangnamsinh[1] << '/' << ptr->data.ngaythangnamsinh[2];
		luong << ptr->data.luong;
		int doDaiDem = doDaiCuaSoInt(dem);
		cout << separator_2 << dem << taoKhoangTrong(max_tongSoLuonPhanTu - doDaiDem) << separator_2 << ptr->data.ho_va_ten << taoKhoangTrong(max_ten - ptr->data.ho_va_ten.size()) << separator_2 << ptr->data.chucvu_chu << taoKhoangTrong(max_chucvu - ptr->data.chucvu_chu.size()) << separator_2
			<< ss.str() << taoKhoangTrong(max_ngay - ss.str().size()) << separator_2 << ptr->data.luong << taoKhoangTrong(max_luong - luong.str().size()) << separator_2 << "\n";
		// in duong ket thuc 1 bo 
		cout << '+' << string(max_tongSoLuonPhanTu + max_ten + max_luong + max_ngay + max_chucvu + 4, '-') << '+' << "\n";

		ptr = ptr->left;

}
void linkList::show_khung() 
{
	const char separator = ' ';
	const char separator_2 = '|';
	string hoTen, chuc, ngaythang, heSoLuong, stt;
	stt = "STT";
	hoTen = "ho va ten";
	chuc = "chuc vu";
	ngaythang = "ngay thang nam sinh";
	heSoLuong = "he so luong";
	if (max_tongSoLuonPhanTu < doDaiCuaSoInt(tongSoLuonPhanTu)) max_tongSoLuonPhanTu = doDaiCuaSoInt(tongSoLuonPhanTu);

	cout << separator_2 << stt << taoKhoangTrong(max_tongSoLuonPhanTu - stt.size()) << separator_2 << hoTen << taoKhoangTrong(max_ten - hoTen.size()) << separator_2 << chuc << taoKhoangTrong(max_chucvu - chuc.size()) << separator_2
		<< ngaythang << taoKhoangTrong(max_ngay - ngaythang.size()) << separator_2 << heSoLuong << taoKhoangTrong(max_luong - heSoLuong.size()) << separator_2 << "\n";
	// in duong ket thuc 1 bo 
	cout << '+' << string(max_tongSoLuonPhanTu + max_ten + max_luong + max_ngay + max_chucvu + 4, '-') << '+' << "\n";
}

void linkList::MergeSort(tree_node** headRef)
{
	tree_node* head = *headRef;
	tree_node* a;
	tree_node* b;


	if ((head == NULL) || (head->left == NULL)) {
		return;
	}


	FrontBackSplit(head, &a, &b);


	MergeSort(&a);
	MergeSort(&b);



	*headRef = SortedMerge(a, b, type_sort);

}

// so sanh vs noi mang 
tree_node*linkList::SortedMerge(tree_node* a, tree_node* b, int type_sort)
{
	tree_node* result = NULL;

	if (a == NULL)
		return (b);
	else if (b == NULL)
		return (a);
	//sort theo luong neu bang bang nhau sort theo ten
	bool ketQua = soSanhNhanVien(a, b);
	
	if (ketQua) {
		result = a;

		result->left = SortedMerge(a->left, b, type_sort);
	}
	else {
		result = b;

		result->left = SortedMerge(a, b->left, type_sort);
	}
	return (result);
}

// tach mang ra 2 con 
void FrontBackSplit(tree_node* source, tree_node** frontRef, tree_node** backRef)
{
	tree_node* fast;
	tree_node* slow;
	slow = source;
	fast = source->left;


	while (fast != NULL) {
		fast = fast->left;
		if (fast != NULL) {
			slow = slow->left;
			fast = fast->left;
		}
	}


	*frontRef = source;
	*backRef = slow->left;
	slow->left = NULL;
}

void linkList::Sort(int const &type , int const &thuTu) {
	type_sort = type;
	thuTu_sort = thuTu;
	MergeSort(&roots);
}

void linkList::deleteList(tree_node** headRef) {
	tree_node* current = *headRef;
	tree_node* left;
	while (current != NULL) {
		left = current->left;
		delete(current);
		current = left;
	}
	*headRef = NULL;
}




// Tìm kiếm theo họ và tên
//void linkList::searchChucVu(string cv) {
//	int i=1;
//	tree_node *tree = roots;
//	while(tree != NULL)
//	{
//		if (tree->data.ho_va_ten.substr(0,cv.length()) == cv)
//		{
//			cout << "tim thay o vi tri: "<<i<<endl;
//		}
//		else
//		{
//			cout << "Khong tim thay";
//		}
//		tree = tree->left;
//		i++;
//	}
//
//}

// Tim kiếm theo hệ số lương
void linkList::searchLuong(double cv) {
	tree_node *tree = roots;
	int i=1;
	show_khung();
	while(tree != NULL)
	{
		if (tree->data.luong == cv)
		{
			//cout << "tim thay o vi tri: "<< i <<endl;
			show_3(tree,i);
		}
		tree = tree->left;
		i++;
	}
		cout << endl;
}

// Tìm kiếm theo Chức Vụ
void linkList::searchChucVu(string cv) {
	tree_node *tree = roots;
	int i = 1;
	show_khung();
	while (tree != NULL)
	{
		if (tree->data.chucvu_chu == cv)
		{
			//cout << "tim thay o vi tri: "<< i <<endl;
			show_3(tree, i);
		}
		tree = tree->left;
		i++;
	}
	 cout <<endl;
}

// Tìm kiếm theo ngày tháng năm sinh
void linkList::searchNTN(int ngay, int thang, int nam) {
	tree_node *tree = roots;
	int i = 1;
	show_khung();
	if (ngay == 0 && thang !=0 && nam !=0)
	{
		while (tree != NULL)
		{
			if (tree->data.ngaythangnamsinh[1] == thang && tree->data.ngaythangnamsinh[2] == nam)
			{
				show_3(tree, i);
			}
			tree = tree->left;
			i++;
		}
	}

	if (thang == 0 && ngay != 0 && nam != 0)
	{
		while (tree != NULL)
		{
			if (tree->data.ngaythangnamsinh[0] == ngay && tree->data.ngaythangnamsinh[2] == nam)
			{
				show_3(tree, i);
			}
			tree = tree->left;
			i++;
		}
	}

	if (nam == 0 && ngay != 0 && thang != 0)
	{
		while (tree != NULL)
		{
			if (tree->data.ngaythangnamsinh[0] == ngay && tree->data.ngaythangnamsinh[1] == thang )
			{
				show_3(tree, i);
			}
			tree = tree->left;
			i++;
		}
	}

	if (ngay == 0 && thang == 0)
	{
		while (tree != NULL)
		{
			if (tree->data.ngaythangnamsinh[2] == nam)
			{
				show_3(tree, i);
			}
			tree = tree->left;
			i++;
		}
	}

	if (ngay == 0 && nam == 0)
	{
		while (tree != NULL)
		{
			if ( tree->data.ngaythangnamsinh[1] == thang )
			{
				show_3(tree, i);
			}
			tree = tree->left;
			i++;
		}
	}

	if (thang == 0 && nam == 0)
	{
		while (tree != NULL)
		{
			if (tree->data.ngaythangnamsinh[0] == ngay)
			{
				show_3(tree, i);
			}
			tree = tree->left;
			i++;
		}
	}
	
	if (ngay != 0 && thang !=0 && nam !=0)
	{
		while (tree != NULL)
		{
			if (tree->data.ngaythangnamsinh[0] == ngay && tree->data.ngaythangnamsinh[1] == thang && tree->data.ngaythangnamsinh[2] == nam)
			{
				show_3(tree, i);
			}
			tree = tree->left;
			i++;
		}
	}
	
	cout << endl;
}

// Tìm kiếm theo họ và tên

int linkList::search(string txt, string pat) 
{
	int M = pat.size();
	int N = txt.size();
	int i = 0;

	while (i <= N - M)
	{
		int j;

		for (j = 0; j < M; j++)
			if (txt[i + j] != pat[j])
				break;

		if (j == M) 
		{
			//cout << "Vi tri xuat hien " << i << endl;
			return 1;
			//i = i + M;
		}
		else	if (j == 0)
			i = i + 1;
		else
			i = i + j; 
		if (i==(N-M+1))
		{
			return 0;
		}

	}
}
void linkList::searchHoTen(string cv)
{
	tree_node *tree = roots;
	int i = 1;
	show_khung();
	while (tree != NULL)
	{
		if (search(tree->data.ho_va_ten,cv) == 1)
		{
			show_3(tree,i);
		}
		tree = tree->left;
		i++;
	}
	 
	cout << endl;
}


// Xóa theo chức vụ
void linkList::removeHead(linkList &l) 
{   
	tree_node *last = l.getLast();
	if (!l.roots)
	{
		cout << "Danh sach rong!"<<endl;
	}
	else if (l.roots==last)
	{
		delete l.roots;
		l.roots = last = NULL;
	}
	else
	{
		tree_node *temp = l.roots;
		l.roots = l.roots->left;
		delete temp;
	}
}
void linkList::removeTail(linkList &l)
{
	tree_node *last = l.getLast();
	if (!l.roots)
		cout << "Danh sach rong!" << endl;
	else if (l.roots == last)
	{
		delete l.roots;
		l.roots = last = NULL;
	}
	else
	{
		tree_node *temp = l.roots;
		while (temp->left != last)
			temp = temp->left;
		delete last;
		temp->left = NULL;
	}
}
void linkList::removeAfter(linkList &l,tree_node *t)
{
	if (!l.roots)
		cout << "Danh sach rong!" << endl;
	else
	{
		tree_node *temp = t->left;
		if (temp)
		{
			t->left = temp->left;
			delete temp;
		}
	}
}
void linkList::RemoveKeyChucvu(linkList &l, string key) 
{
		if (!l.roots)
			cout << "Danh sach rong!" << endl;
		else
		{
			tree_node *result = l.roots, *before = NULL;
			while (result && result->data.chucvu_chu != key)
			{
				before = result;
				result = result->left;
			}
			if (result)
			{
				if (result == l.roots)
					removeHead(l);
				else
					removeAfter(l, before);
			}
		}
}


void linkList::deleteChucvu(linkList &l,string cv)
{
	tree_node *p, *q, *t;
	p = l.roots;
	while (p != NULL)
	{
		t = p;
		q = p->left;
		while (q != NULL)
		{
			//if (q->left != NULL && q->data.chucvu_chu == cv)
				if (q->data.chucvu_chu == cv)
			{
				removeAfter(l, t);
				q = t->left;
			}
			else
			{
				t = q;
				q = q->left;
			}
		}
		p = p->left;
	}
	RemoveKeyChucvu(l, cv);
}


//void linkList::deleteChucvu(string cv)
//{
//	tree_node *tree = roots;
//	//tree_node *t1 = NULL;
//	//tree_node *t2 = NULL;
//	//while(tree != NULL)
//	//{
//	//	
//	//	tree = tree->left;
//	//}
//
//
//	//tree_node *t1 = NULL;
//	//tree_node *t2 = NULL;
//	//while (tree != NULL)
//	//{
//
//
//	//	if (roots->data.chucvu_chu == cv)
//	//	{
//	//		roots = roots->left;
//	//		//return;
//	//	}
//	//	t1 = roots;
//	//	while (t1->left != NULL && t1->data.chucvu_chu != cv)
//	//	{
//	//		t2 = t1;
//	//		t1 = t1->left;
//	//	}
//
//	//	if (t1->left !=NULL && t1->data.chucvu_chu == cv)
//	//	{
//	//		t2->left = t2->left->left;
//	//		free(t1);
//	//		//return;
//	//	}
//
//	//	else
//	//	{
//	//		cout << "Khong tim thay " << cv << " trong danh sach"<<endl;
//	//	}
//	//	tree = tree->left;
//	//}
//	//return;
//}
void linkList::RemoveKeyLuong(linkList &l, double key)
{
	if (!l.roots)
		cout << "Danh sach rong!" << endl;
	else
	{
		tree_node *result = l.roots, *before = NULL;
		while (result && result->data.luong != key)
		{
			before = result;
			result = result->left;
		}
		if (result)
		{
			if (result == l.roots)
				removeHead(l);
			else
				removeAfter(l, before);
		}
	}
}
void linkList::RemoveKeyHoTen(linkList &l, string key)
{
	if (!l.roots)
		cout << "Danh sach rong!" << endl;
	else
	{
		tree_node *result = l.roots, *before = NULL;
		while (result && search(result->data.ho_va_ten,key) != 1)
		{
			before = result;
			result = result->left;
		}
		if (result)
		{
			if (result == l.roots)
				removeHead(l);
			else
				removeAfter(l, before);
		}
	}
}
void linkList::RemoveKeyNgay(linkList &l, int key)
{
	if (!l.roots)
		cout << "Danh sach rong!" << endl;
	else
	{
		tree_node *result = l.roots, *before = NULL;
		while (result && result->data.ngaythangnamsinh[0] != key)
		{
			before = result;
			result = result->left;
		}
		if (result)
		{
			if (result == l.roots)
				removeHead(l);
			else
				removeAfter(l, before);
		}
	}
}
void linkList::RemoveKeyThang(linkList &l, int key)
{
	if (!l.roots)
		cout << "Danh sach rong!" << endl;
	else
	{
		tree_node *result = l.roots, *before = NULL;
		while (result && result->data.ngaythangnamsinh[1] != key)
		{
			before = result;
			result = result->left;
		}
		if (result)
		{
			if (result == l.roots)
				removeHead(l);
			else
				removeAfter(l, before);
		}
	}
}
void linkList::RemoveKeyNam(linkList &l, int key)
{
	if (!l.roots)
		cout << "Danh sach rong!" << endl;
	else
	{
		tree_node *result = l.roots, *before = NULL;
		while (result && result->data.ngaythangnamsinh[2] != key)
		{
			before = result;
			result = result->left;
		}
		if (result)
		{
			if (result == l.roots)
				removeHead(l);
			else
				removeAfter(l, before);
		}
	}
}
void linkList::RemoveKeyNgayThang(linkList &l, int ngay, int thang)
{
	if (!l.roots)
		cout << "Danh sach rong!" << endl;
	else
	{
		tree_node *result = l.roots, *before = NULL;
		while (result && result->data.ngaythangnamsinh[0] != ngay && result->data.ngaythangnamsinh[1] != thang)
		{
			before = result;
			result = result->left;
		}
		if (result)
		{
			if (result == l.roots && result->data.ngaythangnamsinh[0] != ngay && result->data.ngaythangnamsinh[1] != thang)
				removeHead(l);
			else if (result->data.ngaythangnamsinh[0] == ngay && result->data.ngaythangnamsinh[1] == thang)
			{
				removeAfter(l, before);
			}
		}
	}
}
void linkList::RemoveKeyNgayNam(linkList &l, int ngay, int nam)
{
	if (!l.roots)
		cout << "Danh sach rong!" << endl;
	else
	{
		tree_node *result = l.roots, *before = NULL;
		while (result && result->data.ngaythangnamsinh[0] != ngay && result->data.ngaythangnamsinh[2] != nam)
		{
			before = result;
			result = result->left;
		}
		if (result)
		{
			if (result == l.roots && result->data.ngaythangnamsinh[0] != ngay && result->data.ngaythangnamsinh[2] != nam)
				removeHead(l);
			else if (result->data.ngaythangnamsinh[0] == ngay && result->data.ngaythangnamsinh[2] == nam)
			{
				removeAfter(l, before);
			}
		}
	}
}
void linkList::RemoveKeyThangNam(linkList &l, int thang, int nam)
{
	if (!l.roots)
		cout << "Danh sach rong!" << endl;
	else
	{
		tree_node *result = l.roots, *before = NULL;
		while (result && result->data.ngaythangnamsinh[1] != thang && result->data.ngaythangnamsinh[2] != nam)
		{
			before = result;
			result = result->left;
		}
		if (result)
		{
			if (result == l.roots && result->data.ngaythangnamsinh[1] != thang && result->data.ngaythangnamsinh[2] != nam)
				removeHead(l);
			else if (result->data.ngaythangnamsinh[1] == thang && result->data.ngaythangnamsinh[2] == nam)
			{
				removeAfter(l, before);
			}
		}
	}
}
void linkList::RemoveKeyNgayThangNam(linkList &l, int ngay, int thang, int nam)
{
	if (!l.roots)
		cout << "Danh sach rong!" << endl;
	else
	{
		tree_node *result = l.roots, *before = NULL;
		while (result && result->data.ngaythangnamsinh[0] != ngay && result->data.ngaythangnamsinh[1] != thang && result->data.ngaythangnamsinh[2] != nam)
		{
			before = result;
			result = result->left;
		}
		if (result)
		{
			if (result == l.roots && result->data.ngaythangnamsinh[0] != ngay && result->data.ngaythangnamsinh[1] != thang && result->data.ngaythangnamsinh[2] != nam)
				removeHead(l);
			else if (result->data.ngaythangnamsinh[0] == ngay && result->data.ngaythangnamsinh[1] == thang && result->data.ngaythangnamsinh[2] == nam)
			{
				removeAfter(l, before);
			}
		}
	}
}


void linkList::deleteLuong(linkList &l, double cv)
{
	tree_node *p, *q, *t;
	p = l.roots;
	while (p != NULL)
	{
		t = p;
		q = p->left;
		while (q != NULL)
		{
			//if (q->left != NULL && q->data.chucvu_chu == cv)
			if (q->data.luong == cv)
			{
				removeAfter(l, t);
				q = t->left;
			}
			else
			{
				t = q;
				q = q->left;
			}
		}
		p = p->left;
	}
	RemoveKeyLuong(l, cv);
}
void linkList::deleteHoTen(linkList &l, string cv)
{
	tree_node *p, *q, *t;
	p = l.roots;
	while (p != NULL)
	{
		t = p;
		q = p->left;
		while (q != NULL)
		{
			//if (q->left != NULL && q->data.chucvu_chu == cv)
			if (search(q->data.ho_va_ten, cv) == 1)
			{
				removeAfter(l, t);
				q = t->left;
			}
			else
			{
				t = q;
				q = q->left;
			}
		}
		p = p->left;
	}
	RemoveKeyHoTen(l, cv);
}
void linkList::deleteNgaySinh(linkList &l, int ngay, int thang, int nam)
{
	tree_node *p, *q, *t;
	p = l.roots;
	if (ngay == 0 && thang != 0 && nam != 0)
	{
		while (p != NULL)
		{
			t = p;
			q = p->left;
			while (q != NULL)
			{
				//if (q->left != NULL && q->data.chucvu_chu == cv)
				if (q->data.ngaythangnamsinh[1] == thang && q->data.ngaythangnamsinh[2] == nam)
				{
					removeAfter(l, t);
					q = t->left;
				}
				else
				{
					t = q;
					q = q->left;
				}
			}
			p = p->left;
		}
		RemoveKeyThangNam(l,thang,nam);
	}

	if (thang == 0 && ngay != 0 && nam != 0)
	{
		while (p != NULL)
		{
			t = p;
			q = p->left;
			while (q != NULL)
			{
				//if (q->left != NULL && q->data.chucvu_chu == cv)
				if (q->data.ngaythangnamsinh[0] == ngay && q->data.ngaythangnamsinh[2] == nam)
				{
					removeAfter(l, t);
					q = t->left;
				}
				else
				{
					t = q;
					q = q->left;
				}
			}
			p = p->left;
		}
		RemoveKeyNgayNam(l,ngay,nam);
	}

	if (nam == 0 && ngay != 0 && thang != 0)
	{
		while (p != NULL)
		{
			t = p;
			q = p->left;
			while (q != NULL)
			{
				//if (q->left != NULL && q->data.chucvu_chu == cv)
				if (q->data.ngaythangnamsinh[0] == ngay && q->data.ngaythangnamsinh[1] == thang)
				{
					removeAfter(l, t);
					q = t->left;
				}
				else
				{
					t = q;
					q = q->left;
				}
			}
			p = p->left;
		}
		RemoveKeyNgayThang(l,ngay,thang);
	}

	if (ngay == 0 && thang == 0)
	{
		while (p != NULL)
		{
			t = p;
			q = p->left;
			while (q != NULL)
			{
				//if (q->left != NULL && q->data.chucvu_chu == cv)
				if (q->data.ngaythangnamsinh[2] == nam)
				{
					removeAfter(l, t);
					q = t->left;
				}
				else
				{
					t = q;
					q = q->left;
				}
			}
			p = p->left;
		}
		RemoveKeyNam(l,nam);
	}

	if (ngay == 0 && nam == 0)
	{
		while (p != NULL)
		{
			t = p;
			q = p->left;
			while (q != NULL)
			{
				//if (q->left != NULL && q->data.chucvu_chu == cv)
				if (q->data.ngaythangnamsinh[1] == thang)
				{
					removeAfter(l, t);
					q = t->left;
				}
				else
				{
					t = q;
					q = q->left;
				}
			}
			p = p->left;
		}
		RemoveKeyThang(l,thang);
	}

	if (thang == 0 && nam == 0)
	{
		while (p != NULL)
		{
			t = p;
			q = p->left;
			while (q != NULL)
			{
				//if (q->left != NULL && q->data.chucvu_chu == cv)
				if (q->data.ngaythangnamsinh[0] == ngay)
				{
					removeAfter(l, t);
					q = t->left;
				}
				else
				{
					t = q;
					q = q->left;
				}
			}
			p = p->left;
		}
		RemoveKeyNgay(l,ngay);
	}

	if (ngay != 0 && thang != 0 && nam != 0)
	{
		while (p != NULL)
		{
			t = p;
			q = p->left;
			while (q != NULL)
			{
				//if (q->left != NULL && q->data.chucvu_chu == cv)
				if (q->data.ngaythangnamsinh[0] == ngay && q->data.ngaythangnamsinh[1] == thang && q->data.ngaythangnamsinh[2] == nam)
				{
					removeAfter(l, t);
					q = t->left;
				}
				else
				{
					t = q;
					q = q->left;
				}
			}
			p = p->left;
		}
		RemoveKeyNgayThangNam(l,ngay,thang,nam);
	}
}