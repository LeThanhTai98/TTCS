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


bool soSanhNgayThangNam(nhanvien data1 , nhanvien data2) {
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
	else if (sosanhten(data1.ten,data2.ten, data1.ho_va_ten , data2.ho_va_ten) <= 0) {
		return true;
	}
	return false;
}





void FrontBackSplit(tree_node* source, tree_node** frontRef, tree_node** backRef);

ostream& operator<<(ostream& os, const nhanvien& item);

linkList::linkList() { roots = NULL;last = NULL;type_sort = 0;max_ten = 11; max_luong = 13;max_chucvu = 11;max_ngay = 21;max_tongSoLuonPhanTu = 5; }

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
			if (type_sort == 1)

				do {
					if (ptr->data.luong == p->data.luong) {

						string ten1 = ptr->data.ten;
						string ten2 = p->data.ten;
						string hoten1 = ptr->data.ho_va_ten;
						string hoten2 = p->data.ho_va_ten;
						if (sosanhten(ten1, ten2, hoten1, hoten2) <= 0) {
							parent = ptr;
							ptr = ptr->left;
						}
						else {
							break;
						}
					}
					else
						if (ptr->data.luong > p->data.luong) {
							parent = ptr;
							ptr = ptr->left;
						}
						else {
							break;
						}

				} while (ptr != NULL);

				if (type_sort == 2)
					do {
						if (ptr->data.chucvu == p->data.chucvu) {

							string ten1 = ptr->data.ten;
							string ten2 = p->data.ten;
							string hoten1 = ptr->data.ho_va_ten;
							string hoten2 = p->data.ho_va_ten;
							if (sosanhten(ten1, ten2, hoten1, hoten2) <= 0) {
								parent = ptr;
								ptr = ptr->left;
							}
							else {
								break;
							}
						}
						else
							if (ptr->data.chucvu > p->data.chucvu) {
								parent = ptr;
								ptr = ptr->left;
							}
							else {
								break;
							}

					} while (ptr != NULL);


					if (type_sort == 3) {
						do {
							if (soSanhNgayThangNam(ptr->data, p->data))
							{
								parent = ptr;
								ptr = ptr->left;
							}
							else
							{
								break;
							}

						} while (ptr != NULL);



					}

					if (type_sort == 4) {
						do {
							string ten1 = ptr->data.ten;
							string ten2 = p->data.ten;
							string hoten1 = ptr->data.ho_va_ten;
							string hoten2 = p->data.ho_va_ten;
							if (sosanhten(ten1, ten2, hoten1, hoten2) <= 0) {
								parent = ptr;
								ptr = ptr->left;
							}
							else {
								break;
							}

						} while (ptr != NULL);
					}
					
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
	if (type_sort == 1) {
		if (a->data.luong == b->data.luong) {
			string ten1 = a->data.ten;
			string ten2 = b->data.ten;
			string hoten1 = a->data.ho_va_ten;
			string hoten2 = b->data.ho_va_ten;
	
			if (sosanhten(ten1, ten2, hoten1, hoten2 )<= 0) {
				result = a;

				result->left = SortedMerge(a->left, b, type_sort);
			}
			else {
				result = b;

				result->left = SortedMerge(a, b->left, type_sort);
			}
		}
		else
	 if (a->data.luong > b->data.luong) {
			result = a;

			result->left = SortedMerge(a->left, b, type_sort);

		    }
		    else {
			result = b;

			result->left = SortedMerge(a, b->left, type_sort);

		        }
	}
	// sort theo chuc vu so neu bang bang nhau sort theo ten
	if (type_sort == 2) {
		if (a->data.chucvu == b->data.chucvu) {
			string ten1 = a->data.ten;
			string ten2 = b->data.ten;
			string hoten1 = a->data.ho_va_ten;
			string hoten2 = b->data.ho_va_ten;

			if (sosanhten(ten1, ten2, hoten1, hoten2) <= 0) {
				result = a;

				result->left = SortedMerge(a->left, b, type_sort);
			}
			else {
				result = b;

				result->left = SortedMerge(a, b->left, type_sort);
			}
		}
		else
			if (a->data.chucvu > b->data.chucvu) {
			result = a;

			result->left = SortedMerge(a->left, b, type_sort);

		    }
		       else {
			result = b;

			result->left = SortedMerge(a, b->left, type_sort);

		       }
	}
	// sort theo ngay thang nam sinh neu bang bang nhau sort theo ten
	if (type_sort == 3) {

		if(soSanhNgayThangNam(a->data,b->data))
		{
			result = a;

			result->left = SortedMerge(a->left, b, type_sort);
		}
		else 
		{
			result = b;

			result->left = SortedMerge(a, b->left, type_sort);
		}
		
	}
	if (type_sort == 4) {
		string ten1 = a->data.ten;
		string ten2 = b->data.ten;
		string hoten1 = a->data.ho_va_ten;
		string hoten2 = b->data.ho_va_ten;

		if (sosanhten(ten1, ten2, hoten1, hoten2) <= 0) 
			{
				result = a;

				result->left = SortedMerge(a->left, b, type_sort);
			}
		else {
			result = b;

			result->left = SortedMerge(a, b->left, type_sort);
		}
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

void linkList::Sort(int const &type) {
	type_sort = type;
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

void linkList::setLast() {
	tree_node *current = roots;
	
	while (current != NULL) {
		if (current->left == NULL) last = current;
		current = current->left;

	}
}