#include <string>
#include <vector>
#include <ctype.h>
#include "token.hpp"
#include "tokenizer.hpp"

void cuttle::tokenize(
    const std::string &query,
    tokens_t& tokens,
    unsigned short line
) {
    using namespace cuttle;

    token_type type = token_type::unknown;
    unsigned short i_start = 0, line_start = line, i_line_start = 0;
    std::string acc = "";
    std::string str = query + '\n';

    for (register unsigned i = 0; i < str.length(); ++i) {
        if (str[i] == ' ' || str[i] == '\n'
            || (type == token_type::number && !isdigit(str[i]))
            || (type == token_type::atom && isdigit(str[i]))
        ) {
            if (acc != "") {
                tokens.push_back(token_t {
                    (token_type) type, acc, line_start, ++i_start
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
            type = token_type::unknown;
        } else {
            if (acc == "") {
                type = isdigit(str[i]) ? token_type::number : token_type::atom;
            }
            acc += str[i];
        }
    }
}