/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_test.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbindl <pbindl@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 17:25:44 by pbindl            #+#    #+#             */
/*   Updated: 2026/03/26 18:00:12 by pbindl           ###   ########.fr       */
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
	char		*val;
	static char	*value1 = "42";
	static char	*value2 = "other_value";
	static char	*varname = "ANOTHER_TEST";

	printf("Current state of var: %s\n", getenv("ANOTHER_TEST"));
	printf("Testing 'export'...\n");
	printf("Test 1... ");
	export(&varname, &value1, 1);
	val = getenv("ANOTHER_TEST");
	if (!val || ft_strncmp(val, "42", 2) != 0)
	{
		printf("failed\n");
		printf("export failed creating a variable: %s != 42\n", val);
		return (1);
	}
	printf("successfull\n");
	printf("Test 2... ");
	export(&varname, &value2, 1);
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
