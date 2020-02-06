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

int abs(int val) {
  // if(val < 0) return -1 * val else return val;
  return val < 0 ? -1 * val : val;
}

int error_check(int val) {
  if(val < 0) printf("error %d: %s\n", errno, strerror(errno));
  return val;
}

char *get_color(int val) {
  char *ans, *R, *G, *B;
  // char *ans, R[4], G[4], B[4];
  ans = calloc(15, sizeof(char));
  R = calloc(4, sizeof(char));
  G = calloc(4, sizeof(char));
  B = calloc(4, sizeof(char));
  sprintf(R, "%d", abs(val % 255));
  sprintf(G, "%d", abs(val / 1000 % 255));
  sprintf(B, "%d", abs(val / 1000000 % 255));
  sprintf(ans, "%s %s %s ", R, G, B);
  // free(R); free(G); free(B);
  return ans;
}

char *y_reflect(char *row) {
  //char copy[strlen(row)];
  char *copy;
  copy = strdup(row);
  /* char delim[2] = " "; */
  /* char *ptr = strtok(copy, delim); */
  int i = 0;
  char *ans = malloc(strlen(row) * sizeof(char));
  char color[10];
  char *rgb_val;
  /* while(ptr != NULL) { */
  /*   ptr = strtok(NULL, delim); */
  /* } */
  while((rgb_val = strsep(&copy, " ")) != NULL) {
  /* for(i = 0; i < 250; i++) { */
    //sprintf(color, "%c %c %c", copy[i * 3], copy[i * 3 + 1], copy[i * 3 + 2]);
    if(i % 3 == 0) {
      sprintf(ans, "%s %s", color, ans);
      strcpy(color, "");
    }
    sprintf(color, "%s %s", color, rgb_val);
    i++;
    /* sprintf(color, "%s %s %s", copy[i * 3], copy[i * 3 + 1], copy[i * 3 + 2]); */
  }
  return ans;
}

char *x_reflect(char *pic) {
  /* char copy[strlen(pic)]; */
  /* strcpy(copy, pic); */
  char *copy, *row;
  copy = strdup(pic);
  while((row = strsep(&copy, "\n")) != NULL) {
    sprintf(pic, "%s\n%s", row, copy);
  }
  return pic;
}

int main(int argc, char *argv[]) {
  int devrandom = error_check(open("/dev/urandom", O_RDONLY));
  int newfile = error_check(open("pic.ppm", O_CREAT | O_RDWR, 0644));
  int *randarr = calloc(250, sizeof(int));
  char *row = calloc(500 * 4 + 20, sizeof(char));
  //char *row = calloc(13, sizeof(char));
  char *intro = calloc(20, sizeof(char));
  sprintf(intro, "P3\n500 500\n255\n");

  error_check(write(newfile, intro, strlen(intro)));
  free(intro);
  error_check(read(devrandom, randarr, 250 * sizeof(int)));
  int i, j;
  if (argc > 1) {
    for(i = 0; i < 250; i++) {
      error_check(read(devrandom, randarr, 250 * sizeof(int)));
      for(j = 0; j < 250; j++)
        printf("%d ", randarr[j]);
      printf("\n");
    }
  } else {
    char *color;
    for (i = 0; i < 255; i++) {
      sprintf(row, "%s %s", row, get_color(randarr[i]));
      /* sprintf(row + strlen(row), get_color(randarr[i])); */
    }
    sprintf(row, "%s %s", row, y_reflect(row));
    printf("%lu %d\n", sizeof(row), strlen(row));
    printf("%s\n", row);
    //sprint(row, "%s %s", row, y_reflect(row));
    strcat(row, "\n");
    error_check(write(newfile, row, 255 * 4 + 1 * sizeof(int)));
    // my_write(newfile, randarr1, 125 * sizeof(int));
  }

  //free(row);
  free(randarr);
  close(devrandom);
  close(newfile);
  return 0;
}
