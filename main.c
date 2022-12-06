#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

/*
 * written by Iszak Gábor on 2022.12.06
 */

int power(int base, int exponent)
{
    int result = 1;

    if(exponent == 0)
    {
        return 1;
    }
    else if(exponent == 1)
    {
        return base;
    }
    else{
        for (int i = exponent; i>0; i--) {
            result = result * base;
        }
    }
    return result;
}


int numberCheck(int system, char szam[], int szamhossz)
{
    if(system >= 2 && system <= 36)
    {
        if(system <= 10)
        {
            for (int i = 0; i < szamhossz; ++i) {
                if(!isdigit(szam[i]))    ///isdigit() megállapítja hogy egy string decimális értékekből áll-e ctype.h include kell hozzá
                {
                    return 0;
                }
            }
            return 1;
        }
        else{
            for (int i = 0; i < szamhossz; ++i) {
                if(!isxdigit(szam[i]))  ///isxdigit() megállapítja hogy egy string hexadecimális értékekből áll-e ctype.h include ehez is kell.
                {
                    return 0;
                }
            }
            return 1;
        }
    }
    else{
        return 0;
    }
}

int toDecimal(char szam[], int szamhossz, int szamrendszer) ///Bármilyen számrendszerben lévő számot 10-es számrendszerbe vált
{
    int val, dec = 0;

    for (int i = 0; i < szamhossz; ++i) {               ///ASCII kódok segítségével van megállapítva a szám, hogy utána int-é lehessen alakítani
        if(szam[i] >= '0' && szam[i] <= '9')
        {
            val = szam[i] - '0';
        }
        else if(szam[i] >= 'a' && szam[i] <= 'z')
        {
            val = szam[i] - 'a' + 10;
        }
        else if(szam[i] >= 'A' && szam[i] <= 'Z')
        {
            val = szam[i] - 'A' + 10;
        }
        dec += val * power(szamrendszer, i);
        }

    return dec;
}

char* fromDecimal(int szamrendszer, int szam)
{
    char abc[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9','A', 'B', 'C', 'D', 'E', 'F'};
    char eredmeny[50];
    int maradek,index = 0, seged = szam;

    while(seged != 0)        ///10-esből bármelyik számrendszerbe való átváltás
    {
        maradek = seged % szamrendszer;
        eredmeny[index] = abc[maradek];
        index++;
        seged = seged / szamrendszer;
    }

    int resultIndex = 0;
    char* result = malloc(index * sizeof(char)); ///Kimeneti tömb

    for (int i = index - 1; i >= 0; i--) { ///Az "eredmeny" tömb \n-ig megfordító genyó
        result[resultIndex] = eredmeny[i];
        resultIndex++;
    }
    result[resultIndex] = '\n';
    return result;
}

int main()
{
    int xbol, yba;
    char szam[50];
    FILE* f_be = fopen("be.txt", "r");
    FILE* f_ki = fopen("ki.txt", "w");
    fscanf(f_be, "%d %d %s", &xbol, &yba, szam);
    int szamhossz = 0;

    while(szam[szamhossz] != '\0') {
        szamhossz++;
    }

    int result;


    if(numberCheck(xbol, szam, szamhossz) == 1) ///a numberCheck függvény ha 1-et ad vissza, akkor a szám a megfelelő számrendszerben van.
    {
        if(xbol == 10)
        {
            result = atoi(szam); ///atoi(char*) stdlib tartalmazza, egy stringet konvertál int-é
        }
        else{
            result = toDecimal(szam, szamhossz, yba);
        }
        fprintf(f_ki, "%s\n", fromDecimal(yba, result));
    }
    else
    {
        fprintf(f_ki, "HIBA\n");
    }


    fclose(f_be);
    fclose(f_ki);

    return 0;
}
