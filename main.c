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

int game(int codelen, int tries)
{
  int guess[codelen], entry[codelen], i, j, right = 0;

  for(i = 0; i < LN; ++i)
  {
    guess[i] = rand() % 10;
  }

  printf("Start guessing %d digit sequence:\n", codelen);
  for (j = 0; j < tries; ++j)
  {
    printf("[%d] >", tries - j);
    for (i = 0; i < LN; ++i)
    {
      scanf("%d", &entry[i]);
    }

    printf("Hint: ");
    right = 0;
    for (i = 0; i < codelen; ++i)
    {
      if (guess[i] == entry[i])
      {
        printf("!");
        ++right;
      }
      else if (is_in(codelen, guess, entry[i]))
      {
        printf("?");
      }
      else
      {
        printf("-");
      }
    }
    printf("\n");
    if (right  == codelen)
    {
      return 1;
    }
  }
  printf("No more tries\n");
  return 0;
}

int main()
{
  srand(time(NULL));
  puts("Codebreaker");
  puts("Open code lock by guessing the sequence of digits");
  puts("You will get \"hint\" given by your experience. Right numbers "
       "on right position are marked by !, those who are on wrong position"
       "are marked by ?. But you have only a number of tries before alarm starts"
       );
  if (game(LN, TRIES))
  {
    puts("CLICK! The lock is open!");
  }
  else
  {
    puts("BEEP! The alarm starts!");
  }
  return 0;
}
