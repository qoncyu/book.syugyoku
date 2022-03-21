#include <stdio.h>

#define CHAR_BIT 8
#define BITSPERWORD 32 // 4バイト = 8bit x 4
#define SHIFT 5 // 32(BITSPERWORD)で除算することは、右に5でシフトすることと同じ
#define MASK 0x1F // 0001 1111
#define N 10

// 実行
// ```
// $ cc -g a.c
// $ cat in.txt | ./a.out
// ```

// |= ビット単位のOR代入演算子
// ~  補数演算子 反転させる

void printb(unsigned int v) {
    unsigned int mask = (int)1 << (sizeof(v) * CHAR_BIT - 1);
    do putchar(mask & v ? '1' : '0');
    while (mask >>= 1);
    printf("\n");
}

int a[1 + N/BITSPERWORD]; // 10/32+1 = 1
void set(int i) {
    // ビット列
    // 1のビット列表現
    // data | 0000 0001 | 1
    // mask | 0001 1111 | 1F
    // ----------------------
    // calc | 0000 0001 | 1 & : 1
    // calc | 0000 0010 | 1 << ビット列となる

    // 16のビット列表現
    // data | 1001 0000 | 144
    // mask | 0001 1111 | 1F
    // ----------------------
    // calc | 0001 0000 | 1 & : 16
    // calc | 1000 0000 0000 0000 | 1 << 16 : ビット列となる

    // 添字: ひとつの添字（int）につき、32個（32bit=4byte*8bit）の数情報を保持できる
    // 0の最初
    // data | 0000 0001 | 1
    // ----------------------
    // calc | 0000 0000 | >> SHIFT : 添字 [0]

    // 0の最後
    // data | 0001 1111 | 31
    // ----------------------
    // calc | 0000 0000 | >> SHIFT : 添字 [0]

    // 1の最初
    // data | 0010 0000 | 32
    // ----------------------
    // calc | 0000 0001 | >> SHIFT : 添字 [1]

    // 1の最後
    // data | 0011 1111 | 63
    // ----------------------
    // calc | 0000 0001 | >> SHIFT : 添字 [1]

    a[i>>SHIFT] |= (1<<(i & MASK));
    printf("[set] i: %d, a[i>>SHIFT]: %d, i>>SHIFT: %d, i & MASK: %d, (1<<(i & MASK): %d, a[i>>SHIFT]: %d\n", i, a[i>>SHIFT], i>>SHIFT, i & MASK, 1<<(i & MASK), a[i>>SHIFT]);
    printb(a[i>>SHIFT]);
}
void clr(int i) {
    // 各ビットに0をセットする
    a[i>>SHIFT] &= ~(1<<(i & MASK));
    printf("[clr] in: %d, a[i>>SHIFT]: %d, i>>SHIFT: %d, ~(1<<(i & MASK)): %d\n", i, a[i>>SHIFT], i>>SHIFT, ~(1<<(i & MASK)));
}
int test(int i) {
    // 配列各要素のビットをチェック
    return a[i>>SHIFT] & (1<<(i & MASK));
}

int main(void)
{
    int i;
    for (i = 0; i < N; i++)
        clr(i);

    while (scanf("%d", &i) != EOF)
        set(i);

    for (i = 0; i < N; i++)
        if (test(i))
            printf("%d\n", i);

    printf("a[0] %d\n", a[0]);
    return 0;
}
