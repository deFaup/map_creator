#include <stdio.h>
//#include <stdint.h>
#include <stdlib.h>		/* malloc free srand rand*/
#include <time.h>       /* time */

int* ones(int rows, int cols);
int* new_line_index(int* x, int height);
void print_mat(int* mat, int rows, int cols);
void puts_zero(int* mat, int height, int width, int x, int y);
int* new_column_index(int* y, int width);

void matrix(int *mat, int row, int col);
int int_power(int number, int power);
int Bernoulli(float p);

/*	Largeur image = width
hauteur image = height
row = lignes = x
col = colonnes = y
x_max = height
y_max = width
*/
/*
mat[0 * width + width - 1] is top right
mat[(height-1) * width + width - 1] is bottom right
*/
int main()
{
	printf("Hello, World!\n");

	/* Intializes random number generator */
	time_t t;
	srand((unsigned)time(&t));

	/* Make matrix full of one*/
	int height = 50, width = 50;
	int* mat = ones(height, width);
	//print_mat(mat, height, width);

	/* Starting with the first column and random row */
	int x = 0, y = 0;
	x = rand() % height;
	mat[x*width + y]++;
	puts_zero(mat, height, width, x, y);
	//print_mat(mat, height, width);

	while (y != width - 1) {
		/* new x and new y*/
		new_column_index(&y, width);
		new_line_index(&x, height);
		printf("x,y : %d %d\n", x, y);

		/* update the matrix */
		mat[x*width + y]++;
		puts_zero(mat, height, width, x, y);

		//print_mat(mat, height, width);
	}
	print_mat(mat, height, width);

	free(mat);
	while(1){}
	return 0;
}

int* ones(int rows, int cols)
{
	int* mat;
	mat = (int*)malloc(rows * cols * sizeof(int));
	int i, j = 0;

	for (i = 0; i < rows; i++) {
		for (j = 0; j < cols; j++) {
			mat[i*cols + j] = 1;
		}
	}

	return mat;
}

void print_mat(int* mat, int rows, int cols) {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			printf("%d ", mat[i*cols + j]);
		}
		printf("\n");
	}
	printf("\n\n\n");
}

int* new_line_index(int* x, int height) {
	/* new index based on the preivous one */
	/* be careful no to make x negative or superior to height -1 */
	int sign = 1;
	if (*x <= 0.3 * height) //30% of free space in the top for the sky
		sign = +1;
	else if (*x >= 0.8 * height) // 20% of bottom space for the ground
		sign = -1;
	else
		sign = int_power(-1, rand() % 1); // Either -1 or 1

	*x = *x + sign* (rand() % 3);
	return x;
}

int* new_column_index(int* y, int width) {
	/* We give the possibility to our mask to go backwards */
	float p = 1.0;
	if (*y == 0) { /* If the previous position is zero then we need to go right */
		*y = *y + 1;
		p = 0.5;
		printf("p= %lf\n", p);
	}
	else { 
	/* If you make one you go right and then you have p*100 % of chances to make one again
	   but if you don't then you go left and you have p*100 % of chances to make zero again
	*/
		if (Bernoulli(p)) {
			*y = *y + 1;
			p = 0.7;
			printf("p= %lf\n", p);
		}
		else {
			*y--;
			p = 0.3;
			printf("p= %lf\n", p);
		}
	}
	return y;
}


void puts_zero(int* mat, int height, int width, int x, int y) {
	/* if mat(xxx xxx) = 2 then
	we put all values in the col xxx from the beginning to xxx to 0 (reduce 1)
	*/
	for (int i = 0; i < x; i++) {
		mat[i*width + y] --;
	}
}

void matrix(int *mat, int row, int col) {

}

int int_power(int number, int power) {
	int temp = 1;
	for (int i = 0; i < power; i++) {
		temp = temp*number;
	}
	return temp;
}

int Bernoulli(float p) {
	/* p between 0 and 1 */
	int temp = rand() % 101;
	printf("temp= %d\t", temp);
	if (temp <= p * 100)
		return 1;
	else
		return 0;
}