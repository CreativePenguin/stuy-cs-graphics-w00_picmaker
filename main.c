#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

void print_arr(int *arr, int size) {
  int i = 0;
  for(; i < size; i++) {
    printf("%d\n", arr[i]);
  }
}

int error_check(int val) {
  if(val < 0) printf("error %d: %s\n", errno, strerror(errno));
  return val;
}

char *get_color(int val) {
  char *ans, R[3], G[3], B[3];
  ans = calloc(9, sizeof(char));
  sprintf(R, "%d", val % 255);
  sprintf(G, "%d", val / 1000 % 255);
  sprintf(B, "%d", val / 1000000 % 255);
  sprintf(ans, "%s %s %s", R, G, B);
  return ans;
}

char *reflect(char *orig) {
  char **rows = malloc(250 * sizeof(char *));
  char *color = orig;
  char *val = malloc(250 * 3 * sizeof(char));
  int i = 0;
  while(color) {
    rows[i] = strsep(&color, " ");
    i++;
  }
  rows[i] = NULL;
  for(i = 0; i < 250; i++) {
    sprintf(val, "%s %s", rows[i], val);
  }
  free(rows);
  return val;
}

int main() {
  int devrandom = error_check(open("/dev/urandom", O_RDONLY));
  int newfile = error_check(open("pic.ppm", O_CREAT | O_RDWR, 0644));
  int *randarr = calloc(250, sizeof(int));
  char *row = calloc(250 * 3, sizeof(char));
  char *intro = calloc(20, sizeof(char));
  sprintf(intro, "P3\n500 500\n255\n");

  error_check(write(newfile, intro, 10));
  free(intro);
  error_check(read(devrandom, randarr, 250 * sizeof(int)));
  int i = 0;
  for(i = 0; i < 255; i++) {
    sprintf(row, "%s %s", row, get_color(randarr[i]));
  }
  error_check(write(newfile, randarr, 255 * sizeof(int)));
  //my_write(newfile, randarr1, 125 * sizeof(int));

  free(randarr);
  close(devrandom);
  close(newfile);
  return 0;
}
