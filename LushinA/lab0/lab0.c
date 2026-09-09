
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>

int main()
{
    double R1, x1, y1, d;
    double R2, x2, y2;

    printf("Enter R1: ");
    scanf("%lf", &R1);
    printf("Enter x1: ");
    scanf("%lf", &x1);
    printf("Enter y1: ");
    scanf("%lf", &y1);

    printf("Enter R2: ");
    scanf("%lf", &R2);
    printf("Enter x2: ");
    scanf("%lf", &x2);
    printf("Enter y2: ");
    scanf("%lf", &y2);

    d = sqrt((x2-x1) * (x2-x1) + (y2-y1) * (y2-y1));

    if (d==0 && R1==R2)
    {
        printf("Intersect");
    }
    else if (d<fabs(R1 - R2))
    {
        printf("do not Intersect");
    }
    else if (d==R1+R2 || d ==fabs(R1-R2))
    {
        printf("Touch");
    }
    else if (d > fabs(R1-R2) && d<R1+R2)
    {
        printf("Intersect");
    }
    else
    {
        printf("do not Intersect");
    }
}

