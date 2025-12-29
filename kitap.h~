#ifndef KITAP_H
#define KITAP_H

#define MAKS_KITAP 500

typedef struct {
    int id;
    char baslik[100];
    char yazar[100];
    int yil;
    char kategori[50];
} Kitap;

extern Kitap kitaplar[MAKS_KITAP];
extern int kitap_sayisi;

// mevcutlar
void tum_kitaplari_listele(void);
void ornek_kitaplari_yukle(void);

// yeni eklenenler
int  kitap_id_var_mi(int id);
void kullanici_kitap_ekle(void);
void kullanici_kitap_sil(void);

#endif
