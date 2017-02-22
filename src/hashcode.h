#ifndef HASHCODE_H
# define HASHCODE_H

# include <stdio.h>
# include <stdlib.>
# include <stdarg.h>

typedef struct		s_coord
{
	unsigned int	x;
	unsigned int	y;
}					t_coord;

typedef struct		s_slice
{
	struct s_slice	*next;
	t_coord			min;
	t_coord			max;
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

typedef struct		s_list
{
	struct s_list	*next;
}					t_list;


#endif
