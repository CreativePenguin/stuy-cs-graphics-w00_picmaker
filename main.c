//This Is Your Brain On Drugs
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
  char *ans, R[4], G[4], B[4];
  ans = calloc(9, sizeof(char));
  sprintf(R, "%d", val % 255);
  sprintf(G, "%d", val / 1000 % 255);
  sprintf(B, "%d", val / 1000000 % 255);
  sprintf(ans, "%s %s %s", R, G, B);
  return ans;
}

char *y_reflect(char *row) {
  char copy[strlen(row)];
  strcpy(copy, row);
  char delim[2] = " ";
  char *ptr = strtok(copy, delim);
  int i;
  char *ans = malloc(sizeof(row));
  char color[10];
  while(ptr != NULL) {
    ptr = strtok(NULL, delim);
  }
  for(i = 0; i < 250; i++) {
    sprintf(color, "%c %c %c", copy[i * 3], copy[i * 3 + 1], copy[i * 3 + 2]);
    sprintf(ans, "%s %s", color, ans);
  }
  // char **rows = malloc(250 * sizeof(char *));
  // char *val = malloc(250 * 3 * sizeof(char));
  // int i = 0;
  // while(color) {
  //   rows[i] = strsep(&color, " ");
  //   i++;
  // }
  // rows[i] = NULL;
  // for(i = 0; i < 250; i++) {
  //   sprintf(val, "%s %s", rows[i], val);
  // }
  // free(rows);
  return ans;
}

int main() {
  int devrandom = error_check(open("/dev/urandom", O_RDONLY));
  int newfile = error_check(open("pic.ppm", O_CREAT | O_RDWR, 0644));
  int *randarr = calloc(250, sizeof(int));
  char *row = calloc(250 * 3, sizeof(char));
  char *intro = calloc(20, sizeof(char));
  sprintf(intro, "P3\n500 500\n255\n");

  error_check(write(newfile, intro, strlen(intro)));
  free(intro);
  error_check(read(devrandom, randarr, 250 * sizeof(int)));
  int i = 0;
  char *color;
  for(i = 0; i < 255; i++) {
    sprintf(row, "%s %s", row, get_color(randarr[i]));
  }
  error_check(write(newfile, row, 255 * sizeof(int)));
  //my_write(newfile, randarr1, 125 * sizeof(int));

  free(row);
  free(randarr);
  close(devrandom);
  close(newfile);
  return 0;
}
