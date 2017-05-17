#pragma once

#include <string>

enum function_type {
    PrefixFunctionType,
    InfixFunctionType,
    PostFixFunctionType,
    PostPrefixFunctionType
};

namespace husky {
    class Function {
    public:
        Function(const std::string& name, int numberOfArgs)
            : name(name), numberOfArgs(numberOfArgs) {}

        virtual int GetType() = 0;
        virtual int GetNumberOfArgs() { return numberOfArgs; }
        virtual const std::string& GetName() { return name; }
    protected:
        const std::string name;
        int numberOfArgs = 0;
    };
}
