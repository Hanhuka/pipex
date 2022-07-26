/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralves-g <ralves-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 12:12:13 by ralves-g          #+#    #+#             */
/*   Updated: 2022/07/25 15:39:27 by ralves-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	err_args(void)
{
	write(2, "wrong number of arguments\n", 27);
	exit(1);
}

void	infile_norm(t_pipex *p)
{
	if (p->infile < 0)
		exit(127);
	dup2(p->infile, STDIN_FILENO);
	dup2(p->pipe[1], STDOUT_FILENO);
}

void	child_process(t_pipex *p, int i, char **env)
{
	if (pipe(p->pipe) == -1)
		ft_err(p, "Error");
	p->pid = fork();
	if (p->pid < 0)
		ft_err(p, "Error");
	if (!p->pid)
	{
		close(p->pipe[0]);
		if (p->id == 0)
			infile_norm(p);
		else if (p->id == p->cmdnbr - 1)
			dup2(p->outfile, STDOUT_FILENO);
		else
			dup2(p->pipe[1], STDOUT_FILENO);
		child_work(p, i);
		execve(p->cmdpath, p->cmd, env);
		free_all(p);
		exit(127);
	}
	close(p->pipe[1]);
	dup2(p->pipe[0], STDIN_FILENO);
	close(p->pipe[0]);
}

int	main(int ac, char **av, char **env)
{
	t_pipex	p;
	int		i;

	if (ac < 5)
		err_args();
	parse_args(&p, av, ac);
	p.cmdnbr = ac - p.here_doc - 3;
	parse_path(&p, env);
	p.id = -1;
	while (++p.id < p.cmdnbr)
		child_process(&p, p.id + p.here_doc, env);
	close(0);
	waitpid(p.pid, NULL, 0);
	i = 0;
	while (i++ < p.cmdnbr - 1)
		wait(NULL);
	if (p.here_doc)
		unlink(".heredoc_tmp");
	free_all(&p);
}
