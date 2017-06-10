#include <string>
#include <vector>
#include <memory>
#include <ctype.h>
#include "token.hpp"
#include "string_token.hpp"
#include "atom_token.hpp"
#include "number_token.hpp"
#include "tokenizer.hpp"

using namespace husky;

void Tokenizer::Tokenize(
    const std::string &query, std::vector<std::unique_ptr<Token>>& tokens
) {
    int tokenType = AtomTokenType;
    unsigned line = 1;
    unsigned iStart = 0;
    unsigned lineStart = 1;
    unsigned iLineStart = 0;
    std::string acc = "";
    std::string str = query + '\n';

    for (register unsigned i = 0; i < str.length(); ++i) {
        if (str[i] == ' ' || str[i] == '\n') {
            if (acc != "") {
                if (tokenType == NumberTokenType)
                    tokens.push_back(std::make_unique<NumberToken>(
                                         acc, lineStart, iStart + 1));
                else if (tokenType == AtomTokenType)
                    tokens.push_back(std::make_unique<AtomToken>(
                                         acc, lineStart, iStart + 1));
                acc = "";
            }
            if (str[i] == '\n') {
                iLineStart = i + 1;
                ++line;
            }
            iStart = i - iLineStart + 1;
            lineStart = line;
        } else {
            if (acc == "") {
                if (isdigit(str[i])) tokenType = NumberTokenType;
                else tokenType = AtomTokenType;
            }
            acc += str[i];
        }
    }
}
