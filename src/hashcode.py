import sys
import os


def parsing(filename: str):
    """ Parse the input file.

    Args:
        filename: file to parse

    Returns:
        meta data and tab
    """
    with open(filename) as f:
        rows, cols, min_ing, max_area = [ int(v) for v in f.readline().split(' ')]
        tab = [ [ cell for cell in line.strip() ] for line in f.readlines() ]
    meta = {'rows': rows, 'cols': cols,
            'min_ing': min_ing, 'max_area': max_area}
    return meta, tab


def get_forms(min_area: int, max_area: int):
    """ Make all the form of slice.

    Args:
        min_area: the minimal area required
        max_area: the maximal area possible

    Returns:
        list of forms
    """
    forms = [ (x, y) for y in range(1, max_area + 1)
                        for x in range(1, max_area + 1)
                        if min_area <= x * y <= max_area ]
    return forms


def is_valid(pos, form, min_ing, tab, size):
    pos_x, pos_y = pos
    tab_x, tab_y = size
    form_x, form_y = form
    m, t = (0, 0)
    if pos_x + form_x > tab_x or pos_y + form_y > tab_y :
        return 0
    for x in range(form_x):
        for y in range(form_y):
            ingredient = tab[pos_y + y][pos_x + x]
            if ingredient == 'M':
                m += 1
            elif ingredient == 'T':
                t += 1
            else:
                raise ValueError
            if m >= min_ing and t >= min_ing:
                return 1
    return 0


def counter(tab_ref, tab_counter, forms, meta):
    tab_x, tab_y = meta['cols'], meta['rows']
    for x, y in [(x, y) for y in range(tab_y) for x in range(tab_x)]:
        for form in forms:
            form_x, form_y = form
            if not is_valid((x,y), form, meta['min_ing'], tab_ref,
                    (meta['cols'], meta['rows'])):
                continue
            for pos_x, pos_y in [ (pos_x, pos_y) for pos_x in range(form_x) for
                    pos_y in range(form_y)]:
                tab_counter[pos_y + y][pos_x + x] += 1
    for line in tab_counter:
        print(line)
    return tab_counter


if __name__ == '__main__':
    if len(sys.argv) != 2:
        print('usage: python3 {:s} file'.format(sys.argv[0]))
        exit(os.EX_DATAERR)
    meta, tab = parsing(sys.argv[1])
    forms = get_forms(2 * meta['min_ing'], meta['max_area'])
    print('#   META   #')
    print(meta)
    print('')
    print('#   FROMS   #')
    for form in forms:
        print(form)
    print('')
    print('#   TAB   #')
    for lines in tab:
        print(lines)
    print('')
    print('#   COUNTER   #')
    counter(tab, [ [ 0 for x in range(meta['cols']) ] for y in
        range(meta['rows']) ], forms, meta)


