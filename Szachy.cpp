// Szachy.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <cmath>

using namespace std;
int nr_ruchu = 1;
int w_przelocie[8][2];
enum color { PUSTE = 2, BIALY = 1, CZARNY = 0 };
enum figure { BRAK = 0, KROL = 1, HETMAN = 2, WIEZA = 3, GONIEC = 4, SKOCZEK = 5, PION = 6 };

struct pole {
	color kolor = PUSTE;
	figure figura;
};
pole szachownica[8][8];//[kolumna][rzad]

struct wspolrzedne {
	int kolumna;
	int rzad;				//numerowane 0-7
};
wspolrzedne start, cel;		

void gdzie(string rozkaz) {
	cel.kolumna = rozkaz[rozkaz.length() - 2] - 'a';
		cel.rzad = rozkaz[rozkaz.length() - 1] - '1';
}
//TODO
bool czy_szach() {
	return false;
}
//TODO
bool czy_mat() { return false; }
//DONE
void promocja_piona(wspolrzedne cel) {
	char w_co;
	cout << "wpisz w jak¹ figurê powinien zostaæ promowany pion (H, S, W, G)";
	cin >> w_co;
	switch (w_co) {
	case 'H':szachownica[cel.kolumna][cel.rzad].figura = HETMAN; break;
	case 'S':szachownica[cel.kolumna][cel.rzad].figura = SKOCZEK; break;
	case 'W':szachownica[cel.kolumna][cel.rzad].figura = WIEZA; break;
	case 'G':szachownica[cel.kolumna][cel.rzad].figura = GONIEC; break;
	default:promocja_piona(cel);
	}
}
//DONE
void wykonaj_ruch(wspolrzedne start, wspolrzedne cel) {
	pole bufor = szachownica[cel.kolumna][cel.rzad];
	szachownica[cel.kolumna][cel.rzad] = szachownica[start.kolumna][start.rzad];
	szachownica[start.kolumna][start.rzad].kolor = PUSTE;
	szachownica[start.kolumna][start.rzad].figura = BRAK;
	if (czy_szach()) {
		szachownica[start.kolumna][start.rzad] = szachownica[cel.kolumna][cel.rzad];
		szachownica[cel.kolumna][cel.rzad] = bufor;
		cout<< "Niemo¿liwy ruch wykonaj_ruch, jest szach\n";
		w_przelocie[cel.kolumna][(nr_ruchu + 1) % 2] = 0;
	}	
	else if (bufor.kolor==szachownica[cel.kolumna][cel.rzad].kolor) {
		szachownica[start.kolumna][start.rzad] = szachownica[cel.kolumna][cel.rzad];
		szachownica[cel.kolumna][cel.rzad] = bufor;
		cout << "Niemo¿liwy ruch wykonaj_ruch, nie mo¿esz zbiæ swojej bierki\n";
		w_przelocie[cel.kolumna][(nr_ruchu + 1) % 2] = 0;
	}
	else {
		nr_ruchu++;
		cout << "wykona³em ruch\n";
		if (szachownica[cel.kolumna][cel.rzad].figura == PION) {
			if (cel.rzad == 0 || cel.rzad == 7) {
				promocja_piona(cel);
			}
		}
	}
}

//DONE
void ruch_K(string rozkaz) {
	int sasiedzi_K[8] = { -1,-1,-1,0,+1,+1,+1,0 };
	// Król jest zawsze jeden wiêc nie sprawdzam czy jest kilka
	for (int i = 0; i < 8; i++) {
		start.kolumna = cel.kolumna + sasiedzi_K[i];
		start.rzad = cel.rzad + sasiedzi_K[(i + 2) % 8];
		if (szachownica[start.kolumna][start.rzad].figura == KROL && szachownica[start.kolumna][start.rzad].kolor == nr_ruchu % 2) {
			wykonaj_ruch(start, cel);
		 break;
		}
	}
}

//TODO
void ruch_H(string rozkaz) {

}

//TODO
void ruch_G(string rozkaz) {

}

