/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcyprien <dcyprien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 10:53:24 by dcyprien          #+#    #+#             */
/*   Updated: 2021/12/06 18:21:10 by dcyprien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strchr(const char *s, int c)
{
	if (s != NULL)
	{
		while (*s && *s != c)
			s++;
		if (*s != c)
			return (NULL);
		else
			return ((char *)s);
	}
	return (NULL);
}
