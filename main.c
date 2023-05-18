#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LN 4
#define TRIES 10

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
        goto ok;
      }
      if (guess[0] == entry[i] ||
          guess[1] == entry[i] ||
          guess[2] == entry[i] ||
          guess[3] == entry[i])
      {
        printf("?");
        goto ok;
      }
      printf("_");
      ok:
    }
    printf("\n");
    if (right == LN)
    {
      printf("Brawo!!1ONE\n");
      goto end;
    }
  }
  printf("Niestety, koniec prob\n");
  end: return 0;
}
