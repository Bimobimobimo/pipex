/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcollong <lcollong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 15:49:46 by lcollong          #+#    #+#             */
/*   Updated: 2024/12/20 17:46:10 by lcollong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	execution(t_pipex *pipex, char **path_file, char *cmd_path, int j)
{
	if (access(cmd_path, X_OK) == 0)
	{
		execve(cmd_path, pipex->tab[pipex->cmd_i], pipex->env);
		free(cmd_path);
		free_tab(path_file, j + 1);
		error_exit("Execution error\n");
	}
	free(cmd_path);
}

void	get_command_path(t_pipex *pipex, char **path_file, char *path)
{
	int		j;
	char	*tmp_path;
	char	*cmd_path;

	j = 0;
	tmp_path = NULL;
	cmd_path = NULL;
	while (path_file[j])
	{
		tmp_path = ft_strjoin(path_file[j], "/");
		if (!tmp_path)
			return (free_tab(path_file, j), error_exit("Malloc error\n"));
		cmd_path = ft_strjoin(tmp_path, pipex->tab[pipex->cmd_i]);
		free(tmp_path);
		if (!cmd_path)
			return (free_tab(path_file, j), error_exit("Malloc error\n"));
		execution(pipex, path_file, cmd_path, j);
		j++;
	}
	free(path);
	free_tab(path_file);
	error_exit("Command not found in PATH\n");
}

void	get_path_1(t_pipex *pipex, char **env)
{
	char	*path_env;
	int		k;
	
	k = 0;
	path_env = NULL;
	while (env[k])
	{
		if (ft_strncmp(env[k], "PATH=", 5) == 0)
		{
			path_env = env[k] + 5;
			pipex->env = path_env;
			break;
		}
		k++;
	}
	if (!path_env)
		error_exit("Error : PATH not found\n");
	get_path_2(pipex, env, path_env);
}

void	get_path_2(t_pipex *pipex, char **env, char *path_env)
{
	char	*path;
	char	**path_file;

	path_file = NULL;
	path = ft_strdup(path_env);
	if (!path)
		error_exit("Malloc error\n");
	path_file = ft_split(path, ":");
	if (!path_file)
		return(free(path), error_exit("Malloc error\n"));
	get_command_path(pipex, path_file, path);
}
