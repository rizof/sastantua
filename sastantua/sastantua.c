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
		return(0);
	while (size[i] >= '0' && size[i] <= '9')
	{
		nb = nb * 10;
		nb = nb + size[i] - '0';
		i++;
	}
	return (nb);
}

void 	put_pyramide(int etoile)
{
	if(etoile >= 1 )
	{
		write(1, "/", 1);		
		while (etoile)
		{	
			write(1, "*", 1);
			etoile--;
		}
	write(1, "\\", 1);
	}
}

void	door(int etoile, int size, int boule, int door,int tmp)
{
	if (boule < 2)
		put_pyramide(etoile);
	if (0 == etoile - 1)
		write(1, "/", 1);
	if (!(etoile = etoile / 2))
	{
		write(1, "*", 1);
		return (door(etoile--, size, boule, door, tmp));
	}
	if (tmp > 0)
		return (door(etoile, size, boule, door--, tmp));
}

void 	sastantua(int etage, int size, int etoile, int indent, int boule)
{
	if(etage == 0)
		size = 0;
	if (boule < size && etage != 1 )
	{
		put_pyramide(etoile);
		write(1,"\n",1);
		return (sastantua(etage, size, etoile += 2, indent, boule += 1));
	}
	else if (boule < size && etage == 1)
	{
		door(etoile, size = size - 2, boule, etage = etoile / 2,indent);
				write(1,"\n",1);
		return (sastantua(etage, size, etoile += 2, indent, boule += 1));
	}
	indent++;
	etoile -= 2;
	boule = 0;
	if (indent % 3 == 0)
		etoile += 2;
	if (indent % 3 == 0 || indent >= 3)
		etoile += 4;
	if (etage > 2)
		return (sastantua(etage -= 1, size += 1, etoile += 6, indent, boule));
	 else if (etage == 2)
		return (sastantua(etage -= 1, size += 1, etoile +=6 , indent, boule));
}

int		main(int argc, char **argv)
{
	int size;
	int etage;
	int etoile;
	int indent;
	int boole;

	boole = 0;
	size = 3;
	indent = 0;
	etoile = 1;
	if (argc > 1)
	{
		etage = ft_atoi(argv[1]);
		sastantua(etage, size, etoile, indent, boole);
	}
	return 0;
}