
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

using namespace std;



ostream& operator<<(ostream& os, const nhanvien& item)
{
	os << item.ho_va_ten << '|' << item.luong << '|' << item.chucvu << "" << item.chucvu_chu << '|' << item.ngaythangnamsinh[0] << '/' << item.ngaythangnamsinh[1]
		<< '/' << item.ngaythangnamsinh[2] << '\n';
	return os;
}

string trim(const string& str)
{
	size_t first = str.find_first_not_of(' ');
	if (string::npos == first)
	{
		return str;
	}
	size_t last = str.find_last_not_of(' ');
	return str.substr(first, (last - first + 1));
}

vector<string> tach(string str , char kyHieuBoQua ) {
	stringstream mangCanTach(str);
	vector<string> listThanhPhanTach;

	string thanhPhanTach;

	

	while (getline(mangCanTach, thanhPhanTach, kyHieuBoQua))
	{
		listThanhPhanTach.push_back(thanhPhanTach);
		
	}

	return listThanhPhanTach;
}
void reset(nhanvien &nhan) {
	    nhan.chucvu_chu = "";
		nhan.ho_va_ten = "";
		nhan.ngaythangnamsinh[0] = 0;
		nhan.ngaythangnamsinh[1] = 0;
		nhan.ngaythangnamsinh[2] = 0;
		nhan.luong = 0;
}

string layTen(string nhan) {
	int dodaichuoi = nhan.size() ;
	int i;
	for ( i = dodaichuoi; i > 0; i--) {
		if (nhan[i] == ' ') break;
	}
	if (nhan[i] == ' ') i++;
	return nhan.substr(i,dodaichuoi);

}

string tolower(string dauVao) {
	for (int i = 0; i < dauVao.size();i++) {
		if (dauVao[i] >= 'A' and dauVao[i] <= 'Z')
			dauVao[i] = dauVao[i] + 32;
	}
	return dauVao;
}

bool coPhaiLaSo(string dauVao) {
	char* p;
	string kt;
	kt += (dauVao[0] >= 'A' and dauVao[0] <= 'Z') ? dauVao[0] + 32 : dauVao[0];
	kt += (dauVao[1] >= 'A' and dauVao[1] <= 'Z') ? dauVao[1] + 32 : dauVao[1];
	kt += (dauVao[2] >= 'A' and dauVao[2] <= 'Z') ? dauVao[2] + 32 : dauVao[2];

	if (kt.compare("nan") != 0 && kt.compare("inf") != 0) {
		long converted = strtod(dauVao.c_str(), &p);

		if (*p) {
			return false;
		}
		else {
			return true;
		}
	}
	else return false;
}

