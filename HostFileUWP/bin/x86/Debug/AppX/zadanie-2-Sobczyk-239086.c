#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
// liczba ta okreœla rozmiar alfabetu
#define ROZMIAR_ALFABETU 6
// Jezeli 1 to wyswietla tablice stanow po wlaczeniu programu, 0 wy³¹cza
#define POKAZ_TABLICE 1
// Liczba liter do ktorej wyswietlanie tablicy wyrownoje znaki(n-1), 8, 12 i 16 S¥ NIEOBSLUGIWANE!!!
#define DLUGOSC_WYSWIETLANIA 9
// maksymalna dlugosc linii
#define wielkosc_bufora 255

char alfabet[ROZMIAR_ALFABETU] =  {'1', '2', '3', 'a', 'b', 'c'};

struct Element {
  int e_liczba;
  char* e_nastepny[4];
};

struct Przejscie {
  struct Element* element;
};

// strukttura pojedynczego stanu
struct Stan {
  char nazwa[5];
  int typ; // 0 nieakceptujacy 1 powtorzona liczba 2 powtorzona litera
  struct Element stany_nastepne[ROZMIAR_ALFABETU];
};
// Tablela stanowa
struct Stan tabela_stanow[124] = {
//
{"q0",     0,  { { 2, {"q0", "q1"} }, { 2, {"q0", "q2"} }, { 2, {"q0", "q3"} }, { 2, {"q0", "qa"} }, { 2, {"q0", "qb"}}, { 2, {"q0", "qc"}}}},
{"q1",     0,  { { 1, {"qcy"} },       { 0, NULL },         { 0, NULL },         { 0, NULL },         { 0, NULL },        { 0, NULL }       }},
{"q2",     0,  { { 0, NULL },         { 1, {"qcy"} },       { 0, NULL },         { 0, NULL },         { 0, NULL },        { 0, NULL }       }},
{"q3",     0,  { { 0, NULL },         { 0, NULL },         { 1, {"qcy"} },       { 0, NULL },         { 0, NULL },        { 0, NULL }       }},
{"qa",     0,  { { 0, NULL },         { 0, NULL },         { 0, NULL },         { 1, {"qli"} },      { 0, NULL },        { 0, NULL }       }},
{"qb",     0,  { { 0, NULL },         { 0, NULL },         { 0, NULL },         { 0, NULL },         { 1, {"qli"} },     { 0, NULL }       }},
{"qc",     0,  { { 0, NULL },         { 0, NULL },         { 0, NULL },         { 0, NULL },         { 0, NULL },        { 1, {"qli"} }    }},
{"qli",    2,  { { 1, {"qli"} },      { 1, {"qli"} },      { 1, {"qli"} },      { 1, {"qli"} },      { 1, {"qli"} },     { 1, {"qli"} }    }},
{"qcy",    2,  { { 1, {"qcy"} },      { 1, {"qcy"} },      { 1, {"qcy"} },      { 1, {"qcy"} },      { 1, {"qcy"} },     { 1, {"qcy"} }    }}
};

void usun_pierwszy(char ciag[255])
{
  int i;
  for(i = 0; i < wielkosc_bufora - 1; i = i + 1)
  {
    ciag[i] = ciag[i+1];
  }
}

// zwraca dlugosc podanego ciagu znakow
int get_len(char* str)
{
    int result = 0;///
    // sprawdza na ktorym miejsu jest znak konca, wyrzuca warning
    for (; str[result] != NULL; result = result + 1)
    ;

    return result;
}

// Ucina puste znaki z konca zwracajac dynamiczna tablice znakow
char* trim_val(char* val)
{
  char* result;
  int i;
  // sprawdza na ktorym miejscu jest znak konca
  for (i = 0; i < 7; i = i + 1)
  {
    if (val[i] == '\0')
      break;
  }
  // przypisuje pamiec o odpowiedniej wielkosci
  result = malloc(sizeof(char) * i);
  // przepisuje wartosc
  for (i = i - 1; i >= 0; i = i - 1)
    result[i] = val[i];

  return result;
}

// porownuje zawartosc char* az do napotkania znaku konca
bool str_cmp(char* s1, char* s2)
{
  int i = 0;
  for(; i < get_len(s1) + 1; i = i + 1)
  {
    // jezeli nie sa takie same zwroc false
    if(s1[i] != s2[i]) return false;
    // jezeli koniec ciag zwroc true
    if(s1[i] == '\0') return true;
  }
  return false;
}

