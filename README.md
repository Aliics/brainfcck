# brainfcck - A Brainf*ck C Compiler

Brainf*ck Compiler written in C with a C backend.

Take a look at the examples in the [test](test/) directory of Brainf*ck programs that have
been created to develop this.

In particular, a more *"complete program"* would be [greet.bf](test/greet.bf), which takes
user input and concatenates it onto the end of some nice output.

To test it out, you need to compile brainfcck first, and then we can compile our examples.

```bash
make # Build brainfcck
./out/brainfcck -i test/greet.bf -o out/greet # Compile using brainfcck
./out/greet # Use it as an executable
```

Our example, will look something like this:

```bf
+ just for the loop entrace
[
  [ - ] buffer cell needs to be empty
  >> , get one character
  [
    copy character over to next cells
    < + 
    < + 
    >> - 
  ]
  < last cell is used for LF check
  
  ---- ---- -- 10 = LF
]
< [ - ] clear newline buffer
< move to last char

shift chars over and add a front buffer
[ [ > + < - ] < ]

write "hi"
++++ ++++ ++++ + [ > ++++ ++++ < - ] > . h
+ . i

add a space
< ++++ ++++ [ > ---- ---- - < - ] > -

write input
[ . > ]

++++ ++++ ++ .
```

This is compiled down to the approximate C:

```c
#include <stdio.h>
int main(void) {
int cells[1 << 16] = {0};
int cell = 0;
cells[cell] += 1;
while (cells[cell]) {
while (cells[cell]) {
cells[cell] -= 1;
}
cell += 2;
cells[cell] = getchar();
while (cells[cell]) {
cell -= 1;
cells[cell] += 1;
cell -= 1;
cells[cell] += 1;
cell += 2;
cells[cell] -= 1;
}
cell -= 1;
cells[cell] -= 4;
cells[cell] -= 4;
cells[cell] -= 2;
}
cell -= 1;
while (cells[cell]) {
cells[cell] -= 1;
}
cell -= 1;
while (cells[cell]) {
while (cells[cell]) {
cell += 1;
cells[cell] += 1;
cell -= 1;
cells[cell] -= 1;
}
cell -= 1;
}
cells[cell] += 4;
cells[cell] += 4;
cells[cell] += 4;
cells[cell] += 1;
while (cells[cell]) {
cell += 1;
cells[cell] += 4;
cells[cell] += 4;
cell -= 1;
cells[cell] -= 1;
}
cell += 1;
printf("%c", cells[cell]);
cells[cell] += 1;
printf("%c", cells[cell]);
cell -= 1;
cells[cell] += 4;
cells[cell] += 4;
while (cells[cell]) {
cell += 1;
cells[cell] -= 4;
cells[cell] -= 4;
cells[cell] -= 1;
cell -= 1;
cells[cell] -= 1;
}
cell += 1;
cells[cell] -= 1;
while (cells[cell]) {
printf("%c", cells[cell]);
cell += 1;
}
cells[cell] += 4;
cells[cell] += 4;
cells[cell] += 2;
printf("%c", cells[cell]);
return 0;
}
```
