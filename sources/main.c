/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bemoreau <bemoreau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 14:04:49 by bemoreau          #+#    #+#             */
/*   Updated: 2021/06/21 18:07:44 by bemoreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

pid_t	g_child;

char	*first_arg(char *str)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str[i] == ' ' && str[i])
		i++;
	while (str[i + j] != ' ' && str[i + j])
		j++;
	return (ft_substr(str, i, j));
}

int	free_arg(t_parser *comm, int bool)
{
	if (!bool)
		free(comm->argument);
	if (bool == 1)
	{
		free(comm->argument);
		free(comm->next->command);
	}
	if (bool == 2)
	{
		free(comm->argument);
		free(comm->next->command);
		free(comm->next->argument);
	}
	return (1);
}

int	get_arg(char *left, char *right, t_parser *comm)
{
	comm->command = first_arg(left);
	if (!comm->command)
		return (1);
	comm->argument = ft_split(left + ft_strlen(comm->command), ' ');
	if (!comm->argument)
		return (free_arg(comm, 0));
	comm->next->command = first_arg(right);
	if (!comm->next->command)
		return (free_arg(comm, 1));
	comm->next->argument = ft_split(right + ft_strlen(comm->next->command), ' ');
	if (!comm->argument)
		return (free_arg(comm, 2));
	return (0);
}

int main(int argc, char **argv, char **envp)
{
	int			err;
	t_redir		redir;
	t_pipe		spipe;
	t_parser	*comm;

	comm = (t_parser *)malloc(sizeof(t_parser));
	if (!comm)
		return (1);
	comm->command = NULL;
	comm->argument = NULL;
	comm->next = (t_parser *)malloc(sizeof(t_parser));
	if (!comm->next)
		return (1);
	comm->next->command = NULL;
	comm->next->argument = NULL;
	err = 0;
	spipe.path = NULL;
	spipe.l_env = envp;
	if (argc != 5)
		return (1);
	err = exec_redir(argv[1], argv[4], &redir);
	if (err)
		return (err);
	err = get_arg(argv[2], argv[3], comm);
	if (err)
		return (err);
	err = single_pipe(comm, &redir, &spipe);
	if (err)
		return (err);
}