// Wyrownoje dlugosc znakow w celu wyswietlenia tabeli na ekranie
char* wyrownaj_do(char* str)
{
  char* result = malloc(DLUGOSC_WYSWIETLANIA * sizeof(char));
  int i;
  for (i = 0; i < DLUGOSC_WYSWIETLANIA - 2; i = i + 1)
  {
    if (str[i] == '\0')
      break;
    result[i] = str[i];
  }
  for (; i < DLUGOSC_WYSWIETLANIA - 2; i = i + 1)
  {
    result[i] = ' ';
  }
  result[DLUGOSC_WYSWIETLANIA - 1] = '\0';

  return result;
}

// Dodaje wpis do logu
char* dodaj_do_log(char* log, char val[7])
{

  char* foo;
  // przypisanie pamieci powiekszona o znaki -> oraz dlugosc tablicy znakow w nazwie stanu
  foo = (char*)malloc((7 + 2 + get_len(log)) * sizeof(char) );
  // Przepisanie wartoœci z tablicy char o nazwie log do tymczasowej tablicy foo
  int i;
  for (i = 0; i < get_len(log); i = i + 1)
  {
    foo[i] = log[i];
  }
  // dodanie do tablicy  znaku "->"
  foo[get_len(log)] = '-';
  foo[get_len(log) + 1] = '>';
  // dodanie do tablicy nazwe nastepnego stanu
  for(i = 0; i < 7; i = i + 1)
  {
    foo[i + get_len(log) + 2] = val[i];
  }
  return foo;
}

// zmienia znak podany przez uzytkownika na indeks tablicy
int znak_na_indeks(char* wybor)
{
	int result = -1;
	switch (wybor[0])
	{
		case '1':
			result = 0;
			break;
		case '2':
			result = 1;
			break;
		case '3':
			result = 2;
			break;
		case 'A':
    case 'a':
			result = 3;
			break;
		case 'B':
    case 'b':
			result = 4;
			break;
    case 'C':
    case 'c':
      result = 5;
      break;
    default:
      printf("Nieprawidlowy znak: %s\n", wybor);
      break;
	}
	return result;
}

// znajduje stan w tablicy stanow
struct Stan* znajdz_stan(char* nazwa)
{
  int i;
  for (i = 0; i < 124; i = i + 1)
  {
    if (str_cmp(tabela_stanow[i].nazwa, nazwa))
    {
      return &tabela_stanow[i];
    }
  }
  return NULL;
}

int execute(struct Stan stan, char* lokalny_log, char* logger, char* ciag, char* l_logger, int idx, int j)
{
  struct Stan* stan_2 = znajdz_stan(stan.nazwa);
  stan_2 = znajdz_stan(stan.stany_nastepne[idx].e_nastepny[j]);
  char kopia_ciagu[255];
  int wynik, i = 0;
  for (;i <= get_len(ciag); i = i + 1)
  {
    kopia_ciagu[i] = ciag[i];
  }
  kopia_ciagu[i+1] = '\0';
  // dodaje wpis do loggera
  lokalny_log = dodaj_do_log(l_logger, stan_2->nazwa);
  usun_pierwszy(kopia_ciagu);
  wynik = wykonaj_sciezke(logger, kopia_ciagu, stan_2, lokalny_log);
  //free(kopia_ciagu);
  return wynik;
}

int wykonaj_sciezke(char* logger, char ciag[wielkosc_bufora], struct Stan* stan, char* l_logger)
{
  if(get_len(ciag) == 0)
  {
    logger = l_logger;
    printf("%s\t", l_logger);
    return stan->typ;
  }
  int wynik = 0;
  char* val;
  char* lokalny_log = "\0";
  char wybor;
  int i, j, idx;

  if(ciag[0] != '\0')
  {
    idx = znak_na_indeks(&ciag[0]);
    // zabezpieczenie przed wyjsciem poza indeks - programowanie defensywne
    if ( idx >= 0 && idx < ROZMIAR_ALFABETU)
	  {
      //printf("->%s", stan->nazwa);
      for(j = stan->stany_nastepne[idx].e_liczba - 1; j >= 0; j = j - 1)
      {
        wynik = execute(*stan, lokalny_log, logger, ciag, l_logger, idx, j);
        if(wynik != 0)
          return wynik;
      }
      // wyswietla na ekranie przejscie
      //printf("->%s", stan->nazwa);
	  }

  }
  return wynik;
}

