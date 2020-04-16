#include "ush.h"

int mx_streams(t_st *st, char **tokens) {
    //Function replace for ~ $ alias and run if `` $() and for <>| make psevdoterm ()
    //mx_replace_tok(st, tokens);
    //mx_if_


    for (int i = 0; tokens[i] != NULL; i++) {

//        **input = mx_streams_in(tokens[i]); // возвращает аргументы после знака < с этих аргуметов потом считывается
//        **output = mx_streams_out(tokens[i]); // >
//        **pipes = mx_streams_pipes(tokens[i]); // |

//      if (tokens[i][0] == '(' || tokens[i][0] == ')' || tokens[i][0] == '$'
//            || tokens[i][0] == '<' || tokens[i][0] == '>'
//            || tokens[i][0] == '`' || tokens[i][0] == '|') {
//            mx_
//        }
        printf("%s\n", tokens[i]);
    }


    return 1;
}
