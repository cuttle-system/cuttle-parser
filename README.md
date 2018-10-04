# Cuttle Parser
A code parser to be used in Cuttle System

## API

Set `tokenizer_config_t` and `context_t` rules as in the following code example.

```c++
tokenizer_config_t config = {
    {{"'", {"'"}}}, // formatted string
    {{{"\"", {"\""}}}}, // normal string (without formatted characters)
    {{"+", "+=", "-"}}, // separated symbols
    {{"#", {"\n"}}}, // comments
    {{{"\\s", "\n"}}}, // formatted characters
    {{{"\n", "\\s"}}}, // formatted characters flipped
    {{"0if"}}, // if macros symbols
    {{"0ps", {"0"}}}, // function arguments
    {{"0pf", {"0pf"}}}, // function call as an argument
    {{"0p", {"0"}}, // function argument
    false // separate digits and alpha characters
};

tokens_t tokens;
tokenize(config, input, tokens);

context_t context;
initialize(context);

add(context, "!", function_t{ function_type::postfix, 1 }, FUNCTION_ID_UNKNOWN);
add(context, "-", function_t{ function_type::infix, 2 }, 3 /* executes after what function (id) */);
add(context, "+", function_t{ function_type::infix, 2 }, 4);
add(context, "*", function_t{ function_type::infix, 2 }, 5);

call_tree_t tree;
parse(tokens, tree, context); // Output stored in tree
```

## Building

### Prerequisites
 
- CMake 3.0.2
- Cygwin or MSYS Git if on Windows
- GCC 8.1.0
- GNU Make if manual process is followed

### Default process

1. Enable CMake support in your IDE (Visual Studio or CLion).
2. Open directory using your IDE.

### Manual process

1. Create directory build under the project directory.
2. Under the project directory run 
    1. `cd build`
    2. `cmake ..`
    3. `make`
