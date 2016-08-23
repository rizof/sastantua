#include <unistd.h>
#include <stdio.h>

int		ft_atoi(char *size)
{
	int nb;
	int i;

	nb = 0;
	i = 0;
	while (size[i] == '\t' || size[i] == '\v' || size[i] == '\r'
		|| size[i] == '\f' || size[i] == '\n' || size[i] == ' ')
		i++;
	if (size[i] == '+')
		i++;
	if (size[i] >= 'a' && size[i] <= 'z' && size[i] >= 'A' && size[i] <= 'Z')
		return (0);
	while (size[i] >= '0' && size[i] <= '9')
	{
		nb = nb * 10;
		nb = nb + size[i] - '0';
		i++;
	}
	return (nb);
}

void 	put_space(int etoile, int size, int etage, int size2, int indent)
{	
	int width;

	etage = 1;
	width = 1;
	indent = 4;
	while (etage <= size2)
	{
		width += 2 * (2 + etage);
		etage++;
		width += indent;
		if (etage % 2 && etage < size2)
			indent += 2;
	}
	width -= indent;
	etage = 0;
	while (size-- != 3)
		etage++;
	width = (width - etoile) / 2;
	width -= 1;
	while (width--)
		write(1, " ", 1);
}

void	put_etoile(int etoile, int size, int etage, int etoile2, int boule)
{	
	write(1, "/", 1);
	if (etage > 0 || boule < 2)
		while (etoile--)
			write(1, "*", 1);
	if (etage == 0 && boule > 1)
	{
		etoile = etoile / 2;
		etoile -= size / 2 - (+1);
		etoile2 = etoile;
		while (etoile--)
			write(1, "*", 1);
		if (size % 2 == 0)
			etoile2 += 1;
		etage = size - 2;
		while (etage--)
			if ((etage - 1 == 0 && boule == size / 2 && size > 6 && size % 2 == 0)
				|| (etage - 1 == 0 && boule == size / 2 + 1 && size > 6))
				write(1, "$", 1);
			else
				write(1, "|", 1);
		while (etoile2--)
			write(1, "*", 1);
	}
}

int 	calsize(int etage, int size, int etoile, int size2, int boole)
{
	if (boole < size)
	{
		put_space(etoile, size, etage, size2, boole);
		put_etoile(etoile, size, etage, size2, boole);
		write(1, "\\", 1);
		write(1, "\n", 1);
		return (calsize(etage, size, etoile += 2, size2, boole += 1));
	}
	return (etoile);
	// if (size > 4 && size % 2 == 1)
	// 	indent += 2;
	// if (etage > 1)
	// 	return (calsize(etage -= 1, size += 1, etoile += indent, indent, boole = 0));
}

void 	sastantua(int size)
{
	int etage;
	int etoile;
	int indent;
	int boole;
	int size2;

	size2 = size;
	boole = 0;
	etage = 3;
	indent = 4;
	etoile = 1;
	if (size == 0)
		return ;
	else
	{
		while (size--)
		{
			etoile = calsize(size, etage, etoile, size2, boole);
			if (etage > 4 && etage % 2 == 1)
				indent += 2;
			etoile += indent;
			etage += 1;
		}
	}
}

int		main(int argc, char **argv)
{
	int etage;

	if (argc > 1)
	{
		etage = ft_atoi(argv[1]);
		sastantua(etage);
	}
	return (0);
}