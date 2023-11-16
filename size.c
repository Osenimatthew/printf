#include "main.h"

/*Function to get size*/
int in_getting_size(const char *format, int *i)
{
	int curr_y = *i + 1;
	int size = 0;

	if (format[curr_y] == 'l')
		size = S_LONG;
	else if (format[curr_y] == 'h')
		size = S_SHORT;

	if (size == 0)
		*i = curr_y - 1;
	else
		*i = curr_y;

	return (size);
}
