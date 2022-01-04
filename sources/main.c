/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bemoreau <bemoreau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 14:04:49 by bemoreau          #+#    #+#             */
/*   Updated: 2022/01/03 10:03:10 by bemoreau         ###   ########.fr       */
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
	if ((i + j) == 0)
		return (NULL);
	return (ft_substr(str, i, j));
}

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		free(tab[i++]);
	free(tab);
}

int	get_arg(char *left, char *right, t_parser *comm)
{
	comm->command = first_arg(left);
	if (!comm->command)
		return (1);
	comm->argument = ft_split(left, ' ');
	if (!comm->argument)
		return (free_comm(comm));
	comm->next->command = first_arg(right);
	if (!comm->next->command)
		return (free_comm(comm));
	comm->next->argument = ft_split(right, ' ');
	if (!comm->argument)
		return (free_comm(comm));
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_redir		redir;
	t_pipe		spipe;
	t_parser	*comm;
	int			err;

	if (argc != 5)
		return (err_msg("Wrong number of arguments"));
	comm = init_comm();
	if (!comm)
		return (err_msg("Malloc error"));
	init_spipe(&spipe, envp);
	if (get_arg(argv[2], argv[3], comm))
	{
		free_comm(comm);
		return (err_msg("Error while parsing commands"));
	}
	err = single_pipe(comm, &redir, &spipe, argv);
	if (err)
	{
		free_comm(comm);
		return (err);
	}
	free_comm(comm);
	return (0);
}