int nhapfile(string duongDanFile, linkList &root , vector< pair<int, string> > &chuc_nhanvien ) {
	nhanvien nhanv;
	string line;
	ifstream myfile(duongDanFile);
	string temps;
	double  temp[10];
	int i = 0;
	int dem = 0;
	if (myfile.is_open())
	{ // doc chuc vu   xem example.txt 
		while (!myfile.eof()) {
			char c;
			myfile.get(c);
			// bo qua ki tu cho toi khi gap | 
			if (c == '|') {
				string chucvu_chu = "";
				dem = 0;
				while (!myfile.eof()) {
					// doc toi khi gap |
					myfile.get(c);
					if (c == '|') {
						chucvu_chu = trim(chucvu_chu);
						
						temps = "";
						while (!myfile.eof()) {
							myfile.get(c);
							// doc toi khi gap |
							if (c == '|') {
								int chucvu_so = 0;
								int doiSangInt = stoi(temps);
								temp[i] = doiSangInt;
								chucvu_so = doiSangInt;
								chuc_nhanvien.push_back( make_pair(chucvu_so,chucvu_chu));
								i++;
								dem++;
								break;
							}
							temps += c;
						}

					}
					else { chucvu_chu += c; }
					if (dem == 1) break;
				}
			}
			// gap + ngung doc|
			if (c == '+') break;
		}
		int soLuongChucVu = i;
		
		// doc thu tu ho va ten  | luong | chuc vu | ngay thang nam sinh |
		int dem_break = 0;
		string tieuDe = "";
		int kiemtra_docxong_1_tieude = 0;
		int thuTuTieuDe[4];
		int thuTutieuDe_dem = 0;
		while (!myfile.eof()) {
			char c;
			myfile.get(c);
			if (c == '|') {
				dem_break++;
				kiemtra_docxong_1_tieude = 1;
			}
			else tieuDe += c;
			if (kiemtra_docxong_1_tieude == 1) {

				tieuDe = trim(tieuDe);
				
				if (tieuDe.compare("ho va ten") == 0) {
					thuTuTieuDe[thuTutieuDe_dem] = 1;
					thuTutieuDe_dem++;
				}
				else if (tieuDe.compare("chuc vu") == 0) {
					thuTuTieuDe[thuTutieuDe_dem] = 2;
					thuTutieuDe_dem++;
				}
				else if (tieuDe.compare("ngay thang nam sinh") == 0) {
					thuTuTieuDe[thuTutieuDe_dem] = 3;
					thuTutieuDe_dem++;
				}
				else if (tieuDe.compare("he so luong") == 0) {
					thuTuTieuDe[thuTutieuDe_dem] = 4;
					thuTutieuDe_dem++;
				}
				tieuDe = "";
				
				kiemtra_docxong_1_tieude = 0;
			}
			if (dem_break == 5) break;
		}
		
		
		//doc nhan vien 
		int kt_duLieuHopLe = 0;
		while (!myfile.eof()) {
			char c;
			reset(nhanv);
			myfile.get(c);

			if (c == '|') {
				dem = 0;
				for (int k = 0; k < 4; k++)
				{

					if (thuTuTieuDe[k] == 1)while (!myfile.eof()) {
						myfile.get(c);
						if (c == '|') {
							dem++;
						}
						else { nhanv.ho_va_ten += c; }
						if (dem == 1) { //xoa khoan trang dau va cuoi cua ten 
							nhanv.ho_va_ten = trim(nhanv.ho_va_ten);
							// lay ten nhan ra 
							string ten = layTen(nhanv.ho_va_ten);

							nhanv.ten = ten;

							break;
						}
					}

					dem = 0; string tam = "";
					if (thuTuTieuDe[k] == 4)while (!myfile.eof()) {
						myfile.get(c);
						if (c == '|') {
							dem++;
						}
						else { tam += c; }
						if (dem == 1) {
							// chuyen string sang double
							tam = trim(tam);
							char* p;
							long converted = strtod(tam.c_str(), &p);
							if (*p) {
								kt_duLieuHopLe++;
								return 0;
								
							}
							else {
								double a = stod(tam);
								nhanv.luong = a;
								break;
							}
							
						}
					}

					dem = 0;
					if (thuTuTieuDe[k] == 2)while (!myfile.eof()) {
						myfile.get(c);
						if (c == '|') {

							nhanv.chucvu_chu = trim(nhanv.chucvu_chu);
							for (int j = 0;j < soLuongChucVu;j++) {
								if (nhanv.chucvu_chu.compare(chuc_nhanvien[j].second) == 0) { nhanv.chucvu = chuc_nhanvien[j].first; break; }
							}

							dem++;
						}
						else { nhanv.chucvu_chu += c; }
						if (dem == 1) break;
					}

					dem = 0; tam = "";
					if (thuTuTieuDe[k] == 3)while (!myfile.eof()) {
						myfile.get(c);
						if (c == '|') {
							dem++;
						}
						else { tam += c; }
						if (dem == 1) {

							vector<string> my = tach(tam, '/');
							// chuyen string sang int
							
							my[0] = trim(my[0]);
							my[1] = trim(my[1]);
							my[2] = trim(my[2]);
							char* p;
							//lay ngay sinh 
							long converted = strtod(my[0].c_str(), &p);
							if (*p) {
								kt_duLieuHopLe++;
								return 0;

							}
							else {
								int chuyen = stoi(my[0]);
								nhanv.ngaythangnamsinh[0] = chuyen;
							
							}
							// lay thang sinh 
							 converted = strtod(my[1].c_str(), &p);
							if (*p) {
								kt_duLieuHopLe++;
								return 0;

							}
							else {
								int chuyen = stoi(my[1]);
								nhanv.ngaythangnamsinh[1] = chuyen;

							}
							//lay nam sinh 
							 converted = strtod(my[2].c_str(), &p);
							if (*p) {
								kt_duLieuHopLe++;
								return 0;

							}
							else {
								int chuyen = stoi(my[2]);
								nhanv.ngaythangnamsinh[2] = chuyen;

							}
							
							break;

						}
					}
					
				}
				
			}
			
			if (nhanv.ho_va_ten != "") {
				// dua nhan vien dc vao link list
				root.insert(nhanv);

			}
		}

		myfile.close();
		return 1;
	}
	
	else {
		
		return 0;
	}
}




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
	int nhapFileThanhCong = nhapfile(a, root,chuc_nhanvien);
	
	int dungChuongTring = 0;
	root.show_1();
	string nguoiDungnhap;
	if (nhapFileThanhCong == 1) {
		while (dungChuongTring >= 0) {

			cout << "\n\n\n\n\n\n\n\n";

			cout << "nhap " << endl;
			cout << "1. " << " de sap xep " << endl;
			cout << "2. " << " de them nhan vien " << endl;
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




