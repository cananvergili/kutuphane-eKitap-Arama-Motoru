#include <stdio.h>
#include "stack.h"

int arama_yigini[MAKS_YIGIN];
int arama_sayisi = 0;

void yigin_ekle(int id) {
    if (arama_sayisi >= MAKS_YIGIN) {
        for (int i = 1; i < MAKS_YIGIN; i++) {
            arama_yigini[i - 1] = arama_yigini[i];
        }
        arama_sayisi = MAKS_YIGIN - 1;
    }
    arama_yigini[arama_sayisi] = id;
    arama_sayisi++;
}

int yigin_geri_al(void) {
    if (arama_sayisi == 0) {
        printf("Geri alinacak arama yok.\n");
        return -1;
    }

    int id = arama_yigini[arama_sayisi - 1];
    arama_sayisi--;

    printf("Son arama geri alindi (ID: %d).\n", id);
    return id;
}

void yigin_listele(void) {
    if (arama_sayisi == 0) {
        printf("Henuz arama gecmisi yok.\n");
        return;
    }

    printf("Arama gecmisi (sondan basa dogru):\n");
    for (int i = arama_sayisi - 1; i >= 0; i--) {
        printf("- ID: %d\n", arama_yigini[i]);
    }
}