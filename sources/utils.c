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

int	free_comm(t_parser *comm)
{
	int	i;

	i = 0;
	if (comm->command)
		free(comm->command);
	while (comm->argument && comm->argument[i])
		free(comm->argument[i++]);
	if (comm->argument)
		free(comm->argument);
	i = 0;
	while (comm->next->argument && comm->next->argument[i])
		free(comm->next->argument[i++]);
	if (comm->next->argument)
		free(comm->next->argument);
	if (comm->next->command)
		free(comm->next->command);
	if (comm->next)
		free(comm->next);
	if (comm)
		free(comm);
	return (1);
}

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
	comm->next->next = NULL;
	return (comm);
}

void	init_spipe(t_pipe *spipe, char **envp)
{
	spipe->path = NULL;
	spipe->l_env = envp;
	spipe->index = 0;
	spipe->g_child = 0;
	spipe->curr_p[0] = -1;
	spipe->curr_p[1] = -1;
	spipe->ret[0] = 0;
	spipe->ret[1] = 0;
}
