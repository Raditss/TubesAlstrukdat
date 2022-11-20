

#ifndef _KULKAS_H
#define _KULKAS_H

#include "../QueueFood/queuefood.h"

#define CAPACITY_MATRIKS_KULKAS 20
#define IdxType int
/* Definisi Kulkas */
typedef struct
{
    Makanan Isi[CAPACITY_MATRIKS_KULKAS][CAPACITY_MATRIKS_KULKAS];
    boolean Terisi[CAPACITY_MATRIKS_KULKAS][CAPACITY_MATRIKS_KULKAS];
} Kulkas;

#define ISI_KULKAS(K, X, Y) (K).Isi[X][Y]
#define TERISI(K, X, Y) (K).Terisi[X][Y]

/* Membuat kulkas pada Simulator*/
void createKulkas(Kulkas *k)
{
    // Definisikan sebuah kulkas kosong
    /* I.S. Kulkas Sembarang */
    /* F.S. Kulkas berisi matriks isi makanan dan matriks penanda terisi*/
    for (IdxType i = 0; i < CAPACITY_MATRIKS_KULKAS; i++)
    {
        for (IdxType j = 0; j < CAPACITY_MATRIKS_KULKAS; j++)
        {
            TERISI(*k, i, j) = false;
        }
    }
}

boolean isValidIndeksKulkas(int baris, int kolom)
{
    /* Mengecek apakah indeks berada pada matriks kulkas*/
    return ((baris > 0) && (baris <= CAPACITY_MATRIKS_KULKAS) && (kolom > 0) && (kolom <= CAPACITY_MATRIKS_KULKAS));
}

void displayKulkas(Kulkas k)
{ /* Melakukan display isi Kulkas */
    printf("______________________\n");
    for (IdxType i = 0; i < CAPACITY_MATRIKS_KULKAS; i++)
    {
        printf("|");
        for (IdxType j = 0; j < CAPACITY_MATRIKS_KULKAS; j++)
        {
            if (TERISI(k, i, j))
                printf("X");
            else
            {
                printf(" ");
            }
        }

        printf("|\n");
    }
    printf("----------------------\n");
}

boolean positionAvaliable(Makanan isi, Kulkas *k, int baris, int kolom)
{
    /* Mengecek apakah suatu posisi pada kulkas memungkinan untuk menaruh makanan */
    /* I.S. Sembarang */
    /* F.S. Kulkas akan terisi makanan apabila memungkinkan makanan tersebut ditaruh
            pada posisi tersebut */
    Kulkas temp = *k;

    for (IdxType i = baris - 1; i < baris + PANJANG(isi) - 1; i++)
    {
        for (IdxType j = kolom - 1; j < kolom + LEBAR(isi) - 1; j++)
        {
            if (TERISI(temp, i, j) || !(isValidIndeksKulkas(i + 1, j + 1)))
            {
                return false;
            }
            else
            {
                TERISI(temp, i, j) = true;
                ISI_KULKAS(temp, i, j) = isi;
            }
        }
    }

    *k = temp;
    return true;
}

void masukanMakananKeKulkas(Simulator *sim, Kulkas *k, Makanan isi, boolean *IsValid)
{
    /* Memasukkan makanan pada kulkas */
    /* I.S. Sembarang */
    /* F.S. Kulkas akan berisi makanan yang baru ditambahkan.
            Waktu akan berganti bila sukses memasukkan makanan. */
    displayKulkas(*k);

    printf("\nNama makanan = ");
    DisplayWordNoEnter(NAMA(isi));
    printf("\nUkuran = (%d,%d)", PANJANG(isi), LEBAR(isi));
    printf("\nMasukkan posisi koordinat yang akan ditempatkan untuk makanan!\n");
    printf("NOTE : Untuk posisi bagian kiri atas makanan\n");
    printf("----------------------\n");
    printf("Enter Baris: ");
    STARTKALIMAT();
    int Baris = strToIntV2(kalimatToWord(currentKalimat));

    printf("Enter Kolom: ");
    STARTKALIMAT();
    int Kolom = strToIntV2(kalimatToWord(currentKalimat));
    printf("============================================================================\n");
    if (isValidIndeksKulkas(Baris, Kolom))
    {
        if (positionAvaliable(isi, k, Baris, Kolom))
        {
            *IsValid = true;
            printf("Berhasil Memasukkan Makanan Ke Dalam Kulkas!\n");
        }
        else
        {
            printf("Gagal Memasukkan Makanan Ke Dalam Kulkas\n");
        }
    }
    else
    {
        printf("Indeks Posisi Tidak Valid!\n");
    }
}

