/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shell.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggrimes <ggrimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 17:28:23 by aashara-          #+#    #+#             */
/*   Updated: 2019/08/27 21:09:07 by ggrimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SHELL_H
# define FT_SHELL_H

# include "libft.h"
# include <termios.h>
# include "term/term.h"
# include "libstr.h"
# include "libdir.h"
# include "libdar.h"
# include "libfifo.h"
# include "libstack.h"
# include "prompt/prompt.h"
# include "make/make.h"
# include "error/error.h"
# include "hash_table/hash_table.h"
# include "history/history.h"
# include "macro/colour.h"
# include "macro/command.h"
# include "line_editing/line_editing.h"
# include "signal/signal.h"
# include "reading/reading.h"
# include "autocom/autocom.h"
# include "parser/parser.h"
# include "exec/exec.h"
# include "builtins/cd.h"
# include "builtins/env.h"
# include "builtins/echo.h"
# include "builtins/setenv.h"
# include "builtins/unsetenv.h"
# include "builtins/hash.h"
# include "builtins/his.h"
# include "lexer/lexer.h"

# define RUNNING 1
# define TERM_SIGINT (1 << 1)
# define TERM_EXIT (1 << 2)
# define HISTORY_SEARCH (1 << 3)
# define TERM_HIGHLIGHT (1 << 4)
# define START_POS (1 << 5)
# define TERM_QUOTES (1 << 6)
# define TERM_INIT_HASH (1 << 7)
# define TERM_FREE_HASH (1 << 8)
# define TERM_NL (1 << 9)
# define NORMAL_LINE 100
# define FT_HOST_NAME_MAX 255
# define LINE_MAX 2048
# define SOMETHING "1"
# define READING 1
# define INIT_FLAGS 0

struct s_line	g_line;
unsigned short	g_flags;
struct termios	g_orig_mode;
struct termios	g_raw_mode;
struct s_lexer  *g_lexer;
int				g_errno_f;
char			**g_env;
char			**g_argv;
#endif
