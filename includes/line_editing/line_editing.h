/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_editing.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 11:20:50 by filip             #+#    #+#             */
/*   Updated: 2019/09/01 17:23:48 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LINE_EDITING_H
# define LINE_EDITING_H

# include <stdlib.h>

# define HEREDOC_FLAG (1 << 1)
# define HISTORY_SEARCH (1 << 2)
# define TERM_HIGHLIGHT (1 << 3)
# define START_POS (1 << 4)
# define TERM_QUOTES (1 << 5)
# define TERM_NL (1 << 6)
# define BREAK_FLAG (1 << 7)
# define NEW_LINE '\n'
typedef struct		s_cord
{
	short			x_start;
	short			y_start;
	short			x_cur;
	short			y_cur;
	short			ws_col;
	short			ws_row;
	short			highlight_pos;
	short			pos;
	struct s_cord	*nl;
}					t_cord;

typedef struct		s_buff
{
	char			*buffer;
	short			malloc_len;
}					t_buff;

typedef struct		s_line
{
	t_buff			buffer;
	t_buff			history_search;
	t_buff			save_buff;
	t_buff			copy_buff;
	t_buff			stop_buff;
	t_cord			*cord;
	t_history		history;
}					t_line;

unsigned char	g_line_flags;

char	*check_heredoc(t_buff buffer, t_buff *stop_buff, t_cord *cord);
short	find_heredoc(char *buffer);
void	print_heredoc(char *buffer, t_cord *cord);
void	check_heredoc_end(char *buffer, char *stop_buff, t_cord *cord);
void	check_new_line(t_line *line, char *c);
void	check_quotes(t_line *line);
char	*quotes_dquotes_brackets(short q, short dq, short br, t_line *line);
void	print_quotes(short q, short dq, short br, t_line *line);
t_cord	*init_cord(void);
void	get_win_size(t_cord *cord);
void	get_cur_cord(t_cord *cord);
void	set_start_cord(t_cord *cord);
void	init_buff(t_buff *buffer);
void	check_malloc_len_buffer(t_buff *buffer, char *c);
void	init_line(t_line *line, t_term *term);
void	free_line(t_line *line, t_term *term);
void	go_left(short i, t_cord *cord);
void	check_nl_left(t_cord *cord, short i);
void	go_to_cord(short x, short y, int fd);
void	go_right(short i, t_cord *cord);
void	check_nl_right(t_cord *cord, short i);
char	*print_symbols(char *c, t_line *line);
char	*cut_copy_paste(char *c, t_line *line);
void	highlight_left(char *buffer, t_cord *cord);
void	ft_putstr_highlight(char *str, short start, short end, t_cord *cord);
void	highlight_right(char *buffer, t_cord *cord);
short	is_start_pos(t_cord *cord);
void	unset_start_pos(t_cord	*cord);
void	free_cord(t_cord **cord);
void	copy_highlight(t_buff *copy_buff, t_buff *buffer, t_cord *cord);
char	*cut_copy_paste(char *c, t_line *line);
void	ft_putstr_cord(char *str, t_cord *cord);
void	check_end_window(t_cord *cord);
void	paste_highlight(t_buff *buffer, t_buff *copy_buff, t_cord *cord);
void	go_history(char *c, t_line *line);
void	history_up(t_line *line, short len);
void	history_down(t_line *line, short len);
void	find_history(char *symbol, t_line *line);
char	*check_history(t_history *history, t_buff *buffer,
t_buff *history_search);
void	disable_highlight(t_cord *cord, char *buffer);
void	prev_word(char *buf, t_cord *cord);
void	next_word(char *buf, t_cord *cord);
char	*print_printable(char *c, char *buffer, t_cord *cord);
void	del_symb(char *buf, t_cord *cord);
void	print_symb(char *c, char *buf, t_cord *cord);
char	*print_move(char *c, char *buffer, t_cord *cord);
void	free_buffer(t_buff *buffer);
void	save_cord(t_cord *cord);
#endif
