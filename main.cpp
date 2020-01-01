#include <iostream>
#include <fstream>
#include <locale.h>

using namespace std;

void swap(float &a, float &b);

int main() {
	setlocale(LC_ALL, "Turkish"); //Konsolda türkçe karakter için. http://mesutpiskin.com/blog/cc-turkce-karakter-kullanmak.html
	int soruSayisi,i,j,k;
	int ogrSayisi=4; //Ne kadar öðrenci varsa o kadar girilmelidir eksik veya fazla, çýktýda hataya sebep olur.
	int ogrNoUzunlugu=10; //Benim kullandýðým öðrenci numarasý 10 olduðu için.
	string inputCevapAnahtari, input[ogrSayisi];
	float ogrNot[ogrSayisi];
	
	ifstream dosyaR; //input.txt deki verileri input adlý geçici bi arraye yazar.
	dosyaR.open("input.txt");
	dosyaR >> soruSayisi;	
	dosyaR >> inputCevapAnahtari;
	for (i=0;i<ogrSayisi;i++){ 
		dosyaR >> input[i];
	}
	dosyaR.close();
	
	string data[ogrSayisi][soruSayisi+1], cevapAnahtari[soruSayisi];
	
	for (i=0;i<ogrSayisi;i++){ //data[i][0] lar öðrenci numaralarýdýr, cevaplar input[i][1]'den baþlar.
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
	
	j=0; //Düzensiz olan cevap anahtarýný inputCevapAnahtari adlý arraye sýralar.
	for (i=0;i<soruSayisi;i++){ 
		cevapAnahtari[i]=inputCevapAnahtari[j];
		j+=2;
	}
	
	for (i=0;i<ogrSayisi;i++){ //Tüm öðrencilerin notlarýný sýfýrlar.
		ogrNot[i]=0;
	}
	
	for (i=0;i<ogrSayisi;i++){ //Öðrencilerin boþ cevaplarýna "N" yazdýrýr.
		for(j=1;j<soruSayisi+1;j++){
			if (data[i][j]!="A" && data[i][j]!="B" && data[i][j]!="C" && data[i][j]!="D"){
				data[i][j]="N";
			}
		}
	}
	
	for (i=0;i<ogrSayisi;i++){ //Tüm öðrencilerin notlarýný hesaplar.
		for (j=1;j<soruSayisi+1;j++){
			if (data[i][j]==cevapAnahtari[j-1]){
				ogrNot[i]+=4;
			} else if (data[i][j]=="N"){			
			} else {
				ogrNot[i]-=1;
			}
		}
	}
	
	for (i=0;i<ogrSayisi;i++){ //Tüm öðrencilerin notunun 100e göre karþýlýðý alýnýr
		ogrNot[i]=ogrNot[i]*100/40;
	}
		
	for (i=ogrSayisi-1;i>=0;i--){ //Tüm öðrencileri nota göre sýralar. Bölüm 9 daki c++ bubble sort'u kullandým.
		for (j=0;j<=i-1;j++){
			if (ogrNot[j]<ogrNot[j+1]){
				swap(ogrNot[j],ogrNot[j+1]);
				swap(data[j][0],data[j+1][0]);
			}
		}
	}	
	
	float enDusukNot,enYuksekNot,ortalama,medyan,aciklik;
	
	enDusukNot=ogrNot[ogrSayisi-1];// En düþük notu bulur
	
	enYuksekNot=ogrNot[0]; //En yüksek notu bulur.
	
	int notTop=0; //Ortalamayý bulur.
	for(i=0;i<ogrSayisi;i++){
		if (ogrNot[i]<0){
			ogrNot[i]=0;
		}
		notTop+=ogrNot[i];
	}
	ortalama=notTop/ogrSayisi;
	
	int medyanPos; //Medyaný bulur.
	if (ogrSayisi%2==1){
		medyanPos=(ogrSayisi+1)/2;
		medyan=ogrNot[medyanPos];
	} else {
		medyanPos=ogrSayisi/2;
		medyan=(ogrNot[medyanPos-1]+ogrNot[medyanPos])/2;	
	}
	
	aciklik=ogrNot[0]-ogrNot[ogrSayisi-1]; //Açýklýðý bulur.
	
	ofstream dosyaW; // Verileri output.txt adlý dosyaya yazar.
	dosyaW.open("output.txt");
	for (i=0;i<ogrSayisi;i++){
		dosyaW << data[i][0] << "," << ogrNot[i] << endl;
	}
	dosyaW << enDusukNot <<","<< enYuksekNot <<","<< ortalama <<","<< medyan <<","<< aciklik;
	cout << "Veriler 'output.txt' adlý dosyaya yazýlmýþtýr." << endl;
	dosyaW.close();
	
	return 0;
}

void swap(float &a, float &b){ //bubblesort için swap modülü.
	float temp;
	temp=a;
	a=b;
	b=temp;
}
