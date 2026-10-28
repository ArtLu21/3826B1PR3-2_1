#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int read_guess(int n, int guess[])
{
    int i, c;
    c=getchar();
    while (c==' ' || c=='\n')
        c= getchar();

    for (i=0; i<n;i++)
    {
        if (c<'0' || c>'9')
        {
            while (c!='\n')
                c=getchar();
            return 0;
        }
        guess[i]=c-'0';
        c = getchar();
    }

    if (c!='\n' && c!=' ')
    {
        while (c!= '\n')
            c=getchar();
        return 0;
    }

    while (c!='\n')
        c=getchar();

    return 1;
}

int main()
{
    int n,c;
    int secret[5], guess[5];
    int bulls, cows;
    int ok;
    int good;

    srand((unsigned)time(NULL));
    printf("GAME 'cows and bulls', input n from 2 to 5:'\n");

    do
    {
        good=1;
        if (scanf("%d", &n)!= 1)
        {
            while ((c=getchar())!='\n') {}
            printf("Bad input, try again,please.\n");
            good=0;
        }
        else
        {
            while ((c=getchar())!= '\n') {}
            if (n<2 || n>5)
            {
                printf("Wrong n, try again.\n");
                good=0;
            }
        }
    } while (!good);

    for (i=0; i<n; i++)
    {
        int r;
        do
        {
            r=rand()%10;
            ok = 1;
            for (j=0; j<i;j++)
                if (secret[j]==r) ok= 0;
        } while (!ok);
        secret[i] = r;
    }

    bulls=0;
    while (bulls!= n)
    {
        printf("Your guess: ");

        if (!read_guess(n, guess))
        {
            printf("Bad input, try again.\n");
            continue;
        }

        bulls = 0;
        cows = 0;
        for (int i=0;i < n;i++)
        {
            if (guess[i] == secret[i])
                bulls++;
            else
            {
                for (int j=0; j<n;j++)
                    if (i!=j && guess[i]==secret[j])
                        cows++;
            }
        }

        printf("Bulls: %d, Cows: %d\n",bulls,cows);
    }

    printf("You win!\n");
    return 0;
}