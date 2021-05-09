#include <stdio.h>
#include <stdlib.h>
#include <mulib/macros.h>
#include <mulib/vec.h>

#include <readline/history.h>
#include <readline/readline.h>

#include "reader.h"

void 
repl(void)
{
    char *input;

    for(;;)
    {
        input = readline("\033[1m\033[31m>\033[33m>\033[32m>\033[0m ");

        if (input == NULL)
        {
            clear_history();
            free(input);
            
            return;
        }
        else if (*input)
        {
            add_history(input);
        }

        free(input);
    }
}

int 
main(int argc, char *argv[])
{
    UNUSED(argv);

    if (argc == 1)
    {
        repl();
    }

    return 0;
}