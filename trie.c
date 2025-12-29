#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "trie.h"

TrieNode *trie_kok = NULL;
static void to_lower_copy(char *hedef, const char *kaynak, int max_uzunluk) {
    int i;
    for (i = 0; i < max_uzunluk - 1 && kaynak[i] != '\0'; i++) {
        char c = kaynak[i];
        if (c >= 'A' && c <= 'Z') {
            c = (char)(c - 'A' + 'a');
        }
        hedef[i] = c;
    }
    hedef[i] = '\0';
}
static int harf_indeksi(char c) {
    if (c >= 'A' && c <= 'Z') {
        c = (char)(c - 'A' + 'a');
    }
    if (c >= 'a' && c <= 'z') {
        return c - 'a';
    }
    return -1;
}

static TrieNode *yeni_trie_dugumu(void) {
    TrieNode *dugum = (TrieNode *)malloc(sizeof(TrieNode));
    if (!dugum) return NULL;

    dugum->is_end_of_word = 0;
    dugum->kitap_sayisi = 0;
    for (int i = 0; i < TRIE_ALFABE; i++) {
        dugum->children[i] = NULL;
    }
    for (int i = 0; i < MAKS_KITAP; i++) {
        dugum->kitap_indeksleri[i] = -1;
    }
    return dugum;
}
void trie_ekle_baslik(const Kitap *k, int indeks) {
    if (trie_kok == NULL) {
        trie_kok = yeni_trie_dugumu();
        if (!trie_kok) return;
    }

    char baslik_kucuk[128];
    to_lower_copy(baslik_kucuk, k->baslik, sizeof(baslik_kucuk));

    TrieNode *simdiki = trie_kok;

    for (int i = 0; baslik_kucuk[i] != '\0'; i++) {
        int idx = harf_indeksi(baslik_kucuk[i]);
        if (idx < 0) {
            // Harf degilse (bosluk, noktalama vs.), atla
            continue;
        }

        if (simdiki->children[idx] == NULL) {
            simdiki->children[idx] = yeni_trie_dugumu();
            if (!simdiki->children[idx]) return;
        }

        simdiki = simdiki->children[idx];

        if (simdiki->kitap_sayisi < MAKS_KITAP) {
            simdiki->kitap_indeksleri[simdiki->kitap_sayisi] = indeks;
            simdiki->kitap_sayisi++;
        }
    }

    simdiki->is_end_of_word = 1;
}
void trie_yukle(void) {
    trie_kok = yeni_trie_dugumu();
    if (!trie_kok) {
        printf("Trie icin bellek ayirilamadi.\n");
        return;
    }

    for (int i = 0; i < kitap_sayisi; i++) {
        trie_ekle_baslik(&kitaplar[i], i);
    }
}
void trie_ara_baslik_on_ek(const char *on_ek) {
    if (trie_kok == NULL) {
        printf("Trie bos, once kitaplari yukleyin.\n");
        return;
    }

    if (on_ek == NULL || on_ek[0] == '\0') {
        printf("On ek bos olamaz.\n");
        return;
    }

    char on_ek_kucuk[128];
    to_lower_copy(on_ek_kucuk, on_ek, sizeof(on_ek_kucuk));

    TrieNode *simdiki = trie_kok;

    for (int i = 0; on_ek_kucuk[i] != '\0'; i++) {
        int idx = harf_indeksi(on_ek_kucuk[i]);
        if (idx < 0) {
            continue; // harf degilse atla
        }

        if (simdiki->children[idx] == NULL) {
            printf("\"%s\" ile baslayan baslik bulunamadi.\n", on_ek);
            return;
        }

        simdiki = simdiki->children[idx];
    }

    if (simdiki->kitap_sayisi == 0) {
        printf("\"%s\" ile baslayan baslik bulunamadi.\n", on_ek);
        return;
    }

    printf("\n\"%s\" on eki icin bulunan kitaplar:\n", on_ek);

    for (int i = 0; i < simdiki->kitap_sayisi; i++) {
        int kitap_idx = simdiki->kitap_indeksleri[i];
        if (kitap_idx < 0 || kitap_idx >= kitap_sayisi) continue;

        Kitap k = kitaplar[kitap_idx];
        printf("\nID       : %d\n", k.id);
        printf("Baslik   : %s\n", k.baslik);
        printf("Yazar    : %s\n", k.yazar);
        printf("Yil      : %d\n", k.yil);
        printf("Kategori : %s\n", k.kategori);
    }
}
