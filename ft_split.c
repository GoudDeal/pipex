/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcyprien <dcyprien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 17:28:15 by dcyprien          #+#    #+#             */
/*   Updated: 2021/12/06 18:23:09 by dcyprien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	*ft_calloc(size_t count, size_t size)
{
	char	*mem;
	int		i;

	i = 0;
	if (count != 0 && size != 0)
	{
		mem = malloc(count * size);
		if (!(mem))
			return (NULL);
		while (i < (int)(count * size))
		{
			mem[i] = 0;
			i++;
		}
		return (mem);
	}
	return (malloc(1));
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char		*str;
	size_t		i;

	if (s != NULL)
	{
		i = 0;
		if (start >= (unsigned int)ft_strlen((char *)s) || !(*s) || len == 0)
			return (ft_strdup("\0"));
		str = (char *)malloc(sizeof(char) * (len + 1));
		if (!(str))
			return (NULL);
		while (s[start + i] && i < len)
		{
			str[i] = s[start + i];
			i++;
		}
		str[i] = '\0';
		return (str);
	}
	return (ft_strdup("\0"));
}

size_t	get_n_word(const char *s, char c)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 1;
	while (s[j])
	{
		if ((s[j] == c && s[j - 1] != c && s[j + 1])
			|| (s[j] != c && s[j + 1] == '\0'))
			i++;
		j++;
	}
	return (i);
}

char	*extract_word(const char *s, char c)
{
	int	end;

	end = 0;
	while (s[end] && s[end] != c)
		end++;
	return (ft_substr(s, 0, end));
}

char	**ft_split(const char *s, char c)
{
	char	**result;
	size_t	n_word;
	size_t	j;

	if (s != NULL && c && *s != 0)
	{
		j = 0;
		n_word = get_n_word(s, c);
		result = ft_calloc(n_word + 1, sizeof(char *));
		if (!(result))
			return (NULL);
		while (j < n_word && *s)
		{
			while (*s == c)
				s++;
			result[j] = extract_word(s, c);
			s = ft_strchr(s, c);
			j++;
		}
		result[j] = NULL;
		return (result);
	}
	return (NULL);
}
