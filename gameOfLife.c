/* PART II: SHOW CELL AGE */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WIDTH 79
#define MAX_HEIGHT 51

/* Integer -1 indicates a dead cell. */
/* Integer 1 indicates a live cell. */


int** create_board(void)
{
	int i, j;

	/* Creates the board using dynamic memory allocation. */
	int** new_board;
	new_board = malloc(sizeof(int*) * MAX_HEIGHT); /* Allocates the maximum rows. */
	for (i = 0; i < MAX_HEIGHT; i++)
	{
		new_board[i] = malloc(sizeof(int*) * MAX_WIDTH); /* Allocates the maximum columns. */
	}

	/* Assigns -1 (dead cell) to all the positions on the board. */
	for (i = 0; i < MAX_HEIGHT; i++)
	{
		for (j = 0; j < MAX_WIDTH; j++)
		{
				new_board[i][j] = -1;
		}
	}

	return new_board;
}


void check_board(int** board, int width, int height)
{
	int i, j;

	/* Checks if the width and height are within the allowed range. */
	if (width >= MAX_WIDTH || width <= 0)
	{
		fprintf(stderr, "\nThe width, %d, is not between the allowed range (1 - 78).\n", width);
		exit(EXIT_FAILURE);
	}

	if (height >= MAX_HEIGHT || height <= 0)
	{
		fprintf(stderr, "\nThe height, %d, is not between the allowed range (1 - 50).\n", height);
		exit(EXIT_FAILURE);
	}

	/* Checks if the initial live cells fit on the board. */
	for (i = 0; i < MAX_HEIGHT; i++)
	{
		for (j = 0; j < MAX_WIDTH; j++)
		{
			if (board[i][j] == 1)
			{
				if (j >= width)
				{
					fprintf(stderr, "\nThe width, %d, is too small to fit all the intial cells.\n", width);
					exit(EXIT_FAILURE);
				}
				if (i >= height)
				{
					fprintf(stderr, "\nThe height, %d, is too small to fit all the intial cells.\n", height);
					exit(EXIT_FAILURE);
				}
			}
		}
	}
}


int count_neighbours(int** board, int i, int j)
{
	int count = 0;

	/* If there is a live cell around a live cell, count increments by 1. */
	if (i != 0 && j != 0)
	{
		if (board[i-1][j-1] == 1)
			count++;

		if (board[i][j-1] == 1)
			count++;

		if (board[i+1][j-1] == 1)
			count++;

		if (board[i-1][j] == 1)
			count++;

		if (board[i+1][j] == 1)
			count++;

		if (board[i-1][j+1] == 1)
			count++;

		if (board[i][j+1] == 1)
			count++;

		if (board[i+1][j+1] == 1)
			count++;
	}


	/* Prevents segmentation faults by skipping the spaces where there are no cells. */
	else if (i == 0 && j == 0)
	{
		if (board[i+1][j] == 1)
			count++;

		if (board[i][j+1] == 1)
			count++;

		if (board[i+1][j+1] == 1)
			count++;
	}

	/* Prevents segmentation faults by skipping the spaces where there are no cells. */
	else if (i == 0 && j != 0)
	{
		if (board[i][j-1] == 1)
			count++;

		if (board[i+1][j-1] == 1)
			count++;

		if (board[i+1][j] == 1)
			count++;

		if (board[i][j+1] == 1)
			count++;

		if (board[i+1][j+1] == 1)
			count++;
	}

	/* Prevents segmentation faults by skipping the spaces where there are no cells. */
	else if (j == 0 && i != 0)
	{
		if (board[i-1][j] == 1)
			count++;

		if (board[i+1][j] == 1)
			count++;

		if (board[i-1][j+1] == 1)
			count++;

		if (board[i][j+1] == 1)
			count++;

		if (board[i+1][j+1] == 1)
			count++;
	}

	return count;
}


