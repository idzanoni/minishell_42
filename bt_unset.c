/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgonzaga <mgonzaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 15:59:21 by izanoni           #+#    #+#             */
/*   Updated: 2024/07/11 19:12:09 by mgonzaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *bt_unset(t_minishell *s_minishell)
{
	int i = 1;
	while (s_minishell->splited_prompt[i] != NULL)
	{
		if (check_name(s_minishell->splited_prompt[i]) != 0)
		{
			print_error(s_minishell->splited_prompt[i], ": not a valid identifier\n");
		}
		else
		{
			process_prompt(s_minishell->splited_prompt[i], &s_minishell->envp);
		}
		i++;
	}
	return (0);
}

void process_prompt(char *prompt, t_env_list **envp)
{
	int len_var = ft_strlen(prompt);
	t_env_list *temp_node = *envp;
	while (temp_node != NULL)
	{
		if (should_remove_node(temp_node, prompt, len_var))
		{
			delnode(envp, temp_node);
			break;
		}
		temp_node = temp_node->next;
	}
}

int should_remove_node(t_env_list *node, char *prompt, int len_var)
{
	if ((ft_strnstr(node->content, prompt, len_var)) != NULL)
	{
		if ((node->content)[len_var] == '=' || (node->content)[len_var] == '\0')
		{
			return (1);
		}
	}
	return (0);
}

/* char *bt_unset(char **splited_prompt, t_env_list **envp)
{
	int i = 1;
	while (splited_prompt[i] != NULL)
	{
		if (check_name(splited_prompt[i]) != 0)
		{
			print_error(splited_prompt[i], ": not a valid identifier\n");
		}
		else
		{
			process_prompt(splited_prompt[i], envp);
		}
		i++;
	}
	return (0);
}

void process_prompt(char *prompt, t_env_list **envp)
{
	int len_var = ft_strlen(prompt);
	t_env_list *temp_node = *envp;
	while (temp_node != NULL)
	{
		if (should_remove_node(temp_node, prompt, len_var))
		{
			delnode(envp, temp_node);
			break;
		}
		temp_node = temp_node->next;
	}
}

int should_remove_node(t_env_list *node, char *prompt, int len_var)
{
	if ((ft_strnstr(node->content, prompt, len_var)) != NULL)
	{
		if ((node->content)[len_var] == '=' || (node->content)[len_var] == '\0')
		{
			return (1);
		}
	}
	return (0);
} */

/* char	*bt_unset(char **splited_prompt, t_env_list **envp)
{
	int			i;
	int			len_var;
	t_env_list	*temp_node;

	i = 1;
	while (splited_prompt[i] != NULL)
	{
		if (check_name(splited_prompt[i]) != 0)
		{
			print_error(splited_prompt[i], ": not a valid identifier\n");
			i++;
			continue ;
		}
		len_var = ft_strlen(splited_prompt[i]);
		temp_node = *envp;
		while (temp_node != NULL)
		{
			if ((ft_strnstr(temp_node->content, splited_prompt[i], len_var)) != NULL)
			{
				if ((temp_node->content)[len_var] == '='
				|| (temp_node->content)[len_var] == '\0')
				{
					delnode(envp, temp_node);
					break ;
				}
			}
			temp_node = temp_node->next;
		}
		i++;
	}
	return (0);
} */

void	delnode(t_env_list	**envp, t_env_list	*node)
{
	t_env_list	*temp;

	temp = *envp;
	if (node == *envp)
	{
		(*envp) = (*envp)->next;
		free (node->content);
		free (node);
	}
	else
	{
		while (temp != NULL && temp->next != node)
			temp = temp->next;
		if (temp == NULL)
			return ;
		else
		{
			temp->next = node->next;
			free (node->content);
			free (node);
		}
	}
}


int	check_name(char *splited_prompt)
{
	int	i;

	i = 0;
	if (ft_isdigit(splited_prompt[i]) == 1)
		return (1);
	while (splited_prompt[i] != '\0')
	{
		if (ft_isalnum(splited_prompt[i]) != 1 && splited_prompt[i] != '_')
			return (1);
		i++;
	}
	return (0);
}


