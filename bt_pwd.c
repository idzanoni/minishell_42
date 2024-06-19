/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgonzaga <mgonzaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 19:17:20 by mgonzaga          #+#    #+#             */
/*   Updated: 2024/06/18 19:17:51 by mgonzaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishel.h"

void    bt_pwd(void)
{
    char    *path;
    
    path = getcwd(NULL, 0);
    ft_putstr_fd(path, 1);
    ft_putstr_fd("\n", 1);
    free(path);
}
