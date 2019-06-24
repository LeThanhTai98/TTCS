
#include "pch.h"
#include <iostream>
#include <string>
#include <string.h>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <vector>
#include "linkList.h"
#include "struct.h"
#include "xuatNhapFile.h"
using namespace std;



ostream& operator<<(ostream& os, const nhanvien& item)
{
	os << item.ho_va_ten << '|' << item.luong << '|' << item.chucvu << "" << item.chucvu_chu << '|' << item.ngaythangnamsinh[0] << '/' << item.ngaythangnamsinh[1]
		<< '/' << item.ngaythangnamsinh[2] << '\n';
	return os;
}





// Kiểm tra dữ liệu nhập trước khi chèn
void chenNhanvien(nhanvien &nhan, vector< pair<int, string> > chuc_nhanvien) {

	cout << " nhap thong tin nhan vien " << endl;
	cout << " ho va ten " << endl;
	
	cin.ignore(0);

	getline(cin, nhan.ho_va_ten);
	nhan.ho_va_ten = trim(nhan.ho_va_ten);

	cout << "trim " << nhan.ho_va_ten << endl;

	nhan.ten = layTen(nhan.ho_va_ten);
	cout << nhan.ten << endl;
	cout << " chuc vu " << endl;
	int check = 0;

	
	do {
		cin.ignore(0);
		cout << endl;
		getline(cin, nhan.chucvu_chu);
		int kt_chucVuHopLe = 0;
		nhan.chucvu_chu = trim(nhan.chucvu_chu);
		int soLuongChucVu = chuc_nhanvien.size();
		for (int j = 0;j < soLuongChucVu;j++) {
			if (nhan.chucvu_chu.compare(chuc_nhanvien[j].second) == 0) { nhan.chucvu = chuc_nhanvien[j].first; kt_chucVuHopLe = 1; break; }
		}
		if (kt_chucVuHopLe == 0) cout << " chuc vu khong phu hop vui long nhap lai ";
		else break;
	} while (check == 0);

	cout << endl;

	cout << "nhap ngay thang nam sinh " << endl;

	cout << "nhap nam " << endl;

	
	do {
		cin.ignore(0);
		cout << endl;
		string namSinh;
		getline(cin, namSinh);

		namSinh = trim(namSinh);
		
		if (coPhaiLaSo(namSinh)) {
			
			int chuyen = stoi(namSinh);
			nhan.ngaythangnamsinh[2] = chuyen;
			break;
			

		}
		else {
			cout << " du nhieu nhap ko phu hop nhap xin nhap lai ";
		}
		
		
	} while (check == 0);
	
	int namNhuan = 0;
	if (((nhan.ngaythangnamsinh[2] % 4 == 0) && (nhan.ngaythangnamsinh[2] % 100 != 0)) || (nhan.ngaythangnamsinh[2] % 400 == 0))
		namNhuan = 1;


	cout << " nhap thang " << endl;


	do {
		cin.ignore(0);
		cout << endl;
		string thangSinh;
		getline(cin, thangSinh);

		thangSinh = trim(thangSinh);
		
	
	
		if (coPhaiLaSo(thangSinh)) {
			
			int chuyen = stoi(thangSinh);
			if (chuyen > 0 and chuyen < 13) {
				nhan.ngaythangnamsinh[1] = chuyen;
				break;
			}
			else cout << " du nhieu nhap ko phu hop nhap xin nhap lai ";
		}
		else {
			cout << " du nhieu nhap ko phu hop nhap xin nhap lai ";
		}


	} while (check == 0);


	cout << " ngay " << endl;
	int kt_ngay = 0;
	if (nhan.ngaythangnamsinh[1] == 2 and namNhuan == 1)// 29 ngay 
		kt_ngay = 1;
	else if (nhan.ngaythangnamsinh[1] == 2 and namNhuan == 0) //28 ngay 
		kt_ngay = 2;
	else if (nhan.ngaythangnamsinh[1] == 1 or nhan.ngaythangnamsinh[1] == 3 or nhan.ngaythangnamsinh[1] == 5 or nhan.ngaythangnamsinh[1] == 7 or nhan.ngaythangnamsinh[1] == 8 or nhan.ngaythangnamsinh[1] == 10 or nhan.ngaythangnamsinh[1] == 12)
		kt_ngay = 3; //31 ngay 
	
	
	do {
		cin.ignore(0);
		cout << endl;
		string thangSinh;
		getline(cin, thangSinh);

		thangSinh = trim(thangSinh);

		int kt_ngaySinhHopLe = 0;

		if (coPhaiLaSo(thangSinh)) {

			int chuyen = stoi(thangSinh);
			switch (kt_ngay)
			{
			case 0 :
				if (chuyen > 0 && chuyen <= 30) kt_ngaySinhHopLe = 1;
				break;
			case 1 :
				if (chuyen > 0 && chuyen <= 29) kt_ngaySinhHopLe = 1;
				break;
			case 2 :
				if (chuyen > 0 && chuyen <= 28) kt_ngaySinhHopLe = 1;
				break;
			case 3 : 
				if (chuyen > 0 && chuyen <= 31) kt_ngaySinhHopLe = 1;
			default:
				break;
			}
			if (kt_ngaySinhHopLe == 1) {
				nhan.ngaythangnamsinh[0] = chuyen;
				break;
			}
			else cout << " du nhieu nhap ko phu hop nhap xin nhap lai ";
		}
		else {
			cout << " du nhieu nhap ko phu hop nhap xin nhap lai ";
		}


	} while (check == 0);

	cout << endl;
	cout << " he so luong ";

	do {
		cin.ignore(0);
		cout << endl;
		string luong;
		getline(cin, luong);

		luong = trim(luong);

		if (coPhaiLaSo(luong)) {

			double chuyen = stod(luong);
			nhan.luong = chuyen;
			break;


		}
		else {
			cout << " du nhieu nhap ko phu hop nhap xin nhap lai ";
		}


	} while (check == 0);
	cout << endl;

}

