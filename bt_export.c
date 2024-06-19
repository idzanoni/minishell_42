/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgonzaga <mgonzaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 12:37:07 by mgonzaga          #+#    #+#             */
/*   Updated: 2024/06/19 14:50:09 by mgonzaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	bt_export(char **splited_prompt, t_list	*envp)
{

    int	count;
	int i;
	t_list	*local;

	count = 1;
	i = 1;
    if(splited_prompt[1] == NULL)
    {
		while (envp != NULL)
		{
			ft_putstr_fd("declare -x ", 1);
			ft_putendl_fd(envp->content, 1);
			envp = envp->next;
		}
    }
    else
    {
        while(splited_prompt[count] != NULL)
		{
			if(ft_isalpha(splited_prompt[count][0]) == 1 || splited_prompt[count][0] == '_')
			{
				while(splited_prompt[count][i] != '\0' && splited_prompt[count][i] != '=')
				{
					if(ft_isalnum(splited_prompt[count][i]) == 1 || splited_prompt[count][i] == '_')
                    {   
					    i++;
					}
					else
                    {
                        ft_putstr_fd("export: not a valid identifier", 1);
                        break;
                    }
                }
                if(valid_var(envp, splited_prompt[count]) == 1)
				{
					if(splited_prompt[count][i] == '=')
					{
						local = localize_envp(envp, splited_prompt[count]);
						free(local->content);
						local->content = ft_strdup(splited_prompt[count]);
					}
				}
				else
				{
					ft_lstadd_back(&envp, ft_lstnew(ft_strdup(splited_prompt[count])));

				}
			}
			else
				ft_putstr_fd("export: splited_pront[count]: not a valid identifier", 1);
            count++;
		}
	}
}


size_t	ft_strlen_2(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0' && s[i] != '=')
		i++;
	return (i);
}


int valid_var(t_list *envp, char *var) //grep
{
	int		value;
	int		len_var;
	t_list	*tmp;

	len_var = ft_strlen_2(var);
	tmp = envp;
	while (tmp != NULL)
	{
		value = ft_memcmp (tmp->content, var, len_var);
		if (value == 0)
            return(1);
		tmp = tmp->next;
	}
	return(0);
}

t_list *localize_envp(t_list *envp, char *var) //grep
{
	int		value;
	int		len_var;
	t_list	*tmp;

	len_var = ft_strlen_2(var);
	tmp = envp;
	while (tmp != NULL)
	{
		value = ft_memcmp (tmp->content, var, len_var);
		if (value == 0)
            return(tmp);
		tmp = tmp->next;
	}
	return(NULL);
}
