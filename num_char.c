#include "main.h"

/************************* PRINT CHAR *************************/
int in_printing_char(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char x = va_arg(types, int);

	return (handle_write_char(x, buffer, flags, width, precision, size));
}

/************************* PRINT A STRING *************************/
int in_printing_string(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int length = 0, z;
	char *str = va_arg(types, char *);

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	if (str == NULL)
	{
		str = "(null)";
		if (precision >= 6)
			str = "      ";
	}

	while (str[length] != '\0')
		length++;

	if (precision >= 0 && precision < length)
		length = precision;

	if (width > length)
	{
		if (flags & F_MINUS)
		{
			write(1, &str[0], length);
			for (z = width - length; z > 0; z--)
				write(1, " ", 1);
			return (width);
		}
		else
		{
			for (z = width - length; z > 0; z--)
				write(1, " ", 1);
			write(1, &str[0], length);
			return (width);
		}
	}

	return (write(1, str, length));
}

/************************* PRINT PERCENT SIGN *************************/
int in_printing_percent(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	UNUSED(types);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	return (write(1, "%%", 1));
}

/************************* PRINT INT *************************/
int in_printing_int(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int z = BUFF_SIZE - 2;
	int is_negative = 0;
	long int n = va_arg(types, long int);
	unsigned long int num;

	n = convert_size_number(n, size);

	if (n == 0)
		buffer[z--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';
	num = (unsigned long int)n;

	if (n < 0)
	{
		num = (unsigned long int)((-1) * n);
		is_negative = 1;
	}

	while (num > 0)
	{
		buffer[z--] = (num % 10) + '0';
		num /= 10;
	}

	z++;

	return (write_number(is_negative, z, buffer, flags, width, precision, size));
}

/************************* PRINT BINARY *************************/
int in_printing_binary(va_list types, char buffer[],
int flags, int width, int precision, int size)
{
	unsigned int p, r, s, sum;
	unsigned int a[32];
	int count;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	p = va_arg(types, unsigned int);
	r = 2147483648; /* (2 ^ 31) */
	a[0] = p / r;
	for (s = 1; s < 32; s++)
	{
		r /= 2;
		a[s] = (p / r) % 2;
	}
	for (s = 0, sum = 0, count = 0; s < 32; s++)
	{
		sum += a[s];
		if (sum || s == 31)
		{
			char z = '0' + a[s];

			write(1, &z, 1);
			count++;
		}
	}
	return (count);
}
