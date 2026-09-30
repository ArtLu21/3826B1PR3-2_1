#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main()
{
	double dsp = 550, dvp = 800, tree = 400; // kg/m^3
	double h, d, w;

	printf("Enter height, depth, and width of the wardrobe (in cm) separated by spaces: ");
	if (scanf("%lf %lf %lf", &h, &d, &w) != 3) {
		printf("Error\n");
		return 1;
	}

	if (h < 180 || h > 220 || w < 80 || w > 120 || d < 50 || d > 90)
	{
		printf("Error: invalid range of values\n clue: h>=180 & h<=220\n w>=80 & w<=120\n d>=50 & d<=90\n");
		return 1;
	}

	double h_m = h / 100;
	double d_m = d / 100;
	double w_m = w / 100;

	// 1.Back wall (dvp)
	double v_dvp = h_m * w_m * 0.005;
	double ms_dvp = v_dvp * dvp;

	// 2. 2 side walls (dsp)
	double v_sides = 2 * h_m * d_m * 0.015;

	// 3.Top and bottom covers (dsp)
	double v_covers = 2 * w_m * d_m * 0.015;

	// 4. 2 doors (tree)
	double v_doors = h_m * w_m * 0.01;
	double ms_doors = v_doors * tree;

	// 5.shelves (dsp)
	int num_shelves = (int)((h - 3) / 40);
	double w_shelf_m = (w - 3) / 100;
	double v_shelves = num_shelves * w_shelf_m * d_m * 0.005;

	double ms_dsp = (v_sides + v_covers + v_shelves) * dsp;
	double total_ms = ms_dvp + ms_dsp + ms_doors;

	printf("Total mass of the wardrobe: %.2lf kg\n", total_ms);

	return 0;
}