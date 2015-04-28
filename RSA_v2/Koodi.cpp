#include <iostream>
#include <string>
#include <cmath>
#include <climits>
#include <ctime>
#include <chrono>
#include <Windows.h>

using namespace std;

class RSA {
private:
	unsigned long long p, q, N, n, a, d, apu, pot, luku, salaluku;
	clock_t aika;
	clock_t aika2;
	double kulunut_aika;


public:
	bool onko_alkuluku(unsigned long long);
	bool samat_tekijat(unsigned long long,unsigned long long);
	void aseta_arvot();
	void syota_luku();
	void syota_salaluku();
	void avaa(unsigned long long);
	void salaa(unsigned long long);
	unsigned long long saa_vaa(unsigned long long x, unsigned long long k, unsigned long long a, unsigned long long N);
	unsigned long long salaa_avaa(unsigned long long k, unsigned long long a, unsigned long long N);
	unsigned long long anna_avattu();
	unsigned long long anna_salattu();
	void etsi_d();
	double anna_aika();
	




};

bool RSA::onko_alkuluku(unsigned long long x) {
	unsigned long long y = x/2;
	if (y < 1) {
		return false;
	}
	for (unsigned long i = 2; i <= y; i++) {
		if (x % i == 0 || y < 2) {
			return false;
		}
	}
	return true;
}

bool RSA::samat_tekijat(unsigned long long n, unsigned long long a) {
	unsigned long long x = a/2;	
	if (this->onko_alkuluku(a) == true && n%a == 0) {
		cout << "Luvulla n = (p-1)*(q-1) on sama tekija kuin luvulla a!\n";
		return true;
	}
	for (unsigned long long i = 1; i <= x; i++) {
		if (this->onko_alkuluku(i) == true && n%i == 0 && a%i == 0) {
			cout << "Luvulla n = (p-1)*(q-1) on sama tekija kuin luvulla a!\n";
			return true;
		}
	}
	return false;
}

void RSA::aseta_arvot(){
	bool jatko = true;
	while(jatko == true) {
		cout << "Anna ensimmainen alkuluku: ";
		cin >> this->p;
		if (this->onko_alkuluku(this->p) == true) {
			jatko = false;
		}
		if (jatko == true) {cout << "Luku ei ollut alkuluku!" << endl;}
	}

	jatko = true;
	while(jatko == true) {
		cout << "Anna toinen alkuluku: ";
		cin >> this->q;
		if (this->onko_alkuluku(this->q) == true && (this->q)*(this->p) > 256) {
			jatko = false;
		}
		if (jatko == true) {cout << "Luku ei ollut alkuluku tai ensimmaisen ja toisen luvun kertoma oli pienempi tai yhta suuri kuin 256!" << endl;}
	}
	this->N = (this->p)*(this->q);
	this->n = ((this->p)-1)*((this->q)-1);
	jatko = true;
	while(jatko == true) {
		cout << "Anna luku (toinen julkinen avain, ei saa olla yhteisia tekijoita luvun n kanssa): ";
		cin >> this->a;
		if (this->samat_tekijat(this->n,this->a) == false || this->a == 1) {
			jatko = false;
		}
	}
	this->etsi_d();

}

void RSA::etsi_d() {
	this->d = 1;
	while (((this->a)*(this->d))%this->n != 1) {
		d++;
	}
}

unsigned long long RSA::anna_salattu() {
	return this->salaluku;
}

unsigned long long RSA::anna_avattu() {
	return this->luku;
}

void RSA::syota_luku() {
	cout << "Syota salattava luku: ";
	cin >> this->luku;
}

void RSA::syota_salaluku() {
	cout << "Syota salattu luku: ";
	cin >> this->salaluku;
}

void RSA::salaa(unsigned long long x) {	
	

	if (x = 1) {
	
		clock_t startTime = clock();
		this->salaluku = this->salaa_avaa(this->luku,this->a,this->N);
		clock_t endTime = clock();
		clock_t clockTicksTaken = endTime - startTime;
		this -> kulunut_aika = clockTicksTaken / (double) CLOCKS_PER_SEC;//;= endTime / (double) CLOCKS_PER_SEC;

	} 

	else if (x = 2) {
		clock_t startTime = clock();
		this->salaluku = this->saa_vaa(1,this->luku,this->a,this->N);
		clock_t endTime = clock();
		clock_t clockTicksTaken = endTime - startTime;
		this -> kulunut_aika = clockTicksTaken / (double) CLOCKS_PER_SEC;//= endTime / (double) CLOCKS_PER_SEC;

	
	}

	
}

