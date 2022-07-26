/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_work.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralves-g <ralves-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 14:25:07 by ralves-g          #+#    #+#             */
/*   Updated: 2022/07/26 17:12:47 by ralves-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	not_absolute(t_pipex *p)
{
	int		i;
	char	*tmp;

	i = -1;
	while (p->path[++i])
	{
		tmp = ft_strjoin(p->path[i], p->cmdpath);
		if (access(tmp, X_OK) >= 0)
		{
			p->cmdpath = ft_strdup(tmp);
			free(tmp);
			return ;
		}
		free(tmp);
	}
	i = 0;
	while (p->cmd[i])
	{
		free(p->cmd[i]);
		i++;
	}
	free(p->cmd);
	free(p->cmdpath);
	special_err(p, "Error");
}

void	absolute(t_pipex *p)
{
	if (access(p->cmdpath, F_OK) < 0)
		err_all(p, "Error");
}

void	child_work(t_pipex *p, int i)
{
	int	i2;

	i2 = 0;
	if (p->arg[i][0] == '/')
	{
		while (p->arg[i][i2] && p->arg[i][i2] != ' ')
			i2++;
		p->cmdpath = ft_substr(p->arg[i], 0, i2);
		p->cmd = ft_split(ft_strrchr(p->arg[i], '/') + 1, ' ');
		absolute(p);
	}
	else
	{
		p->cmd = ft_split(p->arg[i], ' ');
		p->cmdpath = ft_strjoin("/", p->cmd[0]);
		not_absolute(p);
	}
}
