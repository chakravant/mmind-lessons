#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LN 4
#define TRIES 10

int is_in(int haysize, int haystack[haysize], int needle)
{
  int i;
  for (i = 0; i < haysize; ++i)
  {
    if (needle == haystack[i])
    {
      return 1;
    }
  }
  return 0;
}

int main()
{
  int guess[LN], entry[LN], i, j, right = 0;
  srand(time(NULL));

  for(i = 0; i < LN; ++i)
  {
    guess[i] = rand() % 10;
  }

  printf("Zgadnij %d cyfry kodu:\n", LN);
  for (j = 0; j < TRIES; ++j)
  {
    printf("[%d] >", j);
    for (i = 0; i < LN; ++i)
    {
      scanf("%d", &entry[i]);
    }

    printf("Hint: ");
    right = 0;
    for (i = 0; i < LN; ++i)
    {
      if (guess[i] == entry[i])
      {
        printf("!");
        ++right;
      }
      else if (is_in(LN, guess, entry[i]))
      {
        printf("?");
      }
      else
      {
        printf("-");
      }
    }
    printf("\n");
    if (right  == LN)
    {
      printf("Brawo!!1ONE\n");
      return 0;
    }
  }
  printf("Niestety, koniec prob\n");
  return 0;
}
