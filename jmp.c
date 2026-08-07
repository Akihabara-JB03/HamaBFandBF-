#include "jmp.h"
int position[CODE_SIZE];
int j = 0;
void find_open(int i) {
    if (j >= CODE_SIZE) {
        return;
    }
    position[j] = i;
    j++;

}
void find_close(int i) {
    if (j <= 0) {
        // 対応する [ がない
        return;
    }
    j--;

    int open = position[j];

    position[open] = i;
    position[i] = open;

}