#include <stdio.h>
#include <string.h>
#include "kitap.h"
#include "dosya.h"

Kitap kitaplar[MAKS_KITAP];
int kitap_sayisi = 0;

static void newline_temizle(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}

static int id_var_mi(int id) {
    for (int i = 0; i < kitap_sayisi; i++) {
        if (kitaplar[i].id == id) return 1;
    }
    return 0;
}

static int id_index_bul(int id) {
    for (int i = 0; i < kitap_sayisi; i++) {
        if (kitaplar[i].id == id) return i;
    }
    return -1;
}

void tum_kitaplari_listele(void) {
    if (kitap_sayisi == 0) {
        printf("Listelenecek kitap yok.\n");
        return;
    }

    printf("\n=== Tum Kitaplar ===\n");
    for (int i = 0; i < kitap_sayisi; i++) {
        printf("\nID       : %d\n", kitaplar[i].id);
        printf("Baslik   : %s\n", kitaplar[i].baslik);
        printf("Yazar    : %s\n", kitaplar[i].yazar);
        printf("Yil      : %d\n", kitaplar[i].yil);
        printf("Kategori : %s\n", kitaplar[i].kategori);
    }
}

void kullanici_kitap_ekle(void) {
    if (kitap_sayisi >= MAKS_KITAP) {
        printf("Kitap eklenemedi: kapasite dolu.\n");
        return;
    }

    Kitap yeni;
    printf("\n=== Kitap Ekle ===\n");

    printf("ID: ");
    if (scanf("%d", &yeni.id) != 1) {
        printf("Gecersiz ID.\n");
        newline_temizle();
        return;
    }
    newline_temizle();

    if (id_var_mi(yeni.id)) {
        printf("Bu ID zaten var. Baska bir ID girin.\n");
        return;
    }

    printf("Baslik: ");
    scanf(" %99[^\n]", yeni.baslik);
    newline_temizle();

    printf("Yazar: ");
    scanf(" %99[^\n]", yeni.yazar);
    newline_temizle();

    printf("Yil: ");
    if (scanf("%d", &yeni.yil) != 1) {
        printf("Gecersiz yil.\n");
        newline_temizle();
        return;
    }
    newline_temizle();

    printf("Kategori: ");
    scanf(" %49[^\n]", yeni.kategori);
    newline_temizle();

    kitaplar[kitap_sayisi] = yeni;
    kitap_sayisi++;

    kitaplari_csvye_kaydet("kitaplar.csv");
    printf("Kitap eklendi. CSV dosyasina kaydedildi: kitaplar.csv\n");
}

void kullanici_kitap_sil(void) {
    if (kitap_sayisi == 0) {
        printf("Silinecek kitap yok.\n");
        return;
    }

    int id;
    printf("\n=== Kitap Sil ===\n");
    printf("Silinecek kitap ID: ");

    if (scanf("%d", &id) != 1) {
        printf("Gecersiz ID.\n");
        newline_temizle();
        return;
    }
    newline_temizle();

    int idx = id_index_bul(id);
    if (idx == -1) {
        printf("Bu ID ile kitap bulunamadi.\n");
        return;
    }

    for (int i = idx; i < kitap_sayisi - 1; i++) {
        kitaplar[i] = kitaplar[i + 1];
    }
    kitap_sayisi--;

    kitaplari_csvye_kaydet("kitaplar.csv");
    printf("Kitap silindi. CSV dosyasina kaydedildi: kitaplar.csv\n");
}

