#ifndef AVL_H
#define AVL_H

#include "kitap.h"

typedef struct AVLNode {
    Kitap veri;
    int yukseklik;
    struct AVLNode *sol;
    struct AVLNode *sag;
} AVLNode;

extern AVLNode* avl_kok;

// AVL islevleri
AVLNode* avl_ekle(AVLNode* kok, Kitap k);
AVLNode* avl_ara(AVLNode* kok, int id);
void avl_yukle();

#endif