boolean isIdxInventoryValid(PrioQueueTime q, IdxType i)
{
    /* Cek apakah indeks elemen Priority Queue pada Inventory User valid */
    return (i > 0) && (i <= NBElmtFood(q));
}

void hapusIsiKulkas(Kulkas *k, ElTypeFoodList val, IdxType x, IdxType y)
{
    /* Menghapus Elemen pada posisi (x,y) kulkas */
    /* I.S. Sembarang */
    /* F.S. Isi dari posisi kulkas (x,y) akan terhapus bila isinya adalah val */
    if (TERISI(*k, x, y) && isValidIndeksKulkas(x + 1, y + 1))
    {
        if (isFoodEqual(ISI_KULKAS(*k, x, y), val))
        {
            TERISI(*k, x, y) = false;
            hapusIsiKulkas(k, val, x + 1, y);
            hapusIsiKulkas(k, val, x - 1, y);
            hapusIsiKulkas(k, val, x, y + 1);
            hapusIsiKulkas(k, val, x, y - 1);
        }
    }
}

void displayMakananKulkas(Kulkas k, ListStatik *isiKulkas, int *banyakIsiKulkas)
{
    /* Melakukan display pada List Statik Makanan yang terdapat pada kulkas */
    for (IdxType i = 0; i < CAPACITY_MATRIKS_KULKAS; i++)
    {
        for (IdxType j = 0; j < CAPACITY_MATRIKS_KULKAS; j++)
        {
            if (TERISI(k, i, j))
            {
                *banyakIsiKulkas += 1;
                insertLastListStatik(isiKulkas, ISI_KULKAS(k, i, j));
                hapusIsiKulkas(&k, ISI_KULKAS(k, i, j), i, j);
            }
        }
    }

    if (*banyakIsiKulkas == 0)
    {
        printf("Isi Kulkas Kosong\n");
    }
    else
    {
        printf("Pilih makanan pada kulkas :\n");

        for (int i = 0; i < *banyakIsiKulkas; i++)
        {
            printf("\n%d.\n", i + 1);
            DisplayMakanan(ELMT_LIST_STATIK(*isiKulkas, i));
        }
    }
}

void cariIsiKulkasDihapus(Kulkas *k, ElTypeFoodList val)
{
    /* Mencari isi kulkas yang sama dengan val */
    /* I.S. val pasti terdapat pada kulkas */
    /* F.S. Semua isi kulkas yang berisi makanan 'val' akan
            terhapus */
    for (IdxType i = 0; i < CAPACITY_MATRIKS_KULKAS; i++)
    {
        for (IdxType j = 0; j < CAPACITY_MATRIKS_KULKAS; j++)
        {
            if (isFoodEqual(ISI_KULKAS(*k, i, j), val))
            {
                hapusIsiKulkas(k, val, i, j);
            }
        }
    }
}

