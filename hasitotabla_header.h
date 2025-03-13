#ifndef HASITOTABLA_HEADER_H
#define HASITOTABLA_HEADER_H
// Futo Evelin, feim2349
#include <iostream>
#include <cstring>

struct adattomb {
    int volt;
    char key[101];
    char jelentes[101];
    char magyarul[101];
};

class hashtable {
private:
    adattomb* hashTable;
    int hashertek = 100;
    int szamlalo = 0;

public:
    hashtable();
    ~hashtable();
    int hash1(const char* key) const;
    int hash2(const char* key) const;
    int getsize() const;
    bool contains(const char* key);
    void insertitem(const char* key, const char* jelentes, const char* angolul);
    void removeitem(const char* key);
    void resize();
    int find(const char* key) const;
    const char* getKey(int index) const;
    const adattomb* getHashTable() const;
    int getHashertek() const;
    void  printitems();
};

#endif
