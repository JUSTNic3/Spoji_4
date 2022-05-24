#include <iostream>
#include <fstream>
#include <stdlib.h>
using namespace std;

int main()
{
    fstream datoteka("Pravila.txt");
    if(!datoteka.is_open())
        datoteka.open("Pravila.txt", ios::app);
    datoteka << "\t" << "Pravila igre" << "\t" << endl;
    datoteka << "-Trebate skupiti 4 žetona iste boje u nizu: okomito, vodoravno ili dijagonalno." << endl;
    datoteka << "-Možete baciti samo jedan žeton po okretu." << endl;
    datoteka << "-Prvi igraè koji spoji 4 jednobojna žetona pobjeðuje." << endl;
    while (1)
    {
        system("cls");
        cout << "Dobrodosli u Spoji 4" << endl << endl;
        cout << "1. pocetak igre" << endl;
        cout << "2. ispis pravila igre" << endl;
        cout << "3. ispis rezultata" << endl;
        cout << "4. izlaz iz programa" << endl << endl;
        cout << "Vas odabir: ";
        int izbor;
        cin >> izbor;
        if (izbor == 1){
        }
        else if (izbor == 2){
        }
        else if(izbor == 4){
            cout << "Dovidjenja!";
            break;
        }
        else{
            cout << "Krivi unos!" << endl;
        }
       system("pause");
    }  
}
/*cout << "Dobrodošli u Spoji 4" << endl;
    cout << "Odaberite 1 ako želite zapoèeti igru" << endl;
    cout << "Odaberite 2 ako želite provjeriti pravila" << endl;
    cout << "Odaberite 3 kako bi ste vidjeli vaše rezultate" << endl;
    fstream datoteka("pravila", ios::app);*/
/*
-poseban bin file ili odabir korisnika za pravila igre
-suèelje sa odabirom poèetka igre,pravila,imena igraèa riješeno
-21 žeton za pojedinog igraèa
-max 2 igraèa
-znakovi na ploèi
-2d polje
-igraèa ploèa
-funkcija za provjeru 4 iste boje paralelno,okomito i dijagonalno
-spremanje rezultata u bin file (dodatna moguænost:sortiranje rezultata prema broju pobjeda ili kronološki)

*ultra izazov(dodatan +):moguænost prestanka igre u bilo kojem trenutku te spremanje svega u bin file za kasniji nastavak

*/