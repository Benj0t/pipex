/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bemoreau <bemoreau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 17:03:17 by psemsari          #+#    #+#             */
/*   Updated: 2021/12/16 16:35:26 by bemoreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	int		ret;

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0' && i < n - 1)
		i++;
	if ((unsigned char)s1[i] - (unsigned char)s2[i] > 0)
		ret = 1;
	else if ((unsigned char)s1[i] - (unsigned char)s2[i] < 0)
		ret = -1;
	else
		ret = 0;
	return (ret);
}
