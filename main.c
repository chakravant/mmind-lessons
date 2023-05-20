#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LN 4
#define TRIES 10

int main()
{
  int guess[LN], entry[LN], i, j, k, right = 0, fnd = 0;
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
        continue;
      }
      fnd = 0;
      for (k = 0; k < LN; ++k)
      {
        if (k == i) continue;
        if (entry[i] == guess[k])
        {
          fnd = 1;
          break;
        }
      }
      if (fnd == 1)
      {
        printf("?");
        continue;
      }
      printf("-");
    }
    printf("\n");
    if (right == LN)
    {
      printf("Brawo!!1ONE\n");
      return 0;
    }
  }
  printf("Niestety, koniec prob\n");
  return 0;
}
