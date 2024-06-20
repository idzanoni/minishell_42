/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izanoni <izanoni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 19:18:17 by mgonzaga          #+#    #+#             */
/*   Updated: 2024/06/20 15:34:06 by izanoni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	bt_echo(char **splited_prompt)
{
    int count;
    int n;
    int val;

    count = 1;
    n = 0;
    val = 0;
    while(splited_prompt[count] != NULL)
    {
        if(splited_prompt[count][0] == '-')
        {
            if(splited_prompt[count][1] == 'n' && val == 0)
            {    
                count++;
                n++;
            }
            else
            {
                ft_putstr_fd(splited_prompt[count], 1);
                count++;   
                val++;
            }
        }
        else
        {
            ft_putstr_fd(splited_prompt[count], 1);
            count++;
			val++;  
        }
    }
    if(n == 0)
        write(1, "\n", 1);
}
