# Symbol Table and Nested Scope Simulation

## Overview
This program simulates a simple programming language with nested scopes and a symbol table.

## Syntax
The language supports the following commands:
- `begin` - Starts a new scope.
- `end` - Ends the current scope.
- `assign variableName value` - Assigns a value to a variable in the current scope.
- `print variableName` - Prints the value of the variable, searching through nested scopes if necessary.

## Example Program
```pseudo
begin
   assign a 1
   assign b 1
   begin
      assign a 3
      assign c 4
      print b
      begin
         assign a HelloWorld
         print b
         print a
         print c
      end
      print a
      print c
   end
   print a
end
```

## Expected Output
```txt
1
1
HelloWorld
4
3
4
1
```

## Explanation
1. **`begin`** creates a new scope.
2. Variables **`a`** and **`b`** are assigned in the first scope.
3. A new scope is created, redefining **`a`** and adding **`c`**.
4. **`b`** is printed from the outer scope.
5. Another nested scope is created where **`a`** is assigned **HelloWorld**.
6. The inner scope prints values from its own and outer scopes.
7. When scopes end, the variables from those scopes are removed.

This demonstrates **variable shadowing** and **scope resolution**.

## Errors and Exceptions
The program detects and prints the following errors:
-  `Error: Line - X scope is undefined` → Attempting to remove a scope when none exist.
-  `Error: Line - X variable 'varName' is undefined` → Trying to print a variable that is not declared in any accessible scope.
-  `Error: Line - X syntax Error` → Incorrect command format.
-  `Error: Line - X unexpected error occurred` → Catch-all for unexpected issues.

## How to Run
1. Use the provided **Makefile** to compile the program:
   ```sh
   make
   ```
2. Run the compiled executable:
   ```sh
   ./main
   ```
3. Ensure **`code_file.txt`** contains the program instructions.
4. The interpreter will process and execute the commands.

