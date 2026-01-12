/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whuth <whuth@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 15:51:39 by whuth             #+#    #+#             */
/*   Updated: 2026/01/12 15:55:30 by whuth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(void)
{
	const char *pwd;
	const char *env_pwd;

	pwd = "PWD";
	env_pwd = getenv(pwd);
	if (env_pwd)
		ft_printf("%s\n", env_pwd);
}
