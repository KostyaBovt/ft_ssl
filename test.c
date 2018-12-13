#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void print_bits(unsigned int x)
{
	int i;

	i = (sizeof(int) * 8) - 1;
	while (i >= 0)
	{
		if (x & (16777216u << i)) {
			write(1, "1", 1);
		} 
		else
		{
			write(1, "0", 1);
		}
		i--;
	}
}


void print_byte(unsigned char c)
{
	int i;
	unsigned char shift;

	i = 7;
	shift = 1;
	while (i >= 0)
	{
		(c & (shift << i)) ? write(1, "1", 1) : write(1, "0", 1);
		i--;
	}

}

void print_memory(void *ptr, int length)
{
	int i;
	unsigned char c;
	unsigned char *p;

	p = (unsigned char*)ptr;
	i = 0;
	while (i < length)
	{
		c = p[i];
		print_byte(c);
		write(1, " | ", 3);
		i++;
	}
	write(1, "\n", 1);
}

int main(void)
{
	char **commands;

	commands[0] = "md5";
	commands[1] = "sha256";
	commands[2] = NULL;
	write(1, commands[0], 4);
	return 0;
}