int main(int argc, char* argv[])
{
  // Je¿eli ustawiono wyswietlanie tablicy - do przerobienia na coœ bardziej uniwersalnego
  // if (POKAZ_TABLICE == 1)
  // {
  //   // wyœiwtla pierwszy wiersz - wartoœci pól
  //   printf("  %s\t%s\t%s\t%s\t%s\t%s\t%s\n", wyrownaj_do(""), wyrownaj_do("1"), wyrownaj_do("2"), wyrownaj_do("5"), wyrownaj_do("p"), wyrownaj_do("s"), wyrownaj_do("w") );
  //   int i,j;
  //   for (i = 0; i < 124; i = i + 1)
  //   {
  //     // Jezeli 1 element oznacz jako stan pocz¹tkowy, je¿eli oznaczony jako akceptuj¹cy dodaj oznaczenie, je¿eli nie dodaj puste pola
  //     if (i == 0)
  //       printf("->");
  //     else if (tabela_stanow[i].czy_akceptujacy)
  //       printf("A ");
  //     else
  //       printf("  ");
  //     // Wyœwietla na ekranie pojedyncza linie
  //     printf("%s\t%s\t%s\t%s\t%s\t%s\t%s\n", wyrownaj_do(tabela_stanow[i].nazwa), wyrownaj_do(tabela_stanow[i].stany_nastepne[0]), wyrownaj_do(tabela_stanow[i].stany_nastepne[1]), wyrownaj_do(tabela_stanow[i].stany_nastepne[2]), wyrownaj_do(tabela_stanow[i].stany_nastepne[3]), wyrownaj_do(tabela_stanow[i].stany_nastepne[4]), wyrownaj_do(tabela_stanow[i].stany_nastepne[5]));
  //   }
  //   printf("\n\n\n");
  // }


  // sciezka do pliku z danymi
  char* sciezka = malloc(sizeof(char) * 50);
  int i, j;
  printf("%s", "podaj nazwe pliku: ");
  scanf("%s", sciezka);
  printf("\n\n");
  //sciezka = "data.txt";
  FILE* wsk_plik;
  char bufor[wielkosc_bufora];
  char swynik[255];
  wsk_plik = fopen(sciezka, "r");
  char* znak = malloc(sizeof(char) * 2);

  for(i = 0; fgets(znak, 2, wsk_plik) && i < 255; i = i + 1)
  {
    if ( znak[0] == '\n' || znak[0] == EOF)
    {
      // dodaje do loggera stan poczatkowy
      char* logger = "q0";
      int wynik = 0;

      // ustawia stan na stan poczatkowy
      struct Stan* stan = znajdz_stan("q0");
      if(stan == NULL)
      {
        printf("Nie znaleziono q0");
      }

      //for (j = 0; wynik == 0 && j < 2 ; j = j + 1)
      //{
        wynik = wykonaj_sciezke(logger, bufor, stan, "q0");
        //if(wynik != 0)
        switch(wynik)
        {
        case 0:
          printf("\nWynik: Nieakceptujacy\n", wynik);
        break;
        case 1:
          printf("\nWynik: Jako pierwsza powtorzyla sie liczba\n", wynik);
        break;
        case 2:
          printf("\nWynik: Jako pierwsza powtorzyla sie litera\n", wynik);
        break;
        }
        printf("\n\n", wynik);
        //  break;
      //}
      i = -1;
      wynik = 0;
      bufor[0] = '\0';
    }
    else
    {
      bufor[i] = znak[0];
      bufor[i+1] = '\0';
    }
  }

  fclose(wsk_plik);

  // wyswietlenie czy uzytkownik jest w stanie akceptujacym
  // if (stan->czy_akceptujacy == true)
  //   printf("Stan jest akceptujacy\n");
  // else
  //   printf("stan jest nieakceptujacy\n");
  // W ramach ulepszenia programu mo¿naby rozczytywaæ nazwy poszczegolnych punktow i wyswietlic dokladny wynik(np. wydrukowano bilet na 2 godziny plywalni z saunami oraz 3 zl reszty)



  return 0;
}

