#ifndef TIME_H
#define TIME_H

#include "boolean.h"

/* *** Definisi TYPE TIME <DD:HH:MM> *** */
typedef struct { 
	int DD; /* integer [0....] */
    int HH; /* integer [0..23] */
	int MM; /* integer [0..59] */
	
} TIME;

/* *** Notasi Akses: selektor TIME *** */
#define Day(T) (T).DD
#define Hour(T) (T).HH
#define Minute(T) (T).MM

/* ***************************************************************** */
/* DEFINISI PRIMITIF                                                 */
/* ***************************************************************** */
/* KELOMPOK VALIDASI TERHADAP TYPE                                   */
/* ***************************************************************** */
boolean IsTIMEValid (int D, int H, int M)
/* Mengirim true jika H,M,S dapat membentuk T yang valid */
/* dipakai untuk mentest SEBELUM membentuk sebuah Jam */
{
    return ((D >= 0) && (H >= 0) && (H <= 23) && (M >= 0) && (M <=59));
}

/* *** Konstruktor: Membentuk sebuah TIME dari komponen-komponennya *** */
TIME MakeTIME (int DD, int HH, int MM)
/* Membentuk sebuah TIME dari komponen-komponennya yang valid */
/* Prekondisi : DD, HH, MM valid untuk membentuk TIME */
{
    TIME t;

    if (IsTIMEValid(DD, HH, MM)){
        Day(t) = DD;
        Hour(t) = HH;
        Minute(t) = MM;
        return t;
    }
}

void CreateTime (TIME * T, int DD, int HH, int MM){
/* Membentuk sebuah TIME dari komponen-komponennya yang valid */
/* Prekondisi : DD, HH, MM valid untuk membentuk TIME */
/* ALGORITMA */
    Day(*T) = DD;
    Hour(*T) = HH;
    Minute(*T) = MM;
}

/* ***************************************************************** */
/* KELOMPOK BACA/TULIS                                               */
/* ***************************************************************** */
void BacaTIME (TIME * T)
/* I.S. : T tidak terdefinisi */
/* F.S. : T terdefinisi dan merupakan jam yang valid */
/* Proses : mengulangi membaca komponen DD, HH, MM sehingga membentuk T */
/* yang valid. Tidak mungkin menghasilkan T yang tidak valid. */
/* Pembacaan dilakukan dengan mengetikkan komponen DD, HH, MM
   dalam satu baris, masing-masing dipisahkan 1 spasi, diakhiri enter. */
/* Jika TIME tidak valid maka diberikan pesan: "Jam tidak valid", dan pembacaan
   diulangi hingga didapatkan jam yang valid. */
/* Contoh: 
   60 3 4
   Jam tidak valid
   1 3 4
   --> akan terbentuk TIME <1,3,4> */
{
    int d, h, m;

    /* ALGORITMA */
    do {
        //scanf("%d %d %d", &d, &h, &m);
        if (!IsTIMEValid(d, h, m)) {
            printf("Waktu tidak valid\n");
        }
    } while (!IsTIMEValid(d, h, m));
    *T = MakeTIME(d, h, m);
}

void TulisTIME (TIME T)
/* I.S. : T sembarang */
/* F.S. : Nilai T ditulis dg format DD:HH:MM */
/* Proses : menulis nilai setiap komponen T ke layar dalam format DD:HH:MM
   tanpa karakter apa pun di depan atau belakangnya, termasuk spasi, enter, dll.*/ 
{
    printf("%02d:%02d:%02d", Day(T), Hour(T), Minute(T));
}
/* ***************************************************************** */
/* KELOMPOK KONVERSI TERHADAP TYPE                                   */
/* ***************************************************************** */
long TIMEToMinute (TIME T)
/* Diberikan sebuah TIME, mengkonversi menjadi jumlah Menit dari pukul 0:0:0 */
/* Rumus : Menit = 1440*DD + 60*HH + MM */
/* Nilai maksimum = 3600*23+59*60+59 */
{
    return (Day(T) * 1440 + Hour(T) * 60 + Minute(T));
}

TIME MinuteToTIME (long N)
/* Mengirim  konversi menit ke TIME */
/* Catatan: Jika N >= 86400, maka harus dikonversi dulu menjadi jumlah menit yang 
   mewakili jumlah menit yang mungkin dalam 1 hari, yaitu dengan rumus: 
   N1 = N mod 86400, baru N1 dikonversi menjadi TIME */
{
    int d, h, m;

    if (N < 0){
        N += 1440;
    }
    d = N / 1440;
    N = N % 1440;
    h = N / 60;
    m = N - h * 60;
    return MakeTIME(d, h, m);
}

/* ***************************************************************** */
/* KELOMPOK OPERASI TERHADAP TYPE                                    */
/* ***************************************************************** */
/* *** Kelompok Operator Relational *** */
boolean TEQ (TIME T1, TIME T2)
/* Mengirimkan true jika T1=T2, false jika tidak */
{
    return ((Day(T1) == Day(T2) && (Hour(T1) == Hour(T2)) && (Minute(T1) == Minute(T2))));
}
boolean TNEQ (TIME T1, TIME T2)
/* Mengirimkan true jika T1 tidak sama dengan T2 */
{
    return (!TEQ(T1, T2));
}
boolean TLT (TIME T1, TIME T2)
/* Mengirimkan true jika T1<T2, false jika tidak */
{
    return (TIMEToMinute(T1) < TIMEToMinute(T2));
}
boolean TGT (TIME T1, TIME T2)
/* Mengirimkan true jika T1>T2, false jika tidak */
{
    return (TIMEToMinute(T1) > TIMEToMinute(T2));
}
/* *** Operator aritmatika TIME *** */
TIME NextMinute (TIME T)
/* Mengirim 1 menit setelah T dalam bentuk TIME */
{
    return (MinuteToTIME(TIMEToMinute(T) + 1));
}
TIME NextNMinute (TIME T, int N)
/* Mengirim N menit setelah T dalam bentuk TIME */
{
    return (MinuteToTIME(TIMEToMinute(T) + N));
}
TIME PrevMinute (TIME T)
/* Mengirim 1 menit sebelum T dalam bentuk TIME */
{
    return (MinuteToTIME(TIMEToMinute(T) - 1));
}
TIME PrevNMinute (TIME T, int N)
/* Mengirim N menit sebelum T dalam bentuk TIME */
{
    return (MinuteToTIME(TIMEToMinute(T) - N));
}
/* *** Kelompok Operator Aritmetika *** */
long Durasi (TIME TAw, TIME TAkh)
/* Mengirim TAkh-TAw dlm Menit, dengan kalkulasi */
/* Jika TAw > TAkh, maka TAkh adalah 1 hari setelah TAw */
{
    long deltaS;

    if (TIMEToMinute(TAw) > TIMEToMinute(TAkh)){
        deltaS = 1440 + TIMEToMinute(TAkh) - TIMEToMinute(TAw);
    }
    else {
        deltaS = TIMEToMinute(TAkh) - TIMEToMinute(TAw);
    }
    return deltaS;
}

#endif