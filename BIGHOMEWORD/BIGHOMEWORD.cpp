
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
#include <ctime>
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
	cout << " nhap ho va ten " << endl;
	int check = 0;
	do {
		int ktTenHopLe = 0;
		cin.ignore(0);
		getline(cin, nhan.ho_va_ten);
		nhan.ho_va_ten = trim(nhan.ho_va_ten);

		if (nhan.ho_va_ten[0] == ' ') { cout << "ten khong phu hop xin nhap lai " << endl; continue; }
		if (nhan.ho_va_ten.size() > 150) { cout << "ten khong phu hop xin nhap lai " << endl; continue; }
		nhan.ten = layTen(nhan.ho_va_ten);
		
		for (int i = 0;i < nhan.ho_va_ten.size();i++) {
			if (i != nhan.ho_va_ten.size() ) 
				if (nhan.ho_va_ten[i] == ' ' && nhan.ho_va_ten[i + 1] == ' ') {
					ktTenHopLe = 1;
					break;
				}

			if ((nhan.ho_va_ten[i] < 'A' || nhan.ho_va_ten[i] > 'Z') && (nhan.ho_va_ten[i] < 'a' || nhan.ho_va_ten[i] > 'z') && nhan.ho_va_ten[i] != ' ')
			{
				ktTenHopLe = 1;
				break;
			}
		}
		if (nhan.ho_va_ten.compare(nhan.ten) != 0 && ktTenHopLe == 0 && nhan.ten.size() != 0) break;

		cout << "ten khong phu hop xin nhap lai " << endl;
	} while (check == 0);
	cout << endl;
	cout << " nhap chuc vu " << endl;
	cout << endl;
	cout << "(chuc vu hien co : " << endl;
	for (int j = 0; j < chuc_nhanvien.size();j++) {
		cout << "  " << chuc_nhanvien[j].second << endl;
	}
	cout << ")"<<endl;
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
	struct tm newtime;
	time_t now = time(0);
	localtime_s(&newtime, &now);
	int Year = 1900 + newtime.tm_year;
	
	do {
		cin.ignore(0);
		cout << endl;
		string namSinh;
		getline(cin, namSinh);

		namSinh = trim(namSinh);
		
		if (coPhaiLaSo(namSinh) && stod(namSinh) - abs(stoi(namSinh)) == 0) {
			
			int chuyen = stoi(namSinh);
			if (Year - chuyen >= 18 && Year - chuyen <= 60) {
				nhan.ngaythangnamsinh[2] = chuyen;
				break;
			}
			else cout << " tuoi nhan vien khong hop le xin nhap lai";

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
		
	
	
		if (coPhaiLaSo(thangSinh) && stod(thangSinh) - abs(stoi(thangSinh)) == 0) {
			
			int chuyen = stoi(thangSinh);
			if (chuyen > 0 && chuyen < 13) {
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
	if (nhan.ngaythangnamsinh[1] == 2 && namNhuan == 1)// 29 ngay 
		kt_ngay = 1;
	else if (nhan.ngaythangnamsinh[1] == 2 && namNhuan == 0) //28 ngay 
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

		if (coPhaiLaSo(thangSinh) && stod(thangSinh) - abs(stoi(thangSinh)) == 0) {

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
			if (nhan.luong > 0 && nhan.luong < 50)break;
			else cout << " du nhieu nhap ko phu hop nhap xin nhap lai " <<endl;
		}
		else {
			cout << " du nhieu nhap ko phu hop nhap xin nhap lai " << endl;
		}


	} while (check == 0);
	cout << endl;

}

string ktHoTen(string ten)
{
	cout << "Hay nhap ho va ten: ";
	string t;
	int check = 0;
	do {
		int ktTenHopLe = 0;
		cin.ignore(0);
		getline(cin,ten);
		ten = trim(ten);

		if (ten[0] == ' ') { cout << "ten khong phu hop xin nhap lai " << endl; continue; }

		t = layTen(ten);

		for (int i = 0;i < ten.size();i++) {
			if (i != ten.size())
				if (ten[i] == ' ' && ten[i + 1] == ' ') {
					ktTenHopLe = 1;
					break;
				}

			if ((ten[i] < 'A' || ten[i] > 'Z') && (ten[i] < 'a' || ten[i] > 'z') && ten[i] != ' ')
			{
				ktTenHopLe = 1;
				break;
			}
		}
		if (ktTenHopLe == 0 && t.size() != 0) break;

		cout << "ten khong phu hop xin nhap lai " << endl;
	} while (check == 0);
	return ten;
}

string ktChucVu(string chucvu, vector< pair<int, string> > chuc_nhanvien)
{
	int check = 0;
	cout << " nhap chuc vu " << endl;
	cout << endl;
	cout << "(chuc vu hien co : " << endl;
	for (int j = 0; j < chuc_nhanvien.size();j++) {
		cout << "  " << chuc_nhanvien[j].second << endl;
	}
	cout << ")" << endl;
	do {
		cin.ignore(0);
		cout << endl;
		cout << "Hay nhap chuc vu: ";
		getline(cin, chucvu);
		int kt_chucVuHopLe = 0;
		chucvu = trim(chucvu);
		int soLuongChucVu = chuc_nhanvien.size();
		for (int j = 0;j < soLuongChucVu;j++) {
			if (chucvu.compare(chuc_nhanvien[j].second) == 0) 
			{
				chucvu = chuc_nhanvien[j].second;
				kt_chucVuHopLe = 1; 
				break; 
			}
		}
		if (kt_chucVuHopLe == 0) cout << " chuc vu khong phu hop vui long nhap lai ";
		else break;
	} while (check == 0);
	return chucvu;
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
	root.show_1();
	string dungChuongTring = " ";
	
	string nguoiDungnhap;
	if (nhapFileThanhCong == 1) {
		while ( trim(dungChuongTring).compare("-1") != 0) {

			cout << "\n\n\n";

			cout << "nhap " << endl;
			cout << "0. " << " de nhap file danh sach " << endl;
			cout << "1. " << " de sap xep " << endl;
			cout << "2. " << " de them nhan vien " << endl;
			cout << "3. " << " de xoa nhan vien " << endl;
			cout << "4. " << " de tim kiem nhan vien " << endl;
			cout << "5. " << " in file" << endl;
			cout << "6. " << " ket thuc chuong trinh" << endl;
			getline(cin, nguoiDungnhap);
			if (nguoiDungnhap.size() == 1) {
				switch (nguoiDungnhap[0])
				{
				case '0':
				{
					nhanvien nhanv;
					string a;
					// nhap vao duong dan den file
					cout << "nhap duong dan den file " << endl;
					getline(cin, a);

					int b = a.length();
					linkList temp;
					vector< pair<int, string> > temp_chucvu;

					xuatNhapFile nhapxuatFile;
					int nhapFileThanhCong = nhapxuatFile.nhapFile(a, temp, temp_chucvu);
					if (nhapFileThanhCong == 1) {
						root.deleteList();
						chuc_nhanvien.clear();
						int nhapFileThanhCong = nhapxuatFile.nhapFile(a, root, chuc_nhanvien);
						root.show_1();

					}
					else { cout << " du lieu khong hop le hoac khong mo duoc file " << endl; }
				}
 
				break;
				case '1':
				{
					string thuTuSort;
					cout << "nhap thu tu sap xep (mac dinh giam dan) " << endl;
					cout << "1. " << " giam dan " << endl;
					cout << "2. " << " tang dan " << endl;
					getline(cin, thuTuSort);
					int thuTu = 1;
					if (thuTuSort.size() == 1) {
						switch (thuTuSort[0])
						{

						case '2':thuTu = 2;
							break;
						default:
							break;
						}
					}
					cout << endl << endl;
					string kieuSort = "0";

					cout << "nhap kieu sap xep " << endl;
					cout << "1. " << " theo luong " << endl;
					cout << "2. " << " theo chuc vu " << endl;
					cout << "3. " << " theo ngay thang nam sinh " << endl;
					cout << "4. " << " theo ho ten" << endl;

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
					if (kt_kieuSort == 0) cout << " lua chon kieu sap xep khong hop le " << endl;
					else {
						root.Sort(kt_kieuSort, thuTu);
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
					string kieuDelete;
					cout << "nhap kieu xoa " << endl;
					cout << "1. " << " theo ho ten " << endl;
					cout << "2. " << " theo chuc vu" << endl;
					cout << "3. " << " theo he so luong" << endl;
					cout << "4. " << " theo ngay thang nam sinh " << endl;
					getline(cin, kieuDelete);
					switch (kieuDelete[0])
					{
					case '1':
					{
						string hoten;
						//getline(cin,hoten);
						hoten = ktHoTen(hoten);
						root.deleteHoTen(root,hoten);
						root.show_1();
						cout << endl;

					}
					break;
					case '2':
					{
						string chucvu;
						//getline(cin, chucvu);
						chucvu = ktChucVu(chucvu,chuc_nhanvien);
						root.deleteChucvu(root,chucvu);
						root.show_1();
						cout << endl;

					}
					break;
					case '3':
					{
						double heso;
						while (1==1)
						{
							string heso1;
							cout << "Hay nhap he so luong:" << endl;
							getline(cin,heso1);
							if (coPhaiLaSo(heso1) && stod(heso1) > 0 && stod(heso1)<50)
							{
								heso = stod(heso1);
								
								break;
							}
							else
							{
								cout << "Du lieu khong phu hop, xin nhap lai"<<endl;
							}
						
						}
						root.deleteLuong(root,heso);
						root.show_1();
						cout << endl;

					}
					break;
					case '4':
					{
						int ngay, thang, nam;
						cout << "(nhap 0 de bo qua)" << endl;
						while (1 == 1)
						{
						
							string ngay1;
							cout << "Hay nhap ngay:";
							cin >> ngay1;
							if (coPhaiLaSo(ngay1) && stod(ngay1) - abs(stoi(ngay1)) == 0 && stod(ngay1)<=31)
							{
								ngay = stoi(ngay1);
								break;
							}
							else
							{
								cout << "Du lieu khong hop le, xin nhap lai!" << endl;
							}
						}
						while (1 == 1)
						{
							string thang1;
							cout << "Hay nhap thang:";
							cin >> thang1;
							if (coPhaiLaSo(thang1) && stod(thang1) - abs(stoi(thang1)) == 0 && stod(thang1) <=12 )
							{
								thang = stoi(thang1);
								break;
							}
							else
							{
								cout << "Du lieu khong hop le, xin nhap lai!" << endl;
							}
						}
						while (1 == 1)
						{
							string nam1;
							cout << "Hay nhap nam:";
							cin >> nam1;
							if (coPhaiLaSo(nam1) && stod(nam1) - abs(stoi(nam1)) == 0 && stod(nam1) <= 2019)
							{
								nam = stoi(nam1);
								break;
							}
							else
							{
								cout << "Du lieu khong hop le, xin nhap lai!" << endl;
							}
						}
						root.deleteNgaySinh(root,ngay, thang, nam);
						root.show_1();
						cout << endl;

					}
					default:
						break;
					}
				}
						  break;
				case '4': {
					string kieuSearch;
					cout << "nhap kieu tim kiem " << endl;
					cout << "1. " << " theo ho ten " << endl;
					cout << "2. " << " theo chuc vu" << endl;
					cout << "3. " << " theo he so luong" << endl;
					cout << "4. " << " theo ngay thang nam sinh " << endl;
					getline(cin,kieuSearch);
					switch (kieuSearch[0])
					{
					case '1':
					{
						string hoten;
						/*cout << "Hay nhap ho va ten: ";
						getline(cin,hoten);*/
						hoten = ktHoTen(hoten);
						root.searchHoTen(hoten);
						cout << endl;
					}
						break;
					case '2':
					{
						//cout << "Hay nhap chuc vu: " << endl;
						string chucvu;
						//getline(cin,chucvu);
						chucvu = ktChucVu(chucvu,chuc_nhanvien);
						root.searchChucVu(chucvu);
						cout << endl;
					}
						break;
					case '3':
					{
						double heso;
						while (1 == 1)
						{
							string heso1;
							cout << "Hay nhap he so luong:" << endl;
							getline(cin,heso1);
							if (coPhaiLaSo(heso1) && stod(heso1)>0 && stod(heso1)<50)
							{
								heso = stod(heso1);
								break;
							}
							else
							{
								cout << "Du lieu khong phu hop, xin nhap lai" << endl;
							}
						}
						root.searchLuong(heso);
						//root.show_1();
						cout << endl;

					}
						break;
					case '4':
					{
						cout << "(nhap 0 de bo qua)" << endl;
						int ngay,thang,nam;
						while (1 == 1)
						{

							string ngay1;
							cout << "Hay nhap ngay:";
							cin >> ngay1;
							if (coPhaiLaSo(ngay1) && stod(ngay1) - abs(stoi(ngay1)) == 0 && stod(ngay1)<=31)
							{
								ngay = stoi(ngay1);
								break;
							}
							else
							{
								cout << "Du lieu khong hop le, xin nhap lai!" << endl;
							}
						}
						while (1 == 1)
						{
							string thang1;
							cout << "Hay nhap thang:";
							cin >> thang1;
							if (coPhaiLaSo(thang1) && stod(thang1) - abs(stoi(thang1)) == 0 && stod(thang1)<=12)
							{
								thang = stoi(thang1);
								break;
							}
							else
							{
								cout << "Du lieu khong hop le, xin nhap lai!" << endl;
							}
						}
						while (1 == 1)
						{
							string nam1;
							cout << "Hay nhap nam:";
							cin >> nam1;
							if (coPhaiLaSo(nam1) && stod(nam1) - abs(stoi(nam1)) == 0 && stod(nam1)<=2019)
							{
								nam = stoi(nam1);
								break;
							}
							else
							{
								cout << "Du lieu khong hop le, xin nhap lai!" << endl;
							}
						}
						/*cout << "Nhap ngay: ";
						cin >> ngay;
						cout << "Nhap thang: ";
						cin >> thang;
						cout << "Nhap nam: ";
						cin >> nam;*/
						root.searchNTN(ngay,thang,nam);
						cout << endl;

					}
					default:
						break;
					}
				}
						  break;
				case '5': {
					root.in_file();
					cout << " file da in xin kiem o thu muc chuong trinh "<<endl;
				}
						  break;
				case '6': {
					return 0;
				}
						  break;
				default:
					cout << " lua chon khong hop le "<<endl;
					break;
				}
				
			}
			else cout << " lua chon khong hop le ";
			cout << "dung chuong trinh bam -1 , tiep tuc bam cac so khac" << endl;
			getline(cin, dungChuongTring);
			/*cin >> dungChuongTring;

			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
*/

		}
	}
	else { cout << " du lieu khong hop le hoac khong mo duoc file "<<endl; }
	return 0;
}




