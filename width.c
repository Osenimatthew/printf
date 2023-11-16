#include "main.h"

/*Function to get width*/
int in_getting_width(const char *format, int *i, va_list list)
{
	int curr_z;
	int width = 0;

	for (curr_z = *i + 1; format[curr_z] != '\0'; curr_z++)
	{
		if (is_digit(format[curr_z]))
		{
			width *= 10;
			width += format[curr_z] - '0';
		}
		else if (format[curr_z] == '*')
		{
			curr_z++;
			width = va_arg(list, int);
			break;
		}
		else
			break;
	}

	*i = curr_z - 1;

	return (width);
}