//DONE
void ruch_S(string rozkaz) {
	int sasiedzi_S[8] = { -1,+1,+2,+2,+1,-1,-2,-2 };
	if (rozkaz.length() > 3) {//jeœli rozkaz doprecyzowuje sk¹d skoczek idzie bo inaczej by³by nieprecyzyjny
		int odl;
		if (rozkaz[rozkaz.length() - 3] >= 'a'&&rozkaz[rozkaz.length() - 3] <= 'h') {
			start.kolumna = rozkaz[rozkaz.length() - 3] - 'a';
			odl = abs(start.kolumna - cel.kolumna);
			if(odl>=3||odl==0){
				cout << "niemo¿liwy ruch ruch_S";
			}
			else for (int i = 0; i < 2; i++) {
				start.rzad = cel.rzad + (3 - odl)*pow(-1, i);
				if (szachownica[start.kolumna][start.rzad].figura==SKOCZEK&& szachownica[start.kolumna][start.rzad].kolor%2==nr_ruchu%2)
				{
					wykonaj_ruch(start, cel); break;
				}
				if (i == 1) {
					cout << "niemo¿liwy ruch ruch_S brak skoczka w mo¿liwych miejscach";
				}
			}
		}
		else if (rozkaz[rozkaz.length() - 3] >= '1'&&rozkaz[rozkaz.length() - 3] <= '8') {
			start.rzad = rozkaz[rozkaz.length() - 3] - '1';
			odl = abs(start.rzad - cel.rzad);
			if (odl >= 3 || odl == 0) {
				cout << "niemo¿liwy ruch ruch_S";
			}
			else for (int i = 0; i < 2; i++) {
				start.kolumna = cel.kolumna + (3 - odl)*pow(-1, i);
				if (szachownica[start.kolumna][start.rzad].figura == SKOCZEK && szachownica[start.kolumna][start.rzad].kolor % 2 == nr_ruchu % 2)
				{
					wykonaj_ruch(start, cel); break;
				}
				if (i == 1) {
					cout << "niemo¿liwy ruch ruch_S brak skoczka w mo¿liwych miejscach";
				}
			}
		}
		else
		{
			cout << "niemo¿liwy ruch";
		}
	}
	else for (int i = 0; i < 8; i++) {//jest tylko jeden skoczek który mo¿e siê ruszyæ
		start.kolumna = cel.kolumna + sasiedzi_S[i];
		start.rzad = cel.rzad + sasiedzi_S[(i + 2) % 8];
		if (szachownica[start.kolumna][start.rzad].figura == SKOCZEK && szachownica[start.kolumna][start.rzad].kolor == nr_ruchu % 2) {
			wykonaj_ruch(start, cel);
			break;
		}
	}
}

//TODO
void ruch_W(string rozkaz) {

}

//TODO
void roszada(string rozkaz) {

}

//TODO
void ruch_P(string rozkaz) {
	if (rozkaz.length() > 2 && rozkaz[rozkaz.length() - 3] >= 'a'&&rozkaz[rozkaz.length() - 3] <= 'h') {//bicie
		start.kolumna = rozkaz[rozkaz.length() - 3] - 'a';
		start.rzad = cel.rzad +pow(-1,nr_ruchu%2);
		if (szachownica[start.kolumna][start.kolumna].kolor != szachownica[cel.kolumna][cel.rzad].kolor&&szachownica[cel.kolumna][cel.rzad].kolor != PUSTE) {
			wykonaj_ruch(start, cel);
		}
		else if (w_przelocie[cel.kolumna][(nr_ruchu+1)%2]==nr_ruchu-1		//en passant
				&& szachownica[start.kolumna][start.rzad].figura==PION
				&& szachownica[start.kolumna][start.rzad].kolor%2==nr_ruchu%2)
		{	
			szachownica[cel.kolumna][start.rzad].figura = BRAK;
			szachownica[cel.kolumna][start.rzad].kolor = PUSTE;
			wykonaj_ruch(start, cel);
			cout << "robie w przelocie";
		}
		else {
			cout << "niemo¿liwy ruch Ruch_P bicie\n";
			for (int j = 7; j >= 0; j--) {
				for (int i = 0; i < 8; i++) {
					cout << szachownica[i][j].kolor << " ";
				}
				cout << endl;
			}
			cout << endl;
		}
	}
	else { 
		start.kolumna = cel.kolumna;
		start.rzad = cel.rzad - 1 + 2 * ((nr_ruchu + 1) % 2);//ruch o jedno pole
		if (szachownica[cel.kolumna][cel.rzad].kolor == PUSTE) {
			if (szachownica[start.kolumna][start.rzad].figura == PION 
				&& szachownica[start.kolumna][start.rzad].kolor % 2 == nr_ruchu % 2)
			{
				wykonaj_ruch(start, cel);
			}
			else if (cel.rzad == 3 && nr_ruchu % 2 == 1 || cel.rzad == 4 && nr_ruchu % 2 == 0) {//ruch o dwa
				start.rzad = 6 - (nr_ruchu % 2) * 5;
				if (szachownica[cel.kolumna][(start.rzad + cel.rzad) / 2].kolor == PUSTE 
					&& szachownica[start.kolumna][start.rzad].figura == PION 
					&& szachownica[start.kolumna][start.rzad].kolor % 2 == nr_ruchu % 2) {
					w_przelocie[cel.kolumna][(nr_ruchu)%2] = nr_ruchu; // przy nieudanym ruchu zaimplementowaæ zerowanie w_przelocie
					wykonaj_ruch(start, cel);
				}
				else {
					cout << "niemo¿liwy ruch ruch_P do przodu, cos stoi na drodze \n";
				}
			}	
			else {
				cout << "niemo¿liwy ruch ruch_P do przodu, nie znaleziono pionu do ruszenia \n";
			}
		}
		else {
			cout << "niemo¿liwy ruch ruch_P do przodu, cos stoi na drodze \n";
		}
	}
}

