#include <unistd.h>
#include <stdio.h>

int		ft_atoi(char *size)
{
	int nb;
	int i;

	nb = 0;
	i = 0;
	while (size[i] == '\t' || size[i] == '\v' || size[i] == '\r' || size[i] == '\f' || size[i] == '\n' || size[i] == ' ')
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

void 	put_pyramide(int etoile, int size, int etage, int space, int boule)
{			
	if (boule < size)
		return (put_pyramide(etoile, size, etage, space += 2, boule += 1));
	space -= 2;
	if (etage > 0)
		return (put_pyramide(etoile, size += 1, etage -= 1, space += 6, boule = 0));
	space -= 6;
	etoile += 1;
	space = space / 2 - size + 2;
	if (space >= 1)
	{
		while (--space)
			write(1, " ", 1);
	}
	if (etoile >= 0)
	{
		write(1, "/", 1);
		while (--etoile)
			write(1, "*", 1);
	}
}

void	door(int etoile, int size, int door, int space, int boule)
{
	if (boule < 2)
		put_pyramide(etoile, size, door, space, boule);
	if (boule > 1)
	{
		etoile = etoile / 2;
		etoile -= door - 1;
		put_pyramide(etoile, size, door, space, boule);
		door = size - 2;
		etoile -= size - 4;
		while (door)
		{
			if (door - 2 == 0 && boule == size / 2 && size > 6 && size % 2 == 0)
				write(1, "$", 1);
			else if (door - 2 == 0 && boule == size / 2 + 1 && size > 6)
				write(1, "$", 1);
			else
				write(1,"|", 1);
			door--;
		}
		while (--etoile)
			write(1, "*", 1);
	}
}

void 	sastantua1(int etage, int size, int etoile, int space, int boule)
{
	if (etage == 0)
		size = 0;
	if (boule < size && etage > 1)
	{
		put_pyramide(etoile, size, etage, space, boule);
		write(1, "\\", 1);
		write(1, "\n", 1);
		return (sastantua1(etage, size, etoile += 2, space, boule += 1));
	}
	else if (boule < size && etage == 1)
	{
		door(etoile, size, etage, space, boule);
		write(1, "\\", 1);
		write(1, "\n", 1);
		return (sastantua1(etage, size, etoile += 2, space, boule += 1));
	}
	etoile -= 2;
	if (etage > 0)
		return (sastantua1(etage -= 1, size += 1, etoile += 6, space, boule = 0));
}

void 	sastantua(int size)
{
	int etage;
	int etoile;
	int space;
	int boole;

	boole = 0;
	etage = 3;
	space = 1;
	etoile = 1;

	sastantua1(size, etage, etoile, space, boole);
}

int		main(int argc, char **argv)
{
	int etage;

	if (argc > 1)
	{
		etage = ft_atoi(argv[1]);
		sastantua(etage);
	}
	return 0;
}