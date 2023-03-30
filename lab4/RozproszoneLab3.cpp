#include <windows.h>
#include <stdio.h>
#include <conio.h>

void gotoxy(int x, int y)
{
	COORD coordinate;
	coordinate.X = x;
	coordinate.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinate);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
# pragma argsused
struct dane_dla_watku // tablica zawiera dane , ktore otrzymaja watki
{
	char nazwa[50];
	int parametr;
} dane[5] = { { "[1]" , 5 } , { "[2]" , 8 } , { "[3]" , 12 }, { "[4]" , 17 }, { "[5]" , 120 } };
// priorytety watkow
int priorytety[5] = { THREAD_PRIORITY_BELOW_NORMAL ,
THREAD_PRIORITY_NORMAL , THREAD_PRIORITY_ABOVE_NORMAL, THREAD_PRIORITY_ABOVE_NORMAL, THREAD_PRIORITY_ABOVE_NORMAL
};
HANDLE watki[5]; // dojscia ( uchwyty ) watkow
// deklaracja funkcji watku
DWORD WINAPI funkcja_watku(void* argumenty);
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
int main(int argc, char** argv)
{
	int i;
	DWORD id; // identyfikator watku
	system("cls");
	//clrscr();
	printf(" Uruchomienie programu \n ");
	// tworzenie watkow
	for (i = 0; i < 5; i++)
	{
		watki[i] = CreateThread(
			NULL, // atrybuty bezpieczenstwa
			0, // inicjalna wielkosc stosu
			funkcja_watku, // funkcja watku
			(void*)&dane[i],// dane dla funkcji watku
			0, // flagi utworzenia
			&id);
		if (watki[i] != INVALID_HANDLE_VALUE)
		{
			
			printf(" Utworzylem watek %s o id %x \n ", dane[i].nazwa, id);
			//gotoxy(0, i+3);
			// ustawienie priorytetu
			SetThreadPriority(watki[i], priorytety[i]);
		}
	}
	Sleep(2000);
	TerminateThread(watki[2], 0);
	Sleep(20000); // uspienie watku glownego na 20 s
	return 0;
}
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// trzy takie funkcje pracuja wspolbieznie w programie
DWORD WINAPI funkcja_watku(void* argumenty)
{
	unsigned int licznik = 0;
	// rzutowanie struktury na wlasny wskaznik
	struct dane_dla_watku* moje_dane = (struct dane_dla_watku*)argumenty;
	// wyswietlenie informacji o uruchomieniu
	
	printf("%s ", moje_dane -> nazwa);
	Sleep(1000);

		// praca , watki sa terminowane przez zakonczenie programu
		// - funkcji main
		while(true)
		{
			
			gotoxy(licznik++ / 5000 + 5, moje_dane -> parametr);

			printf(".");
		}
	return 0;
}