/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bemoreau <bemoreau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 18:04:17 by psemsari          #+#    #+#             */
/*   Updated: 2021/12/16 17:08:52 by bemoreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	if (count * size == 0)
	{
		count = 1;
		size = 1;
	}
	ptr = (void *)malloc(size * count);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, count);
	return (ptr);
}
