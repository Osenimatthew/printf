#include "main.h"

/**
 * handle_print - Processes and prints an argument based on its type
 * @fmt: Formatted string containing the arguments to be printed
 * @ind: Index in the format string
 * @list: List of arguments to be printed
 * @buffer: Buffer array to handle print
 * @flags: Active formatting flags
 * @width: Width specification
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of characters printed or -1 if unknown
 */
int handle_print(const char *fmt, int *ind, va_list list, char buffer[],
	int flags, int width, int precision, int size)
{
	int i, unknow_len = 0, printed_chars = -1;
	fmt_t fmt_types[] = {
		{'c', in_printing_char}, {'s', in_printing_string}, {'%', in_printing_percent},
		{'i', in_printing_int}, {'d', in_printing_int}, {'b', in_printing_binary},
		{'u', in_printing_unsigned}, {'o', in_printing_octal}, {'x', in_printing_hexadecimal},
		{'X', in_printing_hexa_upper}, {'p', in_printing_pointer}, {'S', in_printing_non_printable},
		{'r', in_printing_reverse}, {'R', in_printing_rot13string}, {'\0', NULL}
	};
	for (i = 0; fmt_types[i].fmt != '\0'; i++)
		if (fmt[*ind] == fmt_types[i].fmt)
			return (fmt_types[i].fn(list, buffer, flags, width, precision, size));

	if (fmt_types[i].fmt == '\0')
	{
		if (fmt[*ind] == '\0')
			return (-1);
		unknow_len += write(1, "%%", 1);
		if (fmt[*ind - 1] == ' ')
			unknow_len += write(1, " ", 1);
		else if (width)
		{
			--(*ind);
			while (fmt[*ind] != ' ' && fmt[*ind] != '%')
				--(*ind);
			if (fmt[*ind] == ' ')
				--(*ind);
			return (1);
		}
		unknow_len += write(1, &fmt[*ind], 1);
		return (unknow_len);
	}
	return (printed_chars);
}
