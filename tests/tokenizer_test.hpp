#pragma once

#include <string>
#include <list>

#include "test.hpp"
#include "../src/tokenizer.hpp"
#include "../src/token.hpp"

using namespace husky;

class TokenizerTest : public Test
{
public:
    static void Run() {
        TestTokenizeBasicSpaceSeparatedAtoms();
        TestTokenizeSpaceAndNewlineSeparatedAtoms();
    }

protected:
    static void TestTokenizeBasicSpaceSeparatedAtoms() {
        std::list<std::unique_ptr<Token>> tokens;

        Tokenizer::Tokenize("foo bar baz", tokens);

        AssertTrue(tokens.front()->GetType() == AtomTokenType,
                   "element 1 type", __FILE__, __LINE__);
        AssertTrue(tokens.front()->GetValue() == "foo",
                   "element 1 value", __FILE__, __LINE__);
        AssertTrue(tokens.front()->GetLine() == 1,
                   "element 1 line", __FILE__, __LINE__);
        AssertTrue(tokens.front()->GetCol() == 1,
                   "element 1 col", __FILE__, __LINE__);

        AssertTrue((*++tokens.begin())->GetType() == AtomTokenType,
                   "element 2 type", __FILE__, __LINE__);
        AssertTrue((*++tokens.begin())->GetValue() == "bar",
                   "element 2 value", __FILE__, __LINE__);
        AssertTrue((*++tokens.begin())->GetLine() == 1,
                   "element 2 line", __FILE__, __LINE__);
        AssertTrue((*++tokens.begin())->GetCol() == 5,
                   "element 2 col", __FILE__, __LINE__);

        AssertTrue((*++++tokens.begin())->GetType() == AtomTokenType,
                   "element 3 type", __FILE__, __LINE__);
        AssertTrue((*++++tokens.begin())->GetValue() == "baz",
                   "element 3 value", __FILE__, __LINE__);
        AssertTrue((*++++tokens.begin())->GetLine() == 1,
                   "element 3 line", __FILE__, __LINE__);
        AssertTrue((*++++tokens.begin())->GetCol() == 9,
                   "element 3 col", __FILE__, __LINE__);
    }

    static void TestTokenizeSpaceAndNewlineSeparatedAtoms() {
        std::list<std::unique_ptr<Token>> tokens;

        Tokenizer::Tokenize("foo bar\n\n baz\nquxx", tokens);

        AssertTrue(tokens.front()->GetType() == AtomTokenType,
                   "element 1 type", __FILE__, __LINE__);
        AssertTrue(tokens.front()->GetValue() == "foo",
                   "element 1 value", __FILE__, __LINE__);
        AssertTrue(tokens.front()->GetLine() == 1,
                   "element 1 line", __FILE__, __LINE__);
        AssertTrue(tokens.front()->GetCol() == 1,
                   "element 1 col", __FILE__, __LINE__);

        AssertTrue((*++tokens.begin())->GetType() == AtomTokenType,
                   "element 2 type", __FILE__, __LINE__);
        AssertTrue((*++tokens.begin())->GetValue() == "bar",
                   "element 2 value", __FILE__, __LINE__);
        AssertTrue((*++tokens.begin())->GetLine() == 1,
                   "element 2 line", __FILE__, __LINE__);
        AssertTrue((*++tokens.begin())->GetCol() == 5,
                   "element 2 col", __FILE__, __LINE__);

        AssertTrue((*++++tokens.begin())->GetType() == AtomTokenType,
                   "element 3 type", __FILE__, __LINE__);
        AssertTrue((*++++tokens.begin())->GetValue() == "baz",
                   "element 3 value", __FILE__, __LINE__);
        AssertTrue((*++++tokens.begin())->GetLine() == 3,
                   "element 3 line", __FILE__, __LINE__);
        AssertTrue((*++++tokens.begin())->GetCol() == 2,
                   "element 3 col", __FILE__, __LINE__);

        AssertTrue((*++++++tokens.begin())->GetType() == AtomTokenType,
                   "element 4 type", __FILE__, __LINE__);
        AssertTrue((*++++++tokens.begin())->GetValue() == "quxx",
                   "element 4 value", __FILE__, __LINE__);
        AssertTrue((*++++++tokens.begin())->GetLine() == 4,
                   "element 4 line", __FILE__, __LINE__);
        AssertTrue((*++++++tokens.begin())->GetCol() == 1,
                   "element 4 col", __FILE__, __LINE__);
    }

};
