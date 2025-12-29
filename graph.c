#include <stdio.h>
#include "graph.h"

#define MAKS_DUGUM 6

static const char *raf_isimleri[MAKS_DUGUM] = {
    "Giris",
    "Bilgisayar Rafii",
    "Bilimkurgu Rafii",
    "Fizik Rafii",
    "Roman Rafii",
    "Okuma Alani"
};

static int grafo[MAKS_DUGUM][MAKS_DUGUM] = {
    //  G   B   BK  F   R   O
    {  0,  1,  0,  0,  0,  0 },
    {  1,  0,  1,  1,  0,  0 },
    {  0,  1,  0,  0,  1,  0 },
    {  0,  1,  0,  0,  1,  1 },
    {  0,  0,  1,  1,  0,  1 },
    {  0,  0,  0,  1,  1,  0 }
};

void raflari_yazdir(void) {
    printf("\nRaf listesi:\n");
    for (int i = 0; i < MAKS_DUGUM; i++) {
        printf("%d - %s\n", i + 1, raf_isimleri[i]);
    }
}

void bfs_en_kisa_yol(int baslangic, int hedef) {
    if (baslangic < 0 || baslangic >= MAKS_DUGUM ||
        hedef < 0 || hedef >= MAKS_DUGUM) {
        printf("Gecersiz raf numarasi.\n");
        return;
    }

    int ziyaret[MAKS_DUGUM] = {0};
    int onceki[MAKS_DUGUM];
    int kuyruk[MAKS_DUGUM];
    int front = 0, rear = 0;

    for (int i = 0; i < MAKS_DUGUM; i++) {
        onceki[i] = -1;
    }

    ziyaret[baslangic] = 1;
    kuyruk[rear++] = baslangic;

    while (front < rear) {
        int u = kuyruk[front++];

        if (u == hedef) {
            break;
        }

        for (int v = 0; v < MAKS_DUGUM; v++) {
            if (grafo[u][v] == 1 && !ziyaret[v]) {
                ziyaret[v] = 1;
                onceki[v] = u;
                kuyruk[rear++] = v;
            }
        }
    }

    if (!ziyaret[hedef]) {
        printf("Bu iki raf arasinda yol bulunamadi.\n");
        return;
    }


    int yol[MAKS_DUGUM];
    int uzunluk = 0;
    int simdiki = hedef;

    while (simdiki != -1) {
        yol[uzunluk++] = simdiki;
        simdiki = onceki[simdiki];
    }

    printf("\nEn kisa yol: %s -> %s\n",
           raf_isimleri[baslangic], raf_isimleri[hedef]);
    printf("Rotalama (bastan sona):\n");

    for (int i = uzunluk - 1; i >= 0; i--) {
        printf("%s", raf_isimleri[yol[i]]);
        if (i > 0) {
            printf(" -> ");
        }
    }

    printf("\nToplam adim sayisi: %d\n", uzunluk - 1);
}
