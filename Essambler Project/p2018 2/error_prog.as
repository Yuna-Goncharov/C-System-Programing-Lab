.entry LOOP
.entry LENGTH
.extern L3
.extern W
MAIN: mov M1[2][r7],W
add r2,STR,r3
LOOP: jmp W1
prn #-513
sub r1,	 ,r4
inc #4
mov M1[r3][r3],#1
bne L3
END: stop r5
STR: .string "abc  		def"
sub #5
red
add  #1,#2
inc  #1
and  x,y
Mov  r3,r4
cmp  r1,,r2
add  #1,r1,r2
prn r1 qwe
cmp  #xyz,r1
LOOP:   clr  r2
1label:   sub r1,r7
lea  r3,r1
lea  #3,r5
stop now
.data   1, ,3
.data   #5
.data   1.5
stop:    .data   5
r1:     .data   5
.string blabla
.string "abcdef" g
.string "abcdef
LENGTH: .data 6,-9,15,7.2
K: .data 22
M1: .mat [2][2] 1,2,3,4,5,6

