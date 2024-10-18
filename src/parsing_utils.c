#include "cub.h"

bool    is_valid_char(char c)
{
    return (c == '0' || c == '1' || c == 'N' || \
			c == 'S' || c == 'E' || c == 'W' || \
			c == '\n' || c == ' ' || c == 9);
}
