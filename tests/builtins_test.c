/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_test.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbindl <pbindl@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 17:25:44 by pbindl            #+#    #+#             */
/*   Updated: 2026/03/16 19:29:01 by pbindl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/builtins.h"
#include "../inc/path.h"
#include <stdio.h>

int	builtins_test(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	(void)envp;
	cwd_change("/home");
	printf("Testing 'pwd'... Expecting '/home'\n");
	pwd();
	return (0);
}
