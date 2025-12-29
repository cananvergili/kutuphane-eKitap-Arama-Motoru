#include <stdio.h>
#include "search.h"
#include "sort.h"
static void idye_gore_sirala(Kitap dizi[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            if (dizi[j].id < dizi[min_idx].id) {
                min_idx = j;
            }
        }
        if (min_idx != i) {
            Kitap temp = dizi[i];
            dizi[i] = dizi[min_idx];
            dizi[min_idx] = temp;
        }
    }
}

int binary_search_id(Kitap kaynak[], int n, int aranan_id) {
    if (n <= 0) {
        printf("Arama yapilacak kitap yok.\n");
        return -1;
    }
    Kitap dizi[MAKS_KITAP];
    for (int i = 0; i < n; i++) {
        dizi[i] = kaynak[i];
    }
    idye_gore_sirala(dizi, n);

    int left = 0;
    int right = n - 1;
    while (left <= right) {
        int mid = (left + right) / 2;

        if (dizi[mid].id == aranan_id) {
            printf("\n(Binary Search) Kitap bulundu:\n");
            printf("ID       : %d\n", dizi[mid].id);
            printf("Baslik   : %s\n", dizi[mid].baslik);
            printf("Yazar    : %s\n", dizi[mid].yazar);
            printf("Yil      : %d\n", dizi[mid].yil);
            printf("Kategori : %s\n", dizi[mid].kategori);
            return mid;
        }

        if (aranan_id < dizi[mid].id) {
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }

    printf("(Binary Search) Bu ID ile bir kitap bulunamadi.\n");
    return -1;
}
