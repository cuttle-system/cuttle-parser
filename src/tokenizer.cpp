#include <string>
#include <vector>
#include <ctype.h>
#include "token.hpp"
#include "tokenizer.hpp"

void husky::tokenize(
    const std::string &query,
    std::vector<token_t *>& tokens,
    unsigned short line
) {
    using namespace husky;

    int token_type = -1;
    unsigned short i_start = 0, line_start = line, i_line_start = 0;
    std::string acc = "";
    std::string str = query + '\n';

    for (register unsigned i = 0; i < str.length(); ++i) {
        if (str[i] == ' ' || str[i] == '\n'
            || (token_type == NUMBER_TOKEN && !isdigit(str[i]))
            || (token_type == ATOM_TOKEN && isdigit(str[i]))
        ) {
            if (acc != "") {
                tokens.push_back(new token_t {
                    (enum token_type) token_type, acc, line_start, ++i_start
                });
                acc = "";
                if (!(str[i] == ' ' || str[i] == '\n')) --i;
            }
            if (str[i] == '\n') {
                i_line_start = i + 1;
                ++line;
            }
            i_start = i - i_line_start + 1;
            line_start = line;
            token_type = -1;
        } else {
            if (acc == "") {
                token_type = isdigit(str[i]) ? NUMBER_TOKEN : ATOM_TOKEN;
            }
            acc += str[i];
        }
    }
}