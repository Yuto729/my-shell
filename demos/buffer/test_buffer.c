#include <stdio.h>
#include <unistd.h>

int main(void) {
    printf("=== Test 1: fflush なし ===\n");
    printf("Waiting (no newline)...");  // 改行なし
    sleep(2);  // 2秒待つ
    printf(" Done!\n");

    printf("\n=== Test 2: fflush あり ===\n");
    printf("Waiting (with fflush)...");  // 改行なし
    fflush(stdout);  // バッファを強制フラッシュ
    sleep(2);  // 2秒待つ
    printf(" Done!\n");

    return 0;
}
