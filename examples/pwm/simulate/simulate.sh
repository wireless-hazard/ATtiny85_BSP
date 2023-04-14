#!/bin/bash
echo "Press Ctrl + C to finish the Simulator"

#calls AVR Simulator
${HOME}/simulavr/build/app/simulavr -d attiny85 -f ../pwm_gen.elf -c vcd:tracelist.txt:result.vcd -F 2000000