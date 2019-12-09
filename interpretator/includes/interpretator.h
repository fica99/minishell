/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpretator.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 13:58:11 by aashara-          #+#    #+#             */
/*   Updated: 2019/10/23 16:51:18 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERPRETATOR_H
# define INTERPRETATOR_H

# include "../lex/includes/lex.h"
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>

# define DEF_HEREDOC_SIZE 10;
# define LRED_OPEN O_RDONLY
# define RRED_OPEN O_RDWR | O_CREAT | O_TRUNC
# define DRRED_OPEN O_RDWR | O_CREAT | O_APPEND
# define PERM_MODE S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH
# define INT_LEN 10
# define HEREDOC_FILE "/tmp/.fucking_heredoc"
# define INIT_AGGR_FD -5

// typedef struct s_sep_list
// {
// 	int sep;
// 	int status;
// 	struct	s_sep_list  *next;
// }				t_sep_list;

int			syntax_err(t_lex_tkn *token);
t_lex_tkn	**find_token(t_lex_tkn **list, int type);
void		parse(t_lex_tkn **tokens);
void		*ft_realloc(void *buf, size_t new_size);
char		**ft_strtok(char *s);
char		*ft_strccut(char *str, char c);
char		*ft_stricut(char *str, int i);
t_lex_tkn	**split_list(t_lex_tkn **token);
t_lex_tkn	**find_token(t_lex_tkn **list, int type);
t_job		*job_new(void);
int redirect_list(t_lex_tkn **redir, t_process *cur_proc);

#endif