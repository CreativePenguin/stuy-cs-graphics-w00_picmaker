#include <string.h>
#include "queue.h"

#define MAX 20

char *charArr[MAX];
int front;
int itemcount;

char* peek() {
  return charArr[front];
}

char *deleteData() {
  front++;
  itemcount--;
  return charArr[front];
}
