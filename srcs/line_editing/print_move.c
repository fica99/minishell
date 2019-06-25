/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_move.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 23:29:29 by filip             #+#    #+#             */
/*   Updated: 2019/06/25 20:24:47 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void		go_to_cord(short x, short y, int fd)
{
	char	*cursor;

	cursor = tigetstr("cup");
	ft_putstr_fd(tparm(cursor, y, x), fd);
}

void	go_left(short i, t_cord *cord)
{
	short	len;

	if (i <= 0)
		return ;
	len = cord->x_cur - cord->x_start + ((cord->y_cur - cord->y_start)
			* cord->ws_col);
	if (i > len)
		i = len;
	cord->pos -= i;
	cord->x_cur -= i;
	while (cord->x_cur < 0)
	{
		cord->x_cur += cord->ws_col;
		cord->y_cur--;
	}
	go_to_cord(cord->x_cur, cord->y_cur, STDIN_FILENO);
}

void	go_right(short i, t_cord *cord)
{
	if (i <= 0)
		return ;
	cord->pos += i;
	cord->x_cur += i;
	while (cord->x_cur >= cord->ws_col)
	{
		cord->x_cur -= cord->ws_col;
		cord->y_cur++;
	}
	go_to_cord(cord->x_cur, cord->y_cur, STDIN_FILENO);
}

void	prev_word(char *buf, t_cord *cord)
{
	short	i;

	i = cord->pos;
	while (--i >= 0)
	{
		if ((i == 0 || buf[i - 1] == ' ') &&
		(ft_isalpha(buf[i]) || ft_isdigit(buf[i])))
		{
			go_left(cord->pos - i, cord);
			break ;
		}
	}
}

void	next_word(char *buf, t_cord *cord)
{
	short	i;
	char	flag;

	i = 0;
	flag = 0;
	while (buf[i])
	{
		if (buf[i] == ' ')
			flag = 1;
		if ((ft_isalpha(buf[i]) || ft_isdigit(buf[i])) && flag)
			break ;
		i++;
	}
	go_right(i, cord);
}
