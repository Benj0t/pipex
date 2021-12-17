/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bemoreau <bemoreau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 14:06:55 by bemoreau          #+#    #+#             */
/*   Updated: 2021/12/16 19:02:17 by bemoreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	end_redir(t_redir *redir)
{
	dup2(redir->save_stdin, 0);
	if (redir->save_stdin != -1)
		close(redir->save_stdin);
	if (redir->std_in != -1)
		close(redir->std_in);
	dup2(redir->save_stdout, 1);
	if (redir->save_stdout != -1)
		close(redir->save_stdout);
	if (redir->std_out != -1)
		close(redir->std_out);
	redir->std_out = -1;
	redir->std_in = -1;
}

int	try_rdonly(int *fd, char *redin, t_redir *redir)
{
	*fd = open(redin, O_RDONLY, 0644);
	if (*fd == -1)
		return (err_msg("Can't open redirection file !"));
	if (redir->std_in != -1)
		close(redir->std_in);
	redir->std_in = *fd;
	return (0);
}

int	try_wronly(int *fd, char *redout, t_redir *redir)
{
	*fd = open(redout, O_WRONLY | O_TRUNC, 0644);
	if (*fd == -1)
	{
		*fd = open(redout, O_CREAT, 0644);
		if (*fd == -1)
			return (err_msg("Can't create redirection file !"));
		else
		{
			close(*fd);
			*fd = open(redout, O_WRONLY | O_TRUNC, 0644);
			if (*fd == -1)
				return (err_msg("Can't open redirection file !"));
		}
	}
	if (redir->std_out != -1)
		close(redir->std_out);
	redir->std_out = *fd;
	return (0);
}

int	exec_redir_in(char *red, t_redir *redir)
{
	int	in;

	save_std(redir);
	if (!red)
		return (1);
	in = 0;
	if (try_rdonly(&in, red, redir) == 1)
		return (1);
	dup_files(redir);
	return (0);
}

int	exec_redir_out(char *red, t_redir *redir)
{
	int	out;

	save_std(redir);
	if (!red)
		return (1);
	out = 0;
	if (try_wronly(&out, red, redir) == 1)
		return (1);
	dup_files(redir);
	return (0);
}
