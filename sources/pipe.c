/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bemoreau <bemoreau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 14:35:07 by bemoreau          #+#    #+#             */
/*   Updated: 2022/01/03 10:06:08 by bemoreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	left_command(t_pipe *spipe, t_redir *redir, \
						t_parser *command)
{
	(void)redir;
	if (init_path(spipe->l_env, command, spipe, 0) == NULL)
		return (spipe->ret[0] = invalid_command(spipe, command, 0));
	spipe->g_child = fork();
	if (spipe->g_child == 0)
	{
		dup2(spipe->curr_p[1], 1);
		close(spipe->curr_p[0]);
		exit(execve(spipe->path, command->argument, spipe->l_env));
	}
	spipe->child[0] = spipe->g_child;
	return (0);
}

static int	right_command(t_pipe *spipe, t_redir *redir, \
						t_parser *command)
{
	if (init_path(spipe->l_env, command, spipe, 1) == NULL)
		return (spipe->ret[1] = invalid_command(spipe, command, 1));
	spipe->g_child = fork();
	if (spipe->g_child == 0)
	{
		dup2(spipe->curr_p[0], 0);
		close(spipe->curr_p[1]);
		execve(spipe->path, command->argument, spipe->l_env);
	}
	spipe->child[1] = spipe->g_child;
	end_redir(redir);
	close(spipe->curr_p[0]);
	close(spipe->curr_p[1]);
	free(spipe->path);
	return (0);
}

int	left_pipe(t_parser *command, t_redir *redir, t_pipe *spipe)
{
	if (pipe(spipe->curr_p) < 0)
		return (1);
	if ((left_command(spipe, redir, command)) != 0)
		return (spipe->ret[0]);
	return (0);
}

int	right_pipe(t_parser *command, t_redir *redir, t_pipe *spipe)
{
	if (spipe->curr_p[0] == -1 || spipe->curr_p[1] == -1)
		if (pipe(spipe->curr_p) < 0)
			return (1);
	spipe->index++;
	if ((right_command(spipe, redir, command->next)) != 0)
		return (spipe->ret[1]);
	return (0);
}

int	single_pipe(t_parser *command, t_redir *redir, t_pipe *spipe, char **argv)
{
	t_parser	*tmp;

	tmp = command;
	if (exec_redir_in(argv[1], redir))
		return (1);
	if (left_pipe(tmp, redir, spipe))
		return (spipe->ret[0]);
	end_redir(redir);
	if (exec_redir_out(argv[4], redir))
		return (1);
	if (right_pipe(tmp, redir, spipe))
		return (spipe->ret[1]);
	end_redir(redir);
	waitpid(spipe->child[0], (int *)&(spipe->pid[0]), 0);
	spipe->ret[0] = WEXITSTATUS(spipe->pid[0]);
	waitpid(spipe->child[1], (int *)&(spipe->pid[1]), 0);
	spipe->ret[1] = WEXITSTATUS(spipe->pid[1]);
	if (spipe->ret[0])
		return (spipe->ret[0]);
	return (spipe->ret[1]);
}
