#include <bits/stdc++.h>
using namespace std;
//Ich habe fuer die Eingabe und Ausgabe 2 Textdokumente und mit Hilfe von den gebe ich die Dateien ein und aus
//Falls Sie das nicht so haben, einfach den Teil #ifndef bis #endif loeschen


int main(){

#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin); //input
	freopen("output.txt", "w", stdout); //output
#endif

	int b, h; //integers für Breite und Höhe
	cin >> b;
	cin >> h;
	cin.ignore();
	char matrix[h][b]; // Array für den Plan
	int used[h][b]; // Array für die Positionen, an den sich Baulwürfe schon befinden
	// Textdatei wird eingelesen und gespeichert
	for (int i = 0; i < h; i++){
		string s;
		getline(cin, s);
		for (int j = 0; j < b; j++){
			matrix[i][j] = s[j];
			used[i][j] = 0;
		}
	}

	int ans = 0; //Antwort = 0
	
	// Man überprüft alle Positionen in der Array, an den sich ein Baulwurf befinden kann
	for (int i = 0; i < h-3; i++){
		for (int j = 0; j < b-2; j++){
			// Falls sich an der Position ein X befindet und ist kein Teil eines Baulwurfs
			if (matrix[i][j] == 'X' && used[i][j] == 0){
				// Falls diese Positonen dem "X" entsprechen, Antwort um 1 erhöhen und alle diesen Positionen als benutzt markieren
				if (matrix[i+1][j] == 'X' && matrix[i+2][j] == 'X' && matrix[i+3][j] == 'X' && matrix[i][j+1] == 'X' && matrix[i+1][j+1] == ' ' && matrix[i+2][j+1] == ' ' && matrix[i+3][j+1] == 'X' && matrix[i][j+2] == 'X' && matrix[i+1][j+2] == 'X' && matrix[i+2][j+2] == 'X' && matrix[i+3][j+2] == 'X'){
					ans++;
					used[i][j] = 1;
					used[i+1][j] = 1;
					used[i+2][j] = 1;
					used[i+3][j] = 1;
					used[i][j+1] = 1;
					used[i+3][j+1] = 1;
					used[i][j+2] = 1;
					used[i+1][j+2] = 1;
					used[i+2][j+2] = 1;
					used[i+3][j+2] = 1;
				}
			}
		}
	}

	cout << ans;

	
}