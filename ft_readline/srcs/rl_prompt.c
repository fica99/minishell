/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 12:36:19 by filip             #+#    #+#             */
/*   Updated: 2019/11/05 19:36:21 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

void	rl_write_prompt(char *str, char **env, t_rl_history history)
{
	short	i;
	short	j;

	i = -1;
	while (str[++i])
	{
		j = i;
		if (str[i] == '\\')
		{
			if ((j = rl_prompt_user_host(str, i, env)) == i)
				if ((j = rl_prompt_dir_history(str, i, history, env)) == i)
					if ((j = rl_prompt_colour_name(str, i)) == i)
						j = rl_prompt_time(str, i);
		}
		if (j == i)
			ft_putchar(str[i]);
		else
			i = j;
	}
}

short	rl_prompt_user_host(char *str, short i, char **env)
{
	char	hostname[FT_HOST_NAME_MAX];
	char	*stop;
	char	*path;

	if (!ft_strncmp(str + i, "\\u", 2))
		ft_putstr(ft_getenv("USER", env));
	else if (!ft_strncmp(str + i, "\\h", 2) ||
	!ft_strncmp(str + i, "\\H", 2))
	{
		gethostname(hostname, FT_HOST_NAME_MAX);
		if (!ft_strncmp(str + i, "\\h", 2) &&
		(stop = ft_strchr(hostname, '.')))
			*stop = '\0';
		ft_putstr(hostname);
	}
	else if (!ft_strncmp(str + i, "\\$", 2))
	{
		path = ft_getenv("USER", env);
		(path && !ft_strcmp(path, "root")) ?
		ft_putchar('#') : ft_putchar('$');
	}
	else
		--i;
	return (++i);
}

short	rl_prompt_dir_history(char *str, short i,
t_rl_history history, char **env)
{
	char	*pwd;
	char	*home;

	pwd = ft_getenv("PWD", env);
	if (!ft_strncmp(str + i, "\\W", 2))
	{
		if (!ft_strncmp(str + i, "\\W", 2) && pwd)
			ft_putstr((ft_strlen(pwd) == 1) ? pwd : ft_strrchr(pwd, '/') + 1);
	}
	else if (!ft_strncmp(str + i, "\\w", 2))
	{
		if (ft_strstr(pwd, (home = ft_getenv("HOME", env))))
			ft_putstr("~");
		else
			home = NULL;
		ft_putstr(pwd + ft_strlen(home));
	}
	else if (!ft_strncmp(str + i, "\\!", 2))
		ft_putnbr(history.hist_len);
	else if (!ft_strncmp(str + i, "\\#", 2))
		ft_putnbr(history.cur_command_nb);
	else
		--i;
	return (++i);
}

short	rl_prompt_colour_name(char *str, short i)
{
	char	colour[LINE_MAX];
	short	j;

	if (!ft_strncmp(str, "\\e", 2))
	{
		j = 1;
		colour[0] = '\033';
		while (*(str + i + j + 1) && *(str + i + j + 1) != 'm')
		{
			colour[j] = *(str + i + j + 1);
			j++;
		}
		colour[j] = '\0';
		ft_putstr(colour);
		i += j;
	}
	else if (!ft_strncmp(str + i, "\\s", 2))
	{
		ft_putstr("42sh");
		++i;
	}
	return (i);
}
