void	ft_heredoc(char **argv, int argc)
{
	char	*cmp;
	char	*buffer;

	if (argc <= 2)
	{
		write(2, "Error : missing parameters", 27);
		exit(1);
	}
	cmp = ft_strdup(argv[2]);
	buffer = ft_calloc(1, 1);
	while (ft_strncmp(cmp, buffer) !=  0)
	{
		free(buffer);
		buffer = get_next_line(0);
		args = ft_parsing(argc, argv, envp);
		fd = malloc(sizeof(t_file));
		ft_open_file(argc, argv, fd);
		ft_get_exec(args, fd);
		ft_free_struct(args);
		free(fd);
	}

}
