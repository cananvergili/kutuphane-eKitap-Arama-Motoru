#include <stdio.h>
#include <string.h>
#include "filtre.h"
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
void filtre_kategori_ve_yil(const char *kategori, int min_yil, int max_yil) {
    int bulunan = 0;

    printf("\nFiltre: kategori icinde \"%s\", yil araligi [%d, %d]\n",
           kategori, min_yil, max_yil);

    int kategori_filtre_var = (kategori != NULL &&
                               kategori[0] != '\0' &&
                               kategori[0] != '*');

    char aranan_kat_kucuk[64];
    if (kategori_filtre_var) {
        to_lower_copy(aranan_kat_kucuk, kategori, sizeof(aranan_kat_kucuk));
    }
    for (int i = 0; i < kitap_sayisi; i++) {
        Kitap k = kitaplar[i];

        int kategori_uygun = 1;

        if (kategori_filtre_var) {
            char kitap_kat_kucuk[64];
            to_lower_copy(kitap_kat_kucuk, k.kategori, sizeof(kitap_kat_kucuk));

            if (strstr(kitap_kat_kucuk, aranan_kat_kucuk) == NULL) {
                kategori_uygun = 0;
            }
        }

        int yil_uygun = (k.yil >= min_yil && k.yil <= max_yil);

        if (kategori_uygun && yil_uygun) {
            bulunan++;
            printf("\nID       : %d\n", k.id);
            printf("Baslik   : %s\n", k.baslik);
            printf("Yazar    : %s\n", k.yazar);
            printf("Yil      : %d\n", k.yil);
            printf("Kategori : %s\n", k.kategori);
        }
    }

    if (bulunan == 0) {
        printf("Verilen filtreye uyan kitap bulunamadi.\n");
    }
}
void skorlamali_arama(const char *aranan) {
    if (aranan == NULL || aranan[0] == '\0') {
        printf("Aranacak kelime bos olamaz.\n");
        return;
    }

    int skorlar[MAKS_KITAP];
    int indeksler[MAKS_KITAP];
    int adet = 0;

    char aranan_kucuk[100];
    to_lower_copy(aranan_kucuk, aranan, sizeof(aranan_kucuk));

    for (int i = 0; i < kitap_sayisi; i++) {
        Kitap k = kitaplar[i];
        int skor = 0;

        char baslik_kucuk[128];
        char yazar_kucuk[128];
        char kategori_kucuk[64];

        to_lower_copy(baslik_kucuk,   k.baslik,   sizeof(baslik_kucuk));
        to_lower_copy(yazar_kucuk,    k.yazar,    sizeof(yazar_kucuk));
        to_lower_copy(kategori_kucuk, k.kategori, sizeof(kategori_kucuk));

        int baslik_eslesme   = (strstr(baslik_kucuk,   aranan_kucuk) != NULL);
        int yazar_eslesme    = (strstr(yazar_kucuk,    aranan_kucuk) != NULL);
        int kategori_eslesme = (strstr(kategori_kucuk, aranan_kucuk) != NULL);

        if (baslik_eslesme)   skor += 3;
        if (yazar_eslesme)    skor += 2;
        if (kategori_eslesme) skor += 1;

        if (skor > 0) {
            skorlar[adet] = skor;
            indeksler[adet] = i;
            adet++;
        }
    }

    if (adet == 0) {
        printf("\"%s\" icin eslesen kitap bulunamadi.\n", aranan);
        return;
    }
    for (int i = 0; i < adet - 1; i++) {
        for (int j = 0; j < adet - 1 - i; j++) {
            if (skorlar[j] < skorlar[j + 1]) {
                int temp_skor = skorlar[j];
                skorlar[j] = skorlar[j + 1];
                skorlar[j + 1] = temp_skor;

                int temp_idx = indeksler[j];
                indeksler[j] = indeksler[j + 1];
                indeksler[j + 1] = temp_idx;
            }
        }
    }

    printf("\n\"%s\" icin skorlamali arama sonuclari (en yuksek skordan dusuge):\n",
           aranan);

    for (int i = 0; i < adet; i++) {
        int idx = indeksler[i];
        Kitap k = kitaplar[idx];

        printf("\nSkor     : %d\n", skorlar[i]);
        printf("ID       : %d\n", k.id);
        printf("Baslik   : %s\n", k.baslik);
        printf("Yazar    : %s\n", k.yazar);
        printf("Yil      : %d\n", k.yil);
        printf("Kategori : %s\n", k.kategori);
    }
}
