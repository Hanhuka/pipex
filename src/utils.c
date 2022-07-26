/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralves-g <ralves-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 14:10:52 by ralves-g          #+#    #+#             */
/*   Updated: 2022/07/26 16:05:52 by ralves-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

char	*ft_strdup(const char *s1)
{
	char	*ptr;
	int		i;

	i = 0;
	if (!s1)
		return (0);
	while (s1[i])
		i++;
	ptr = malloc(i + 1);
	if (!ptr)
		return (0);
	i = 0;
	while (s1[i])
	{
		ptr[i] = s1[i];
		i++;
	}
	ptr[i] = 0;
	return (ptr);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n <= 0)
		return (0);
	while (i < n - 1 && *(s1 + i) == *(s2 + i)
		&& *(s1 + i) != '\0' && *(s2 + i) != '\0')
		i++;
	return ((*(unsigned char *)(s1 + i) - *(unsigned char *)(s2 + i)));
}

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	while (&s[i] != &*s && i >= 0)
	{
		if (s[i] == (char) c)
			break ;
		i--;
	}
	if (s[i] == *s && s[i] != (char) c)
		return (NULL);
	if (c == '\0' || s[i] != '\0')
		return ((char *)s + i);
	return (NULL);
}
