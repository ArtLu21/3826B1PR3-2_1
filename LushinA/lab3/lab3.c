#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    int n, c;
    int secret[5], guess[5];
    int bulls, cows;
    int ok, good;
    int i, j;

    srand((unsigned)time(NULL));
    printf("GAME 'cows and bulls', input n from 2 to 5:\n");

    do
    {
        good = 1;
        if (scanf("%d", &n) != 1)
        {
            while ((c = getchar()) != '\n' && c != EOF) {}
            printf("Bad input, try again, please.\n");
            good = 0;
        }
        else
        {
            while ((c = getchar()) != '\n' && c != EOF) {}
            if (n < 2 || n > 5)
            {
                printf("Wrong n, try again.\n");
                good = 0;
            }
        }
    } while (!good);

    for (i = 0; i < n; i++)
    {
        int r;
        do
        {
            r = rand() % 10;
            ok = 1;
            for (j = 0; j < i; j++)
                if (secret[j] == r) ok = 0;
        } while (!ok);
        secret[i] = r;
    }

    bulls = 0;
    while (bulls != n)
    {
        printf("Your guess: ");

        while ((c = getchar()) == ' ' || c == '\n') {
            if (c == EOF) break;
        }

        int count = 0;
        int is_valid = 1;

        while (c != '\n' && c != ' ' && c != EOF)
        {
            if (count >= n || c < '0' || c > '9') {
                is_valid = 0;
            }
            else {
                guess[count] = c - '0';
                count++;
            }
            c = getchar();
        }

        if (count != n) {
            is_valid = 0;
        }

        while (c != '\n' && c != EOF) {
            c = getchar();
        }

        if (!is_valid) {
            printf("Bad input, please enter exactly %d digits.\n", n);
            continue;
        }

        bulls = 0;
        cows = 0;
        for (i = 0; i < n; i++)
        {
            if (guess[i] == secret[i]) {
                bulls++;
            }
            else {
                for (j = 0; j < n; j++) {
                    if (i != j && guess[i] == secret[j]) {
                        cows++;
                    }
                }
            }
        }

        printf("Bulls: %d, Cows: %d\n", bulls, cows);
    }

    printf("You win!\n");
    return 0;
}
