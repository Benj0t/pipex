/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bemoreau <bemoreau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 14:35:07 by bemoreau          #+#    #+#             */
/*   Updated: 2021/06/23 19:00:24 by bemoreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

extern pid_t	g_child;

char		*init_path(char **env, t_parser *command, t_pipe *spipe, int index)
{
	if (spipe->path)
	{
		free(spipe->path);
		spipe->path = NULL;
	}
	if (command->argument && command->argument[0] && !ft_strncmp("", command->argument[0], 1))
		return (NULL);
	if (command->argument && !ft_strncmp(".", command->argument[0], 2))
	{
		spipe->b_ret[index] = 2;
		return (NULL);
	}
	spipe->path = ft_path(env, command, spipe);
	if (!(spipe->path))
		return (NULL);
	return (spipe->path);
}

int			invalid_command(t_pipe *spipe, t_parser *comm1, int index)
{
	if (spipe->b_ret[index] == 3)
		ft_putstr_fd("minishell: permission denied\n", 2);
	if (spipe->b_ret[index] == 2)
		ft_putstr_fd("minishell: .: command not found\n", 2);
	if (spipe->b_ret[index] == 6)
		ft_putstr_fd("minishell: file is a directory\n", 2);
	if (spipe->b_ret[index] == 7)
		ft_putstr_fd("minishell: Can not execute your file\n", 2);
	if (spipe->b_ret[index] == 8)
		ft_putstr_fd("minishell: Can not find or execute your file\n", 2);
	if (spipe->b_ret[index] == 3 || spipe->b_ret[index] == 6 ||\
								spipe->b_ret[index] == 7)
		return (126);
	if (spipe->b_ret[index] == 2 || spipe->b_ret[index] == 8)
		return (127);
	ft_putstr_fd(comm1->argument[0], 2);
	ft_putstr_fd(": command not found\n", 2);
	if (comm1->argument)
		free(comm1->argument);
	return (127);
}

static int		left_command(t_pipe *spipe, t_redir *redir,\
						t_parser *command)
{

	(void)redir;
	if (init_path(spipe->l_env, command, spipe, 0) == NULL)
		return (spipe->ret[0] = invalid_command(spipe, command, 0));
	if ((g_child = fork()) == 0)
	{
		dup2(spipe->curr_p[1], 1);
		close(spipe->curr_p[0]);
		exit(execve(spipe->path, command->argument, spipe->l_env));
	}
	spipe->child[0] = g_child;
	free(command->argument);
	return (0);
}

static int		right_command(t_pipe *spipe, t_redir *redir,\
						t_parser *command)
{
	if ((init_path(spipe->l_env, command, spipe, 1)) == NULL)
		return (spipe->ret[1] = invalid_command(spipe, command, 1));
	if ((g_child = fork()) == 0)
	{
		dup2(spipe->curr_p[0], 0);
		close(spipe->curr_p[1]);
		execve(spipe->path, command->argument, spipe->l_env);
	}
	spipe->child[1] = g_child;
	end_redir(redir);
	close(spipe->curr_p[0]);
	close(spipe->curr_p[1]);
	free(spipe->path);
	return (0);
}

int				left_pipe(t_parser *command, t_redir *redir, t_pipe *spipe)
{
	if (pipe(spipe->curr_p) < 0)
		return (-1);
	if ((left_command(spipe, redir, command)) != 0)
		return (0);
	return (1);
}

int				right_pipe(t_parser *command, t_redir *redir, t_pipe *spipe)
{

	if (spipe->curr_p[0] == -1 || spipe->curr_p[1] == -1)
		if (pipe(spipe->curr_p) < 0)
			return (0);
	spipe->index++;
	if ((right_command(spipe, redir, command->next)) != 0)
		return (0);
	if (spipe->ret[1] <= 1)
		free(command->next->argument);
	return (1);
}

int				single_pipe(t_parser *command, t_redir *redir, t_pipe *spipe, char **argv)
{
	int			i;
	t_parser	*tmp;

	tmp = command;
	i = 0;
	spipe->index = 0;
	spipe->curr_p[0] = -1;
	spipe->curr_p[1] = -1;
	exec_redir_in(argv[1], redir);
	left_pipe(tmp, redir, spipe);
	end_redir(redir);
	exec_redir_out(argv[4], redir);
	right_pipe(tmp, redir, spipe);
	end_redir(redir);
	waitpid(spipe->child[1], (int *)&(spipe->pid[1]), 0);
	spipe->ret[1] = WEXITSTATUS(spipe->pid[1]);
	waitpid(spipe->child[0], (int *)&(spipe->pid[0]), 0);
	spipe->ret[0] = WEXITSTATUS(spipe->pid[0]);
	return (1);
}
