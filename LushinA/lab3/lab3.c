#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
	int n, j,i;
	int secret[5];
	int guess[5];
	int num, uniq;
	int bulls, cows;

	srand(time(NULL));

	printf("GAME 'cows and bulls', input n from 2 to 5: ");
	if (scanf("%d", &n) != 1)
	{
		printf("Error\n");
		return 1;
	}

	if (n < 2 || n > 5)
	{
		printf("Error\n");
		return 1;
	}

	for (i = 0; i < n; i++)
	{
		uniq = 0;
		while (uniq == 0)
		{
			num = rand() % 10;
			uniq = 1;

			for (j = 0; j < i; j++)
			{
				if (secret[j] == num)
				{
					uniq = 0;
				}
			}

			if (uniq == 1)
			{
				secret[i] = num;
			}
		}
	}

	bulls = 0;
	while (bulls!=n)
	{
		printf("Enter your guess (%d digits): ",n);

		for (i = 0; i < n; i++)
		{
			scanf("%1d", &guess[i]);
		}

		bulls = 0;
		cows = 0;

		for (i = 0; i< n; i++)
		{
			for (j = 0; j < n; j++)
			{
				if (guess[i]==secret[j])
				{
					if (i==j)
					{
						bulls= bulls +1;
					}
					else
					{
						cows=cows +1;
					}
				}
			}
		}

		printf("Cows: %d, Bulls: %d\n\n", cows,bulls);
	}
	printf("You won!\n");
	return 0;
}
