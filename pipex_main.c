/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adamiens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 13:24:13 by adamiens          #+#    #+#             */
/*   Updated: 2022/12/14 17:36:38 by adamiens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_error(t_args *args, t_file *fd)
{
	perror("Error");
	ft_free_struct(args);
	free(fd);
	exit(1);
}

int	main(int argc, char **argv, char **envp)
{
	t_file	*fd;
	t_args	*args;

	if (argc != 5)
		exit(1);
	args = ft_parsing(argc, argv, envp);
	fd = malloc(sizeof(t_file));
	ft_open_file(argc, argv, fd, 0);
	ft_init_exec(args, fd);
	ft_free_struct(args);
	free(fd);
	return (0);
}
