#include "szotar_header.h"
#include <fstream>
#include <cstring>
#include <iostream>
//Futo Evelin,feim2349
using namespace std;

const char* szotar_jelentes(const hashtable& szotar, const char* key) {
    try {
        int index = szotar.find(key); // index megkeresese
        if (szotar.getHashTable()[index].volt == -1 || index==-1 ||szotar.getHashTable()[index].volt == -2) { // ha az index -1 vagy -2 (azaz az elem torolve volt), akkor a szo nem talalhato
            throw "a szó nem található";
        }
        return szotar.getHashTable()[index].jelentes; // A jelentes visszateritese
    }
    catch (const char* uzenet) {
        return uzenet;
    }
}


const char* szotar_forditas(const hashtable& szotar, const char* key) {
    try {
        int index = szotar.find(key); // index megkeresese
        if (szotar.getHashTable()[index].volt == -1 || index==-1 || szotar.getHashTable()[index].volt == -2) { // ha az index -1 vagy -2 (azaz az elem torolve volt), akkor a szo nem talalhato
            throw "a szó nem található";
        }
        return szotar.getHashTable()[index].magyarul; // A forditas kiirása
    }
    catch (const char* uzenet) {
        return uzenet;
    }
}
void beolvas(hashtable& szotar) { // szavak beolvasasa
    ifstream in("szoo.in");
    char sor[101];

    while (in.getline(sor, sizeof(sor))) {
        char szo[101], jelentes[101], forditas[101];
        char* next = nullptr;

        try {
            char* t = strtok_s(sor, "\t", &next);
            if (t == nullptr) continue;
            if (strlen(t) > 100) throw "Túl hosszú a karaktersor"; // jelezzuk, ha a szo/ertelmezes/forditas hosszabb, mint 100 karakter
            strcpy_s(szo, sizeof(szo), t);

            t = strtok_s(NULL, "\t", &next);
            if (t == nullptr) continue;
            if (strlen(t) > 100) throw "Túl hosszú a karaktersor";
            strcpy_s(jelentes, sizeof(jelentes), t);

            t = strtok_s(NULL, "\t", &next);
            if (t == nullptr) continue;
            if (strlen(t) > 100) throw "Túl hosszú a karaktersor";
            strcpy_s(forditas, sizeof(forditas), t);

            szotar.insertitem(szo, jelentes, forditas);
        }
        catch (const char* uzenet) {
            cout << uzenet << endl;
            continue;
        }
    }
    in.close();
}


void jatek(hashtable& szotar) {
    cout << "Írd be a betűsorozatot: ";
    char betusorozat[256];
    try {
        cin.getline(betusorozat, sizeof(betusorozat));
        if (strlen(betusorozat) > sizeof(betusorozat) - 1) throw "Túl hosszú betűsorozat";
    }
    catch (const char* uzenet) {
        cout << uzenet << endl;
        return;
    }

    int talalatok = 0;
    int betuk[256] = { 0 };

    for (int i = 0; betusorozat[i] != '\0'; i++) {
        betuk[betusorozat[i]]++;
    }

    for (int i = 0; i < szotar.getHashertek(); i++) {
        const char* szo = szotar.getHashTable()[i].key;
        if (szotar.getHashTable()[i].volt != 1) continue;

        int betuk2[256] = { 0 };
        for (int j = 0; szo[j] != '\0'; j++) {
            betuk2[szo[j]]++;
        }

        bool van = true;
        for (int k = 0; k < 256; k++) {
            if (betuk2[k] > betuk[k]) {
                van = false;
                break;
            }
        }

        if (van) {
            cout << szo << endl;
            talalatok++;
        }
    }
    cout << talalatok << " szó található a megadott betűkből." << endl;
}


void menu(hashtable& szotar) {//valasztasi lehetoseget nyujtunk a felhasznalonak arra nezve, hogy mit szeretne elvegezni
    while (true) {
        cout << "SZÓTÁR!" << endl;
        cout << "1. opció-> SZÓ JELENTÉSE " << endl;
        cout << "2. opció-> SZÓ FORDÍTÁSA " << endl;
        cout << "3. opció-> SZÓ TÖRLÉSE " << endl;
        cout << "4. opció-> JÁTÉK " << endl;
        cout << "5. opció-> KILÉPÉS." << endl;
        cout << "VÁLASZD KI MIT SZERETNÉL! ";
        int valasztas;
        cin >> valasztas;
        cin.ignore();

        if (valasztas == 1) {
            try {
                char szo[100];
                cout << "Add meg a szót, aminek a jelentését szeretnéd megtudni angolul: ";
                cin.getline(szo, 100);
                if (strlen(szo) > 100) throw "túl hosszú szó";
                const char* jelent = szotar_jelentes(szotar, szo);
                cout << (jelent ? jelent : "Nincs jelentés") << endl;
            }
            catch (const char* uzenet) {
                cout << uzenet << endl;
            }
        }
        else if (valasztas == 2) {
            try {
                char szo[100];
                cout << "Add meg a szót, aminek a fordítását szeretnéd megtudni magyarul: ";
                cin.getline(szo, 100);
                if (strlen(szo) > 100) throw "túl hosszú szó";
                const char* ford = szotar_forditas(szotar, szo);
                cout << (ford ? ford : "Nincs fordítás") << endl;
            }
            catch (const char* uzenet) {
                cout << uzenet << endl;
            }
        }
        else if (valasztas == 3) {
            try {
                char szo[100];
                cout << "Add meg a szót, amit ki szeretnél törölni: ";
                cin.getline(szo, 100);
                if (strlen(szo) > 100) throw "túl hosszú szó";
                szotar.removeitem(szo);
                cout << "A szó törölve." << endl;
            }
            catch (const char* uzenet) {
                cout << uzenet << endl;
            }
        }
        else if (valasztas == 4) {
            jatek(szotar);
        }
        else if (valasztas == 5) {
            cout << "Kilépünk." << endl;
            return;
        }
        else {
            cout << "Helytelen választás! " << endl;
            return;
        }
    }
}

