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


static	int		gdel(int n)
{
	int	del;

	del = 1;
	while (n / 10)
	{
		n = n / 10;
		del = del * 10;
	}
	return (del);
}

static	int		mod(int n)
{
	if (n >= 0)
		return (n);
	return (-n);
}

static	void	putch(char c)
{
	write(1, &c, 1);
}

void			ft_putnbr(int n)
{
	int		del;

	del = gdel(n);
	if (n < 0)
		putch('-');
	while (del)
	{
		putch((char)(mod((n / del) % 10) + (int)'0'));
		del /= 10;
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
		ft_putnbr(i);
		write(1, "\n", 1);
		i++;
	}
	write(1, "\n", 1);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char		*dst1;
	char		*src1;
	size_t		i;

	dst1 = (char*)dst;
	src1 = (char*)src;
	i = 0;
	while (i < n)
	{
		dst1[i] = src1[i];
		i++;
	}
	return (dst);
}

void	*ft_bzero(void *s, size_t n)
{
	size_t	i;
	char	*b2;

	b2 = (char*)s;
	i = 0;
	while (i < n)
	{
		b2[i] = '\0';
		i++;
	}
	return ((void*)b2);
}


int main(void)
{
	void *void_v;
	void_v = (void*)malloc(64);
	ft_bzero(void_v, 64);

	unsigned long long int n;
	n = 255;

	ft_memcpy(&void_v[56], &n, sizeof(n));

	print_memory(void_v, 64);
	write(1, "\n\n", 2);
	print_memory(&n, sizeof(n));
	return 0;
}
