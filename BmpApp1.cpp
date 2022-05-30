#include "BmpAppH.h"
#pragma warning (disable: 4996) //Disables deprecation warnings (for outdated code/functions)

struct FileHeader {
    short bfTyp;
    int bfRozmiar;
    short bfReserved1;
    short bfReserved2;
    int bfOffBits;
} File;

struct PictureHeader {
    int biRozmiar;
    int biSzerokosc;
    int biWysokosc;
    short biWarstwy;
    short biIloscBitow;
    int biKompresja;
    int biRozmiarObrazu;
    int biXPelsPerMeter;
    int biYPelsPerMeter;
    int biClrUsed;
    int biClrImportant; //number of important color palettes (0, if all are important)
} Picture;

struct KoloryRGB {
    char R;
    char G;
    char B;
} Rgb;

int main(int arc, char* argv[]) {
    FILE* f;

    f = fopen("test.bmp","rb"); //fopen- opens files. rb is put as an argument to read the file (r also can be used)

    if (f == nullptr) //checks if file exists/is not empty
    {
        printf("\n\n Nie mozna otworzyc pliku f");
        return -1;
    }
    else
    {
        printf("\n\n Plik f został otwarty!");
    }

    printf("\n INFORMACJE O BITMAPIE\n\n");

    fread(&File.bfTyp, sizeof(File.bfTyp), 1, f); //fread- reads an array of elements with a size of specified bytes which is stored in the specified memory pointer (ptr)
    printf(" Typ: %x", File.bfTyp);

    fread(&File.bfRozmiar, sizeof(File.bfRozmiar), 1, f);
    printf("\n Rozmiar pliku: %d bajtow", File.bfRozmiar);

    fread(&File.bfReserved1, sizeof(File.bfReserved1), 1, f);
    printf("\n Zarezerwowane1: %d", File.bfReserved1);

    fread(&File.bfReserved2, sizeof(File.bfReserved2), 1, f);
    printf("\n Zarezerwowane2: %d", File.bfReserved2);

    fread(&File.bfOffBits, sizeof(File.bfOffBits), 1, f);
    printf("\n Pozycja danych obrazkowych: %d", File.bfOffBits);

    printf("\n");

    fseek(f, 14, SEEK_SET); //fseek- function which sets the position indicator (by adding offset) to the beginning of the file
    fread(&Picture.biRozmiar, sizeof(Picture.biRozmiar), 1, f);
    printf("\n Wielkosc naglowka informacyjnego: %d", Picture.biRozmiar);

    fread(&Picture.biSzerokosc, sizeof(Picture.biSzerokosc), 1, f);
    printf("\n Szerokosc: %d pikseli", Picture.biSzerokosc);

    fread(&Picture.biWysokosc, sizeof(Picture.biWysokosc), 1, f);
    printf("\n Wysokosc: %d pikseli", Picture.biWysokosc);

    fread(&Picture.biWarstwy, sizeof(Picture.biWarstwy), 1, f);
    printf("\n Ilosc warstw obrazu: %d", Picture.biWarstwy);

    fread(&Picture.biIloscBitow, sizeof(Picture.biIloscBitow), 1, f);
    printf("\n Liczba bitow na piksel: %d (1, 4, 8, or 24)", Picture.biIloscBitow);

    fread(&Picture.biKompresja, sizeof(Picture.biKompresja), 1, f);
    printf("\n Kompresja: %d (0=none, 1=RLE-8, 2=RLE-4)", Picture.biKompresja);

    fread(&Picture.biRozmiarObrazu, sizeof(Picture.biRozmiarObrazu), 1, f);
    printf("\n Rozmiar obrazu: %d", Picture.biRozmiarObrazu);

    fread(&Picture.biXPelsPerMeter, sizeof(Picture.biXPelsPerMeter), 1, f);
    printf("\n Rozdzielczosc pozioma: %d", Picture.biXPelsPerMeter);

    fread(&Picture.biYPelsPerMeter, sizeof(Picture.biYPelsPerMeter), 1, f);
    printf("\n Rozdzielczosc pionowa: %d", Picture.biYPelsPerMeter);

    fread(&Picture.biClrUsed, sizeof(Picture.biClrUsed), 1, f);
    printf("\n Liczba kolorow w palecie: %d", Picture.biClrUsed);

    fread(&Picture.biClrImportant, sizeof(Picture.biClrImportant), 1, f);
    printf("\n Wazne kolory w palecie: %d", Picture.biClrImportant);

    /*************************/

    FILE* w = fopen("negative.bmp", "wb");
    if (w == nullptr) //checks if file exists/is not empty
    {
        printf("\n\n Nie mozna otworzyc pliku w");
        return -1;
    }
    else
    {
        printf("\n\n Plik w został otwarty!");
    }

    fseek(w, 0, SEEK_SET); //fseek- function which sets the position indicator (by adding offset) to the beginning of the file
    fwrite(&File.bfTyp, sizeof(File.bfTyp), 1, w); //fwrite- writes an array of elements by the size of specified bytes to the current stream position from memory pointer (ptr)
    fwrite(&File.bfRozmiar, sizeof(File.bfRozmiar), 1, w);
    fwrite(&File.bfReserved1, sizeof(File.bfReserved1), 1, w);
    fwrite(&File.bfReserved2, sizeof(File.bfReserved2), 1, w);
    fwrite(&File.bfOffBits, sizeof(File.bfOffBits), 1, w);

    fseek(w, 14, SEEK_SET); //fseek- function which sets the position indicator (by adding offset) to the beginning of the file
    fwrite(&Picture.biRozmiar, sizeof(Picture.biRozmiar), 1, w);
    fwrite(&Picture.biSzerokosc, sizeof(Picture.biSzerokosc), 1, w);
    fwrite(&Picture.biWysokosc, sizeof(Picture.biWysokosc), 1, w);
    fwrite(&Picture.biWarstwy, sizeof(Picture.biWarstwy), 1, w);
    fwrite(&Picture.biIloscBitow, sizeof(Picture.biIloscBitow), 1, w);
    fwrite(&Picture.biKompresja, sizeof(Picture.biKompresja), 1, w);
    fwrite(&Picture.biRozmiarObrazu, sizeof(Picture.biRozmiarObrazu), 1, w);
    fwrite(&Picture.biXPelsPerMeter, sizeof(Picture.biXPelsPerMeter), 1, w);
    fwrite(&Picture.biYPelsPerMeter, sizeof(Picture.biYPelsPerMeter), 1, w);
    fwrite(&Picture.biClrUsed, sizeof(Picture.biClrUsed), 1, w);
    fwrite(&Picture.biClrImportant, sizeof(Picture.biClrImportant), 1, w);

    fseek(w, sizeof(File.bfOffBits), SEEK_SET); //fseek- function which sets the position indicator (by adding offset) to the beginning of the file

    int bmpImg;
    for (int i = File.bfOffBits; i < File.bfRozmiar; i++)
    {
        fseek(f, i, SEEK_SET);
        fseek(w, i, SEEK_SET);
        fread(&bmpImg, 3, 1, f);
        bmpImg = INT_MAX - bmpImg; //Tworzymy negatyw
        fwrite(&bmpImg, 3, 1, w);
    }

    printf("\n");
    fclose(f);
    fclose(w);

    return 0;
}