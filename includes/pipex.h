/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bemoreau <bemoreau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 13:47:42 by bemoreau          #+#    #+#             */
/*   Updated: 2021/12/17 12:49:07 by bemoreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <dirent.h>
# include <unistd.h>
# include <sys/types.h>
# include <signal.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <limits.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/param.h>

typedef struct s_pipe
{
	pid_t					g_child;
	int						index;
	int						pid[2];
	int						curr_p[2];
	int						ret[2];
	int						b_ret[2];
	char					*path;
	pid_t					child[2];
	char					**l_env;
}							t_pipe;

typedef struct s_parser
{
	char					*command;
	char					**argument;
	struct s_parser			*next;
}							t_parser;

typedef struct s_redir
{
	int						std_in;
	int						std_out;
	int						save_stdin;
	int						save_stdout;
}							t_redir;

t_parser	*init_comm(void);
void		free_comm(t_parser *comm);
void		*ft_memset(void *s, int c, size_t n);
void		ft_bzero(void *s, size_t n);
void		ft_putchar_fd(char c, int fd);
size_t		ft_strlen(const char *s);
void		*ft_calloc(size_t count, size_t size);
char		*ft_strjoin_c(char const *s1, char const *s2, char c);
char		*ft_strdup(const char *s1);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
void		ft_putstr_fd(char *s, int fd);
void		ft_putendl_fd(char *s, int fd);
char		*ft_substr(char const *s, unsigned int start, size_t len);
int			exec_redir_in(char *red, t_redir *redir);
int			exec_redir_out(char *red, t_redir *redir);
void		end_redir(t_redir *redir);
int			single_pipe(t_parser *command, t_redir *redir, \
			t_pipe *spipe, char **argv);
char		*ft_path(char **env, t_parser *comm, t_pipe *spipe);
char		*init_path(char **env, t_parser *command, t_pipe *spipe, int index);
int			invalid_command(t_pipe *spipe, t_parser *comm1, int index);
char		**ft_split(char const *s, char c);
void		error_msg(t_pipe *spipe, struct stat buf, int ret);
void		*dealloc_tab(char **tab, void *ret);
int			invalid_command(t_pipe *spipe, t_parser *comm1, int index);
int			get_path_id(char **env);
void		save_std(t_redir *redir);
void		dup_files(t_redir *redir);
int			err_msg(char *str);
char		*init_path(char **env, t_parser *command, t_pipe *spipe, int index);
#endif