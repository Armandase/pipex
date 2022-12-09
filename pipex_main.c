/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adamiens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 13:24:13 by adamiens          #+#    #+#             */
/*   Updated: 2022/12/06 15:24:45 by adamiens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_file	*fd;
	t_args	*args;

	if (argc < 5)
		exit(1);
	//if (ft_strncmp(argv[1], "here_doc", 9) == 0)
	//	ft_heredoc(args, fd);
	args = ft_parsing(argc, argv, envp);
	fd = malloc(sizeof(t_file));
	ft_open_file(argc, argv, fd);
	ft_get_exec(args, fd);
	ft_free_struct(args);
	free(fd);
	return (0);
}
