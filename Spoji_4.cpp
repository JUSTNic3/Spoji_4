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
    datoteka << "-Trebate skupiti 4 �etona iste boje u nizu: okomito, vodoravno ili dijagonalno." << endl;
    datoteka << "-Mo�ete baciti samo jedan �eton po okretu." << endl;
    datoteka << "-Prvi igra� koji spoji 4 jednobojna �etona pobje�uje." << endl;
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
/*cout << "Dobrodo�li u Spoji 4" << endl;
    cout << "Odaberite 1 ako �elite zapo�eti igru" << endl;
    cout << "Odaberite 2 ako �elite provjeriti pravila" << endl;
    cout << "Odaberite 3 kako bi ste vidjeli va�e rezultate" << endl;
    fstream datoteka("pravila", ios::app);*/
/*
-poseban bin file ili odabir korisnika za pravila igre
-su�elje sa odabirom po�etka igre,pravila,imena igra�a rije�eno
-21 �eton za pojedinog igra�a
-max 2 igra�a
-znakovi na plo�i
-2d polje
-igra�a plo�a
-funkcija za provjeru 4 iste boje paralelno,okomito i dijagonalno
-spremanje rezultata u bin file (dodatna mogu�nost:sortiranje rezultata prema broju pobjeda ili kronolo�ki)

*ultra izazov(dodatan +):mogu�nost prestanka igre u bilo kojem trenutku te spremanje svega u bin file za kasniji nastavak

*/