#include <stdio.h>
#include <string.h>
#include "sort.h"


// Swap
static void kitap_swap(Kitap *a, Kitap *b) {
    Kitap temp = *a;
    *a = *b;
    *b = temp;
}

static int partition_yil(Kitap dizi[], int low, int high) {
    int pivot = dizi[high].yil;
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (dizi[j].yil <= pivot) {
            i++;
            kitap_swap(&dizi[i], &dizi[j]);
        }
    }
    kitap_swap(&dizi[i + 1], &dizi[high]);
    return i + 1;
}

void quick_sort_yil(Kitap dizi[], int low, int high) {
    if (low < high) {
        int pi = partition_yil(dizi, low, high);
        quick_sort_yil(dizi, low, pi - 1);
        quick_sort_yil(dizi, pi + 1, high);
    }
}

static void merge(Kitap dizi[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    Kitap L[n1], R[n2];

    for (int i = 0; i < n1; i++) L[i] = dizi[left + i];
    for (int j = 0; j < n2; j++) R[j] = dizi[mid + 1 + j];

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        if (strcmp(L[i].baslik, R[j].baslik) <= 0) {
            dizi[k++] = L[i++];
        } else {
            dizi[k++] = R[j++];
        }
    }

    while (i < n1) dizi[k++] = L[i++];
    while (j < n2) dizi[k++] = R[j++];
}

void merge_sort_baslik(Kitap dizi[], int left, int right) {
    if (left < right) {
        int mid = (left + right) / 2;
        merge_sort_baslik(dizi, left, mid);
        merge_sort_baslik(dizi, mid + 1, right);
        merge(dizi, left, mid, right);
    }
}


void kitaplari_yazdir_sirali(Kitap dizi[], int adet) {
    for (int i = 0; i < adet; i++) {
        printf("\nID       : %d\n", dizi[i].id);
        printf("Baslik   : %s\n", dizi[i].baslik);
        printf("Yazar    : %s\n", dizi[i].yazar);
        printf("Yil      : %d\n", dizi[i].yil);
        printf("Kategori : %s\n", dizi[i].kategori);
    }
}
