
#include "headers/push_swap.h"

typedef struct s_node
{
	int	*a;
	int		sizea;
	int	*b;
	int		sizeb;
}	t_node;

void	error(char *error)
{
	char	*to_printf_error_use;

	to_printf_error_use = error;
	ft_printf("Error\n");
	exit(0);
}

void	swap(int **tab, int size)
{
	int	swap;
	
	swap = tab[0][size - 1];
	tab[0][size - 1] = tab[0][size - 2];
	tab[0][size - 2] = swap;
}
void	sa(t_node	*node)
{
	if (node->sizea >= 2)
		swap(&node->a, node->sizea);
	write(1, "sa\n", 3);
}

void	sb(t_node	*node)
{
	if (node->sizeb >= 2)
		swap(&node->b, node->sizeb);
	write(1, "sb\n", 3);
}

void	ss(t_node	*node)
{
	if (node->sizeb >= 2)
		swap(&node->a, node->sizea);
	if (node->sizea >= 2)
		swap(&node->b, node->sizeb);
	write(1, "ss\n", 3);
}

typedef	struct s_comp
{
	int	**from;
	int	**to;
	int	*s_f;
	int	*s_t;
	int *new_from;
	int	*new_to;
	int	moved;
	int	i;
}	t_comp;

void	ready_allcation(int **first,int	**second, int f, int s)
{
	*first = malloc(f * 4);
	if (!first)
		error("allocation failed");
	*second = malloc(s * 4);
	if (!second)
	{
		free(*first);
		error("allocation failed");
	}
}

int	push(t_comp	*comp)
{
	comp->i = 0;
	if (comp->s_f[0] == 0)
		return (-1);
	comp->s_f[0]--;
	comp->s_t[0]++;
	ready_allcation(&comp->new_from , &comp->new_to, (comp->s_f[0]), (comp->s_t[0]));
	comp->moved = comp->from[0][comp->s_f[0]];
	while(comp->i < comp->s_f[0])
	{
	 	comp->new_from[comp->i]	=  comp->from[0][comp->i];
		comp->i++;
	}
	comp->i = 0;
	while (comp->i < comp->s_t[0] - 1)
	{
		comp->new_to[comp->i] = comp->to[0][comp->i];
		comp->i++;
	}
	comp->new_to[comp->i] = comp->moved;
	free(comp->to[0]);
	free(comp->from[0]);
	comp->to[0] = comp->new_to;
	comp->from[0] = comp->new_from;
	return (0);
}

void	pb(t_node *node)
{
	t_comp	comp;

	comp.from = &node->a;
	comp.to = &node->b;
	comp.s_f = &node->sizea;
	comp.s_t = &node->sizeb;
	node->sizeb = comp.s_t[0];
	push(&comp);
	write(1, "pb\n", 3);
}

void	pa(t_node *node)
{
	t_comp	comp;

	comp.from = &node->b;
	comp.to = &node->a;
	comp.s_f = &node->sizeb;
	comp.s_t = &node->sizea;
	node->sizeb = comp.s_f[0];
	push(&comp);
	write(1, "pa\n", 3);
}

void	ready_stacks(char **arg, t_node *node)
{
	int		words;
	int		*a;
	int		i;

	i = 0;
	words = 1;
	while (arg[words])
		words++;
	a = malloc(words * 4);
	if (!a)
		error("could not allocate memory");
	words--;
	while (words>= 0)
	{
		a[i] = ft_atoi(arg[words]);
		words--;
		i++;
	}
	node->a = a;
}

int	check_digit(char **check)
{
	int	words;
	int	num;

	words = 1;
	num = 0;
	while (check[words])
	{
		if (check[words][num] == '-')
			num++;
		while (check[words][num])
		{
			if (ft_isdigit(check[words][num]) != 1)
				error("only Digits");
			num++;
		}
		num = 0;
		words++;
	}
	return (words - 1);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while ((s1[i] || s2[i]))
	{
		if (s1[i] != s2[i])
			return (((unsigned char)s1[i] - (unsigned char)s2[i]));
		i++;
	}
	return (0);
}

void	check_dub(char	**check)
{
	int	i;
	int j;

	i = 1;
	j = 1;
	while (check[i])
	{
		while (check[j])
		{
			if (j == i)
				j++;
			else if (ft_strcmp(check[i],check[j]) == 0)
				error("There is Dublicate");
			else
				j++;
		}
		j = 0;
		i++;
	}
}

