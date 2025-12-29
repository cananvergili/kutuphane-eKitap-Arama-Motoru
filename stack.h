#ifndef STACK_H
#define STACK_H

#define MAKS_YIGIN 100

extern int arama_yigini[MAKS_YIGIN];
extern int arama_sayisi;
void yigin_ekle(int id);
int yigin_geri_al(void);
void yigin_listele(void);

#endif