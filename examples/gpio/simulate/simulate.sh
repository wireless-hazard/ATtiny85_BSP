#!/bin/bash
echo "Press Ctrl + C to finish the Simulator"

#calls AVR Simulator
simulavr -d attiny85 -f ../toggle.elf -c vcd:tracelist.txt:result.vcd -F 2000000