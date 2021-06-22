/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bemoreau <bemoreau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 14:04:49 by bemoreau          #+#    #+#             */
/*   Updated: 2021/06/22 16:57:29 by bemoreau         ###   ########.fr       */
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

void	print_args(t_parser *comm)
{
	printf("First command: %s\n", comm->command);
	int i = 0;
	while (comm->argument && comm->argument[i])
	{
		printf("Next argument: %s\n", comm->argument[i++]);
	}
	i = 0;
	printf("\nSecond command: %s\n", comm->next->command);
	while (comm->next->argument && comm->next->argument[i])
	{
		printf("Next argument: %s\n", comm->next->argument[i++]);
	}
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
	ft_putstr_fd("esnuifbeyuf\n", 2);
	err = exec_redir(argv[1], argv[4], &redir);
	if (err)
		return (err);
	err = get_arg(argv[2], argv[3], comm);
	if (err)
		return (err);
	//print_args(comm);
	err = single_pipe(comm, &redir, &spipe);
	if (err)
		return (err);
}