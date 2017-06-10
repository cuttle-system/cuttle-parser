#pragma once

#include <string>
#include <vector>

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
        TestTokenizeBasicSpaceSeparatedNumbers();
        TestTokenizeSpaceAndNewlineSeparatedNumbers();
        TestTokenizeSpaceSeparatedMixedNumbersAndAtoms();
    }

protected:
    static void TestTokenizeBasicSpaceSeparatedAtoms() {
        std::vector<std::unique_ptr<Token>> tokens;

        Tokenizer::Tokenize("foo bar baz", tokens);

        AssertTrue(tokens[0]->GetType() == AtomTokenType,
                   "element 1 type", __FILE__, __LINE__);
        AssertTrue(tokens[0]->GetValue() == "foo",
                   "element 1 value", __FILE__, __LINE__);
        AssertTrue(tokens[0]->GetLine() == 1,
                   "element 1 line", __FILE__, __LINE__);
        AssertTrue(tokens[0]->GetCol() == 1,
                   "element 1 col", __FILE__, __LINE__);

        AssertTrue(tokens[1]->GetType() == AtomTokenType,
                   "element 2 type", __FILE__, __LINE__);
        AssertTrue(tokens[1]->GetValue() == "bar",
                   "element 2 value", __FILE__, __LINE__);
        AssertTrue(tokens[1]->GetLine() == 1,
                   "element 2 line", __FILE__, __LINE__);
        AssertTrue(tokens[1]->GetCol() == 5,
                   "element 2 col", __FILE__, __LINE__);

        AssertTrue(tokens[2]->GetType() == AtomTokenType,
                   "element 3 type", __FILE__, __LINE__);
        AssertTrue(tokens[2]->GetValue() == "baz",
                   "element 3 value", __FILE__, __LINE__);
        AssertTrue(tokens[2]->GetLine() == 1,
                   "element 3 line", __FILE__, __LINE__);
        AssertTrue(tokens[2]->GetCol() == 9,
                   "element 3 col", __FILE__, __LINE__);
    }

    static void TestTokenizeSpaceAndNewlineSeparatedAtoms() {
        std::vector<std::unique_ptr<Token>> tokens;

        Tokenizer::Tokenize("foo bar\n\n baz\nquxx", tokens);

        AssertTrue(tokens[0]->GetType() == AtomTokenType,
                   "element 1 type", __FILE__, __LINE__);
        AssertTrue(tokens[0]->GetValue() == "foo",
                   "element 1 value", __FILE__, __LINE__);
        AssertTrue(tokens[0]->GetLine() == 1,
                   "element 1 line", __FILE__, __LINE__);
        AssertTrue(tokens[0]->GetCol() == 1,
                   "element 1 col", __FILE__, __LINE__);

        AssertTrue(tokens[1]->GetType() == AtomTokenType,
                   "element 2 type", __FILE__, __LINE__);
        AssertTrue(tokens[1]->GetValue() == "bar",
                   "element 2 value", __FILE__, __LINE__);
        AssertTrue(tokens[1]->GetLine() == 1,
                   "element 2 line", __FILE__, __LINE__);
        AssertTrue(tokens[1]->GetCol() == 5,
                   "element 2 col", __FILE__, __LINE__);

        AssertTrue(tokens[2]->GetType() == AtomTokenType,
                   "element 3 type", __FILE__, __LINE__);
        AssertTrue(tokens[2]->GetValue() == "baz",
                   "element 3 value", __FILE__, __LINE__);
        AssertTrue(tokens[2]->GetLine() == 3,
                   "element 3 line", __FILE__, __LINE__);
        AssertTrue(tokens[2]->GetCol() == 2,
                   "element 3 col", __FILE__, __LINE__);

        AssertTrue(tokens[3]->GetType() == AtomTokenType,
                   "element 4 type", __FILE__, __LINE__);
        AssertTrue(tokens[3]->GetValue() == "quxx",
                   "element 4 value", __FILE__, __LINE__);
        AssertTrue(tokens[3]->GetLine() == 4,
                   "element 4 line", __FILE__, __LINE__);
        AssertTrue(tokens[3]->GetCol() == 1,
                   "element 4 col", __FILE__, __LINE__);
    }

    static void TestTokenizeBasicSpaceSeparatedNumbers() {
        std::vector<std::unique_ptr<Token>> tokens;

        Tokenizer::Tokenize("10 323 2", tokens);

        AssertTrue(tokens[0]->GetType() == NumberTokenType,
                   "element 1 type", __FILE__, __LINE__);
        AssertTrue(tokens[0]->GetValue() == "10",
                   "element 1 value", __FILE__, __LINE__);
        AssertTrue(tokens[0]->GetLine() == 1,
                   "element 1 line", __FILE__, __LINE__);
        AssertTrue(tokens[0]->GetCol() == 1,
                   "element 1 col", __FILE__, __LINE__);

        AssertTrue(tokens[1]->GetType() == NumberTokenType,
                   "element 2 type", __FILE__, __LINE__);
        AssertTrue(tokens[1]->GetValue() == "323",
                   "element 2 value", __FILE__, __LINE__);
        AssertTrue(tokens[1]->GetLine() == 1,
                   "element 2 line", __FILE__, __LINE__);
        AssertTrue(tokens[1]->GetCol() == 4,
                   "element 2 col", __FILE__, __LINE__);

        AssertTrue(tokens[2]->GetType() == NumberTokenType,
                   "element 3 type", __FILE__, __LINE__);
        AssertTrue(tokens[2]->GetValue() == "2",
                   "element 3 value", __FILE__, __LINE__);
        AssertTrue(tokens[2]->GetLine() == 1,
                   "element 3 line", __FILE__, __LINE__);
        AssertTrue(tokens[2]->GetCol() == 8,
                   "element 3 col", __FILE__, __LINE__);
    }

    static void TestTokenizeSpaceAndNewlineSeparatedNumbers() {
        std::vector<std::unique_ptr<Token>> tokens;

        Tokenizer::Tokenize("1 002\n\n 20\n320", tokens);

        AssertTrue(tokens[0]->GetType() == NumberTokenType,
                   "element 1 type", __FILE__, __LINE__);
        AssertTrue(tokens[0]->GetValue() == "1",
                   "element 1 value", __FILE__, __LINE__);
        AssertTrue(tokens[0]->GetLine() == 1,
                   "element 1 line", __FILE__, __LINE__);
        AssertTrue(tokens[0]->GetCol() == 1,
                   "element 1 col", __FILE__, __LINE__);

        AssertTrue(tokens[1]->GetType() == NumberTokenType,
                   "element 2 type", __FILE__, __LINE__);
        AssertTrue(tokens[1]->GetValue() == "002",
                   "element 2 value", __FILE__, __LINE__);
        AssertTrue(tokens[1]->GetLine() == 1,
                   "element 2 line", __FILE__, __LINE__);
        AssertTrue(tokens[1]->GetCol() == 3,
                   "element 2 col", __FILE__, __LINE__);

        AssertTrue(tokens[2]->GetType() == NumberTokenType,
                   "element 3 type", __FILE__, __LINE__);
        AssertTrue(tokens[2]->GetValue() == "20",
                   "element 3 value", __FILE__, __LINE__);
        AssertTrue(tokens[2]->GetLine() == 3,
                   "element 3 line", __FILE__, __LINE__);
        AssertTrue(tokens[2]->GetCol() == 2,
                   "element 3 col", __FILE__, __LINE__);

        AssertTrue(tokens[3]->GetType() == NumberTokenType,
                   "element 4 type", __FILE__, __LINE__);
        AssertTrue(tokens[3]->GetValue() == "320",
                   "element 4 value", __FILE__, __LINE__);
        AssertTrue(tokens[3]->GetLine() == 4,
                   "element 4 line", __FILE__, __LINE__);
        AssertTrue(tokens[3]->GetCol() == 1,
                   "element 4 col", __FILE__, __LINE__);
    }

    static void TestTokenizeSpaceSeparatedMixedNumbersAndAtoms() {
        std::vector<std::unique_ptr<Token>> tokens;

        Tokenizer::Tokenize("foo 002 20 bar320", tokens);

        AssertTrue(tokens[0]->GetType() == AtomTokenType,
                   "element 1 type", __FILE__, __LINE__);
        AssertTrue(tokens[0]->GetValue() == "foo",
                   "element 1 value", __FILE__, __LINE__);
        AssertTrue(tokens[0]->GetLine() == 1,
                   "element 1 line", __FILE__, __LINE__);
        AssertTrue(tokens[0]->GetCol() == 1,
                   "element 1 col", __FILE__, __LINE__);

        AssertTrue(tokens[1]->GetType() == NumberTokenType,
                   "element 2 type", __FILE__, __LINE__);
        AssertTrue(tokens[1]->GetValue() == "002",
                   "element 2 value", __FILE__, __LINE__);
        AssertTrue(tokens[1]->GetLine() == 1,
                   "element 2 line", __FILE__, __LINE__);
        AssertTrue(tokens[1]->GetCol() == 5,
                   "element 2 col", __FILE__, __LINE__);

        AssertTrue(tokens[2]->GetType() == NumberTokenType,
                   "element 3 type", __FILE__, __LINE__);
        AssertTrue(tokens[2]->GetValue() == "20",
                   "element 3 value", __FILE__, __LINE__);
        AssertTrue(tokens[2]->GetLine() == 1,
                   "element 3 line", __FILE__, __LINE__);
        AssertTrue(tokens[2]->GetCol() == 9,
                   "element 3 col", __FILE__, __LINE__);

        AssertTrue(tokens[3]->GetType() == AtomTokenType,
                   "element 4 type", __FILE__, __LINE__);
        AssertTrue(tokens[3]->GetValue() == "bar320",
                   "element 4 value", __FILE__, __LINE__);
        AssertTrue(tokens[3]->GetLine() == 1,
                   "element 4 line", __FILE__, __LINE__);
        AssertTrue(tokens[3]->GetCol() == 12,
                   "element 4 col", __FILE__, __LINE__);
    }
};
