#ifndef TRIE_H
#define TRIE_H

#include "kitap.h"

#define TRIE_ALFABE 26  // a-z

typedef struct TrieNode {
    struct TrieNode *children[TRIE_ALFABE];
    int is_end_of_word;
    int kitap_indeksleri[MAKS_KITAP];
    int kitap_sayisi;
} TrieNode;

extern TrieNode *trie_kok;
void trie_yukle(void);
void trie_ekle_baslik(const Kitap *k, int indeks);
void trie_ara_baslik_on_ek(const char *on_ek);

#endif
