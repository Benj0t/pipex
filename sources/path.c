/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bemoreau <bemoreau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 14:08:51 by marvin            #+#    #+#             */
/*   Updated: 2021/12/17 00:30:00 by bemoreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*rel_path(char **env, t_parser *comm, t_pipe *spipe)
{
	struct stat	buf;
	int			ret;

	(void)env;
	ret = stat(comm->argument[0], &buf);
	if (ret == 0 && (buf.st_mode & S_IXUSR) && (buf.st_mode & S_IFREG))
		return (ft_strdup(comm->argument[0]));
	error_msg(spipe, buf, ret);
	return (NULL);
}

int	rel_char(char *name)
{
	int	i;

	i = 0;
	while (name[i])
	{
		if (name[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

char	*try_exec(char **tab, char **name, t_parser *comm, t_pipe *spipe)
{
	struct stat	buf;
	int			i;
	int			j;
	int			k;

	i = -1;
	while (tab[++i])
	{
		*name = ft_strjoin_c(tab[i], comm->command, '/');
		if (*name == NULL)
			return (dealloc_tab(tab, NULL));
		if (stat(*name, &buf) == 0)
		{
			k = buf.st_mode & S_IXUSR;
			j = buf.st_mode & S_IFREG;
			if (k && j)
			{
				spipe->b_ret[spipe->index] = 1;
				return (dealloc_tab(tab, *name));
			}
		}
		spipe->b_ret[spipe->index] = 127;
		free(*name);
	}
	return (NULL);
}

char	*ft_path(char **env, t_parser *comm, t_pipe *spipe)
{
	char		*s;
	char		**tab;
	int			i;

	s = NULL;
	if (rel_char(comm->command))
		return (rel_path(env, comm, spipe));
	i = get_path_id(env);
	if (i < 0)
		return (NULL);
	tab = ft_split(env[i] + 5, ':');
	if (!tab)
		return (NULL);
	if (!rel_char(comm->command))
	{
		s = try_exec(tab, &s, comm, spipe);
		if (s)
			return (s);
	}
	return (dealloc_tab(tab, NULL));
}
