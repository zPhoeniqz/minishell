/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entrypoint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbindl <pbindl@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 17:34:02 by pbindl            #+#    #+#             */
/*   Updated: 2026/04/10 18:43:43 by pbindl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/testing.h"
#include "../inc/utils.h"
#include <stdio.h>

extern char	**environ;

int	main(int argc, char **argv)
{
	builtins_test(argc, argv);
}
