#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dosya.h"
#include "avl.h"
#include "trie.h"
#include "stack.h"

void kitaplari_csvye_kaydet(const char *dosya_adi) {
    FILE *f = fopen(dosya_adi, "w");
    if (f == NULL) {
        printf("CSV dosyasi olusturulamadi: %s\n", dosya_adi);
        return;
    }

    fprintf(f, "id;baslik;yazar;yil;kategori\n");

    for (int i = 0; i < kitap_sayisi; i++) {
        fprintf(f, "%d;%s;%s;%d;%s\n",
                kitaplar[i].id,
                kitaplar[i].baslik,
                kitaplar[i].yazar,
                kitaplar[i].yil,
                kitaplar[i].kategori);
    }

    fclose(f);
    printf("Kitaplar CSV dosyasina kaydedildi: %s\n", dosya_adi);
}

void csvden_kitap_yukle(const char *dosya_adi) {
    FILE *f = fopen(dosya_adi, "r");
    if (f == NULL) {
        printf("CSV dosyasi acilamadi: %s\n", dosya_adi);
        return;
    }

    char satir[512];
    int satir_no = 0;
    int yeni_sayac = 0;

    while (fgets(satir, sizeof(satir), f) != NULL) {
        if (satir_no == 0) {
            satir_no++;
            continue;
        }

        char *id_str = strtok(satir, ";\n");
        char *baslik_str = strtok(NULL, ";\n");
        char *yazar_str = strtok(NULL, ";\n");
        char *yil_str = strtok(NULL, ";\n");
        char *kategori_str = strtok(NULL, ";\n");

        if (!id_str || !baslik_str || !yazar_str || !yil_str || !kategori_str) {
            continue; // eksik satir
        }

        if (yeni_sayac >= MAKS_KITAP) {
            printf("Maksimum kitap sayisina ulasildi (%d). Fazlasi yuklenmedi.\n", MAKS_KITAP);
            break;
        }

        Kitap k;
        k.id = atoi(id_str);
        strncpy(k.baslik, baslik_str, sizeof(k.baslik) - 1);
        k.baslik[sizeof(k.baslik) - 1] = '\0';

        strncpy(k.yazar, yazar_str, sizeof(k.yazar) - 1);
        k.yazar[sizeof(k.yazar) - 1] = '\0';

        k.yil = atoi(yil_str);

        strncpy(k.kategori, kategori_str, sizeof(k.kategori) - 1);
        k.kategori[sizeof(k.kategori) - 1] = '\0';

        kitaplar[yeni_sayac] = k;
        yeni_sayac++;
        satir_no++;
    }

    fclose(f);

    kitap_sayisi = yeni_sayac;

    avl_kok = NULL;
    trie_kok = NULL;
    arama_sayisi = 0;

    avl_yukle();
    trie_yukle();

    printf("CSV dosyasindan %d kitap yuklendi ve veri yapilari guncellendi.\n", kitap_sayisi);
}
