/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 21:53:57 by aashara-          #+#    #+#             */
/*   Updated: 2019/10/02 15:25:33 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

char	*read_prompt(void)
{
	char	*buff;

	buff = NULL;
	set_input_mode(&g_raw_mode);
	set_line(&g_line);
	reading(&g_line);
	if (*g_line.buffer.buffer)
	{
		if (!(buff = ft_strdup(g_line.buffer.buffer)))
			err_exit(g_argv[0], "malloc() error", NULL, ENOMEM);
		add_to_history_buff(buff, &g_history);
	}
	set_attr(&g_orig_mode);
	return (buff);
}

void		reading(t_line *line)
{
	char	c[LINE_MAX + 1];
	t_cord	*cord;

	while (READING)
	{
		read_handler(c, STDIN_FILENO);
		check_malloc_len_buffer(&(line->buffer), c);
		find_templ(c, line);
		if (g_flags & BREAK_FLAG)
			break ;
	}
	cord = line->cord;
	go_right(cord->x_end - cord->x_cur + ((cord->y_end - cord->y_cur) *
	cord->ws_col), cord);
	ft_putstr_fd(CLEAR_END_SCREEN, STDIN_FILENO);
	ft_putchar_fd(NEW_LINE, STDIN_FILENO);
}

void		read_handler(char *c, int fd)
{
	short	nb;

	ft_putstr_fd(TRANSMIT_MODE, STDIN_FILENO);
	if ((nb = read(fd, c, LINE_MAX)) < 0)
	{
		ft_putstr_fd(STOP_TRANSMIT_MODE, STDIN_FILENO);
		err_exit(g_argv[0], "read() error", NULL, NOERROR);
	}
	c[nb] = '\0';
	ft_putstr_fd(STOP_TRANSMIT_MODE, STDIN_FILENO);
}