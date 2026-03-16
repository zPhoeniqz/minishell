/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entrypoint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbindl <pbindl@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 17:34:02 by pbindl            #+#    #+#             */
/*   Updated: 2026/03/16 17:35:07 by pbindl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/testing.h"

int	main(int argc, char **argv, char **envp)
{
	builtins_test(argc, argv, envp);
}
