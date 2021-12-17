/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bemoreau <bemoreau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 18:58:56 by bemoreau          #+#    #+#             */
/*   Updated: 2021/12/16 18:58:56 by bemoreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	invalid_command(t_pipe *spipe, t_parser *comm1, int index)
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
	if (spipe->b_ret[index] == 3 || spipe->b_ret[index] == 6 || \
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

int	get_path_id(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp("PATH=", env[i], 5))
			return (i);
		i++;
	}
	return (-1);
}

int	err_msg(char *str)
{
	ft_putendl_fd(str, 2);
	return (1);
}

void	dup_files(t_redir *redir)
{
	if (redir->std_in != -1)
		dup2(redir->std_in, 0);
	if (redir->std_out != -1)
		dup2(redir->std_out, 1);
}

void	save_std(t_redir *redir)
{
	redir->save_stdin = dup(0);
	redir->save_stdout = dup(1);
	redir->std_in = -1;
	redir->std_out = -1;
}
