/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bemoreau <bemoreau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 14:04:49 by bemoreau          #+#    #+#             */
/*   Updated: 2021/12/17 01:05:29 by bemoreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

void	free_tab(char **tab)
{
	int i;

	i = 0;
	while (tab[i])
		free(tab[i++]);
	free(tab);
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
	comm->argument = ft_split(left, ' ');
	if (!comm->argument)
		return (free_arg(comm, 0));
	comm->next->command = first_arg(right);
	if (!comm->next->command)
		return (free_arg(comm, 1));
	comm->next->argument = ft_split(right, ' ');
	if (!comm->argument)
		return (free_arg(comm, 2));
	return (0);
}

void	free_comm(t_parser *comm)
{
	int i;

	i = 0;
	free(comm->command);
	while (comm->argument[i])
		free(comm->argument[i++]);
	free(comm->argument);
	i = 0;
	while (comm->next->argument[i])
		free(comm->next->argument[i++]);
	free(comm->next->argument);
	free(comm->next->command);
	free(comm->next);
	free(comm);
	return ;
}

int	main(int argc, char **argv, char **envp)
{
	int			err;
	t_redir		redir;
	t_pipe		spipe;
	t_parser	*comm;

	if (argc != 5)
		return (1);
	comm = init_comm();
	err = 0;
	spipe.path = NULL;
	spipe.l_env = envp;
	err = get_arg(argv[2], argv[3], comm);
	if (err)
		return (err);
	err = single_pipe(comm, &redir, &spipe, argv);
	if (err)
		return (err);
	free_comm(comm);
	return (0);
}