//DONE
void ruch(string rozkaz) {
	gdzie(rozkaz);
	if (cel.kolumna < 0 || cel.kolumna>7 || cel.rzad < 0 || cel.rzad>7) {
		cout << "NIEMO¯LIWY RUCH Rozkaz poza szachownice\n";
	}
	else switch (rozkaz[0]) {
	case 'K': ruch_K(rozkaz); break;
	case 'H': ruch_H(rozkaz); break;
	case 'G': ruch_G(rozkaz); break;
	case 'S': ruch_S(rozkaz); break;
	case 'W': ruch_W(rozkaz); break;
	case 'O': roszada(rozkaz); break;
	default: ruch_P(rozkaz);
	}
}
//DONE
void inicjalizacja_default() {    //wype³nia szachownicê pocz¹tkowym ustawieniem bierek
	for (int i = 0; i < 2; i ++) {//pionki
		for (int j = 0; j < 8; j++) {
			szachownica[j][1 + 5 * i].figura = PION;
			if (i == 0) {
				szachownica[j][1 + 5 * i].kolor = BIALY;
			}
			else {
				szachownica[j][1 + 5 * i].kolor = CZARNY;
			}
		}
	}
	const figure poczatkowe[8] = { WIEZA,SKOCZEK,GONIEC,HETMAN,KROL,GONIEC,SKOCZEK,WIEZA };
	for (int i = 0; i < 2; i++) {//figury
		for (int j = 0; j < 8; j++) {
			szachownica[j][7 * i].figura = poczatkowe[j];
			if (i == 0) {
				szachownica[j][7 * i].kolor = BIALY;
			}
			else {
				szachownica[j][7 * i].kolor = CZARNY;
			}
		}
	}
}
//TODO
void inicjalizacja_zpliku() {
}
//TODO
void inicjalizacja(){
	string mode;
	cout << "(N)owa gra\t(W)czytaj gre\t(Z)amknij\n";
	cin >> mode;
	nr_ruchu = 1;
	switch (mode[0]) {
	case 'N': inicjalizacja_default(); system("CLS"); break;
	case 'W': inicjalizacja_zpliku(); system("CLS"); break;
	case 'Z':  exit(0);
	default:cout << "WPROWAD PRAWID£OW¥ KOMENDÊ\n";  inicjalizacja();
	}
}

void wyswietl() {
	char plansza[8][8];
	for (int j = 7; j >= 0; j--) {
		for (int i = 0; i < 8; i++) {
			switch (szachownica[i][j].kolor) {
			case PUSTE:		plansza[i][j] = '.'; break;
			case CZARNY:	plansza[i][j] = 'a' - 'A'; break;
			case BIALY:		plansza[i][j] = 0;
			}
			switch (szachownica[i][j].figura)
			{
			case PION:		plansza[i][j] += 'P'; break;
			case SKOCZEK:	plansza[i][j] += 'S'; break;
			case GONIEC:	plansza[i][j] += 'G'; break;
			case WIEZA:		plansza[i][j] += 'W'; break;
			case HETMAN:	plansza[i][j] += 'H'; break;
			case KROL:		plansza[i][j] += 'K'; break;
			}
			cout << plansza[i][j] << " ";
		}
		cout << endl;
	}

}

string s;
int main()
{	
	inicjalizacja();
	while (!czy_mat()) {
		wyswietl();
		cout << "teraz ruch ";
		if (nr_ruchu % 2 == 0) { cout << "czarnego\n"; }
		else { cout << "bialego\n"; }
		cin >> s;
		system("CLS");
		ruch(s);
	}

	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
