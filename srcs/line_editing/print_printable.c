/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_printable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 23:27:46 by filip             #+#    #+#             */
/*   Updated: 2019/07/01 20:36:01 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void	del_symb(char *buf, t_cord *cord)
{
	short	pos;

	buf = ft_strdel_el(buf, cord->pos);
	pos = cord->pos;
	ft_putstr_fd(tigetstr("ed"), STDIN_FILENO);
	ft_putstr_cord(buf + cord->pos, cord);
	go_left(cord->pos - pos, cord);
}


void		print_symb(char *c, char *buf, t_cord *cord)
{
	short	pos;

	buf = ft_stradd(buf, c, cord->pos);
	if (*c == '\n')
	{
		cord->pos++;
		return ;
	}
	pos = cord->pos;
	ft_putstr_fd(tigetstr("ed"), STDIN_FILENO);
	ft_putstr_cord(buf + cord->pos, cord);
	go_left(cord->pos - pos - ft_strlen(c), cord);
}

void		ft_putstr_cord(char *str, t_cord *cord)
{
	t_cord	*new_line;

	new_line = cord->nl;
	free_cord(&(new_line));
	while (str && *str)
	{
		ft_putchar_fd(*str, STDIN_FILENO);
		if (*str == '\n')
		{
			while (new_line)
				new_line = new_line->nl;
			new_line = init_cord();
			new_line->x_cur = cord->x_cur;
			new_line->y_cur = cord->y_cur - cord->y_start;
			cord->x_cur = 0;
			check_end_window(cord);
		}
		else
			(cord->x_cur)++;
		if (cord->x_cur >= cord->ws_col)
		{
			ft_putchar_fd('\n', STDIN_FILENO);
			cord->x_cur = 0;
			check_end_window(cord);
		}
		str++;
		cord->pos++;
	}
}
