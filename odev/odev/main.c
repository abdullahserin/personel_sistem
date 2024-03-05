#include <stdio.h>
#include <string.h>

// Personel struct tanımı
struct Personel {
    char TCKimlik[11];
    char isim[20];
    char soyisim[16];
    char telefon[12];
    char bolum[31];
};

// Dosya adı
const char dosyaAdi[] = "personel.txt";

// Fonksiyon prototipleri
void menuGoster();
void kayitListele();
void kayitAra();
void kayitEkle();
void kayitSil();
void kayitGuncelle();

int main() {
    int secim;

    do {
        menuGoster();
        printf("Seciminizi girin (1-6): ");
        scanf("%d", &secim);

        switch (secim) {
            case 1:
                kayitListele();
                break;
            case 2:
                kayitAra();
                break;
            case 3:
                kayitEkle();
                break;
            case 4:
                kayitSil();
                break;
            case 5:
                kayitGuncelle();
                break;
            case 6:
                printf("Programdan cikiliyor...\n");
                break;
            default:
                printf("Gecersiz secim! Tekrar deneyin.\n");
        }

    } while (secim != 6);

    return 0;
}

void menuGoster() {
    printf("\n--- Personel Kayit Programi ---\n");
    printf("1. Kayitlari Listele\n");
    printf("2. Kayit Ara\n");
    printf("3. Kayit Ekle\n");
    printf("4. Kayit Sil\n");
    printf("5. Kayit Guncelle\n");
    printf("6. Cikis\n");
}

void kayitListele() {
    FILE *dosya = fopen(dosyaAdi, "r");
    if (dosya == NULL) {
        printf("Dosya acilamadi!\n");
        return;
    }

    printf("\n--- Tum Kayitlar ---\n");

    struct Personel personel;

    while (fread(&personel, sizeof(struct Personel), 1, dosya) == 1) {
        printf("T.C. Kimlik: %s\n", personel.TCKimlik);
        printf("Isim: %s\n", personel.isim);
        printf("Soyisim: %s\n", personel.soyisim);
        printf("Telefon: %s\n", personel.telefon);
        printf("Bolum: %s\n", personel.bolum);
        printf("------------------------\n");
    }

    fclose(dosya);
}

void kayitAra() {
    FILE *dosya = fopen(dosyaAdi, "r");
    if (dosya == NULL) {
        printf("Dosya acilamadi!\n");
        return;
    }

    char aramaKelimesi[30];
    int bulunan = 0;

    printf("Aranacak kelimeyi girin: ");
    scanf("%s", aramaKelimesi);

    struct Personel personel;

    while (fread(&personel, sizeof(struct Personel), 1, dosya) == 1) {
        if (strstr(personel.TCKimlik, aramaKelimesi) ||
            strstr(personel.isim, aramaKelimesi) ||
            strstr(personel.soyisim, aramaKelimesi) ||
            strstr(personel.telefon, aramaKelimesi) ||
            strstr(personel.bolum, aramaKelimesi)) {
            printf("T.C. Kimlik: %s\n", personel.TCKimlik);
            printf("Isim: %s\n", personel.isim);
            printf("Soyisim: %s\n", personel.soyisim);
            printf("Telefon: %s\n", personel.telefon);
            printf("Bolum: %s\n", personel.bolum);
            printf("------------------------\n");
            bulunan = 1;
        }
    }

    if (!bulunan) {
        printf("Kayit bulunamadi.\n");
    }

    fclose(dosya);
}

void kayitEkle() {
    FILE *dosya = fopen(dosyaAdi, "a");
    if (dosya == NULL) {
        printf("Dosya acilamadi!\n");
        return;
    }

    struct Personel personel;

    printf("T.C. Kimlik: ");
    scanf("%s", personel.TCKimlik);
    printf("Isim: ");
    scanf("%s", personel.isim);
    printf("Soyisim: ");
    scanf("%s", personel.soyisim);
    printf("Telefon: ");
    scanf("%s", personel.telefon);
    printf("Bolum: ");
    scanf("%s", personel.bolum);

    fwrite(&personel, sizeof(struct Personel), 1, dosya);

    printf("Kayit eklendi.\n");

    fclose(dosya);
}

void kayitSil() {
    FILE *dosya = fopen(dosyaAdi, "r");
    if (dosya == NULL) {
        printf("Dosya acilamadi!\n");
        return;
    }

    FILE *geciciDosya = fopen("gecici.txt", "w");
    if (geciciDosya == NULL) {
        printf("Gecici dosya acilamadi!\n");
        fclose(dosya);
        return;
    }

    char silinecekTCKimlik[12];
    int bulunan = 0;

    printf("Silinecek personelin T.C. Kimlik numarasini girin: ");
    scanf("%s", silinecekTCKimlik);

    struct Personel personel;

    while (fread(&personel, sizeof(struct Personel), 1, dosya) == 1) {
        if (strcmp(personel.TCKimlik, silinecekTCKimlik) != 0) {
            fwrite(&personel, sizeof(struct Personel), 1, geciciDosya);
        } else {
            bulunan = 1;
        }
    }

    fclose(dosya);
    fclose(geciciDosya);

    remove(dosyaAdi);
    rename("gecici.txt", dosyaAdi);

    if (bulunan) {
        printf("Kayit silindi.\n");
    } else {
        printf("Kayit bulunamadi.\n");
    }
}

void kayitGuncelle() {
    FILE *dosya = fopen(dosyaAdi, "r");
    if (dosya == NULL) {
        printf("Dosya acilamadi!\n");
        return;
    }

    FILE *geciciDosya = fopen("gecici.txt", "w");
    if (geciciDosya == NULL) {
        printf("Gecici dosya acilamadi!\n");
        fclose(dosya);
        return;
    }

    char guncellenecekTCKimlik[12];
    int bulunan = 0;

    printf("Guncellenecek personelin T.C. Kimlik numarasini girin: ");
    scanf("%s", guncellenecekTCKimlik);

    struct Personel personel;

    while (fread(&personel, sizeof(struct Personel), 1, dosya) == 1) {
        if (strcmp(personel.TCKimlik, guncellenecekTCKimlik) == 0) {
            printf("Yeni isim: ");
            scanf("%s", personel.isim);
            printf("Yeni soyisim: ");
            scanf("%s", personel.soyisim);
            printf("Yeni telefon: ");
            scanf("%s", personel.telefon);
            printf("Yeni bolum: ");
            scanf("%s", personel.bolum);

            fwrite(&personel, sizeof(struct Personel), 1, geciciDosya);
            bulunan = 1;
        } else {
            fwrite(&personel, sizeof(struct Personel), 1, geciciDosya);
        }
    }

    fclose(dosya);
    fclose(geciciDosya);

    remove(dosyaAdi);
    rename("gecici.txt", dosyaAdi);

    if (bulunan) {
        printf("Kayit guncellendi.\n");
    } else {
        printf("Kayit bulunamadi.\n");
    }
}


