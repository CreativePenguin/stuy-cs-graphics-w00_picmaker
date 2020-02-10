#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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
  free(tmp);
  return dest;
}

char *x_reflect(char *pic) {
  /* char copy[strlen(pic)]; */
  /* strcpy(copy, pic); */
  char *copy, *row;
  copy = strdup(pic);
  while ((row = strsep(&copy, "\n")) != NULL) {
    /* sprintf(row, "%s\n", row); */
    /* sprintf(pic, "%s\n%s", row, pic); */
    strprefix(pic, "\n");
    strprefix(pic, row);
    /* printf("%s: %s\n", "---", pic); */
  }
  free(copy);
  return pic;
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
  free(copy); free(rgb_val); free(color);
  return ans;
}

int main() {
  char *test = malloc(255 * sizeof(char));
  /* strcpy(test, "123 255 694 33 1 3 99 54 9"); */
  /* sprintf(test, "%s%s\n", test, y_reflect(test)); */
  /* printf("%s\n", test); */
  strcpy(test, "123 225 694\n33 1 3\n99 54 9");
  sprintf(test, x_reflect(test));
  printf("%s\n", test);
  free(test);
  return 0;
}
