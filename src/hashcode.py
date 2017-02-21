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


def make_coords(max_x: int, max_y: int):
    return ((x, y) for y in range(max_y) for x in range(max_x))


def counter(tab_ref, tab_counter, forms, meta):
    """ Make the counter map.

    The counter map help to see the avaibility of each case.

    Args:
        tab_ref: the pizza tab
        tab_counter: tab initlized at 0
        forms: the valid forms
        meta: mate information of the game

    Returns:
        The counter_tab and the valid slices.
    """
    saved_forms = list()
    tab_x, tab_y = meta['cols'], meta['rows']
    tab_coord = (tab_x, tab_y)
    min_ing = meta['min_ing']

    for x, y in make_coords(tab_x, tab_y):
        form_filter = lambda f: is_valid((x,y), f, min_ing, tab_ref, tab_coord)
        for form_x, form_y in filter(form_filter, forms):
            saved_forms.append((y, x, y + form_y - 1, x + form_x - 1))
            for pos_x, pos_y in make_coords(form_x, form_y):
                tab_counter[pos_y + y][pos_x + x] += 1

    # print the result
    for line in tab_counter:
        print(line)

    return tab_counter, saved_forms


def score_slice(tab_counter, _slice):
    min_y, min_x, max_y, max_x = _slice
    index = 0
    res = 0
    for x, y in ( (x, y) for x in range(min_x, max_x + 1) for y in range(min_y, max_y + 1) ):
        res += tab_counter[y][x]
        index += 1
    return {'score': res / index, 'slice': _slice}


def sort_slices(tab_counter, slices):
    return sorted(map(lambda x: score_slice(tab_counter, x), slices), key = lambda x: x['score'])


def case_in_slice(case, _slice):
    x, y = case
    min_y, min_x, max_y, max_x = _slice
    return not (min_x <= x <= max_x and min_y <= y <= max_y)

def list_slices(sorted_slices):
    slices = sorted_slices.copy()
    res = list()
    while slices:
        tmp = slices.pop(0)
        res.append(tmp)
        min_y, min_x, max_y, max_x = tmp['slice']
        for x, y in [ (x, y) for x in range(min_x, max_x + 1) for y in range(min_y, max_y + 1) ]:
            slices = list(filter(lambda item: case_in_slice((x, y),
                item['slice']), slices))
    return res


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
    tab_counter, saved_forms = counter(tab, [ [ 0 for x in range(meta['cols']) ] for y in
        range(meta['rows']) ], forms, meta)
    print('')
    print('#   SLICES   #')
    print('count:', len(saved_forms))
    for form in saved_forms:
        print(form)
    print('')
    print('#   SORTED SLICES   #')
    print('count:', len(saved_forms))
    sorted_slices = sort_slices(tab_counter, saved_forms)
    for form in sorted_slices:
        print(form)
    res = list_slices(sorted_slices)
    print('')
    print('#   FINAL SLICE   #')
    print('len slice:', len(res))
    for _slice in res:
        print(_slice['slice'])
