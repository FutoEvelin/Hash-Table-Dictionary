#ifndef SZOTAR_HEADER_H
#define SZOTAR_HEADER_H
// Futo Evelin, feim2349
#include "hasitotabla_header.h"

void beolvas(hashtable& szotar);
void jatek(hashtable& szotar);
void menu(hashtable& szotar);

const char* szotar_jelentes(const hashtable& szotar, const char* key); // jelentes
const char* szotar_forditas(const hashtable& szotar, const char* key); // forditas
const char* szavak(const hashtable& szotar, int index); 

#endif
