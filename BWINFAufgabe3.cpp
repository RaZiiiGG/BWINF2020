#include <bits/stdc++.h>
using namespace std;
//Ich habe fuer die Eingabe und Ausgabe 2 Textdokumente und mit Hilfe von den gebe ich die Dateien ein und aus
//Falls Sie das nicht so haben, einfach den Teil #ifndef bis #endif loeschen

int main(){

#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin); //Eingabe
	freopen("output.txt", "w", stdout); //Ausgabe
#endif
	srand(unsigned(std::time(0)));
	
	int n;
	cin >> n;
	vector <pair <int, pair<int,int>>> liga2(n); //Liste mit Spieleren fuer Liga Variante (Spielstaerke, Anzahl der Siege, Spielernummer)
	vector <pair <int, int>> ko(2*n-1); //Liste mit Spieleren fuer K.0. Variante (mit normalen Positionen) (Spielstaerke, Spielernummer)
	vector <pair <int, int>> korandom(n); //Liste mit Spieleren fuer K.0. Variante (mit zufaelligen Positionen) (Spielstaerke, Spielernummer)
	vector <pair <int, int>> ko5(2*n-1); //Liste mit Spieleren fuer K.0. x5 Variante (mit normalen Positionen) (Spielstaerke, Spielernummer)
	vector <pair <int, int>> ko5random(n); //Liste mit Spieleren fuer K.0. x5 Variante (mit zufaelligen Positionen) (Spielstaerke, Spielernummer)
	
	//Jeder Spieler bekommt seine Spielstaerke
	for (int i = 0; i < n; i++){
		int a;
		cin >> a;
		ko[i].first = a, ko[i].second = i+1;
		korandom[i].first = a, korandom[i].second = i+1;
		ko5[i].first = a, ko5[i].second = i+1;
		ko5random[i].first = a, ko5random[i].second = i+1;
		liga2[i].first = a, liga2[i].second.first = 0, liga2[i].second.second = i+1;
	}

	mt19937 mt_rand(time(0));

	//------------------------------------------------------------------------------//
	//Liga
	//Jeder spielt gegen jeden einmal, falls er gewinnt, erhoeht sich seine Anzahl der Siege um 1
	vector <int> AlleGewinner(n);
	for (int Spiele = 0; Spiele < 5000; Spiele++){

	vector <pair <int, pair <int,int>>> liga(n);
	for (int i = 0; i < n; i++){
		liga[i].first = liga2[i].first; liga[i].second.first = liga2[i].second.first; liga[i].second.second = liga2[i].second.second;
	}

	for (int i = 0; i < n; i++){
		for (int j = i+1; j < n; j++){
			// zufaellige Zahl wird generiert
			double r1 = mt_rand() / (double)mt_rand.max();
			// beide Spieler werden definiert
			double player1 = liga[i].first;
			double player2 = liga[j].first;
			double sum = player1+player2;
			// Der selbe Prozess wie schon in der Aufgabenstellung beschrieben ist
			if (r1 <= player1/sum){
				liga[i].second.first++;
			} else {
				liga[j].second.first++;
			}
		}
	}

	// hier wird die grosste Anzahl der Siege gesucht
	int maxn = 0;
	for (int i = 0; i < n; i++){
		maxn = max(maxn, liga[i].second.first);
	}

	// Bei Gleichstand werden alle Spieler in die Liste GewinnerLiga addiert
	vector <pair <int, int>> GewinnerLiga;
	for (int i = 0; i < n; i++){
		if (liga[i].second.first == maxn){
			GewinnerLiga.push_back(make_pair(liga[i].second.second, liga[i].first));
		}
	}
	// Die Liste wird nach der Spielernummern sortiert, damit an der erste Stelle der Spieler mit der kleinsten Spielernummer steht
	sort(GewinnerLiga.begin(), GewinnerLiga.end());
	AlleGewinner[GewinnerLiga[0].first-1]++;

	GewinnerLiga.clear();

	}
	cout << "Liga Variante (5000 Spiele): " << endl;
	for (int i = 0; i < n; i++){
		double winrate = AlleGewinner[i]/50;
		cout << "Spieler " << i+1 << " hat " << AlleGewinner[i] << " Mal gewonnen. (" << winrate << "%)" << endl;
	}
	for (int i = 0; i < n; i++){
		AlleGewinner[i] = 0;
	}
	
	//------------------------------------------------------------------------------//
	//KOnormal
	// die Variable Position wird definiert, um uns zu helfen, die Spieler, die gewinnen, weiter zu schicken
	for (int Spiele = 0; Spiele < 5000; Spiele++){

	int pos = 0;
	for (int i = n; i < 2*n-1; i++){
		// zufaellige Zahl wird generiert
		double r2 = mt_rand() / (double)mt_rand.max();
		// beide Spieler werden definiert
		double player1 = ko[pos].first;
		double player2 = ko[pos+1].first;
		double sum = player1+player2;
		if (r2 <= player1/sum){
			// Falls der erste Spieler gewinnt, geht er weiter in den Turnier und bekommt eine Stelle in der Liste
			ko[i].first=ko[pos].first;
			ko[i].second=ko[pos].second;
		} else {
			// Falls der zweite Spieler gewinnt, geht er weiter in den Turnier und bekommt eine Stelle in der Liste
			ko[i].first=ko[pos+1].first;
			ko[i].second=ko[pos+1].second;
		}
		// die Variable wird um 2 erhoeht, weil das die neue leere Position in der Liste ist, die in der naechsten Loop Runde erfuellt wird
		pos+=2;
	}

	AlleGewinner[ko[2*n-2].second-1]++;

	}
	cout << "K.0. (normal) Variante (5000 Spiele): " << endl;
	for (int i = 0; i < n; i++){
		double winrate = AlleGewinner[i]/50;
		cout << "Spieler " << i+1 << " hat " << AlleGewinner[i] << " Mal gewonnen. (" << winrate << "%)" << endl;
	}
	for (int i = 0; i < n; i++){
		AlleGewinner[i] = 0;
	}

	
	//------------------------------------------------------------------------------//
	//KOshuffled
	// hier passiert das Selbe wie oben, der Unterschied ist nur, dass die Positionen nicht gleich sind, sondern jeder Spieler bekommt eine Position in der Liste zufaellig
	for (int Spiele = 0; Spiele < 5000; Spiele++){

	random_shuffle(korandom.begin(), korandom.end());
	vector <pair <int,int>> korandomshuffled(2*n-1);
	for (int i = 0; i < n; i++){
		korandomshuffled[i].first = korandom[i].first;
		korandomshuffled[i].second = korandom[i].second;
	}
	int pos = 0;
	for (int i = n; i < 2*n-1; i++){
		double r3 = mt_rand() / (double)mt_rand.max();
		double player1 = korandomshuffled[pos].first;
		double player2 = korandomshuffled[pos+1].first;
		double sum = player1+player2;
		if (r3 <= player1/sum){
			korandomshuffled[i].first=korandomshuffled[pos].first;
			korandomshuffled[i].second=korandomshuffled[pos].second;
		} else {
			korandomshuffled[i].first=korandomshuffled[pos+1].first;
			korandomshuffled[i].second=korandomshuffled[pos+1].second;
		}
		pos+=2;
	}

	AlleGewinner[korandomshuffled[2*n-2].second-1]++;
	
	}
	
	cout << "K.0. (zufaellige Positionen) Variante (5000 Spiele): " << endl;
	for (int i = 0; i < n; i++){
		double winrate = AlleGewinner[i]/50;
		cout << "Spieler " << i+1 << " hat " << AlleGewinner[i] << " Mal gewonnen. (" << winrate << "%)" << endl;
	}
	
	for (int i = 0; i < n; i++){
		AlleGewinner[i] = 0;
	}

	//------------------------------------------------------------------------------//
	//KO5normal
	//Wieder das Gleiche wie bei K.O. Variante, der Unterschied ist nur, dass hier gezaehlt wird, wer wie oft gewinnt und das entscheidet, wer weiter geht
	for (int Spiele = 0; Spiele < 5000; Spiele++){

	int pos = 0;
	for (int i = n; i < 2*n-1; i++){
		double player1 = ko5[pos].first;
		double player2 = ko5[pos+1].first;
		double sum = player1+player2;
		int cnt1 = 0, cnt2 = 0;
		// In dieser For Loop wird entscheidet, wer gewinnt und in die naechste Runde kommt
		for (int j = 0; j < 5; j++){
			double r4 = mt_rand() / (double)mt_rand.max();
			if (r4 <= player1/sum){
				cnt1++;
			} else {
				cnt2++;
			}
		}
		if (cnt1 > cnt2){
			ko5[i].first=ko5[pos].first;
			ko5[i].second=ko5[pos].second;
		} else {
			ko5[i].first=ko5[pos+1].first;
			ko5[i].second=ko5[pos+1].second;
		}
		pos+=2;
	}

	AlleGewinner[ko5[2*n-2].second-1]++;

	}

	cout << "K.0. 5 (normale Positionen) Variante (5000 Spiele): " << endl;
	for (int i = 0; i < n; i++){
		double winrate = AlleGewinner[i]/50;
		cout << "Spieler " << i+1 << " hat " << AlleGewinner[i] << " Mal gewonnen. (" << winrate << "%)" << endl;
	}
	
	for (int i = 0; i < n; i++){
		AlleGewinner[i] = 0;
	}


	//------------------------------------------------------------------------------//
	//KO5shuffled
	// Das Gleiche wie bei K.0. 5 normal, nur sind die Positionen zuafellig generiert
	for (int Spiele = 0; Spiele < 5000; Spiele++){

	random_shuffle(ko5random.begin(), ko5random.end());
	vector <pair <int,int>> ko5shuffled(2*n-1);
	for (int i = 0; i < n; i++){
		ko5shuffled[i].first = ko5random[i].first;
		ko5shuffled[i].second = ko5random[i].second;
	}
	int pos = 0;
	for (int i = n; i < 2*n-1; i++){
		double player1 = ko5shuffled[pos].first;
		double player2 = ko5shuffled[pos+1].first;
		double sum = player1+player2;
		int cnt1 = 0, cnt2 = 0;
		for (int j = 0; j < 5; j++){
			double r5 = mt_rand() / (double)mt_rand.max();
			if (r5 <= player1/sum){
				cnt1++;
			} else {
				cnt2++;
			}
		}
		if (cnt1 > cnt2){
			ko5shuffled[i].first=ko5shuffled[pos].first;
			ko5shuffled[i].second=ko5shuffled[pos].second;
		} else {
			ko5shuffled[i].first=ko5shuffled[pos+1].first;
			ko5shuffled[i].second=ko5shuffled[pos+1].second;
		}
		pos+=2;
	}

	AlleGewinner[ko5shuffled[2*n-2].second-1]++;

	}

	cout << "K.0. 5 (zufaellige Positionen) Variante (5000 Spiele): " << endl;
	for (int i = 0; i < n; i++){
		double winrate = AlleGewinner[i]/50;
		cout << "Spieler " << i+1 << " hat " << AlleGewinner[i] << " Mal gewonnen. (" << winrate << "%)" << endl;
	}
	
	for (int i = 0; i < n; i++){
		AlleGewinner[i] = 0;
	}


	
}