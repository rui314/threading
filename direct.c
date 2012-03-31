#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LEN (1024 * 1024 * 8)
#define LOOP 50

struct timespec start;

static int vec[16] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

static void loop(char *inst) {
  void *table[] = { &&L0, &&L1, &&L2, &&L3, &&L4, &&L5, &&L6, &&L7, &&L8, &&L9, &&L10, &&L11, &&L12, &&L13, &&L14, &&L15 };

  void **addrs = malloc(LEN * sizeof(void *));
  for (int i = 0; i < LEN; i++)
    addrs[i] = table[inst[i]];

  clock_gettime(CLOCK_REALTIME, &start);
#define NEXT goto *(*addrs++)
  NEXT;
L0: return;
L1: for (int i = 0; i < LOOP; i++) vec[1]++; NEXT;
L2: for (int i = 0; i < LOOP; i++) vec[2]++; NEXT;
L3: for (int i = 0; i < LOOP; i++) vec[3]++; NEXT;
L4: for (int i = 0; i < LOOP; i++) vec[4]++; NEXT;
L5: for (int i = 0; i < LOOP; i++) vec[5]++; NEXT;
L6: for (int i = 0; i < LOOP; i++) vec[6]++; NEXT;
L7: for (int i = 0; i < LOOP; i++) vec[7]++; NEXT;
L8: for (int i = 0; i < LOOP; i++) vec[8]++; NEXT;
L9: for (int i = 0; i < LOOP; i++) vec[9]++; NEXT;
L10: for (int i = 0; i < LOOP; i++) vec[10]++; NEXT;
L11: for (int i = 0; i < LOOP; i++) vec[11]++; NEXT;
L12: for (int i = 0; i < LOOP; i++) vec[12]++; NEXT;
L13: for (int i = 0; i < LOOP; i++) vec[13]++; NEXT;
L14: for (int i = 0; i < LOOP; i++) vec[14]++; NEXT;
L15: for (int i = 0; i < LOOP; i++) vec[15]++; NEXT;
}

void printvec() {
  for (int i = 0; i < 16; i++)
    printf("%d ", vec[i]);
  printf("\n");
}

void printtime() {
  struct timespec end;
  clock_gettime(CLOCK_REALTIME, &end);
  long t1 = start.tv_sec * 1000 * 1000 * 1000 + start.tv_nsec;
  long t2 = end.tv_sec * 1000 * 1000 * 1000 + end.tv_nsec;
  printf("time: %f\n", (t2 - t1) / 1e9);
}

int main(int argc, char **argv) {
  char *inst = malloc(LEN);
  for (int i = 0; i < LEN - 1;) {
    int op = rand() & 15;
    if (op == 0) continue;
    inst[i++] = op;
  }
  inst[LEN - 1] = 0;
  loop(inst);
  printvec();
  printtime();
  return 0;
}