void keluarkanIsiKulkas(Simulator *sim, Kulkas *k, ElTypeFoodList val, TIME *realTime, NOTIF_STACK *NS, boolean *isValid)
{
    /* Mengeluarkan isi makanan pada kulkas */
    /* I.S. Sembarang */
    /* F.S. Jika menyimpan ke dalam inventory dan Inventory tersebut tidak penuh,
            maka makanan tersebut akan disimpan dalam inventory.
            Makanan tersebut sudah dikeluarkan dari kulkas */
    printf("Pilih opsi!\n\n");
    printf("1. Simpan Makanan ke dalam Inventory\n");
    printf("2. Buang Makanan\n");
    printf("----------------------\n");
    printf("Enter Command: ");
    STARTKALIMAT();
    int input = strToIntV2(kalimatToWord(currentKalimat));
    printf("============================================================================\n");
    if ((input == 1) && !(IsFullFood(UserInventory(*sim))))
    {
        cariIsiKulkasDihapus(k, val);
        addInventory(sim, val, *realTime, NS);
        *realTime = NextMinute(*realTime);
        *isValid = true;
        printf("Berhasil memindahkan isi kulkas ke dalam inventory!\n");
    }
    else if (input == 2)
    {
        cariIsiKulkasDihapus(k, val);
        *realTime = NextMinute(*realTime);
        *isValid = true;
        printf("Berhasil membuang isi kulkas!\n");
    }
    else
    {
        printf("Tidak dapat diproses\n");
    }
}

void KULKAS(Simulator *sim, Kulkas *k, TIME *realTime, boolean *IsValid, NOTIF_STACK *NS)
{
    /* Program Kulkas */

    if (isClose(UserPeta(*sim), 'K')) // Cek apakah disekitar user adalah kulkas
    {

        printf("======================\n");
        printf("=       KULKAS       =\n");
        printf("======================\n");
        printf("1. Masukkan makanan ke dalam kulkas\n");
        printf("2. Keluarkan makanan ke dalam kulkas\n\n");
        printf("----------------------\n");
        printf("Enter Command: ");
        STARTKALIMAT();
        int input = strToIntV2(kalimatToWord(currentKalimat));
        printf("============================================================================\n");
        if (input == 1)
        {
            printf("Pilih makanan pada inventory :\n");
            PrioQueueTime inventory = UserInventory(*sim);
            displayInventory(inventory, *realTime);
            printf("\n----------------------\n");
            printf("Enter Command: ");
            STARTKALIMAT();
            input = strToIntV2(kalimatToWord(currentKalimat));
            printf("============================================================================\n");
            if (!isIdxInventoryValid(inventory, input))
            {
                printf("Input Tidak Valid! \n");
            }
            else
            {
                FoodType val = Elmt(inventory, ((input - 1) + Head(inventory)) % CAPACITY);

                Makanan isi = val.food;
                isi.expired = MinuteToTIME((val.time_left) - TIMEToMinute(*realTime));

                *IsValid = false;

                masukanMakananKeKulkas(sim, k, isi, IsValid);

                if (*IsValid)
                {
                    removeInventory(sim, val.food);
                    *realTime = NextMinute(*realTime);
                }
            }
        }
        else if (input == 2)
        {
            ListStatik isiKulkas;
            int banyakIsiKulkas = 0;
            CreateListStatik(&isiKulkas);
            displayMakananKulkas(*k, &isiKulkas, &banyakIsiKulkas);

            if (banyakIsiKulkas > 0)
            {
                printf("----------------------\n");
                printf("Enter Command: ");
                STARTKALIMAT();
                input = strToIntV2(kalimatToWord(currentKalimat));
                printf("============================================================================\n");
                if ((input <= banyakIsiKulkas) && (input > 0))
                {
                    keluarkanIsiKulkas(sim, k, ELMT_LIST_STATIK(isiKulkas, input - 1), realTime, NS, IsValid);
                }
                else
                {
                    printf("Input Tidak Valid!\n");
                }
            }
        }
        else
        {
            printf("Input Tidak Valid!\n");
        }

        // Olah(sim, daftarResep, daftarInformasi, realTime, NS, "Fry.", isValid);
        // *realTime = NextMinute(*realTime);
    }
    else
    {
        printf("Anda tidak berada di dekat KULKAS.\n");
    }
}

#endif