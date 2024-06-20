#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct hastaBilgileri {
    char tc[20];
    char ad[20];
    char soyad[20];
    char cinsiyet;
    char dtarih[20];
    char adres[20];
    char tel[20];
    char sifre[20];
    int durum;
    char rtarih[20];
    char rsaat[20];
    float boy;
    float kilo;
    float vki;
} Hasta;

typedef struct hastaNode {
    Hasta hasta;
    struct hastaNode* next;
} HastaNode;

typedef struct {
    HastaNode* head;
} HastaList;
void listeyeEkle(HastaList* liste, Hasta hasta) {
    HastaNode* yeniNode = (HastaNode*)malloc(sizeof(HastaNode));
    yeniNode->hasta = hasta;
    yeniNode->next = NULL;

    if (liste->head == NULL) {
        liste->head = yeniNode;
    } else {
        HastaNode* iter = liste->head;
        while (iter->next != NULL) {
            iter = iter->next;
        }
        iter->next = yeniNode;
    }
}

void listeYazdir(HastaList* liste) {
    HastaNode* iter = liste->head;
    while (iter != NULL) {
        printf("%s\t%s\t%s\t%c\t%s\t%s\t%s\n", iter->hasta.tc, iter->hasta.ad, iter->hasta.soyad, iter->hasta.cinsiyet, iter->hasta.dtarih, iter->hasta.rtarih, iter->hasta.rsaat);
        iter = iter->next;
    }
}

Hasta* listedeAra(HastaList* liste, char* tc) {
    HastaNode* iter = liste->head;
    while (iter != NULL) {
        if (strcmp(iter->hasta.tc, tc) == 0) {
            return &(iter->hasta);
        }
        iter = iter->next;
    }
    return NULL;
}

void listeyiTemizle(HastaList* liste) {
    HastaNode* iter = liste->head;
    while (iter != NULL) {
        HastaNode* temp = iter;
        iter = iter->next;
        free(temp);
    }
    liste->head = NULL;
}
void giris(HastaList* hastaListesi) {
    system("cls");
    printf("Giris ekrani \n");
    char tc[20], sifre[20];
    printf("TC       : ");
    scanf(" %[^\n]s", tc);
    printf("PAROLA   : ");
    scanf(" %[^\n]s", sifre);

    Hasta* hasta = listedeAra(hastaListesi, tc);

    if (hasta != NULL && strcmp(sifre, hasta->sifre) == 0) {
        printf("%s %s hos geldiniz \n", hasta->ad, hasta->soyad);
        printf("Randevu tarihi : ");
        scanf(" %[^\n]s", hasta->rtarih);
        printf("Randevu saati  : ");
        scanf(" %[^\n]s", hasta->rsaat);

        printf("%s randevu talebiniz alinmistir \n", hasta->ad);
    } else {
        printf("hatali giris islemi \n");
    }
}

void yeniKayit(HastaList* hastaListesi) {
    system("cls");
    printf("Yeni kayit ekrani \n");
    Hasta yeniHasta;
    printf("TC       : ");
    scanf(" %[^\n]s", yeniHasta.tc);
    printf("AD       : ");
    scanf(" %[^\n]s", yeniHasta.ad);
    printf("SOYAD    : ");
    scanf(" %[^\n]s", yeniHasta.soyad);
    printf("CINSIYET : ");
    scanf(" %c", &yeniHasta.cinsiyet);
    printf("dTARIH   : ");
    scanf(" %[^\n]s", yeniHasta.dtarih);
    printf("ADRES    : ");
    scanf(" %[^\n]s", yeniHasta.adres);
    printf("GSM      : ");
    scanf(" %[^\n]s", yeniHasta.tel);
    printf("PAROLA   : ");
    scanf(" %[^\n]s", yeniHasta.sifre);
    yeniHasta.durum = 0;
    strcpy(yeniHasta.rtarih, "0.0");
    strcpy(yeniHasta.rsaat, "0.0");
    yeniHasta.boy = 0;
    yeniHasta.kilo = 0;
    yeniHasta.vki = 0.0;

    listeyeEkle(hastaListesi, yeniHasta);
    printf("Yeni kayit tamam \n");
}

void parolaHatirlat(HastaList* hastaListesi) {
    system("cls");
    printf("Parola hatirlatma ekrani \n");
    char tc[20], dtarih[20];
    printf("TC       : ");
    scanf(" %[^\n]s", tc);
    printf("dTarihi  : ");
    scanf(" %[^\n]s", dtarih);

    Hasta* hasta = listedeAra(hastaListesi, tc);

    if (hasta != NULL && strcmp(dtarih, hasta->dtarih) == 0) {
        printf("%s %s  sifreniz : %s \n", hasta->ad, hasta->soyad, hasta->sifre);
    } else {
        printf("%s ve %s ile eslesen kayit yok \n", tc, dtarih);
    }
}

