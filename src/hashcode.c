#include <stdio.h>
#include <stdlib.>

typedef struct		s_slice
{
	struct s_slice	*next;
	unsigned int	min_x;
	unsigned int	min_y;
	unsigned int	max_x;
	unsigned int	max_y;
	float			mean;
}					t_slice;

typedef struct		s_meta
{
	unsigned int	rows;
	unsigned int	cols;
	unsigned int	min_ing;
	unsigned int	max_area
	char			**tab;
	unsigned int	**counter_tab;
}					t_meta;

typedef struct		s_form
{
	struct s_form	*next;
	unsigned int	x;
	unsigned int	y;
}					t_form;

typedef struct		s_coord
{
	unsigned int	x;
	unsigned int	y;
}					t_coord;

typedef struct		s_list
{
	struct s_list	*next;
}					t_list;

void	*ft_memalloc(size_t size)
{
	char	*ptr;
	int		i;

	ptr = malloc(size);
	for(i = 0 ; i < size ; i++)
		ptr[i] = 0;
	return (ptr);
}

t_meta	*parsing(char *filename)
{
	int		index;
	FILE	*fd;
	t_meta	*meta;

	fd = fopen(filename, "r");
	meta = malloc(sizeof(t_meta));
	fscanf(fd, "%d %d %d %d", &meta->rows, &meta->cols, &meta->min_ing, &meta->max_area);
	meta->tab = malloc(sizeof(char *) * meta->rows);
	meta->counter_tab = malloc(sizeof(unsigned int *) * meta->rows);
	for (index = 0 ; index < meta->rows ; index++)
	{
		meta->counter_tab[index] = ft_memalloc(sizeof(unsigned int) * meta->cols);
		meta->tab[index] = malloc(sizeof(char) * meta->cols);
		fgets(meta->tab[index], meta->cols, fd);
	}
	return meta;
}

t_form	*make_form(unsigned int x, unsigned int y)
{
	t_form	*form;

	form = malloc(sizeof(t_form));
	form->x = x;
	form->y = y;
	return (form);
}

t_form *get_form(unsigned int min_area, unsigned int max_area)
{
	unsigned int	x;
	unsigned int	y;
	unsigned int	area;
	t_form			*forms;
	t_form			*tmp;

	forms = make_form(0, 0);
	tmp = forms;
	for (y = 0 ; y < max_area ; y++)
	{
		for (x = 0 ; x < max_area ; l++)
		{
			area = x * y
			if (min_area > area || max_area < area)
				continue ;
			tmp->next = make_form(x, y);
			tmp = tmp->next:
		}
	}
	tmp->next = NULL;
	tmp = forms->next;
	free(forms);
	return(tmp);
}

char	is_good_slice(t_coord pos, t_form form, t_meta *meta)
{
	int	mushrooms, tomatos = 0;
	t_coord	tmp;

	if (pos.x + form.x > meta->rows || pos.y + form.y > meta->cols)
		return (0);
	for (tmp.y = 0 ; tmp.y < form.y ; tmp.y++)
	{
		for (tmp.x = 0 ; tmp.x < form.x ; tmp.x++)
		{
			if (meta->tab[pos.y + tmp.y] == 'M')
				mushrooms++;
			else
				tomatos++;
			if (mushrooms >= meta.min_ing && tomatos >= meta.min_ing)
				return (1);
		}
	}
	return (0);
}

void	*filter(char (*fn)(void *), t_list *lst)
{
	t_list	*res, *tmp = NULL;

	while (lst && !fn(lst))
		lst = lst->next;
	if (!(res = lst))
		return (NULL);
	tmp = res;
	while ((lst = lst->next))
	{
		if (fn(lst))
		{
			tmp->next = lst;
			tmp = tmp->next;
		}
	}
	return (res);
}

void	counter(t_meta *meta, t_form *forms)
{

}
