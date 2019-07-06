/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsetenv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 19:55:51 by aashara-          #+#    #+#             */
/*   Updated: 2019/07/05 19:07:53 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void	ft_unsetenv(int argc, char **argv, char **env_cp)
{
	short	i;
	short	j;
	char	**envp;

	(void)env_cp;
	if (argc < 2)
		print_error_withoutexit("unsetenv", NULL, "not enough arguments", 0);
	else
	{
		j = 0;
		while (argv[++j])
		{
			if ((i = get_count_var(argv[j])) < 0)
				continue;
			envp = copy_new_arr(i);
			free(g_env);
			g_env = envp;
			if (!ft_strcmp(argv[j], "PATH"))
				g_flags |= TERM_FREE_HASH;
		}
	}
}

char	**copy_new_arr(short i)
{
	char	**envp;
	short	j;

	if (!(envp = (char**)malloc(sizeof(char *)
					* (ft_darlen(g_env)))))
		print_error("unsetenv", "malloc() error", NULL, ENOMEM);
	j = -1;
	while (g_env[++j])
	{
		if (j >= i)
		{
			if (j == i)
				ft_memdel((void**)&(g_env[j]));
			envp[j] = g_env[j + 1];
		}
		else
			envp[j] = g_env[j];
	}
	return (envp);
}