void hastaGiris(HastaList* hastaListesi) {
    system("cls");
    printf("Hasta giris ekrani \n");
    
    int secim;
    do {
        printf("1- Giris \n");
        printf("2- Yeni kayit  \n");
        printf("3- Parola hatirlat \n");
        printf("0- Ana menuye don \n");
        printf("Seciminiz : ");
        scanf("%d", &secim);
        
        switch(secim) {
            case 1: giris(hastaListesi); break;
            case 2: yeniKayit(hastaListesi); break;
            case 3: parolaHatirlat(hastaListesi); break;
            case 0: return; 
            default: printf("Hatali secim yaptiniz, lutfen tekrar deneyin.\n");
        }
    } while(secim != 0);
}

void sekreter(HastaList* hastaListesi) {
    system("cls");
    printf("Sekreter giris ekrani \n");

    HastaNode* iter = hastaListesi->head;
    int sonuc = 0;

    while (iter != NULL) {
        if (iter->hasta.durum == 0) {
            sonuc = 1;
            printf("%s\t%s\t%s\t%c\t%s\t%s\t%s\n", iter->hasta.tc, iter->hasta.ad, iter->hasta.soyad, iter->hasta.cinsiyet, iter->hasta.dtarih, iter->hasta.rtarih, iter->hasta.rsaat);

            printf("1- Randevu talebini onayla \n");
            printf("2- Randevu talebini reddet \n");
            printf("3- Anamenuye don \n");
            printf("seciminiz  : ");
            int secim;
            scanf("%d", &secim);

            if (secim == 1) {
                iter->hasta.durum = 1;
                printf("%s randevu talebi onaylandi\n", iter->hasta.ad);
            } else if (secim == 2) {
                iter->hasta.durum = 2;
                printf("%s randevu talebi reddedildi\n", iter->hasta.ad);
            } else {
                return;
            }
        }
        iter = iter->next;
    }

    if (sonuc == 0)
        printf("bekleyen hasta yok \n");
    printf("Ana menuye yonlendiriliyorsunuz... \n");
}

void doktor(HastaList* hastaListesi) {
    system("cls");
    printf("Diyetisyen giris ekrani \n");

    HastaNode* iter = hastaListesi->head;
    int secim = -1;
    int sonuc = 0;
    char teshis[20];
    char aciklama[100];

    while (iter != NULL) {
        if (iter->hasta.durum == 0) {
            sonuc = 1;
            printf("%s\t%s\t%s\t%c\t%s\n", iter->hasta.tc, iter->hasta.ad, iter->hasta.soyad, iter->hasta.cinsiyet, iter->hasta.dtarih);

            printf("1- Hastayi guncelle \n");
            printf("2- Anamenuye don \n");
            printf("seciminiz  : ");
            scanf("%d", &secim);

            if (secim == 1) {
                printf("Hasta boy : ");
                scanf("%f", &iter->hasta.boy);
                printf("Hasta kilo : ");
                scanf("%f", &iter->hasta.kilo);
                iter->hasta.vki = iter->hasta.kilo / pow(iter->hasta.boy / 100, 2);
                printf("Hasta VKI : %f\n", iter->hasta.vki);
            } else {
                return;
            }
        }
        iter = iter->next;
    }

    if (sonuc == 0)
        printf("hasta bulunamadi \n");
}

void yonetici(HastaList* hastaListesi) {
    system("cls");
    printf("Yonetici giris ekrani \n");

    listeYazdir(hastaListesi);
    printf("Ana menuye yonlendiriliyorsunuz... \n");
}
int main() {
    HastaList hastaListesi;
    hastaListesi.head = NULL;

    int secim;
    do {
        printf("Hastane Otomasyon Sistemine Hosgeldiniz\n");
        printf("1- Hasta girisi \n");
        printf("2- Sekreter girisi  \n");
        printf("3- Diyetisyen girisi \n");
        printf("4- Yonetici girisi \n");
        printf("0- Cikis \n");
        printf("Seciminiz : ");
        scanf("%d", &secim);
        
        switch(secim) {
            case 1: hastaGiris(&hastaListesi); break;
            case 2: sekreter(&hastaListesi); break;
            case 3: doktor(&hastaListesi); break;
            case 4: yonetici(&hastaListesi); break;
            case 0: break;
            default: printf("Hatali secim yaptiniz, lutfen tekrar deneyin.\n");
        }
    } while(secim != 0);

    listeyiTemizle(&hastaListesi);
    return 0;
}

