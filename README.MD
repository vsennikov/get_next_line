# Get Next Line

This project provides a function `get_next_line` that reads a line from a file descriptor. It is designed to handle reading from a file efficiently, even when the file is large or the lines are of varying lengths.

## Usage

To use the `get_next_line` function, include the [`get_next_line.h`](get_next_line.h) header in your source file and link against the compiled object files of [`get_next_line.c`](get_next_line.c) and [`get_next_line_utils.c`](get_next_line_utils.c).

## Compilation

To compile the project, you can use the following command:

```sh
gcc -D BUFFER_SIZE=32 get_next_line.c get_next_line_utils.c your_file.c
```

You can modify the `BUFFER_SIZE` by changing the value in the `-D BUFFER_SIZE=32` flag to any desired buffer size.

Or you can use predefined buffer size

```sh
gcc get_next_line.c get_next_line_utils.c your_file.c
```

# Example

```c
#include "get_next_line.h"

int main(void)
{
	int fd;
	char *line;

	fd = open("file.txt", O_RDONLY);
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line);
		free(line);
	}
	close(fd);
	return (0);
}
```
