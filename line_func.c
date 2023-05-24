#include "aushell.h"

/**
 * my_getline - Function to read input from a stream.
 * @ptr_line: Variable for double pointer to keep the input.
 * @num: Variable for size of lineptr.
 * @stream: The stream to read from.
 *
 * Return: The number of bytes read, or -1 on failure.
 */

ssize_t my_getline(char **ptr_line, size_t *num, FILE *stream)
{
	static ssize_t bytes_read;
	char ch = 'x', *buf;
	ssize_t exit_code;
	int buffer_size = 120, read_file;

	if (bytes_read == 0)
		fflush(stream);
	else
		return (-1);

	bytes_read = 0;
	buf = malloc(sizeof(char) * buffer_size);
	if (!buf)
		return (-1);

	while (ch != '\n')
	{
		read_file = read(STDIN_FILENO, &ch, 1);
		if (read_file == -1 || (read_file == 0 && bytes_read == 0))
		{
			free(buf);
			return (-1);
		}
		if (read_file == 0 && bytes_read != 0)
		{
			bytes_read++;
			break;
		}

		if (bytes_read >= buffer_size)
			buf = my_realloc(buf, bytes_read, bytes_read + 1);

		buf[bytes_read++] = ch;
	}
	buf[bytes_read] = '\0';

	assign_ptr(ptr_line, num, buf, bytes_read);
	exit_code = bytes_read;
	if (read_file != 0)
		bytes_read = 0;
	return (exit_code);
}

/**
 * assign_ptr - Function to reassigns variable for my_getline.
 * @ptr_line: variable for buffer to store string.
 * @num: variable size of ptr.
 * @buf: variable string to assign to ptr.
 * @buffer_size: The size of buffer.
 */
void assign_ptr(char **ptr_line, size_t *num, char *buf, size_t buffer_size)
{
	if (*ptr_line == NULL)
	{
		if (buffer_size > 120)
			*num = buffer_size;
		else
			*num = 120;
		*ptr_line = buf;
	}
	else if (*num < buffer_size)
	{
		if (buffer_size > 120)
			*num = buffer_size;
		else
			*num = 120;

		*ptr_line = buf;
	}
	else
	{
		str_cpy(*ptr_line, buf);
		free(buf);
	}
}


/**
 * my_realloc - Function to reallocate memory block using malloc and free.
 * @prev_mem: Variable for pointer for previusly allocated memory.
 * @old_byte: Variable for size for the allocated space for prev_mem.
 * @new_byte: Variable for size for the new memory in byte.
 *
 * Return: void type
 */
void *my_realloc(void *prev_mem, unsigned int old_byte, unsigned int new_byte)
{
	void *new_ptr;
	unsigned int i;
	char *src, *dest;

	if (new_byte == old_byte)
		return (prev_mem);

	if (prev_mem == NULL)
	{
		new_ptr = malloc(new_byte);
		if (new_ptr == NULL)
			return (NULL);

		return (new_ptr);
	}

	if (new_byte == 0 && prev_mem != NULL)
	{
		free(prev_mem);
		return (NULL);
	}

	src = prev_mem;
	new_ptr = malloc(sizeof(*src) * new_byte);

	if (new_ptr == NULL)
	{
		free(prev_mem);
		return (NULL);
	}

	dest = new_ptr;

	for (i = 0; i < old_byte && i < new_byte; i++)
		dest[i] = *src++;

	free(prev_mem);
	return (new_ptr);
}
