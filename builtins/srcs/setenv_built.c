#include "ft_shell.h"

int setenv_built(int ac, char **av)
{
	if (ac > 3)
	{
		ft_error("42sh", av[0], NULL, "too many arguments");
		return (1);
	}
	if (ac == 1)
		ft_putdar(g_env.env);
	else
		ft_setenv(av[1], av[2], &g_env);
	return (0);
}