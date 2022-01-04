/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bemoreau <bemoreau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 14:08:51 by marvin            #+#    #+#             */
/*   Updated: 2022/01/03 08:54:59 by bemoreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*rel_path(char **env, t_parser *comm, t_pipe *spipe)
{
	int			ret;

	(void)env;
	ret = access(comm->argument[0], F_OK);
	if (ret == 0)
		return (ft_strdup(comm->argument[0]));
	spipe->b_ret[spipe->index] = 8;
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
	int			i;

	i = -1;
	while (tab[++i])
	{
		*name = ft_strjoin_c(tab[i], comm->command, '/');
		if (*name == NULL)
			return (dealloc_tab(tab, NULL));
		if (access(*name, F_OK) == 0)
		{
			spipe->b_ret[spipe->index] = 1;
			return (dealloc_tab(tab, *name));
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
