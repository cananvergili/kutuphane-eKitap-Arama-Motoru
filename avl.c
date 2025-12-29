#include <stdio.h>
#include <stdlib.h>
#include "avl.h"

AVLNode* avl_kok = NULL;

int max(int a, int b) {
    return (a > b) ? a : b;
}

int yukseklik(AVLNode* n) {
    return (n == NULL) ? 0 : n->yukseklik;
}

AVLNode* yeni_dugum(Kitap k) {
    AVLNode* node = (AVLNode*)malloc(sizeof(AVLNode));
    node->veri = k;
    node->sol = NULL;
    node->sag = NULL;
    node->yukseklik = 1;
    return node;
}

AVLNode* saga_dondur(AVLNode* y) {
    AVLNode* x = y->sol;
    AVLNode* T2 = x->sag;

    x->sag = y;
    y->sol = T2;

    y->yukseklik = max(yukseklik(y->sol), yukseklik(y->sag)) + 1;
    x->yukseklik = max(yukseklik(x->sol), yukseklik(x->sag)) + 1;

    return x;
}

AVLNode* sola_dondur(AVLNode* x) {
    AVLNode* y = x->sag;
    AVLNode* T2 = y->sol;

    y->sol = x;
    x->sag = T2;

    x->yukseklik = max(yukseklik(x->sol), yukseklik(x->sag)) + 1;
    y->yukseklik = max(yukseklik(y->sol), yukseklik(y->sag)) + 1;

    return y;
}

int denge(AVLNode* n) {
    if (n == NULL) return 0;
    return yukseklik(n->sol) - yukseklik(n->sag);
}

AVLNode* avl_ekle(AVLNode* kok, Kitap k) {
    if (kok == NULL)
        return yeni_dugum(k);

    if (k.id < kok->veri.id)
        kok->sol = avl_ekle(kok->sol, k);
    else if (k.id > kok->veri.id)
        kok->sag = avl_ekle(kok->sag, k);
    else
        return kok;

    kok->yukseklik = 1 + max(yukseklik(kok->sol), yukseklik(kok->sag));

    int d = denge(kok);


    if (d > 1 && k.id < kok->sol->veri.id)
        return saga_dondur(kok);


    if (d < -1 && k.id > kok->sag->veri.id)
        return sola_dondur(kok);


    if (d > 1 && k.id > kok->sol->veri.id) {
        kok->sol = sola_dondur(kok->sol);
        return saga_dondur(kok);
    }


    if (d < -1 && k.id < kok->sag->veri.id) {
        kok->sag = saga_dondur(kok->sag);
        return sola_dondur(kok);
    }

    return kok;
}

AVLNode* avl_ara(AVLNode* kok, int id) {
    if (kok == NULL)
        return NULL;

    if (id == kok->veri.id)
        return kok;

    if (id < kok->veri.id)
        return avl_ara(kok->sol, id);

    return avl_ara(kok->sag, id);
}

void avl_yukle() {
    for (int i = 0; i < kitap_sayisi; i++) {
        avl_kok = avl_ekle(avl_kok, kitaplar[i]);
    }
}
