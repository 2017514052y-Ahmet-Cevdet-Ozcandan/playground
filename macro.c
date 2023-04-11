#include <stdio.h>
#define SQUARE(x) ((x) * (x))

int main() {
    int num = 5;
    int squared = SQUARE(num);

    printf("%d'nin karesi: %d\n", num, squared);

    return 0;
}
