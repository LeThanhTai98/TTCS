#include "pch.h"
#include "xuatNhapFile.h"


xuatNhapFile::xuatNhapFile()
{
}


xuatNhapFile::~xuatNhapFile()
{
}


string trim(const string& str)
{   

	
	int  first = -1;
	for (int i = 0; i < str.size() ; i++) {
		if (str[i] != ' ') { first = i; break; }
	}

	if (-1 == first)
	{
		return str;
	}
	int last = str.size();
	for (int i = str.size() - 1; i >= 0; i--) {

		if (str[i] != ' ') { last = i; break; }
	}
	string re = str.substr(first, (last - first + 1));
	return re;
}

vector<string> tach(string str, char kyHieuBoQua) {
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
	int dodaichuoi = nhan.size();
	int i;
	for (i = dodaichuoi; i > 0; i--) {
		if (nhan[i] == ' ') break;
	}
	if (nhan[i] == ' ') i++;
	return nhan.substr(i, dodaichuoi);

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
	int soPhanTu = dauVao.size();
	if (soPhanTu > 3) soPhanTu = 3;
	for (int i = 0;i < soPhanTu; i++) {
		kt += (dauVao[i] >= 'A' and dauVao[i] <= 'Z') ? dauVao[i] + 32 : dauVao[i];
	}


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

int xuatNhapFile::nhapFile(string duongDanFile, linkList &root, vector< pair<int, string> > &chuc_nhanvien) {
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
								chuc_nhanvien.push_back(make_pair(chucvu_so, chucvu_chu));
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
			// gap + ngung doc chuc vu 
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
							
							if (coPhaiLaSo(tam)) {
							
								double a = stod(tam);
								nhanv.luong = a;
								break;
							}
							else {

								kt_duLieuHopLe++;
								return 0;
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
							
							//lay ngay sinh 
							
							if (coPhaiLaSo(my[0])) {
								
								int chuyen = stoi(my[0]);
								nhanv.ngaythangnamsinh[0] = chuyen;
							}
							else {

								kt_duLieuHopLe++;
								return 0;

							}
							// lay thang sinh 
							
							if (coPhaiLaSo(my[1])) {
								
								int chuyen = stoi(my[1]);
								nhanv.ngaythangnamsinh[1] = chuyen;
							}
							else {

								kt_duLieuHopLe++;
								return 0;

							}
							//lay nam sinh 
							
							if (coPhaiLaSo(my[2])) {
								int chuyen = stoi(my[2]);
								nhanv.ngaythangnamsinh[2] = chuyen;
							}
							else {

								kt_duLieuHopLe++;
								return 0;

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
