/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   k_print.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 16:54:59 by aashara-          #+#    #+#             */
/*   Updated: 2019/10/18 19:45:36 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_shell.h"

void	k_ctrl_d(t_line *line)
{
	char	*buf;

	buf = line->buffer.buffer;
	if (g_line_flags & HIGHLIGHT_TEXT)
		disable_highlight(buf, line->cord);
	if (g_line_flags & HISTORY_SEARCH)
		disable_history(line);
	if (is_end_pos(line->cord))
	{
		if (*buf == '\0')
		{
			ft_strcpy(buf, "exit");
			ft_putstr_cord(buf, line->cord);
		}
		k_enter(line);
	}
	else
		k_del(line);
}

void	k_enter(t_line *line)
{
	t_cord	*cord;

	if (g_line_flags & HIGHLIGHT_TEXT)
		disable_highlight(line->buffer.buffer, line->cord);
	if (g_line_flags & HISTORY_SEARCH)
		disable_history(line);
	cord = line->cord;
	go_right(cord->x_end - cord->x_cur + ((cord->y_end - cord->y_cur) *
	cord->ws_col), cord);
	if (cord->y_end >= cord->ws_row - 1)
	{
		--cord->y_cur;
		--cord->y_start;
		--cord->y_end;
	}
	ft_putstr_fd(CLEAR_END_SCREEN, STDIN_FILENO);
	ft_putchar_fd(NEW_LINE, STDIN_FILENO);
	g_flags |= BREAK_FLAG;
}

void	k_bcsp(t_line *line)
{
	t_cord	*cord;

	cord = line->cord;
	if (g_line_flags & HIGHLIGHT_TEXT)
		disable_highlight(line->buffer.buffer, cord);
	if (is_start_pos(cord))
		return ;
	go_left(1, cord);
	del_symb(line->buffer.buffer, cord);
}

void	k_del(t_line *line)
{
	t_cord	*cord;

	cord = line->cord;
	if (g_line_flags & HIGHLIGHT_TEXT)
		disable_highlight(line->buffer.buffer, cord);
	if (g_line_flags & HISTORY_SEARCH)
		disable_history(line);
	if (is_end_pos(cord))
		return ;
	del_symb(line->buffer.buffer, cord);
}
