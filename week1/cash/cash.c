#include <stdio.h>
#include <cs50.h>

int main(void) {
    int change;

    do {
        change = get_int("Change owed: ");
    } while (change < 0);

    int coins[] = {25, 10, 5, 1};
    int coin_count = 0;

    for (int i = 0; i < 4; i++) {
        while (change >= coins[i]) {
            change -= coins[i];
            coin_count++;
        }
    }

    printf("%d\n", coin_count);
    return 0;
}
