#include <iostream>
#include <fstream>
#include <locale.h>

using namespace std;

void swap(float &a, float &b);

int main() {
	setlocale(LC_ALL, "Turkish"); //Konsolda t�rk�e karakter i�in. http://mesutpiskin.com/blog/cc-turkce-karakter-kullanmak.html
	int soruSayisi,i,j,k;
	int ogrSayisi=4; //Ne kadar ��renci varsa o kadar girilmelidir eksik veya fazla, ��kt�da hataya sebep olur.
	int ogrNoUzunlugu=10; //Benim kulland���m ��renci numaras� 10 oldu�u i�in.
	string inputCevapAnahtari, input[ogrSayisi];
	float ogrNot[ogrSayisi];
	
	ifstream dosyaR; //input.txt deki verileri input adl� ge�ici bi arraye yazar.
	dosyaR.open("input.txt");
	dosyaR >> soruSayisi;	
	dosyaR >> inputCevapAnahtari;
	for (i=0;i<ogrSayisi;i++){ 
		dosyaR >> input[i];
	}
	dosyaR.close();
	
	string data[ogrSayisi][soruSayisi+1], cevapAnahtari[soruSayisi];
	
	for (i=0;i<ogrSayisi;i++){ //data[i][0] lar ��renci numaralar�d�r, cevaplar input[i][1]'den ba�lar.
		data[i][0]=input[i][0];
		for (j=1;j<ogrNoUzunlugu;j++){	
			data[i][0]+=input[i][j];
		}
		j++;
		for (k=1;k<soruSayisi+1;k++){
			if (input[i][j]==','){
				j++;
			} else {
				data[i][k]=input[i][j];
				j+=2;
			}
		}
	}
	
	j=0; //D�zensiz olan cevap anahtar�n� inputCevapAnahtari adl� arraye s�ralar.
	for (i=0;i<soruSayisi;i++){ 
		cevapAnahtari[i]=inputCevapAnahtari[j];
		j+=2;
	}
	
	for (i=0;i<ogrSayisi;i++){ //T�m ��rencilerin notlar�n� s�f�rlar.
		ogrNot[i]=0;
	}
	
	for (i=0;i<ogrSayisi;i++){ //��rencilerin bo� cevaplar�na "N" yazd�r�r.
		for(j=1;j<soruSayisi+1;j++){
			if (data[i][j]!="A" && data[i][j]!="B" && data[i][j]!="C" && data[i][j]!="D"){
				data[i][j]="N";
			}
		}
	}
	
	for (i=0;i<ogrSayisi;i++){ //T�m ��rencilerin notlar�n� hesaplar.
		for (j=1;j<soruSayisi+1;j++){
			if (data[i][j]==cevapAnahtari[j-1]){
				ogrNot[i]+=4;
			} else if (data[i][j]=="N"){			
			} else {
				ogrNot[i]-=1;
			}
		}
	}
	
	for (i=0;i<ogrSayisi;i++){ //T�m ��rencilerin notunun 100e g�re kar��l��� al�n�r
		ogrNot[i]=ogrNot[i]*100/40;
	}
		
	for (i=ogrSayisi-1;i>=0;i--){ //T�m ��rencileri nota g�re s�ralar. B�l�m 9 daki c++ bubble sort'u kulland�m.
		for (j=0;j<=i-1;j++){
			if (ogrNot[j]<ogrNot[j+1]){
				swap(ogrNot[j],ogrNot[j+1]);
				swap(data[j][0],data[j+1][0]);
			}
		}
	}	
	
	float enDusukNot,enYuksekNot,ortalama,medyan,aciklik;
	
	enDusukNot=ogrNot[ogrSayisi-1];// En d���k notu bulur
	
	enYuksekNot=ogrNot[0]; //En y�ksek notu bulur.
	
	int notTop=0; //Ortalamay� bulur.
	for(i=0;i<ogrSayisi;i++){
		if (ogrNot[i]<0){
			ogrNot[i]=0;
		}
		notTop+=ogrNot[i];
	}
	ortalama=notTop/ogrSayisi;
	
	int medyanPos; //Medyan� bulur.
	if (ogrSayisi%2==1){
		medyanPos=(ogrSayisi+1)/2;
		medyan=ogrNot[medyanPos];
	} else {
		medyanPos=ogrSayisi/2;
		medyan=(ogrNot[medyanPos-1]+ogrNot[medyanPos])/2;	
	}
	
	aciklik=ogrNot[0]-ogrNot[ogrSayisi-1]; //A��kl��� bulur.
	
	ofstream dosyaW; // Verileri output.txt adl� dosyaya yazar.
	dosyaW.open("output.txt");
	for (i=0;i<ogrSayisi;i++){
		dosyaW << data[i][0] << "," << ogrNot[i] << endl;
	}
	dosyaW << enDusukNot <<","<< enYuksekNot <<","<< ortalama <<","<< medyan <<","<< aciklik;
	cout << "Veriler 'output.txt' adl� dosyaya yaz�lm��t�r." << endl;
	dosyaW.close();
	
	return 0;
}

void swap(float &a, float &b){ //bubblesort i�in swap mod�l�.
	float temp;
	temp=a;
	a=b;
	b=temp;
}
