/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 11:20:50 by filip             #+#    #+#             */
/*   Updated: 2019/11/08 21:09:54 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_READLINE_H
# define FT_READLINE_H

# include <termios.h>
# include <curses.h>
# include <term.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/ioctl.h>
# include <signal.h>
# include <fcntl.h>
# include <time.h>
# include "libft.h"
# include "libhash.h"
# include "libstr.h"
# include "libdar.h"
# include "rl_errors.h"
# include "rl_colours.h"
# include "rl_templates.h"

# define MAX_LINE_SIZE 1000
# define VI_HASH_SIZE 21
# define RL_HASH_SIZE 21
# define DONT_FREE_HASH_DATA 0
# define FT_HOST_NAME_MAX 255
# define READING 1
# define LINE_MAX 2048
# define RL_INIT_FLAGS 0
# define RL_BREAK_FLAG (1 << 1)
# define RL_HIGHLIGHT_FLAG (1 << 2)
# define RL_HISTSIZE 500
# define RL_HISTFILESIZE 500
# define RL_HISTORY_FILE "/.42sh_history"
# define RL_PERM_HISTFILE S_IRUSR | S_IWUSR
# define RL_OPEN_HISTFILE O_RDWR | O_CREAT
# define RL_REWRITE_HISTFILE O_RDWR | O_TRUNC | O_CREAT
# define RL_PROMPT_TIME_BRACKETS 2

typedef struct		s_rl_history
{
	char			**history_buff;
	char			*histfile_path;
	short			hist_len;
	short			hist_index;
	short			histsize;
	short			histfilesize;
	short			cur_command_nb;
}					t_rl_history;

typedef enum		e_rl_mode
{
					VI = 1,
					READLINE = 2
}					t_rl_mode;

typedef struct		s_rl_cord
{
	short			x_start;
	short			y_start;
	short			x_end;
	short			y_end;
	short			x_cur;
	short			y_cur;
	short			ws_col;
	short			ws_row;
	short			highlight_pos;
	short			pos;
}					t_rl_cord;

typedef struct		s_rl_buff
{
	char			*buffer;
	short			malloc_len;
}					t_rl_buff;

typedef struct		s_readline
{
	t_hash			**vi_hash;
	t_hash			**rl_hash;
	t_rl_cord		cord;
	t_rl_buff		line;
	t_rl_buff		save_line;
	t_rl_buff		copy_buff;
	t_rl_buff		hist_search;
	struct termios	canon_mode;
	struct termios	non_canon_mode;
	char			*prompt;
	char			**env;
	t_rl_history 	history;
	t_rl_mode		mode;
}					t_readline;

/*
**	rl_main.c
*/
char				*ft_readline(char *prompt, t_rl_mode mode, char **environ);
void				init_readline(char **environ);
void				free_readline(void);
void				rl_err(char *name, char *str, char *err);
/*
**	rl_read_mode.c
*/
void				rl_save_attr(struct termios *savetty);
void				rl_set_non_canon_mode(struct termios *tty);
void				rl_set_attr(struct termios *savetty);
/*
**	rl_init.c
*/
void				rl_init_terminfo(void);
void				rl_init_rl_struct(t_readline *rl, char **env);
void				rl_init_buff(t_rl_buff *buffer);
void				rl_init_cord(t_rl_cord *cord);
void				rl_init_history(t_rl_history *history, char **env);
/*
**	rl_free.c
*/
void				rl_free_rl_struct(t_readline *rl);
void				rl_free_buff(t_rl_buff *buffer);
void				rl_clr_data(t_readline *rl);
/*
**	rl_prompt.c
*/
void				rl_write_prompt(char *str, char **env, t_rl_history history);
short				rl_prompt_user_host(char *str, short i, char **env);
short				rl_prompt_dir_history(char *str, short i,
t_rl_history history, char **env);
short				rl_prompt_colour_name(char *str, short i);
/*
**	rl_init_hash.c
*/
t_hash				**init_vi_hash(void);
t_hash				**init_rl_hash(void);
t_hash				**init_standart_templates(int hash_size);
t_hash				**init_standart_symb_templates(t_hash **table,
int hash_size);
/*
**	rl_reading.c
*/
char				*rl_reading(t_readline *rl);
void				rl_read_handler(char *c, int fd);
void				rl_find_template(t_readline *rl, char *c);
/*
**	rl_cord.c
*/
void				rl_get_cur_cord(t_rl_cord *cord);
void				rl_get_win_size(t_rl_cord *cord);
void				rl_set_start_cord(t_rl_cord *cord);
void				rl_set_end_cord(t_rl_cord *cord);
void				rl_start_cord_data(t_rl_cord *cord);
/*
**	rl_print.c
*/
void				rl_print(char *str, t_rl_cord *cord);
void				rl_del_symb(char *buf, t_rl_cord *cord);
void				rl_print_highlight(char *str, short start,
short end, t_rl_cord cord);
void				rl_disable_line(t_readline *rl);
/*
**	rl_check.c
*/
char				rl_is_start_pos(t_rl_cord cord);
char				rl_is_end_pos(t_rl_cord cord);
void				rl_malloc_len(t_rl_buff *buffer, char *c);
void				rl_is_end_window(t_rl_cord *cord);
char				rl_check_empty_line(char *line);
/*
**	rl_cur_movements.c
*/
void				rl_go_to_cord(short x, short y);
void				rl_go_left(short i, t_rl_cord *cord);
void				rl_go_right(short i, t_rl_cord *cord);
/*
**	rl_k_cur_left.c
*/
void				rl_k_left(t_readline *line);
void				rl_k_home(t_readline *rl);
void				rl_k_ctrl_up(t_readline *rl);
void				rl_k_ctrl_left(t_readline *rl);
/*
**	rl_k_cur_right.c
*/
void				rl_k_right(t_readline *rl);
void				rl_k_end(t_readline *rl);
void				rl_k_ctrl_down(t_readline *rl);
void				rl_k_ctrl_right(t_readline *rl);
/*
**	rl_k_highlight.c
*/
void				rl_k_shift_left(t_readline *rl);
void				rl_k_shift_right(t_readline *rl);
void				rl_k_ctrl_c(t_readline *rl);
void				rl_k_ctrl_x(t_readline *rl);
void				rl_k_ctrl_v(t_readline *rl);
/*
**	rl_k_other.c
*/
void				rl_k_enter(t_readline *rl);
void				rl_k_ctrl_d(t_readline *rl);
void				rl_print_symb(char *c, t_readline *rl);
void				rl_k_del(t_readline *rl);
void				rl_k_bcsp(t_readline *rl);
/*
**	rl_history.c
*/
void				rl_make_history_buff(t_rl_history *history);
void				rl_free_history(t_rl_history *history);
void				rl_rewrite_file(t_rl_history *history);
void				rl_add_to_history_buff(char *buffer, t_rl_history *history);
/*
**	rl_k_history.c
*/
void				rl_k_up(t_readline *rl);
void				rl_k_down(t_readline *rl);
void				rl_k_ctrl_r(t_readline *rl);
/*
**	rl_signal.c
*/
void				rl_win_handler(int sign);
/*
**	rl_history_params.c
*/
void				rl_get_hist_size(t_rl_history *history, char **env);
char				*rl_get_history_file_path(char **env);
void				rl_check_history_size(t_rl_history *history, char **env);
/*
**	rl_prompt_time.c
*/
short				rl_prompt_time(char *str, short i);
short				rl_check_time_flags(char *str, short i, struct tm *info);
short				rl_time_format_flag(char *str, short i, struct tm *info);
t_readline			g_rl;
unsigned char		g_rl_flags;
#endif
