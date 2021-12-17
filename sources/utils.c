/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bemoreau <bemoreau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 18:04:20 by bemoreau          #+#    #+#             */
/*   Updated: 2021/12/16 18:04:20 by bemoreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*init_path(char **env, t_parser *command, t_pipe *spipe, int index)
{
	if (spipe->path)
	{
		free(spipe->path);
		spipe->path = NULL;
	}
	if (command->argument && command->argument[0] && \
			!ft_strncmp("", command->argument[0], 1))
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

void	*dealloc_tab(char **tab, void *ret)
{
	char	**start;

	start = tab;
	while (*tab != NULL)
	{
		free(*tab);
		tab++;
	}
	free(start);
	return (ret);
}

void	error_msg(t_pipe *spipe, struct stat buf, int ret)
{
	spipe->b_ret[spipe->index] = 8;
	if (!(buf.st_mode & S_IFREG) && ret == 0)
		spipe->b_ret[spipe->index] = 6;
	if (!(buf.st_mode & S_IXUSR) && ret == 0)
		spipe->b_ret[spipe->index] = 7;
}

t_parser	*init_comm(void)
{
	t_parser	*comm;

	comm = (t_parser *)malloc(sizeof(t_parser));
	if (!comm)
		return (NULL);
	comm->command = NULL;
	comm->argument = NULL;
	comm->next = (t_parser *)malloc(sizeof(t_parser));
	if (!comm->next)
	{
		free(comm);
		return (NULL);
	}
	comm->next->command = NULL;
	comm->next->argument = NULL;
	return (comm);
}