#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;
const int Cn = 50;
const char Crez[] = "rez.txt";
struct Mokiniai {
	string vardas;
	double mokinioVidurkis;
};
struct Klases {
	Mokiniai duomenys[Cn];
	int kiekMokiniu;
	double klasesVidurkis;
};
void rikiavimas(Klases &sar);
void ivedimas(Klases sar[]);
void isvedimas(const char fv[], Klases sar[],Klases nSar);
void klasesVidurkioSkaiciavimas(Klases &sar);
void mokiniuSalinimas(Klases &sar);
void bendriMokiniai(Klases &sar, Klases &nSar);
int main() {
	Klases kiekvienaKlase[4];
	Klases sujungtaKlase;
	sujungtaKlase.kiekMokiniu = 0;
	ivedimas(kiekvienaKlase);
	for (int i = 0; i < 4; i++) {
		klasesVidurkioSkaiciavimas(kiekvienaKlase[i]);
		mokiniuSalinimas(kiekvienaKlase[i]);
		rikiavimas(kiekvienaKlase[i]);
		bendriMokiniai(kiekvienaKlase[i], sujungtaKlase);
	}
	klasesVidurkioSkaiciavimas(sujungtaKlase);
	mokiniuSalinimas(sujungtaKlase);
	rikiavimas(sujungtaKlase);
	isvedimas(Crez, kiekvienaKlase,sujungtaKlase);
	return 0;
}

void ivedimas(Klases sar[]) {
	for (int i = 0; i < 4; i++) {
		int k = 0;
		ifstream fd("duom" + to_string(i+1)+".txt");
		while(!fd.eof()) {

			fd >> sar[i].duomenys[k].vardas >> sar[i].duomenys[k].mokinioVidurkis;
			fd.ignore();
			k++;
		}
		sar[i].kiekMokiniu = k;
		fd.close();
	}
}
void isvedimas(const char fv[], Klases sar[], Klases nSar) {
	ofstream fr(fv);
	int n;
	fr << fixed << setprecision(2);
	for (int i = 0; i < 4; i++) {
		n = sar[i].kiekMokiniu;
		fr << "Klase "<<i+1<<":"<< endl;
		for (int j = 0; j < n; j++) {
			fr << sar[i].duomenys[j].vardas << " " << sar[i].duomenys[j].mokinioVidurkis << endl;
		}
		fr << "--------------" << endl;
	}
	fr << "Rezultatas:" << endl;
	for (int i = 0; i < nSar.kiekMokiniu; i++)
		fr << nSar.duomenys[i].vardas << " " << nSar.duomenys[i].mokinioVidurkis << endl;
	fr.close();
}
void rikiavimas(Klases &sar) {
	Mokiniai naujas[Cn];
	int n;
		n = sar.kiekMokiniu;
		for (int i = 0; i < n - 1; i++) {
			for (int j = i + 1; j < n; j++) {
				if (sar.duomenys[j].mokinioVidurkis > sar.duomenys[i].mokinioVidurkis) {
					naujas[i] = sar.duomenys[j];
					sar.duomenys[j] = sar.duomenys[i];
					sar.duomenys[i] = naujas[i];
				}
			}
		}
}
void klasesVidurkioSkaiciavimas(Klases &sar) {
	int n;	
		double sum = 0;
		n = sar.kiekMokiniu;
		for (int j = 0; j < n; j++) {
			sum += sar.duomenys[j].mokinioVidurkis;
		}
		sar.klasesVidurkis = sum / n;
	}

void mokiniuSalinimas(Klases &sar) {
	int n;
	int m;
	Mokiniai naujas[Cn];
	
		n = sar.kiekMokiniu;
		m = 0;
		for (int j = 0; j < n; j++) {
			if (sar.duomenys[j].mokinioVidurkis > sar.klasesVidurkis) {
				naujas[m]=sar.duomenys[j];
				m++;
			}
		}
		for (int j = 0; j < m; j++) {
			sar.duomenys[j] = naujas[j];
		}
		sar.kiekMokiniu = m;
	
}
void bendriMokiniai(Klases &sar, Klases& nSar) {
	int n;
	int m;
	m = nSar.kiekMokiniu;
	n = sar.kiekMokiniu;
		for (int j = 0; j < n; j++) {
			nSar.duomenys[m] = sar.duomenys[j];
			m++;
		}
	nSar.kiekMokiniu = m;	
}
