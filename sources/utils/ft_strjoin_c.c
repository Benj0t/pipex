/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_c.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bemoreau <bemoreau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 18:43:30 by psemsari          #+#    #+#             */
/*   Updated: 2021/12/16 16:38:38 by bemoreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_strjoin_c(char const *s1, char const *s2, char c)
{
	char	*ptr;
	char	*tmp;

	if (!s1 || !s2)
		return (NULL);
	ptr = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 2));
	if (!ptr)
		return (NULL);
	tmp = ptr;
	while (*s1 != '\0')
		*ptr++ = *s1++;
	*ptr++ = c;
	while (*s2 != '\0')
		*ptr++ = *s2++;
	*ptr = '\0';
	return (tmp);
}
