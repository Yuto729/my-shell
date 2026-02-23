#include <stdio.h>
#include <unistd.h>

int main(void) {
    printf("=== Without fflush ===\n");
    for (int i = 0; i < 5; i++) {
        printf(".");  // 改行なし、fflushなし
        sleep(1);
    }
    printf(" Done!\n");

    printf("\n=== With fflush ===\n");
    for (int i = 0; i < 5; i++) {
        printf(".");  // 改行なし
        fflush(stdout);  // 毎回フラッシュ
        sleep(1);
    }
    printf(" Done!\n");

    return 0;
}
