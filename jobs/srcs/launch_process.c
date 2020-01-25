/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 23:37:26 by filip             #+#    #+#             */
/*   Updated: 2020/01/25 15:16:15 by lcrawn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void	dup_pipes(t_process *p)
{
	if (p->next && p->next->inpipe)
		if (close(p->next->inpipe) < 0)
			err_exit("42sh", "close() error", NULL, NOERROR);
	if (p->inpipe != STDIN_FILENO)
	{
		if (dup2(p->inpipe, STDIN_FILENO) < 0)
			err_exit("42sh", "dup2() error", NULL, NOERROR);
		if (close(p->inpipe) < 0)
			err_exit("42sh", "close() error", NULL, NOERROR);
	}
	if (p->outpipe != STDOUT_FILENO)
	{
		if (dup2(p->outpipe, STDOUT_FILENO) < 0)
			err_exit("42sh", "dup2() error", NULL, NOERROR);
		if (close(p->outpipe) < 0)
			err_exit("42sh", "close() error", NULL, NOERROR);
	}
}

void	ft_sub(char **args)
{
	while (*args)
	{
		*args = spec_symbols(*args);
		args++;
	}
}

void	launch_process(t_process *p, pid_t pgid, int foreground)
{
	pid_t	pid;
	char	*fname;

	pid = getpid();
	setpgid(pid, pgid);
	if (foreground)
		tcsetpgrp(g_shell_terminal, pgid);
	set_sig_def();
	dup_pipes(p);
	if (redir_handle(p) < 0)
		exit(1);
	dup_redir(p->fd_list);
	if (!launch_builtin(p, FORK))
	{
		//p->completed = 1;
		p->error = g_last_exit_status;
		exit(g_last_exit_status);
	}
	else
	{
		ft_sub(p->args);
		fname = get_fname(p->args[0]);
		if (execve(fname, p->args, g_env.env) < 0)
		{
			p->error = g_last_exit_status;
			err_exit("42sh", "permission denied", p->args[0], NOERROR);
		}
		//p->completed = 1;
		exit(g_last_exit_status);
	}
}
