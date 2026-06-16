
#include "libft.h"

t_list	*sort_list(t_list* lst)
{
	t_list	*p1 = lst, *p2;
	int		tmp;

	while (p1->next)
	{
		p2 = p1->next;
		while (p2)
		{
			printf("%d, %d\n", p1->x, p2->x);
			if (p1->x > p2->x)
			{
				tmp = p1->x;
				p1->x = p2->x;
				p2->x = tmp;
			}
			p2 = p2->next;
		}
		p1 = p1->next;
	}
	return (lst);
}