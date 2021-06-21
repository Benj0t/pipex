/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bemoreau <bemoreau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 13:47:42 by bemoreau          #+#    #+#             */
/*   Updated: 2021/06/21 16:34:24 by bemoreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _PIPEX_H_
# define _PIPEX_H_
# include "libft.h"
# include <dirent.h>
# include <unistd.h>
# include <sys/types.h>
# include <signal.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <limits.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/param.h>

typedef struct				s_pipe
{
	int						index;
	int						pid[2];
	int						curr_p[2];
	int						ret[2];
	int						b_ret[2];
	char					*path;
	pid_t					child[2];
	char					**l_env;
}							t_pipe;

typedef	struct				s_parser
{
	char					*command;
	char					**argument;
	struct s_parser		*next;
}							t_parser;

typedef struct				s_redir
{
	int						std_in;
	int						std_out;
	int						save_stdin;
	int						save_stdout;
}							t_redir;

int		exec_redir(char *redin, char *redout, t_redir *redir);
void	end_redir(t_redir *redir);
int		single_pipe(t_parser *command, t_redir *redir, t_pipe *spipe);
char	*ft_path(char **env, t_parser *comm, t_pipe *spipe);
char	*init_path(char **env, t_parser *command, t_pipe *spipe, int index);
int		invalid_command(t_pipe *spipe, t_parser *comm1, int index);
#endif