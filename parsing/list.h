#ifndef SORT_LIST_H
# define SORT_LIST_H

# include <stdlib.h>
# include <stdio.h>

typedef struct  s_list
{
	int				x;
	int				sorted_index;
	struct s_list	*next;
}			t_list;

#endif