void	test(t_node node)
{
	int	i;
	static int j;

	i = 0;
	if (!j)
		j = 1;
	ft_printf("\n=++==++=+==++===[We are in %d oparetion]==++==+++==+====+==++=+\n", j);
	ft_printf("Stack A\n\n");
	while (i < node.sizea)
	{
		ft_printf("%d   ", node.a[i]);
		i++;
	}
	i = 0;
	ft_printf("\n=-=-=-==-=-=-=-=-==-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=\n");
	ft_printf("Stack B\n\n");
	while (i < node.sizeb)
	{
		ft_printf("%d   ", node.b[i]);
		i++;
	}
	j++;
}
void	rotate(int **rot, int	size)
{
	int *new;
	int	*old;
	int	i;
	int	j;

	i = 1;
	j = 0;
	old =  *rot;
	new = malloc(size * 4);
	if (!new)
		error("allocation failed");
	while (i < size)
	{
		new[j] = old[i];
		i++;
		j++;
	}
	new[j] = old[0];
	free(*rot);
	*rot = new;
}

void	rra(t_node *node)
{
	if (node->sizea > 1)
		rotate(&node->a, node->sizea);
	write (1, "rra\n", 4);
}

void	rrb(t_node *node)
{
	if (node->sizeb > 1)
		rotate(&node->b, node->sizeb);
	write (1, "rrb\n", 4);
}

void	rrr(t_node *node)
{
	if (node->sizeb > 1)
		rotate(&node->b, node->sizeb);
	if (node->sizea > 1)
		rotate(&node->a, node->sizea);
	write (1, "rrr\n", 4);
}
void	reverse(int **rot, int	size)
{
	int *new;
	int	*old;
	int	i;
	int	j;

	i = 1;
	j = 0;
	old =  *rot;
	new = malloc(size * 4);
	if (!new)
		error("allocation failed");
	new[0] = old[size -1];
	while (j < size - 1)
	{
		new[i] = old[j];
		i++;
		j++;
	}
	free(*rot);
	*rot = new;
}

void	ra(t_node *node)
{
	if (node->sizea > 1)
		reverse(&node->a, node->sizea);
	write (1, "ra\n", 3);
}
void	rb(t_node *node)
{
	if (node->sizeb > 1)
		reverse(&node->b, node->sizeb);
	write (1, "rb\n", 3);
}

void	rr(t_node *node)
{
	if (node->sizeb > 1)
		reverse(&node->b, node->sizeb);
	if (node->sizea > 1)
		reverse(&node->a, node->sizea);
	write (1, "rr\n", 3);
}

int	check(int **chk, int	size)
{
	int	i;
	int *a;

	i = 0;
	a = *chk;
	while (i < size - 1)
	{
		if (a[i] > a[i + 1])
			i++;
		else
			return (-1);
	}
	i++;
	return (0);
}

int	find_median(int	*n, int	a)
{
	int	total;
	int	*num;
	int	median;
	int	i;

	i = 0;
	num = n;
	total = 0;
	while (i < a)
	{
		total = n[i] + total;
		i++;
	}
	median = total / a;
	return (median);
}

void	Quicksort(t_node	*node)
{
	int	median;
	int	i;

	i = 0;
	median = find_median(node->a, node->sizea);
	ft_printf(">>>%d<<<", median);
	test(*node);
	while (i <= node->sizea)
	{
		if (node->a[0] >= median)
		{ rra(node);ft_printf("\n\n\n{{   ra   }}\n\n");test(*node);}
		else
			{pb(node);ft_printf("{{   pb   }}\n");test(*node);}
		i++;

	}
}

int	main(int argn, char *argv[])
{
	char	**sort;
	t_node	node;
	int i;

	i = 0;
	(node).a = NULL;
	(node).b = NULL;
	node.sizeb = 0;
	node.sizea = 0;
	if (argn > 2)
	{
		sort = argv;
		node.sizea = check_digit(sort);
		check_dub(sort);
		ready_stacks(sort, &node);
		if (check(&node.a, node.sizea) == 0)
			return (0);
		Quicksort(&node);
	}
	else
		return (0);
}
