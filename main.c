//This Is Your Brain On Drugs
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

#define abs_val(X) ((X) < 0 ? -1 * (X) : (X))
#define trim_nullspace(X) ((X)[0] == '\0' ? X + 1 : X)

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
  /* char *ans, *R, *G, *B; */
  char *ans, R[4], G[4], B[4];
  ans = calloc(15, sizeof(char));
  /* R = calloc(4, sizeof(char)); */
  /* G = calloc(4, sizeof(char)); */
  /* B = calloc(4, sizeof(char)); */
  sprintf(R, "%d", abs_val(val % 255));
  sprintf(G, "%d", abs_val(val / 1000 % 255));
  sprintf(B, "%d", abs_val(val / 1000000 % 255));
  sprintf(ans, "%s %s %s ", R, G, B);
  // free(R); free(G); free(B);
  return ans;
}

char *strprefix(char *dest, char *src) {
  int i = 0;
  /* for(i = 0; i < strlen(dest); i++) { */
  /*   dest[i + strlen(src)] = dest[i]; */
  /*   dest[i] = src[i]; */
  /* } */
  char *tmp = strdup(dest);
  size_t dest_len = strlen(dest);
  for (i = 0; i < dest_len; i++)
    dest[i + strlen(src)] = tmp[i];
  for (i = 0; i < strlen(src); i++)
    dest[i] = src[i];
  /* free(tmp); */
  return dest;
}

char *y_reflect(char *row) {
  //char copy[strlen(row)];
  char *copy;
  copy = strdup(row);
  /* char delim[2] = " "; */
  /* char *ptr = strtok(copy, delim); */
  int i = 0;
  char *ans = malloc(strlen(row) * sizeof(char));
  char *color = malloc(13 * sizeof(char));
  char *rgb_val;
  /* while(ptr != NULL) { */
  /*   ptr = strtok(NULL, delim); */
  /* } */
  while((rgb_val = strsep(&copy, " ")) != NULL) {
    /* for(i = 0; i < 250; i++) { */
    /* sprintf(color, "%c %c %c", copy[i * 3], copy[i * 3 + 1], copy[i * 3 + 2]); */
    sprintf(color, "%s%s ", color, rgb_val);
    // strcat(color, rgb_val);
    i++;
    if (i % 3 == 0) {
      strprefix(ans, color);
      /* *(ans - strlen(color)) = *color; */
      /* *ans = *(ans - strlen(color)); */
      // sprintf(ans, "%s%s", color, ans);
      strcpy(color, "");
    }
    /* sprintf(color, "%s %s %s", copy[i * 3], copy[i * 3 + 1], copy[i * 3 + 2]); */
  }
  free(copy);
  /* free(color); */
  return ans;
}

/* char *y_reflect(char *row) { */
/*   //char copy[strlen(row)]; */
/*   char *copy; */
/*   copy = strdup(row); */
/*   /\* char delim[2] = " "; *\/ */
/*   /\* char *ptr = strtok(copy, delim); *\/ */
/*   int i = 0; */
/*   char *ans = malloc(strlen(row) * sizeof(char)); */
/*   char color[15]; */
/*   char *rgb_val; */
/*   /\* while(ptr != NULL) { *\/ */
/*   /\*   ptr = strtok(NULL, delim); *\/ */
/*   /\* } *\/ */
/*   while((rgb_val = strsep(&copy, " ")) != NULL) { */
/*   /\* for(i = 0; i < 250; i++) { *\/ */
/*     /\* sprintf(color, "%c %c %c", copy[i * 3], copy[i * 3 + 1], copy[i * 3 + 2]); *\/ */
/*     if(i % 3 == 0) { */
/*       sprintf(ans, "%s %s", color, ans); */
/*       strcpy(color, ""); */
/*     } */
/*     sprintf(color, "%s %s", color, rgb_val); */
/*     i++; */
/*     /\* sprintf(color, "%s %s %s", copy[i * 3], copy[i * 3 + 1], copy[i * 3 + 2]); *\/ */
/*   } */
/*   return ans; */
/* } */

char *x_reflect(char *pic) {
  /* char copy[strlen(pic)]; */
  /* strcpy(copy, pic); */
  char *copy, *row, *copy2, *x_reflect;
  x_reflect = malloc(strlen(pic) * sizeof(char));
  copy = strdup(pic);
  copy2 = copy;
  while ((row = strsep(&copy, "\n")) != NULL) {
    /* sprintf(row, "%s\n", row); */
    /* sprintf(pic, "%s\n%s", row, pic); */
    strprefix(x_reflect, "\n");
    strprefix(x_reflect, row);
    /* printf("%s: %s\n", "---", pic); */
  }
  free(copy2);
  /* free(row); */
  return x_reflect;
}

int main(int argc, char *argv[]) {
  char *row, *pic, row_full;
  int *randarr;
  int devrandom = error_check(open("/dev/urandom", O_RDONLY));
  int newfile = error_check(open("pic.ppm", O_CREAT | O_RDWR, 0644));
  size_t pic_size = 0;
  /* int *randarr = calloc(250, sizeof(int)); */
  pic = malloc(3);
  /* pic = calloc(500 * 255 * 4, sizeof(char)); */
  /* if(pic == NULL) exit(1); */
  /* error_check(*row); error_check(*pic); */
  /* error_check(char *row = calloc(500 * 4, sizeof(char))); */
  /* error_check(char *pic = calloc(500 * 500 * 4, sizeof(char))); */
  //char *row = calloc(13, sizeof(char));
  char *intro = calloc(20, sizeof(char));
  sprintf(intro, "P3\n500 500\n255\n");

  error_check(write(newfile, intro, strlen(intro)));
  free(intro);
  int i, j;
  if (argc > 1) {
    for(i = 0; i < 250; i++) {
      error_check(read(devrandom, randarr, 250 * sizeof(int)));
      for(j = 0; j < 250; j++)
        printf("%d ", randarr[j]);
      printf("\n");
    }
  } else {
    for(j = 0; j < 500; j++) {
      row = calloc(255 * 4, sizeof(char));
      randarr = calloc(250, sizeof(int));
      error_check(read(devrandom, randarr, 250 * sizeof(int)));
      for (i = 0; i < 255; i++) {
        strcat(row, get_color(randarr[i]));
        /* sprintf(row, "%s%s", row, get_color(randarr[i])); */
        /* sprintf(row + strlen(row), get_color(randarr[i])); */
      }
      /* pic = reallocarray(pic, strlen(row) + pic_size, sizeof(char)); */
      /* free(randarr); */
      error_check(write(newfile, strcat(row, " "), strlen(row)));
      error_check(write(newfile, strcat(y_reflect(row), "\n"), strlen(row)));
      /* strprefix(pic, y_reflect(row)); */
      /* strprefix(pic, row); */
      //strcat(pic, row);
      /* sprintf(pic, "%s\n%s", pic, row); */
      /* printf("%lu %d\n", sizeof(row), strlen(row)); */
      /* printf("%s\n", row); */
      //sprint(row, "%s %s", row, y_reflect(row));
      /* free(randarr); */
      free(row);
    }
    /* error_check(write(newfile, pic, strlen(pic))); */
    //sprintf(pic, "%s\n", x_reflect(pic));
    //printf("%s\n", pic);
    // my_write(newfile, randarr1, 125 * sizeof(int));
  }

  /* free(*row); */
  /* free(randarr); */
  close(devrandom);
  close(newfile);
  return 0;
}