void ornek_kitaplari_yukle(void) {
    kitap_sayisi = 0;

    Kitap k[] = {
        // BILGISAYAR
        {1001, "Veri Yapilari ve Algoritmalar", "Thomas Cormen", 2012, "Bilgisayar"},
        {1002, "Algoritma Tasarimi", "Jon Kleinberg", 2005, "Bilgisayar"},
        {1003, "C Programlama Dili", "Kernighan & Ritchie", 1988, "Bilgisayar"},
        {1004, "Modern C", "Jens Gustedt", 2021, "Bilgisayar"},
        {1005, "Yapay Zeka: Bir Yaklasim", "Stuart Russell", 2010, "Bilgisayar"},
        {1006, "Python ile Programlama", "Mark Lutz", 2016, "Bilgisayar"},
        {1007, "Java Programlama", "Herbert Schildt", 2013, "Bilgisayar"},
        {1008, "Makine Ogrenmesi", "Ethem Alpaydin", 2014, "Bilgisayar"},
        {1009, "Deep Learning", "Ian Goodfellow", 2016, "Bilgisayar"},
        {1010, "Bilgisayar Mimarisi", "John Hennessy", 2011, "Bilgisayar"},

        // ROMAN
        {2001, "Simyaci", "Paulo Coelho", 1988, "Roman"},
        {2002, "Kurk Mantolu Madonna", "Sabahattin Ali", 1943, "Roman"},
        {2003, "Hayvan Ciftligi", "George Orwell", 1945, "Roman"},
        {2004, "1984", "George Orwell", 1949, "Roman"},
        {2005, "Cesur Yeni Dunya", "Aldous Huxley", 1932, "Roman"},
        {2006, "Seker Portakali", "Jose Mauro", 1968, "Roman"},
        {2007, "Tutunamayanlar", "Oguz Atay", 1972, "Roman"},
        {2008, "Bir Delinin Hatira Defteri", "Gogol", 1835, "Roman"},
        {2009, "Cocukluk", "Lev Tolstoy", 1852, "Roman"},
        {2010, "Anna Karenina", "Tolstoy", 1877, "Roman"},

        // BILIM
        {3001, "Zamanin Kisa Tarihi", "Stephen Hawking", 1988, "Bilim"},
        {3002, "Kozmos", "Carl Sagan", 1980, "Bilim"},
        {3003, "Evrenin Yapisi", "Brian Greene", 2011, "Bilim"},
        {3004, "Atomun Icinde", "Jim Al-Khalili", 2013, "Bilim"},
        {3005, "Beyin", "David Eagleman", 2015, "Bilim"},
        {3006, "Mutlu Beyin", "Loretta Graziano", 2017, "Bilim"},
        {3007, "Kara Delikler", "Stephen Hawking", 2016, "Bilim"},
        {3008, "Kaos Teorisi", "James Gleick", 1987, "Bilim"},
        {3009, "Sayi: Matematiksel Bir Yolculuk", "Tobias Dantzig", 1930, "Bilim"},
        {3010, "Sonsuzluk Problemleri", "David Hilbert", 1920, "Bilim"},

        // FANTASTIK
        {4001, "Hobbit", "J.R.R. Tolkien", 1937, "Fantastik"},
        {4002, "Yuzuklerin Efendisi", "J.R.R. Tolkien", 1954, "Fantastik"},
        {4003, "Harry Potter ve Felsefe Tasi", "J.K. Rowling", 1997, "Fantastik"},
        {4004, "Buz ve Atesin Sarkisi", "George R.R. Martin", 1996, "Fantastik"},
        {4005, "Narnia Gunlukleri", "C.S. Lewis", 1950, "Fantastik"},
        {4006, "Altin Pusula", "Philip Pullman", 1995, "Fantastik"},
        {4007, "Ejderha Mizragi Kronikleri", "Weis & Hickman", 1984, "Fantastik"},
        {4008, "Karanlik Orman", "Liu Cixin", 2008, "Fantastik"},
        {4009, "Golgenin Efendisi", "Brandon Sanderson", 2010, "Fantastik"},
        {4010, "Unutulmus Diyarlar", "R.A. Salvatore", 1990, "Fantastik"},

        // KLASIKLER
        {5001, "Suc ve Ceza", "Dostoyevski", 1866, "Klasik"},
        {5002, "Savas ve Baris", "Tolstoy", 1869, "Klasik"},
        {5003, "Beyaz Dis", "Jack London", 1906, "Klasik"},
        {5004, "Deniz Kurdu", "Jack London", 1904, "Klasik"},
        {5005, "Notre Dame'in Kamburu", "Victor Hugo", 1831, "Klasik"},
        {5006, "Donusum", "Franz Kafka", 1915, "Klasik"},
        {5007, "Madame Bovary", "Flaubert", 1857, "Klasik"},
        {5008, "Germinal", "Emile Zola", 1885, "Klasik"},
        {5009, "Jane Eyre", "Charlotte Bronte", 1847, "Klasik"},
        {5010, "Gurur ve Onyargi", "Jane Austen", 1813, "Klasik"},

        // DRAMA & DIGER
        {6001, "Siyah Inci", "Anna Sewell", 1877, "Drama"},
        {6002, "Peter Pan", "J.M. Barrie", 1911, "Macera"},
        {6003, "Robinson Crusoe", "Daniel Defoe", 1719, "Macera"},
        {6004, "Uyuyan Guzel", "Charles Perrault", 1697, "Masal"},
        {6005, "Pinokyo", "Carlo Collodi", 1883, "Masal"},
        {6006, "Define Adasi", "Robert Louis Stevenson", 1883, "Macera"},
        {6007, "Korsan Adasi", "Louis Stevenson", 1890, "Macera"},
        {6008, "Uc Silahsorlar", "Alexandre Dumas", 1844, "Macera"},
        {6009, "Monte Kristo Kontu", "Alexandre Dumas", 1844, "Macera"},
        {6010, "Kirmizi Baslikli Kiz", "Grimm Kardesler", 1812, "Masal"}
    };

    int toplam = (int)(sizeof(k) / sizeof(k[0]));
    for (int i = 0; i < toplam && i < MAKS_KITAP; i++) {
        kitaplar[i] = k[i];
    }
    kitap_sayisi = toplam;

}

