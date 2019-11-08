/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_k_highlight.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 17:35:44 by aashara-          #+#    #+#             */
/*   Updated: 2019/11/08 18:34:56 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

void	rl_k_shift_left(t_readline *rl)
{
	short		start;
	short		end;

	if (g_rl_flags & RL_HISTORY_SEARCH_FLAG)
		rl_disable_line(rl);
	if (rl_is_start_pos(rl->cord))
		return ;
	if (!(g_rl_flags & RL_HIGHLIGHT_FLAG))
		rl->cord.highlight_pos = rl->cord.pos;
	start = rl->cord.pos - 1;
	end = rl->cord.highlight_pos;
	if (end < start)
	{
		start = end;
		end = rl->cord.pos - 1;
	}
	rl_print_highlight(rl->line.buffer, start, end, rl->cord);
	rl_go_left(1, &rl->cord);
}

void	rl_k_shift_right(t_readline *rl)
{
	short	start;
	short	end;

	if (g_rl_flags & RL_HISTORY_SEARCH_FLAG)
		rl_disable_line(rl);
	if (rl_is_end_pos(rl->cord))
		return ;
	if (!(g_rl_flags & RL_HIGHLIGHT_FLAG))
		rl->cord.highlight_pos = rl->cord.pos;
	start = rl->cord.highlight_pos;
	end = rl->cord.pos + 1;
	if (end < start)
	{
		end = start;
		start = rl->cord.pos + 1;
	}
	rl_print_highlight(rl->line.buffer, start, end, rl->cord);
	rl_go_right(1, &rl->cord);
}

void	rl_k_ctrl_c(t_readline *rl)
{
	short	start;
	short	end;

	if (!(g_rl_flags & RL_HIGHLIGHT_FLAG))
	{
		ft_strclr(rl->line.buffer);
		rl_k_enter(rl);
	}
	else
	{
		start = rl->cord.pos;
		end = rl->cord.highlight_pos;
		if (end < start)
		{
			start = end;
			end = rl->cord.pos;
		}
		while (end - start >= rl->copy_buff.malloc_len)
			rl->copy_buff.buffer = ft_strdup_realloc(rl->copy_buff.buffer,
			rl->copy_buff.malloc_len += MAX_LINE_SIZE);
		ft_strncpy(rl->copy_buff.buffer, rl->line.buffer + start, end - start);
	}
}

void	rl_k_ctrl_x(t_readline *rl)
{
	short	start;
	short	end;
	short	j;

	if (!(g_rl_flags & RL_HIGHLIGHT_FLAG))
		return ;
	rl_k_ctrl_c(rl);
	start = rl->cord.highlight_pos;
	end = rl->cord.pos;
	j = start;
	rl_go_left(end - start, &rl->cord);
	if (end < start)
	{
		start = end;
		end = j;
		j = start;
	}
	while (++j <= end)
		rl->line.buffer = ft_strdel_el(rl->line.buffer, start);
	ft_putstr(RL_CLEAR_END_SCREEN);
	rl_disable_line(rl);
}

void	rl_k_ctrl_v(t_readline *rl)
{
	short	pos;

	if (g_rl_flags & RL_HISTORY_SEARCH_FLAG)
		rl_disable_line(rl);
	if (!(*rl->save_line.buffer))
		return ;
	pos = rl->cord.pos;
	rl_malloc_len(&rl->line, rl->copy_buff.buffer);
	rl->line.buffer = ft_stradd(rl->line.buffer, rl->copy_buff.buffer, pos);
	rl_disable_line(rl);
	rl_go_right(ft_strlen(rl->copy_buff.buffer), &rl->cord);
}