int main()
{
	linkList root;
	

	// cai dong duoi nay de nhap file 
	nhanvien nhanv;
	string a;
	// nhap vao duong dan den file
	cout << "nhap duong dan den file " << endl;
	getline(cin, a);
	
	int b = a.length();
	vector< pair<int, string> > chuc_nhanvien;
	
	xuatNhapFile nhapxuatFile;
	int nhapFileThanhCong = nhapxuatFile.nhapFile(a, root,chuc_nhanvien);
	
	int dungChuongTring = 0;
	root.show_1();
	string nguoiDungnhap;
	if (nhapFileThanhCong == 1) {
		while (dungChuongTring >= 0) {

			cout << "\n\n\n\n\n\n\n\n";

			cout << "nhap " << endl;
			cout << "1. " << " de sap xep " << endl;
			cout << "2. " << " de them nhan vien " << endl;
			cout << "3. " << " de xoa nhan vien " << endl;
			cout << "4. " << " de tim kiem nhan vien " << endl;
			cout << "5. " << " in file" << endl;

			getline(cin, nguoiDungnhap);
			if (nguoiDungnhap.size() == 1) {
				switch (nguoiDungnhap[0])
				{
				case '1':
				{
					cout << "nhap kieu sap xep " << endl;
					cout << "1. " << " theo luong " << endl;
					cout << "2. " << " theo chuc vu vu" << endl;
					cout << "3. " << " theo ngay thang nam sinh " << endl;
					cout << "4. " << " theo ho ten" << endl;
					string kieuSort;
					cout << endl;
					getline(cin, kieuSort);
					int kt_kieuSort = 0;
					if (kieuSort.size() == 1) {
						switch (kieuSort[0])
						{
						case '1':
							kt_kieuSort = 1;
							break;
						case '2':
							kt_kieuSort = 2;
							break;
						case '3':
							kt_kieuSort = 3;
							break;
						case '4':
							kt_kieuSort = 4;
						default:
							break;
						}
					}
					if (kt_kieuSort == 0) cout << " lua chon khong hop le ";
					else {
						root.Sort(kt_kieuSort);
						root.show_1();
						
					}
				}
				break;
				case '2': {
					nhanvien nhan;
					chenNhanvien(nhan, chuc_nhanvien);
					root.insert(nhan);

					root.show_1();
				}
						  break;
				case '3': {
					cout << "Chuc nang nay chua duoc su li!";
				}
						  break;
				case '4': {
					string nhap;
					cout << "nhap kieu tim kiem " << endl;
					cout << "1. " << " theo ho ten " << endl;
					cout << "2. " << " theo chuc vu" << endl;
					cout << "3. " << " theo he so luong" << endl;
					cout << "4. " << " theo ngay thang nam sinh " << endl;
					getline(cin,nhap);
					switch (nhap[0])
					{
					case '1':
					{
						string hoten;
						cout << "Hay nhap ho va ten: ";
						getline(cin,hoten);
						root.searchHoTen(hoten);
					}
						break;
					case '2':
					{
						cout << "Hay nhap chuc vu: " << endl;
						string chucvu;
						getline(cin,chucvu);
						root.searchChucVu(chucvu);
					}
						break;
					case '3':
					{
						double heso;
						cout << "Hay nhap he so luong:" << endl;
						cin >> heso;
						root.searchLuong(heso);
						//root.show_1();

					}
						break;
					case '4':
					{
						int ngay,thang,nam;
						cout << "Nhap ngay: ";
						cin >> ngay;
						cout << "Nhap thang: ";
						cin >> thang;
						cout << "Nhap nam: ";
						cin >> nam;
						root.searchNTN(ngay,thang,nam);

					}
					default:
						break;
					}
				}
						  break;
				case '5': {
					root.in_file();
					cout << " file da in xin kiem o thu muc chuong trinh ";
				}
						  break;
				default:
					cout << " lua chon khong hop le ";
					break;
				}
				
			}
			else cout << " lua chon khong hop le ";
			cout << "dung chuong trinh bam -1 , tiep tuc bam cac so khac" << endl;
			cin >> dungChuongTring;

			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');


		}
	}
	else { cout << " du lieu khong hop le hoac khong mo duoc file "; }
	return 0;
}




