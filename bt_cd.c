/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izanoni <izanoni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 19:19:29 by mgonzaga          #+#    #+#             */
/*   Updated: 2024/07/17 20:12:48 by izanoni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	bt_cd(t_minishell *s_minishell)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (s_minishell->current_command[1] == NULL)
	{
		change_to_home_directory(s_minishell->envp, path);
		return ;
	}
	if (s_minishell->current_command[2])
	{
		write(2, "cd: too many arguments\n", 24);
		return ;
	}
	change_directory(s_minishell->current_command[1], s_minishell->envp, path);
}

int	change_to_home_directory(t_env_list *envp, char *old_path)
{
	char	*new_path;

	new_path = return_value(envp, "HOME");
	if (!new_path)
	{
		write(2, "cd: HOME not set\n", 18);
		return (1);
	}
	if (chdir(new_path) < 0)
	{
		perror("cd error");
		return (1);
	}
	new_path = getcwd(NULL, 0);
	update_wd(new_path, envp, old_path);
	return (0);
}

int	change_directory(char *dir, t_env_list *envp, char *old_path)
{
	char	*new_path;

	if (chdir(dir) < 0)
	{
		perror("cd error");
		return (1);
	}
	new_path = getcwd(NULL, 0);
	update_wd(new_path, envp, old_path);
	return (0);
}

void	update_wd(char *new_path, t_env_list *envp, char *old_path)
{
	t_env_list	*temp_pwd;
	char		*old_pwd;
	char		*new_pwd;

	temp_pwd = localize_envp(envp, "OLDPWD");
	if (temp_pwd)
	{
		old_pwd = ft_strjoin("OLDPWD=", old_path);
		free (temp_pwd->content);
		temp_pwd->content = old_pwd;
	}
	temp_pwd = localize_envp(envp, "PWD");
	if (temp_pwd)
	{
		new_pwd = ft_strjoin("PWD=", new_path);
		free (temp_pwd->content);
		temp_pwd->content = new_pwd;
	}
}
