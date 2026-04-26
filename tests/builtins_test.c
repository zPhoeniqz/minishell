/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_test.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbindl <pbindl@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 17:25:44 by pbindl            #+#    #+#             */
/*   Updated: 2026/03/26 20:02:53 by pbindl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/builtins.h"
#include "../inc/path.h"
#include "../inc/utils.h"
#include "../libft/libft.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static int	pwd_test(void)
{
	cwd_change("/home");
	printf("Testing 'pwd'... Expecting '/home'\n");
	pwd();
	return (0);
}

static bool	check_env_var(char *varname, char *value)
{
	char	*val;

	val = getenv(varname);
	if (!val || ft_strncmp(val, value, 2) != 0)
	{
		printf("failed\n");
		printf("export failed creating a variable: %s != %s\n", val, value);
		return (false);
	}
	printf("successful\n");
	return (true);
}

static int	export_unset_test(void)
{
	char		*val;
	static char	*stmt1 = "ANOTHER_TEST=42";
	static char	*stmt2 = "ANOTHER_TEST=other_value";
	char		**stmt_multiple;

	stmt_multiple = ft_split("TEST1=hello;TEST2=world;73573=invalid", ';');
	printf("Current state of var: %s\n", getenv("ANOTHER_TEST"));
	printf("Testing 'export'...\n");
	printf("Test 1... ");
	export(1, &stmt1);
	if (!check_env_var("ANOTHER_TEST", "42"))
		return (1);
	printf("Test 2... ");
	export(1, &stmt2);
	if (!check_env_var("ANOTHER_TEST", "other_value"))
		return (1);
	printf("Test 3... ");
	export(3, stmt_multiple);
	arr_destroy((void **)stmt_multiple);
	if (!check_env_var("TEST1", "hello") || !check_env_var("TEST2", "world"))
		return (1);
	if ((val = getenv("73573")))
	{
		printf("Fail: Allowed invalid variable to be assigned:'73573'= %s\n",
			val);
		return (1);
	}
	printf("Testing 'unset'...\n");
	printf("Test 1...");
	export(1, &stmt1);
	unset("ANOTHER_TEST");
	val = getenv("ANOTHER_TEST");
	if (val)
	{
		printf("failed.\n");
		printf("State of %s: %s\n", "ANOTHER_TEST", val);
		return (1);
	}
	printf("successful.\n");
	return (0);
}

int	builtins_test(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	pwd_test();
	export_unset_test();
	return (0);
}
