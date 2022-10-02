// Felicia Chen

#include <stdio.h>
#include <stdlib.h>

char matrix[500][500];
char inputData[500];

void errorMsg(char *msg)
{
	printf(msg);
	printf("Program syntax: ./cipher SWITCH KEY LENGTH < FILENAME\n");
	printf("Legal usage examples: ./cipher -e 10 100 < filename.txt\n");
	printf("./cipher -d 10 200 < filename.e\n");
}

void read(int length)
{
	int index = 0;
	while (index < (length))
	{
		inputData[index] = getc(stdin);
		index++;
	}
}

void encrypt(int key, int length)
{
	// Store characters from file into array 1
	read(length);

	int keyCounter = 0;
    int curRow = 0;
    for (int i = 0; i < length; i++)
    {
        if (keyCounter == key)
        {
            curRow++;
            keyCounter = 0;
        }
        matrix[curRow][keyCounter] = inputData[i];
        keyCounter++;
    	
		}

	// Print encrypted message
	for (int column = 0; column < key; column++)
	{
		for (int row = 0; row <= curRow; row++)
		{
			if (!matrix[row][column])
			{
				continue;
			}
			
			printf("%c", matrix[row][column]);
		}
	}
}

void decrypt(int key, int length)
{
	// Store characters from encrypted file into array 1
	read(length);

	// Create a dummy matrix of the desired size
	int maxRows = (length / key);
	int modulo = length % key;
	if (modulo != 0)
	{
		maxRows++;
	}
	matrix[maxRows][key];
	int counter = 0;
	for (int row = 0; row < maxRows; row++)
	{
		for (int column = 0; column < key; column++)
		{
			if (counter == length)
			{
				break;
			}
			counter++;
			matrix[row][column] = 'z';
		}
	}
	counter = 0;
	for (int column = 0; column < key; column++)
	{
		for (int row = 0; row < maxRows; row++)
		{
			if (counter == length)
			{
				break;
			}
			if (!matrix[row][column])
			{
				continue;
			}
			matrix[row][column] = inputData[counter];
			counter++;
		}
	}
	// Print decrypted message
	for (int row=0; row < maxRows; row++)
    {
        for (int column=0; column < key; column++)
        {
            printf("%c", matrix[row][column]);
        }
    }
}

int main(int argc, char *argv[])
{

   // Check for correct number of arguments
   if (argc != 4)
	{
		errorMsg("ERROR: Invalid number of arguments.\n");
		return EXIT_FAILURE;
	}
	// Check switch
	int position = 0;
	while (argv[1][position] != 0)
	{
		if (position == 0 && argv[1][position] != '-')
		{
			errorMsg("ERROR: SWITCH must be either -e or -d.\n");
			return EXIT_FAILURE;
		}
		if (position == 1 && (argv[1][position] != 'e' && argv[1][position] != 'd'))
		{
			errorMsg("ERROR: SWITCH must be either -e or -d.\n");
			return EXIT_FAILURE;
		}
		if (position > 1)
		{
			errorMsg("ERROR: SWITCH must be either -e or -d.\n");
			return EXIT_FAILURE;
		}
		position++;
	}
	// Check length
	if (atoi(argv[3]) >= 500)
	{
		errorMsg("ERROR: LENGTH must be less than 500.\n");
		return EXIT_FAILURE;
	}
	if (atoi(argv[3]) <= 0)
	{
		errorMsg("ERROR: LENGTH must be greater than 0.\n");
		return EXIT_FAILURE;
	}
	// Check key
	if (atoi(argv[2]) >= atoi(argv[3]))
	{
		errorMsg("ERROR: KEY must be less than SWITCH.\n");
		return EXIT_FAILURE;
	}
	if (atoi(argv[2]) <= 0)
	{
		errorMsg("ERROR: KEY must be greater than 0.\n");
		return EXIT_FAILURE;
	}
	// Check encrypt or decrypt
	if (argv[1][1] == 'e') 
	{
		encrypt(atoi(argv[2]), atoi(argv[3]));
		return EXIT_SUCCESS;
	}
	if (argv[1][1] == 'd')
	{
		decrypt(atoi(argv[2]), atoi(argv[3]));
		return EXIT_SUCCESS;
	}
}
