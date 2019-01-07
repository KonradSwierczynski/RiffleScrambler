#include <riffle/riffle_scrambler_c.h>
#include <string.h>
#include <stdio.h>

char hash[100];

int main() {
    const char *pwd = "pwd", *salt = "salt";

    int result = riffle_scrambler((void *)hash, 40, (void *)pwd, 3, (void *)salt, 4, 2, 12);


    printf("%d %s", result, hash);

    printf("\n");

    for(int i = 0; i < 32; i++) {
        printf("%2x", hash[i] & 0xff);
    }

    return 0;
}

