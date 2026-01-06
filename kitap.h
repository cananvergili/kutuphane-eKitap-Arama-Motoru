#ifndef KITAP_H
#define KITAP_H

#define MAKS_KITAP 200

typedef struct {
    int id;
    char baslik[100];
    char yazar[100];
    int yil;
    char kategori[50];
} Kitap;

extern Kitap kitaplar[MAKS_KITAP];
extern int kitap_sayisi;

void tum_kitaplari_listele(void);
void ornek_kitaplari_yukle(void);

void kullanici_kitap_ekle(void);
void kullanici_kitap_sil(void);

#endif
