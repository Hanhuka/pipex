/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_and_frees.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralves-g <ralves-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 16:17:17 by ralves-g          #+#    #+#             */
/*   Updated: 2022/07/26 17:26:22 by ralves-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	free_all(t_pipex *p)
{
	int	i;

	i = -1;
	while (p->path[++i])
		free(p->path[i]);
	free(p->path);
	i = -1;
	while (p->arg[++i])
		free(p->arg[i]);
	free(p->arg);
	if (p->infile > 0)
		close(p->infile);
	close(p->outfile);
}

void	ft_err(t_pipex *p, char *str)
{
	perror(str);
	if (p->here_doc)
		free_all(p);
	else
		free_all(p);
	exit(1);
}

void	special_err(t_pipex *p, char *str)
{
	perror(str);
	free_all(p);
	exit(1);
}

void	err_all(t_pipex *p, char *str)
{
	perror(str);
	free_all(p);
	exit(1);
}
