# QuickPad - A Brief Overview
For Half-Life Week One, I designed QuickPad, a six-key macropad with a rotary encoder and 0.91" OLED screen. I designed QuickPad because my keyboard doesn't have any function keys, so I wanted to add some in the form of a macropad. During the design process, I also decided to add a rotary encoder for volume control. The OLED screen displays the date and time with the help of a DS3231 time module, which will keep track of time even when QuickPad is unplugged thanks to its coin cell battery.

# How it Works
QuickPad uses the XIAO RP2040 microcontroller. Each switch uses one of the microcontrollers pins. The firmware maps the switches to function keys F1-F6. The rotary encoder controls volume, and pressing it mutes the volume. The time module records the time at the time the code is compiled and displays it on the OLED screen, with the date on the top and the time in AM/PM format right below it.
