/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   k_history.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 20:16:36 by aashara-          #+#    #+#             */
/*   Updated: 2019/10/18 19:45:36 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_shell.h"


void	k_up(t_line *line)
{
	t_cord	*cord;

	if (g_line_flags & HISTORY_SEARCH)
		disable_history(line);
	if ((!line->history_index))
		return ;
	cord = line->cord;
	go_left(cord->pos, cord);
	ft_putstr_fd(CLEAR_END_SCREEN, STDIN_FILENO);
	if (line->history_index == g_history.hist_len)
	{
		check_malloc_len_buffer(&line->save_buff, line->buffer.buffer + cord->pos);
		ft_strcpy(line->save_buff.buffer, line->buffer.buffer + cord->pos);
	}
	--(line->history_index);
	check_malloc_len_buffer(&line->buffer,
	g_history.history_buff[line->history_index]);
	ft_strcpy(line->buffer.buffer + cord->pos,
	g_history.history_buff[(line->history_index)]);
	ft_putstr_cord(line->buffer.buffer + cord->pos, cord);
}

void	k_down(t_line *line)
{
	char	*history_buffer;
	t_cord	*cord;

	if (g_line_flags & HISTORY_SEARCH)
		disable_history(line);
	if (line->history_index == g_history.hist_len)
		return ;
	cord = line->cord;
	go_left(cord->pos, cord);
	ft_putstr_fd(CLEAR_END_SCREEN, STDIN_FILENO);
	++(line->history_index);
	if (line->history_index == g_history.hist_len)
		history_buffer = line->save_buff.buffer;
	else
		history_buffer = g_history.history_buff[(line->history_index)];
	check_malloc_len_buffer(&line->buffer, history_buffer);
	ft_strcpy(line->buffer.buffer + cord->pos, history_buffer);
	ft_putstr_cord(line->buffer.buffer + cord->pos, cord);
}

void	k_ctrl_r(t_line *line)
{
	t_cord	*cord;

	cord = line->cord;
	if (g_line_flags & HIGHLIGHT_TEXT)
		disable_highlight(line->buffer.buffer, cord);
	if (!g_history.hist_len)
		return ;
	ft_putstr_fd(SAVE_CUR, STDIN_FILENO);
	go_to_cord(cord->x_end, cord->y_end, STDIN_FILENO);
	ft_putchar_fd(NEW_LINE, STDIN_FILENO);
	if (cord->y_end >= cord->ws_row - 1)
	{
		--cord->y_cur;
		--cord->y_start;
		--cord->y_end;
	}
	ft_putstr_fd("bck-i-search: ", STDIN_FILENO);
	ft_putstr_fd(line->history_search.buffer, STDIN_FILENO);
	ft_putstr_fd(RESTORE_CUR, STDIN_FILENO);
	go_to_cord(cord->x_cur, cord->y_cur, STDIN_FILENO);
	g_line_flags |= HISTORY_SEARCH;
}
