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
      return 1;
    }
  }
  return 0;
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

int calculate(int codelen, int answer[codelen], int lock[codelen],
    enum guess hint[codelen])
{
  int i, right = 0, work[codelen];
  memset(hint, no, codelen);
  memcpy(work, lock, sizeof(int) * codelen);
  for (i = 0; i < codelen; ++i)
  {
    if (answer[i] == lock[i])
    {
      hint[i] = hit;
      work[i] = -1;
      ++right;
    }
    else if (is_in(codelen, lock, answer[i]))
    {
      hint[i] = miss;
    }
  }
  return right;
}

int game(int codelen, int tries)
{
  int lock[codelen], answer[codelen], work[codelen], i, j, right = 0;
  enum guess hint[codelen];

  generate_code(codelen, lock);
  prepare_game(codelen, tries);

  for (j = 0; j < tries; ++j)
  {
    read_answer(tries - j, codelen, answer);
    right = calculate(codelen, answer, lock, hint);
    show_hint(codelen, hint);
    if (right == codelen)
    {
      return 1;
    }
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
