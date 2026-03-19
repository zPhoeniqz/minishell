/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_test.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbindl <pbindl@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 17:25:44 by pbindl            #+#    #+#             */
/*   Updated: 2026/03/19 18:53:36 by pbindl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/builtins.h"
#include "../inc/path.h"
#include "../libft/libft.h"
#include <stdio.h>
#include <stdlib.h>

static int	pwd_test(void)
{
	cwd_change("/home");
	printf("Testing 'pwd'... Expecting '/home'\n");
	pwd();
	return (0);
}

static int	export_test(void)
{
	char	*val;

	printf("Current state of var: %s\n", getenv("ANOTHER_TEST"));
	printf("Testing 'export'...\n");
	printf("Test 1... ");
	export("ANOTHER_TEST", "42");
	val = getenv("ANOTHER_TEST");
	if (!val || ft_strncmp(val, "42", 2) != 0)
	{
		printf("failed\n");
		printf("export failed creating a variable: %s != 42\n", val);
		return (1);
	}
	printf("successfull\n");
	printf("Test 2... ");
	export("ANOTHER_TEST", "other_value");
	val = getenv("ANOTHER_TEST");
	if (!val || ft_strncmp(val, "other_value", 11) != 0)
	{
		printf("failed\n");
		printf("export failed setting a new value: %s != other_value\n", val);
		return (1);
	}
	printf("successfull\n");
	return (0);
}

int	builtins_test(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	pwd_test();
	export_test();
	return (0);
}
