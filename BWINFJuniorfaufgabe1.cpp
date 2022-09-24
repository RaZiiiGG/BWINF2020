#include <bits/stdc++.h>
using namespace std;
//Ich habe fuer die Eingabe und Ausgabe 2 Textdokumente und mit Hilfe von den gebe ich die Dateien ein und aus
//Falls Sie das nicht so haben, einfach den Teil #ifndef bis #endif loeschen


int main(){

#ifndef ONLINE_JUDGE
	freopen("dictionary.txt", "r", stdin); // Das Programm liest das Worterbuch ein / Input
	freopen("output.txt", "w", stdout); // Output
#endif

	//Ein Vector, um Wörter zu speichern
	vector <string> v;
	for (int i = 0; i < 64622; i++){
		string s;
		getline(cin, s);
		v.push_back(s);
	}

	//Zufällig generierte Zahl
	srand(unsigned(std::time(0)));
	random_device rd;    
	mt19937 rng(rand());
	uniform_int_distribution<int> uni(0, 64621);
	auto random_integer = uni(rng);

	// Alle Variablen, die ich brauche
	bool ok = true; // bool Variable; um den Loop konstant zu wiederholen, bis das Passwort generiert ist
	int cnt = 0; // integer Variable; mit Hilfe von cnt unterscheide ich die Fälle im "ok" Loop
	string wort1copy; // Die Kopie des ersten Wortes
	string passwort = ""; 
	int versuche = 0; // integer Variable; mit der zähle ich Versuche, um die richtigen Wörter zu finden
					  // Falls es zu viele Versuche gibt, das erste Wort wird wieder ausgesucht
	
	while (ok){
		// Der erste Fall, das erste Wort wird gesucht
		if (cnt == 0){
			string wort1 = v[uni(rng)];
			// Ueberpruefen, ob es Doppel-Buchstaben im Wort gibt, falls ja, ein Neues finden
			bool repeat = false;
			for (int i = 0; i < wort1.size()-1; i++){
				if (wort1[i] == wort1[i+1]){
					repeat = true;
				}
			}
			if (!repeat){
				// Hier gibt es ein paar Bedinungen für das erste Wort
				// Das Wort muss länger als 6 Buchstaben sein
				// In meinem Worterbuch, in dem sich die Wörter befinden, aus irgendwelchem Grund gibt es am Ende mancher Wörter Zeichen wie "+", "&", "^"...
				// Diese Wörter werden ignoriert
				if (wort1.size() > 6 && wort1[wort1.size()-1] != '&' && wort1[wort1.size()-1] != '+' && wort1[wort1.size()-1] != '$' && wort1[wort1.size()-1] != '^'){
					passwort+=wort1;
					passwort+=',';
					wort1copy = wort1;
					cnt++;
				}
			}
		}
		// Der zweite Fall, das zweite Wort wird gesucht
		if (cnt == 1){
			string wort2 = v[uni(rng)];
			// Ueberpruefen, ob es Doppel-Buchstaben im Wort gibt, falls ja, ein Neues finden
			bool repeat = false;
			for (int i = 0; i < wort2.size()-1; i++){
				if (wort2[i] == wort2[i+1]){
					repeat = true;
				}
			}
			if (!repeat){
				// Das zweite Wort ist genauso lang wie das Erste und die letzen drei Buchstaben des zweiten Wortes entsprechen den drei letzen Buchstaben des ersten Wortes
				if (wort2.size() == wort1copy.size() && wort2[0] != wort1copy[wort1copy.size()-1] &&  wort2 != wort1copy && wort2[wort2.size()-1] == wort1copy[wort1copy.size()-1] && wort2[wort2.size()-2] == wort1copy[wort1copy.size()-2] && wort2[wort2.size()-3] == wort1copy[wort1copy.size()-3]){
					passwort+=wort2;
					ok = false;
				}
			}
		}
		// Falls es zu viele Versuche gibt, die richtigen Wörter zu finden, wird der Loop wiederholt
		versuche++;
		if (versuche > 500){
			versuche = 0;
			cnt = 0;
			passwort = "";
		}

	}

	cout << "Die Grundlage des Passworts lautet: " << passwort << endl;

	// Vector, um das Passwort, in Vector zu speichern
	vector <char> passwortv;
	// Alphabet
	vector <char> alphabet = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
	// die Variable, mit der ich die Buchstaben addiere, modulo ist hier verwendet, falls ich mehr als 26 Buchstaben addieren muss, weil 27%26 = 1...
	int cur = 0%26;

	// Von String zu Vector
	for (auto x : passwort){
		if (x != ','){
			passwortv.push_back(x);
		}
	}

	// Loop, um die richtigen Buchstaben zu addieren
	for (int i = 0; i < passwortv.size(); i++){
		if (passwortv[i] == 'a' || passwortv[i] == 'e' || passwortv[i] == 'i' || passwortv[i] == 'o' || passwortv[i] == 'u'){
			if (alphabet[cur] == passwortv[i]){
				// Falls der selbe Buchstabe addiert werden soll, wird der naechste Buchstabe addiert, damit es nicht zu Doppel-Buchstaben kommt
				passwortv.insert(passwortv.begin()+i+1, toupper(alphabet[cur+1]));
				cur+=2;
			} else {
				// Falls nicht, einfach einen Buchstaben addieren, der Buchstabe wird mit Hilfe der Variable "cur" ausgesucht
				passwortv.insert(passwortv.begin()+i+1, toupper(alphabet[cur]));
				cur++;
			}
		}
	}

	cout << "Das komplette Passwort lautet: ";
	for (int i = 0; i < passwortv.size(); i++){
		cout << passwortv[i];
	}

	
}