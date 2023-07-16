# Current Programming language

This is my first big c++ project. Please don't kill me for my (really) bad code. It works, but there are many unused functions and it's really obvious that I removed a lot of stuff during developement.

Simple:
```
use the "current" command:
current current example    //compiles the directory "example"
current cvm example        //runs the compiled code @ "example/compiled"
```


Features of the "current" language:

datatypes: char, bool and uint32

bool is basically useless because it's immutable, char is immutable too.

variables are declared like this:


[type] [name]: [value]
```
uint32 x: 10;
bool y: 1;
char z: 69;
```

This program applies the basic math operations:
```
uint32 x: 10;
uint32 y: 4;

call math add: x y;
call math sub: x y;
call math mul: x y;
call math div: x y;
call math mod: x y;
```

The output of these math operations are put into ```x```. Since there is no "float" datatype, the ```div``` operation is integer division.

To output a variable's content, use ```call std cout```:

```
uint32 x: 10;
bool y: 1;
char z: 69;

call std cout: x;
call std cout: y;
call std cout: z;
```

Printing an integer works like you'd expect. Printing a bool either outputs "false" or "true". Using ```call std cout``` on a char, prints its corresponding ASCII value.

There are no functions int current, but you can call other .curr files using ```call file: [filename without .curr]```

There are no if-statements and traditional loops, but you can use ```whileNotZero [variable]: [filename without .curr]```:


main file:
```
uint x: 10;
uint one: 1;
whileNotZero x: example_file
```

example_file.curr:
```
call math sub: x one;
cal std cout: x;
```

As one could guess from this, all variables are global and shared across files.


Use this to quit out of the program:
```
call std quit 0;
```

Replace the 0 with a 1 to see debug output.
