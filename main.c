#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define LN 4
#define TRIES 10

enum guess
{
  no = 0, miss, hit
};

int is_in(int haysize, int haystack[haysize], int needle)
{
  int i;
  for (i = 0; i < haysize; ++i)
  {
    if (needle == haystack[i])
    {
      return i;
    }
  }
  return -1;
}

void generate_code(int codelen, int lock[codelen])
{
  int i;
  for (i = 0; i < codelen; ++i)
  {
    lock[i] = rand() % 10;
  }
}

void prepare_game(int codelen, int tries)
{
  printf("Guess %d digit sequence\n", codelen);
  printf("You have %d attempts\n", tries);
}

void show_prompt(int tries)
{
  printf("[%d] >", tries);
}

void read_answer(int tries, int codelen, int answer[codelen])
{
  int i;
  show_prompt(tries);
  for (i = 0; i < codelen; ++i)
  {
    scanf("%d", &answer[i]);
  }
}

void show_hint(int codelen, enum guess hint[codelen])
{
  int i;
  fputs("Hint: ", stdout);
  for (i = 0; i < codelen; ++i)
  {
    switch (hint[i])
    {
    case hit:
      putchar('!');
      break;
    case miss:
      putchar('?');
      break;
    default:
      putchar('-');
    }
  }
  putchar('\n');
}

int calculate_hits(int codelen, int answer[codelen], int lock[codelen],
    enum guess hint[codelen], int erase_found)
{
  int i, right = 0;
  for (i = 0; i < codelen; ++i)
  {
    if (answer[i] == lock[i])
    {
      hint[i] = hit;
      ++right;
      if (erase_found)
      {
        lock[i] = -1;
      }
    }
    else
    {
      hint[i] = no;
    }
  }
  return right;
}

void calculate_miss(int codelen, int answer[codelen], int lock[codelen],
    enum guess hint[codelen], int erase_found)
{
  int i, p;
  for (i = 0; i < codelen; ++i)
  {
    if (hint[i] != hit && (p = is_in(codelen, lock, answer[i])) > -1)
    {
      hint[i] = miss;
      if (erase_found)
      {
        lock[p] = -1;
      }
    }
  }
}

int calculate(int codelen, int answer[codelen], int lock[codelen],
    enum guess hint[codelen], int erase_found)
{
  int work[codelen];
  memset(hint, no, codelen);
  memcpy(work, lock, sizeof(int) * codelen);
  if (calculate_hits(codelen, answer, work, hint, erase_found) == codelen)
  {
    return 1;
  }

  calculate_miss(codelen, answer, work, hint, erase_found > 1);
  return 0;
}

int game(int codelen, int tries)
{
  int lock[codelen], answer[codelen], j;
  enum guess hint[codelen];

  generate_code(codelen, lock);
  prepare_game(codelen, tries);

  for (j = 0; j < tries; ++j)
  {
    read_answer(tries - j, codelen, answer);
    if (calculate(codelen, answer, lock, hint, 0))
    {
      return 1;
    }

    show_hint(codelen, hint);
  }
  return 0;
}

int main()
{
  srand(time(NULL));
  puts("Codebreaker");
  puts("Open code lock by guessing the sequence of digits");
  puts(
      "You will get \"hint\" given by your experience. Right numbers "
          "on right position are marked by !, those who are on wrong position"
          "are marked by ?. But you have only a number of tries before alarm starts");
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
