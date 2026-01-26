#ifndef LOCALVAR_H
# define LOCALVAR_H

# include <stdbool.h>
# include <stdio.h>

typedef struct s_lv
{
	bool		dq;
	char		*key;
	char		*value;
	struct s_lv	*next;
}	t_lv;

#endif