void RSA::avaa(unsigned long long x) {
	

	if (x = 1) {
		clock_t startTime = clock();
		this->luku = this->salaa_avaa(this->salaluku,this->d,this->N);
		clock_t endTime = clock();
		clock_t clockTicksTaken = endTime - startTime;
		this -> kulunut_aika= clockTicksTaken / (double) CLOCKS_PER_SEC; 
		

	} else if (x = 2) { 
		clock_t startTime = clock();
		this->luku = this->saa_vaa(1,this->salaluku,this->d,this->N);
		clock_t endTime = clock();
		clock_t clockTicksTaken = endTime - startTime;
		this -> kulunut_aika = clockTicksTaken / (double) CLOCKS_PER_SEC;//((float)this->aika)/(float)CLOCKS_PER_SEC;
	 
	}
	

}


unsigned long long RSA::salaa_avaa(unsigned long long k, unsigned long long a, unsigned long long N) {
	if (a <= 2) {
		return (unsigned long long)pow(k,a) % this->N;
	} else {
		return (k*this->salaa_avaa(k,a-1,this->N)) % this->N;
	}

}
}
unsigned long long RSA::saa_vaa(unsigned long long x, unsigned long long k, unsigned long long a, unsigned long long N) {
	unsigned long long pot;
	if (a == 1) {
		return (x*k) % this->N;
	} else {
		pot = a%2;
		a = (a - pot)/2;
		x = (unsigned long long)(x*pow(k,pot)) % this->N;
		k = (unsigned long long)pow(k,2)%this->N;
		return saa_vaa(x,k,a,this->N);
	}
}

double RSA::anna_aika() {
	return this->kulunut_aika;
}

int main() {

	
	RSA rsa;
	int valinta = 1;
	while(valinta != 0) {
		cout << "Mita haluat tehda?\n";
		cout << "1. Generoi avaimet\n";
		cout << "2. Syota selkokielinen teksti\n";
		cout << "3. Syota salattu teksti\n";
		cout << "4. Salaa teksti kayttaen salaa_avaa-algoritmia\n";
		cout << "5. Salaa teksti kayttaen saa_vaa-algoritmia\n";
		cout << "6. Avaa salattu teksti kayttaen salaa_avaa-algoritmia\n";
		cout << "7. Avaa salattu teksti kayttaen saa_vaa-algoritmia\n";
		cout << "0. Lopeta\n";
		cout << "Valintasi: ";
		cin >> valinta;

		switch(valinta) {
		case 1:
			rsa.aseta_arvot();
			break;
		case 2:
			rsa.syota_luku();
			break;
		case 3:
			rsa.syota_salaluku();
			break;
		case 4:
			rsa.salaa(1);
			cout << "Luku salaa_avaa-funktiolla salattuna: " << rsa.anna_salattu() << endl;
			printf("Aikaa salaukseen kului: %f ",rsa.anna_aika(),"sekuntia. " "\n");//cout <<"Aikaa salaukseen kului: "<< rsa.anna_aika() <<"sekuntia. ";
			cout << endl;
			break;
		case 5:
			rsa.salaa(2);
			cout << "Luku saa_vaa-funktiolla salattuna: " << rsa.anna_salattu() << endl;
			printf("Aikaa salaukseen kului: %f ",rsa.anna_aika(),"sekuntia. " "\n");//cout <<"Aikaa salaukseen kului: "<< rsa.anna_aika() <<"sekuntia. ";
			cout << endl;
			break;
		case 6:
			rsa.avaa(1);
			cout << "Luku salaa_avaa-funktiolla purettuna: " << rsa.anna_avattu() << endl;
			printf("Aikaa salaukseen kului: %f ",rsa.anna_aika(),"sekuntia. " "\n");//cout <<"Aikaa avaukseen kului: "<< rsa.anna_aika() <<"sekuntia. ";
			cout << endl;
			break;
		case 7:
			rsa.avaa(2);
			cout << "Luku saa_vaa-funktiolla purettuna: " << rsa.anna_avattu() << endl;
			printf("Aikaa salaukseen kului: %f ",rsa.anna_aika(),"sekuntia. " "\n");//cout <<"Aikaa avaukseen kului: "<< rsa.anna_aika() <<"sekuntia. ";
			cout << endl;
			break;
		case 0:
			cout << "Lopetetaan!\n";
			break;
		default:
			cin.clear();
			cout << "Virheellinen valinta!\n";
	}
	}
	
	system("pause");
	return 0;
}
