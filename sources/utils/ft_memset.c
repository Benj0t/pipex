/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bemoreau <bemoreau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 22:02:23 by psemsari          #+#    #+#             */
/*   Updated: 2021/12/16 16:48:07 by bemoreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*resu;

	i = 0;
	resu = (unsigned char *)s;
	while (i < n)
		resu[i++] = (unsigned char)c;
	return ((void *)resu);
}
