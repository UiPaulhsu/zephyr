#!/bin/bash

# Build the firmware for Nucleo-WBA55CG
west build -b nucleo_wba55cg

# Connect to the STM32 target via SWD
STM32_Programmer_CLI --connect port=SWD

# Flash the firmware
west flash
