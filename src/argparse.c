#include <stdlib.h>
#include <string.h>
#include "argparse.h"

void _updateScreenWidth(char *argument, int *screenWidth)
{
	*screenWidth = atoi(argument);
}

void _updateScreenHeight(char *argument, int *screenHeight)
{
	*screenHeight = atoi(argument);
}
/**
 * parseArgs - Parse command line arguments for screen dimensions  
 * @argc: Number of arguments
 * @argv: Argument strings
 * @screenWidth: Pointer to screen width value
 * @screenHeight: Pointer to screen height value
 */
void parseArgs(int argc, char *argv[], int *screenWidth, int *screenHeight)
{
	if (argc < 1)
		return;

	for (int i = 1; i < argc; i++) {
		char *value = argv[i + 1];

		const int isWidthArg = strcmp(argv[i], "--width") == 0 &&
				       i + 1 < argc;
		const int isHeightArg = strcmp(argv[i], "--height") == 0 &&
					i + 1 < argc;

		if (isWidthArg)
			_updateScreenWidth(value, screenWidth);
		else if (isHeightArg)
			_updateScreenHeight(value, screenHeight);
	}
}