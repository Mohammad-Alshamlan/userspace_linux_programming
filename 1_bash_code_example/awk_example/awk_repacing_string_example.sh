#!/bin/bash

# let have these strings
str1="something:1275.77"

# let way we want to output these with just spaces with awk. Note: "$ echo ${str1//[:]/' '}" will do it!!
echo $str1 | awk '{gsub(":"," "); print}'
# let say you want to print the cell that in row 2 and cloumn 5
awk 'FNR==2 { print $5 }' /proc/interrupts	# note: /proc/interrupts is the IRQs info

