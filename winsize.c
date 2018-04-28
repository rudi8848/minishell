#include <stdio.h>
#include <stdlib.h>

#define COLS 24
#define ROWS 80

int
main (int ac, char *av[])
{
  int cols = av[1] ? atoi(av[1]) : COLS,
    rows = av[1] && av[2] ? atoi(av[2]) : ROWS;
  if (cols < 0)
    cols = COLS;
  if (rows < 0)
    rows = ROWS;
	printf("cols: %d; rows: %d", cols, rows); 
  printf("\e[8;%d;%d;t", cols, rows); 

  return fflush(stdout) == EOF;
}