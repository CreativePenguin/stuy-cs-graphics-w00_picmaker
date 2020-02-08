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
  return ans;
}

int main() {
  char *test = malloc(255 * sizeof(char));
  strcpy(test, "123 255 694 33 1 3 99 54 9");
  sprintf(test, "%s%s\n", test, y_reflect(test));
  /* strcpy(test, y_reflect("123 255 694 33 1 3 99 54 9")); */
  printf("%s\n", test);
  /* printf("%s\n", y_reflect("123 255 694 33 1 3")); */
  /* strcpy(test, "It's kind of a funny story"); */
  /* char *thirty = malloc(30 * sizeof(char)); */
  /* strcpy(thirty, "") */
  /* int i = 0; */
  /* for(i = 0; i < 30; i++) */
  /*   test[i + 30] = test[i]; */
  /* for(i = 0; i < 30 ) */
  /* printf("%c", test[50]); */
  free(test);
  return 0;
}
