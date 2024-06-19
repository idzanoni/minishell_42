/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgonzaga <mgonzaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 19:19:29 by mgonzaga          #+#    #+#             */
/*   Updated: 2024/06/19 20:02:55 by mgonzaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*bt_cd(char **splited_prompt, t_list *envp)
{
	char	*path;
	char	*tempwd;
	char	*new_path;


	path = getcwd(NULL, 0);
	if (splited_prompt[1] == NULL)
	{
		new_path = return_value(envp, "HOME");
		if (!new_path)
			print_error("cd", ": HOME not set");
			return();
		if (chdir(new_path) < 0)
			perror("cd error");
			return();

	}
	if (splited_prompt[2])
	{
		print_error ("cd", ": too many arguments")
		return ;
	}
}

void	update_wd(char *new_path , t_list *envp)
{
	
}
//chdir
//getcwd
//perror

