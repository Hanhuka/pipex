/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralves-g <ralves-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 12:50:30 by ralves-g          #+#    #+#             */
/*   Updated: 2022/07/26 15:51:00 by ralves-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	heredoc_filler(int tempfile, char	**av)
{
	char	*buf;
	char	*tmp;

	tmp = ft_strjoin(av[2], "\n");
	while (1)
	{
		write(1, "pipe to heredoc> ", 17);
		buf = get_next_line(0);
		if (buf)
		{
			if (!ft_strncmp(buf, tmp, ft_strlen(tmp)))
				break ;
			write(tempfile, buf, ft_strlen(buf));
			free(buf);
		}
		else
			break ;
	}
	free(tmp);
	if (buf)
		free(buf);
}

void	has_heredoc(t_pipex *p, char **av, int ac)
{
	int	tempfile;

	if (ac < 6)
		err_args();
	p->here_doc = 1;
	tempfile = open(".heredoc_tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	p->outfile = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (tempfile < 0 || p->outfile < 0)
	{
		perror("Error");
		exit(1);
	}
	heredoc_filler(tempfile, av);
	close(tempfile);
	p->infile = open(".heredoc_tmp", O_RDONLY);
	if (p->infile < 0)
	{
		unlink(".heredoc_tmp");
		exit(1);
	}
}

void	no_heredoc(t_pipex *p, char **av, int ac)
{
	p->here_doc = 0;
	p->infile = open(av[1], O_RDONLY);
	p->outfile = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (p->outfile < 0)
	{
		perror("Error");
		exit(1);
	}
	if (p->infile < 0)
	{
		perror("Error");
	}
}

void	parse_args(t_pipex *p, char **av, int ac)
{
	int	i;
	int	i2;

	if (!ft_strncmp(av[1], "here_doc", 8))
		has_heredoc(p, av, ac);
	else
		no_heredoc(p, av, ac);
	p->arg = malloc(sizeof(char *) * ac);
	if (!p->arg)
		ft_err(p, "Error");
	i = 1;
	i2 = -1;
	while (++i < ac)
		p->arg[++i2] = ft_strdup(av[i]);
	p->arg[++i2] = 0;
}

void	parse_path(t_pipex *p, char **env)
{
	char	*str;
	int		i;

	i = -1;
	while (env[++i])
		if (!ft_strncmp(env[i], "PATH", 4))
			str = ft_strdup(env[i] + 5);
	if (!str)
		ft_err(p, "Error");
	p->path = ft_split(str, ':');
	free(str);
}
