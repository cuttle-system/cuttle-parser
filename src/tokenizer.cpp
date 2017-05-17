#include <string>
#include <list>
#include <memory>
#include "token.hpp"
#include "string_token.hpp"
#include "atom_token.hpp"
#include "tokenizer.hpp"

using namespace husky;

void Tokenizer::Tokenize(
    const std::string &query, std::list<std::unique_ptr<Token>>& tokens
) {
    unsigned line = 1;
    unsigned iStart = 0;
    unsigned lineStart = 1;
    unsigned iLineStart = 0;
    std::string acc = "";
    std::string str = query + '\n';

    for (register unsigned i = 0; i < str.length(); ++i) {
        if (str[i] == ' ' || str[i] == '\n') {
            if (acc != "") {
                tokens.push_back(
                    std::make_unique<AtomToken>(acc, lineStart, iStart + 1));
                acc = "";
            }
            if (str[i] == '\n') {
                iLineStart = i + 1;
                ++line;
            }
            iStart = i - iLineStart + 1;
            lineStart = line;
        } else {
            acc += str[i];
        }
    }
}
