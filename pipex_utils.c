/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcyprien <dcyprien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 16:35:26 by dcyprien          #+#    #+#             */
/*   Updated: 2021/12/07 16:24:49 by dcyprien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdlib.h>
#include <stdio.h>

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	if (s)
	{
		while (s[i])
			i++;
		return (i);
	}
	return (0);
}

char	*ft_strdup(const char *s)
{
	char	*copy;
	int		i;

	i = 0;
	if (s != NULL)
	{
		copy = (char *)malloc((ft_strlen(s) + 1) * sizeof(char));
		if (!copy)
			return (NULL);
		while (s[i])
		{
			copy[i] = s[i];
			i++;
		}
		copy[i] = '\0';
		return (copy);
	}
	return (NULL);
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	n;

	if (haystack != NULL && needle != NULL && *needle)
	{
		n = ft_strlen(needle);
		while (*haystack && len-- >= n)
		{
			if (ft_strncmp(haystack, needle, n) == 0)
				return ((char *)haystack);
			haystack++;
		}
		return (NULL);
	}
	return ((char *)haystack);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	if (s1 != NULL && s2 != NULL && n != 0)
	{
		while ((*s1 || *s2) && *s1 == *s2 && --n > 0)
		{
			s1++;
			s2++;
		}
		return (((unsigned char)*s1 - (unsigned char)*s2));
	}
	return (0);
}

char	*ft_strcat(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	str = malloc((ft_strlen(s1) +ft_strlen(s2)) * sizeof(char) + 1);
	if (!str)
		return (NULL);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	str[++i] = '/';
	while (s2[j])
	{
		str[i] = s2[j++];
		i++;
	}
	printf("cmd = %s\n", s2);
	printf("str = %s\n", str);
	return (str);
}