int** update(int** board, int width, int height, int** age)
{
	int i, j;
	int neighbours;

	/* Makes copy of current board. */
	int** current_board = board;

	/* Creates the updated board with all the cells dead. */
	int** updated_board = create_board();

	/* Iterates over the current board. */
	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			/* Counts the number of live neighbours around the current cell. */
			neighbours = count_neighbours(current_board, i, j);

			if (current_board[i][j] == 1) /* Checks if cell is alive. */
			{
				if (neighbours < 2) /* Fewer than two neighbours --> dies, age restarts. */
				{
					updated_board[i][j] = -1;
					age[i][j] = 0;
				}
					else if (neighbours == 2 || neighbours == 3) /* Two or three neighbours --> lives, age increments. */
					{
						updated_board[i][j] = 1;
						age[i][j]++;
					}
						else if (neighbours > 3) /* More than three neighbours --> dies, age restarts. */
						{
							updated_board[i][j] = -1;
							age[i][j] = 0;
						} 
			}

			if (current_board[i][j] == -1) /* Checks if cell is dead. */
			{
				if (neighbours == 3) /* Three neighbours --> becomes alive. */
					updated_board[i][j] = 1;					
			}
		}
	}

	return updated_board;
}


void print_board(int** board, int width, int height, int** age)
{
	int i, j;

	/* Prints header. (borders and top)*/
	printf("*");
	for (i = 0; i < width; i++)
	{
		printf("-");	
	}
	printf("*");
	printf("\n");

	/* Prints vertical borders and the cells configuration. */
	for (i = 0; i < height; i++)
	{
		printf("|");	
		for (j = 0; j < width; j++)
		{
			if (board[i][j] == 1 && age[i][j] < 10) /* If cell is alive and has lived for less than 10 rounds, prints the age of the cell. */
				printf("%d", age[i][j]);
			else if (board[i][j] == 1 && age[i][j] > 9) /* If cell is alive and has lived for 10 rounds or more, prints X". */
				printf("X");
			else
				printf(" "); /* If not, prints an empty space. */
		}
		printf("|");
		printf("\n");
	}

	/* Prints footer. (borders and bottom) */
	printf("*");
	for (i = 0; i < width; i++)
	{
		printf("-");	
	}
	printf("*");
}


/* Reads the file to determine the live cells and returns the board as a 2D array. */
int** read_file(char* file_name)
{
	FILE* pfile;
	int no_cells;
	int i, row, column;

	/* Creates the board. */
	int** board = create_board();

	/* Opens file and checks if the file exists. */
	pfile = fopen(file_name, "r");
	if (pfile == 0)
	{
		fprintf(stderr, "\nFile not found.");
		fprintf(stderr, "\nExiting program...\n");
		exit(EXIT_FAILURE);
	}


	/* Reads the number of live cells from the file. */
	fscanf(pfile, "%d", &no_cells);

	/* Assigns a 1 to the positions on the board where the cells live. */
	for (i = 0; i < no_cells; i++)
	{
		fscanf(pfile, "%d %d", &row, &column);
		board[row][column] = 1;
	}

	fclose(pfile);

	return board;
}


int main(int argc, char* argv[])
{
	
	/* Declare variables. */
	char* infile;
	int width, height, generations;
	int i, j;

	/* Parse input. */
	infile = argv[1];
	width = atoi(argv[2]);
	height = atoi(argv[3]);
	generations = atoi(argv[4]);

	/* Makes a 2D array to hold the age of each position. */
	int** age;
	age = malloc(sizeof(int*) * MAX_HEIGHT); /* Allocates the maximum rows. */
	for (i = 0; i < MAX_HEIGHT; i++)
	{
		age[i] = malloc(sizeof(int*) * MAX_WIDTH); /* Allocates the maximum columns. */
	}

	/* Assigns a 0 to all the positions. */
	for (i = 0; i < MAX_HEIGHT; i++)
	{
		for (j = 0; j < MAX_WIDTH; j++)
		{
				age[i][j] = 0;
		}
	}
		
	/* Makes the board. */
	int** board = read_file(infile);

	/* Checks if the width and height are allowed values and the size is enough for all the intial cells to fit, if not, program exits. */
	check_board(board, width, height);

	/* Prints the board with the intial configuration. */
	print_board(board, width, height, age);

	/* Copies the intial configuration of the board for the first iterartion of generations. */
	int** updated_board = board;

	/* Run for the number of generations. */
	for (i = 0; i < generations; i++)
	{
		/* Updates the board and returns it. */
		updated_board = update(updated_board, width, height, age);

		/* Prints the updated board. */
		printf("\n\n\n");
		print_board(updated_board, width, height, age);
	}

	printf("\n\nFinished\n");

	return 0;
}