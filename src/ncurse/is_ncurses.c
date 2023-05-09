/*
** EPITECH PROJECT, 2023
** 42sh_repo
** File description:
** No file there , just an epitech header example .
*/

int ncurses_on_off(int on_off)
{
    static int ncurses = 0;
    if (on_off != -1 && (on_off == 0 || on_off == 1))
        ncurses = on_off;
    return ncurses;
}

// This function is used to know if the ncurses mode is on or off.
int is_ncurses(void)
{
    return ncurses_on_off(-1);
}
