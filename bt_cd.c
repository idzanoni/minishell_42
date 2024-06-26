/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgonzaga <mgonzaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 19:19:29 by mgonzaga          #+#    #+#             */
/*   Updated: 2024/06/27 13:48:15 by mgonzaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	bt_cd(char **splited_prompt, t_env_list *envp)
{
	char	*path;
	char	*new_path;

	path = getcwd(NULL, 0);
	if (splited_prompt[1] == NULL)
	{
		new_path = return_value(envp, "HOME");
		if (!new_path)
		{
			print_error("cd", ": HOME not set");
			return (1);
		}
		if (chdir(new_path) < 0)
		{
			perror("cd error");
			return (1);
		}
		new_path = getcwd(NULL, 0);
	}
	if (splited_prompt[2])
	{
		print_error ("cd", ": too many arguments");
		return (1);
	}
	if (splited_prompt[1] != NULL)
	{
		if (chdir(splited_prompt[1]) < 0)
		{
			perror("cd error");
			return (1);
		}
		new_path = getcwd(NULL, 0);
	}
	update_wd(new_path, envp, path);
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
