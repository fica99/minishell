/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 13:52:19 by aashara-          #+#    #+#             */
/*   Updated: 2019/07/01 20:37:53 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void signalling(void)
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
}

void signal_handler(int sign)
{
	if (sign == SIGINT || sign == SIGQUIT)
		ft_putchar_fd('\n', STDOUT_FILENO);
	if (sign == SIGWINCH)
	{
		reset_input_mode(&(g_line.savetty));
		get_win_size(g_line.cord);
		ft_putstr_fd(tigetstr("clear"), STDIN_FILENO);
		term_prompt();
		get_cur_cord(g_line.cord);
		set_start_cord(g_line.cord);
		g_line.cord->pos = 0;
		ft_putstr_cord(g_line.buffer.buffer, g_line.cord);
		set_input_mode(&(g_line.savetty));
	}
}
