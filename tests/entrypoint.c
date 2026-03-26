/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entrypoint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbindl <pbindl@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 17:34:02 by pbindl            #+#    #+#             */
/*   Updated: 2026/03/26 17:33:37 by pbindl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/testing.h"
#include "../inc/utils.h"
#include <stdio.h>

extern char	**environ;

int	main(int argc, char **argv)
{
	ft_env_make_individual_alloc(environ);
	builtins_test(argc, argv);
	ft_env_destroy(environ);
}
