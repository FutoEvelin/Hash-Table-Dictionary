#include <iostream>
#include <cstring>
#include <vector>
#include <fstream>
#include <functional>
#include "hasitotabla_header.h"
// Futo Evelin, feim2349
using namespace std;

hashtable::hashtable() { // inicializalas
    hashTable = new adattomb[hashertek];
    for (int i = 0; i < hashertek; ++i) {
        hashTable[i].volt = -1;
        strcpy_s(hashTable[i].key, "");
        strcpy_s(hashTable[i].jelentes, "");
        strcpy_s(hashTable[i].magyarul, "");
    }
}

hashtable::~hashtable() {
    delete[] hashTable;
}

int hashtable::hash1(const char* key)const { // hash1 fuggveny
    if (key == nullptr) return -1;
    hash<string> hashfuggveny;
    return hashfuggveny(string(key)) % hashertek;
}

int hashtable::hash2(const char* key)const { // hash2 fuggveny
    if (key == nullptr) return -1;
    hash<string> hashfuggveny;
    return hashfuggveny(string(key)) % (hashertek - 1) + 1;
}

bool hashtable::contains(const char* key) {
    if (find(key) != -1 && find(key) != -2)
        return 1;
    else return 0;
}

int hashtable::getsize() const {
    return szamlalo;
}

void hashtable::insertitem(const char* key, const char* jelentes, const char* angolul) {
    if (key == nullptr || jelentes == nullptr || angolul == nullptr) return;

    if (getsize() >= 0.75 * hashertek) { // ha a telitettsegi szint meghaladja a 75%-ot, akkor ujra meretezunk es ujra hash-elunk
        resize();
    }

    int index = hash1(key);
    int hash_1 = hash1(key);
    int hash_2 = hash2(key);
    int iteration = 0;

    while (hashTable[index].volt == 1 && iteration < hashertek) {
        index = (hash_1 + iteration * hash_2) % hashertek; // index kiszamitasa
        iteration++;
    }

    if (hashTable[index].volt != 1) {
        hashTable[index].volt = 1;
        strcpy_s(hashTable[index].key, key);
        strcpy_s(hashTable[index].jelentes, jelentes);
        strcpy_s(hashTable[index].magyarul, angolul);
        szamlalo++;
    }
}

void hashtable::removeitem(const char* key) { // elem torlese
    int index = find(key);
    if (contains(key)) {
        hashTable[index].volt = -2;
        strcpy_s(hashTable[index].key, "");
        strcpy_s(hashTable[index].jelentes, "");
        strcpy_s(hashTable[index].magyarul, "");
        szamlalo--;
    }
}



void hashtable::resize() { // ujrameretezes
    int ujmeret = hashertek * 2;
    adattomb* ujtabla = new adattomb[ujmeret];
    for (int i = 0; i < ujmeret; ++i) {
        ujtabla[i].volt = -1;
        strcpy_s(ujtabla[i].key, "");
        strcpy_s(ujtabla[i].jelentes, "");
        strcpy_s(ujtabla[i].magyarul, "");
    }

    int eredeti = hashertek;
    hashertek = ujmeret;
    for (int i = 0; i < eredeti; ++i) {
        if (hashTable[i].volt == 1) {
            int index = hash1(hashTable[i].key);
            int hash_1 = hash1(hashTable[i].key);
            int hash_2 = hash2(hashTable[i].key);
            int iteration = 0;
            while (ujtabla[index].volt == 1 && iteration < hashertek) { // rehash
                index = (hash_1 + iteration * hash_2) % ujmeret;
                iteration++;
            }
            ujtabla[index] = hashTable[i];
        }
    }

    delete[] hashTable;
    hashTable = ujtabla;
}

int hashtable::find(const char* key)const { // index kereses
    if (key == nullptr) return -1;

    int index = hash1(key);
    int hash_1 = hash1(key);
    int hash_2 = hash2(key);
    int iteration = 0;

    if (hashTable[index].volt == 1) {
        while (iteration < hashertek) {
            if (hashTable[index].volt != 1 || (hashTable[index].volt == 1 && strcmp(hashTable[index].key, key) == 0)) {
                return index;
            }
            index = (hash_1 + iteration * hash_2) % hashertek;
            iteration++;
        }
    }
    else
        return -1;
}

const char* hashtable::getKey(int index) const {
    if (index < 0 || index >= hashertek) {
        return nullptr;
    }
    if (hashTable[index].volt == 1) {
        return hashTable[index].key;
    }
    return nullptr;
}


const adattomb* hashtable::getHashTable() const {
    return hashTable;
}

int hashtable::getHashertek() const {
    return hashertek;
}

void hashtable:: printitems() {
    cout << endl << endl << endl;
    for (int i = 0; i < getsize(); i++) {
        if (hashTable[i].volt == 1) {
            cout << endl << hashTable[i].key << " " << hashTable[i].jelentes << " " << hashTable[i].magyarul << endl;
        }
    }
    cout << endl;
}
