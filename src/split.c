/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralves-g <ralves-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 14:08:42 by ralves-g          #+#    #+#             */
/*   Updated: 2022/07/26 17:10:32 by ralves-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

static int	num_splits(char const *str, char c)
{
	int	i;
	int	splits;

	splits = 1;
	i = 0;
	while (str[i] && str[i] == c)
		i++;
	while (str[i])
	{
		if (str[i] != c && (i == 0 || str[i - 1] == c))
			splits++;
		i++;
	}
	return (splits);
}

char	*ft_substr(char const *str, int start, int end)
{
	char	*sub;
	int		i;

	i = 0;
	if (start > end)
		return (NULL);
	sub = malloc(end - start + 2);
	while (start <= end)
	{
		sub[i] = str[start];
		start++;
		i++;
	}
	sub[i] = 0;
	return (sub);
}

char	**ft_split(char const *str, char c)
{
	char	**split;
	int		i;
	int		start;
	int		i2;

	i = 0;
	i2 = 0;
	split = malloc(sizeof(char *) * num_splits(str, c));
	while (str[i] && str[i] == c)
		i++;
	while (str[i])
	{
		if (str[i] && str[i] != c && (!str[i + 1] || (str[i + 1]
					&& str[i + 1] == c)))
		{
			start = i - 1;
			while (!(str[start] && str[start] != c && (start == 0
						|| str[start - 1] == c)))
				start--;
			split[i2++] = ft_substr(str, start, i);
		}
		i++;
	}
	split[i2] = NULL;
	return (split);
}
