#include <stdio.h>
#include <stdlib.h>
#include "menu.h"
#include "kitap.h"
#include "avl.h"
#include "trie.h"
#include "sort.h"
#include "stack.h"
#include "search.h"
#include "filtre.h"
#include "graph.h"
#include "dosya.h"

static void ekrani_temizle(void) {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

static void devam_et(void) {
    printf("\nDevam etmek icin Enter'a basin...");
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
    getchar();
}

void menuyu_yazdir(void) {
    ekrani_temizle();

    printf("=====================================================\n");
    printf("        KUTUPHANE / e-KITAP ARAMA MOTORU             \n");
    printf("=====================================================\n");
    printf("  Dengeli Agac: AVL, Trie                            \n");
    printf("  Arama       : AVL ID, Trie baslik, Binary Search   \n");
    printf("  Siralama    : Quick Sort, Merge Sort               \n");
    printf("  Ekstra      : Stack, BFS, Filtre, CSV, Skor        \n");
    printf("=====================================================\n\n");

    printf("  [1]  Tum kitaplari listele\n");
    printf("  [2]  Kitap ID ile arama (AVL)\n");
    printf("  [3]  Kitap basligina gore arama (Trie)\n");
    printf("  [4]  Kitaplari yila gore sirala (Quick Sort)\n");
    printf("  [5]  Kitaplari basliga gore sirala (Merge Sort)\n");
    printf("  [6]  Arama gecmisini listele (Stack)\n");
    printf("  [7]  Son aramayi geri al (Stack)\n");
    printf("  [8]  Binary Search ile ID arama\n");
    printf("  [9]  Kategori + yil araligina gore filtrele\n");
    printf("  [10] Skorlamali arama (baslik/yazar/kategori)\n");
    printf("  [11] Raflar arasindaki en kisa yol (BFS)\n");
    printf("  [12] Kitaplari CSV dosyasina kaydet\n");
    printf("  [13] CSV dosyasindan kitap yukle\n");
    printf("  [14] Yeni kitap ekle (otomatik CSV)\n");
    printf("  [15] Kitap sil (otomatik CSV)\n");
    printf("  [0]  Cikis\n\n");
}

int kullanicidan_secim_al(void) {
    int secim;
    printf("Seciminiz: ");

    if (scanf("%d", &secim) != 1) {
        printf("Gecersiz giris yapildi. Program sonlandiriliyor.\n");
        return -1;
    }

    return secim;
}

void secimi_isle(int secim, int *program_bitti_mi) {
    switch (secim) {

        case 0:
            printf("Programdan cikiliyor...\n");
            *program_bitti_mi = 1;
            break;

        case 1:
            tum_kitaplari_listele();
            devam_et();
            break;

        case 2: {
            int id;
            printf("Aramak istediginiz ID: ");
            scanf("%d", &id);

            AVLNode* sonuc = avl_ara(avl_kok, id);

            if (sonuc) {
                printf("\nKitap bulundu:\n");
                printf("ID       : %d\n", sonuc->veri.id);
                printf("Baslik   : %s\n", sonuc->veri.baslik);
                printf("Yazar    : %s\n", sonuc->veri.yazar);
                printf("Yil      : %d\n", sonuc->veri.yil);
                printf("Kategori : %s\n", sonuc->veri.kategori);

                yigin_ekle(id);
            } else {
                printf("Bu ID ile bir kitap bulunamadi.\n");
            }
            devam_et();
            break;
        }

        case 3: {
            char on_ek[100];
            printf("Aramak istediginiz baslik on egi: ");
            scanf(" %99[^\n]", on_ek);

            trie_ara_baslik_on_ek(on_ek);
            devam_et();
            break;
        }

        case 4: {
            if (kitap_sayisi == 0) {
                printf("Siralanacak kitap yok.\n");
                devam_et();
                break;
            }

            Kitap kopya[MAKS_KITAP];
            for (int i = 0; i < kitap_sayisi; i++) {
                kopya[i] = kitaplar[i];
            }

            quick_sort_yil(kopya, 0, kitap_sayisi - 1);

            printf("\nYila gore siralanmis kitaplar:\n");
            kitaplari_yazdir_sirali(kopya, kitap_sayisi);
            devam_et();
            break;
        }

        case 5: {
            if (kitap_sayisi == 0) {
                printf("Siralanacak kitap yok.\n");
                devam_et();
                break;
            }

            Kitap kopya[MAKS_KITAP];
            for (int i = 0; i < kitap_sayisi; i++) {
                kopya[i] = kitaplar[i];
            }

            merge_sort_baslik(kopya, 0, kitap_sayisi - 1);

            printf("\nBasliga gore siralanmis kitaplar:\n");
            kitaplari_yazdir_sirali(kopya, kitap_sayisi);
            devam_et();
            break;
        }

        case 6:
            yigin_listele();
            devam_et();
            break;

        case 7:
            yigin_geri_al();
            devam_et();
            break;

        case 8: {
            int id;
            printf("Binary Search ile aramak istediginiz ID: ");
            scanf("%d", &id);

            binary_search_id(kitaplar, kitap_sayisi, id);
            devam_et();
            break;
        }

        case 9: {
            char kategori[50];
            int min_yil, max_yil;

            printf("Kategori (hepsi icin * yazabilirsiniz): ");
            scanf(" %49[^\n]", kategori);

            printf("Minimum yil: ");
            scanf("%d", &min_yil);

            printf("Maksimum yil: ");
            scanf("%d", &max_yil);

            filtre_kategori_ve_yil(kategori, min_yil, max_yil);
            devam_et();
            break;
        }

        case 10: {
            char kelime[100];
            printf("Aramak istediginiz kelime (baslik/yazar/kategori icin): ");
            scanf(" %99[^\n]", kelime);

            skorlamali_arama(kelime);
            devam_et();
            break;
        }

        case 11: {
            int bas, hedef;

            raflari_yazdir();

            printf("Baslangic raf numarasi: ");
            scanf("%d", &bas);
            printf("Hedef raf numarasi   : ");
            scanf("%d", &hedef);

            bfs_en_kisa_yol(bas - 1, hedef - 1);
            devam_et();
            break;
        }

        case 12:
            kitaplari_csvye_kaydet("kitaplar.csv");
            devam_et();
            break;

        case 13:
            csvden_kitap_yukle("kitaplar.csv");
            devam_et();
            break;

        case 14:
            kullanici_kitap_ekle();
            devam_et();
            break;

        case 15:
            kullanici_kitap_sil();
            devam_et();
            break;

        default:
            printf("Gecersiz secim, lutfen menuden bir sayi girin.\n");
            devam_et();
            break;
    }
}
