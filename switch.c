#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LEN (1024 * 1024 * 8)
#define LOOP 50

struct timespec start;

static int vec[16] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

static void loop(char *inst) {
  clock_gettime(CLOCK_REALTIME, &start);
  for (;;) {
    switch (*inst) {
      case 0: return;
      case 1: for (int i = 0; i < LOOP; i++) vec[1]++; break;
      case 2: for (int i = 0; i < LOOP; i++) vec[2]++; break;
      case 3: for (int i = 0; i < LOOP; i++) vec[3]++; break;
      case 4: for (int i = 0; i < LOOP; i++) vec[4]++; break;
      case 5: for (int i = 0; i < LOOP; i++) vec[5]++; break;
      case 6: for (int i = 0; i < LOOP; i++) vec[6]++; break;
      case 7: for (int i = 0; i < LOOP; i++) vec[7]++; break;
      case 8: for (int i = 0; i < LOOP; i++) vec[8]++; break;
      case 9: for (int i = 0; i < LOOP; i++) vec[9]++; break;
      case 10: for (int i = 0; i < LOOP; i++) vec[10]++; break;
      case 11: for (int i = 0; i < LOOP; i++) vec[11]++; break;
      case 12: for (int i = 0; i < LOOP; i++) vec[12]++; break;
      case 13: for (int i = 0; i < LOOP; i++) vec[13]++; break;
      case 14: for (int i = 0; i < LOOP; i++) vec[14]++; break;
      case 15: for (int i = 0; i < LOOP; i++) vec[15]++; break;
    }
    inst++;
  }
}

static void printvec() {
  for (int i = 0; i < 16; i++)
    printf("%d ", vec[i]);
  printf("\n");
}

static void printtime() {
  struct timespec end;
  clock_gettime(CLOCK_REALTIME, &end);
  long t1 = start.tv_sec * 1000 * 1000 * 1000 + start.tv_nsec;
  long t2 = end.tv_sec * 1000 * 1000 * 1000 + end.tv_nsec;
  printf("time: %f\n", (t2 - t1) / 1e9);
}

int main(int argc, char **argv) {
  // create random "VM" instructions
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
