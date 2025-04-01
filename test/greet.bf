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
