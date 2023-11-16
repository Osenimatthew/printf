#include "main.h"

/*Function to get flags*/
int in_getting_flags(const char *format, int *i)
{
	/* - + 0 # ' ' */
	/* 1 2 4 8  16 */
	int g, curr_h;
	int flags = 0;
	const char FLAGS_CH[] = {'-', '+', '0', '#', ' ', '\0'};
	const int FLAGS_ARR[] = {F_MINUS, F_PLUS, F_ZERO, F_HASH, F_SPACE, 0};

	for (curr_h = *i + 1; format[curr_h] != '\0'; curr_h++)
	{
		for (g = 0; FLAGS_CH[g] != '\0'; g++)
			if (format[curr_h] == FLAGS_CH[g])
			{
				flags |= FLAGS_ARR[g];
				break;
			}

		if (FLAGS_CH[g] == 0)
			break;
	}

	*i = curr_h - 1;

	return (flags);
}
