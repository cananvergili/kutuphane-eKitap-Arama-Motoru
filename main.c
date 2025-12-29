#include <stdio.h>
#include "kitap.h"
#include "menu.h"
#include "avl.h"
#include "trie.h"
#include "gui.h"

int main(void) {
    int program_bitti_mi = 0;

    int baslatilsin_mi = gui_calistir();

    if (!baslatilsin_mi) {

        printf("Program, GUI uzerinden kapatildi.\n");
        return 0;
    }

    printf("Kutuphane yonetim sistemi baslatiliyor...\n");

    ornek_kitaplari_yukle();

    avl_yukle();
    trie_yukle();

    while (!program_bitti_mi) {
        menuyu_yazdir();

        int secim = kullanicidan_secim_al();
        if (secim == -1) {
            break;
        }

        secimi_isle(secim, &program_bitti_mi);
    }

    printf("Program sonlandi. Iyi gunler.\n");
    return 0;
}
