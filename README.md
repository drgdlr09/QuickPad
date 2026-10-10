# QuickPad - A Brief Overview
For Half-Life Week One, I designed QuickPad, a six-key macropad with a rotary encoder and 0.91" OLED screen. I designed QuickPad because my keyboard doesn't have any function keys, so I wanted to add some in the form of a macropad. During the design process, I also decided to add a rotary encoder for volume control. The OLED screen displays the date and time with the help of a DS3231 time module, which will keep track of time even when QuickPad is unplugged thanks to its coin cell battery.

<img width="851" height="762" alt="Screenshot 2026-10-10 at 5 21 48 PM" src="https://github.com/user-attachments/assets/f01b9b58-19f6-4bd8-9399-5a39e2281832" />

# How it Works
QuickPad uses the XIAO RP2040 microcontroller. Each switch uses one of the microcontrollers pins. The firmware maps the switches to function keys F1-F6. The rotary encoder controls volume, and pressing it mutes the volume. The time module records the time at the time the code is compiled and displays it on the OLED screen, with the date on the top and the time in AM/PM format right below it.

<img width="572" height="393" alt="Screenshot 2026-10-10 at 5 21 00 PM" src="https://github.com/user-attachments/assets/b5a613c4-f8b9-4149-b4b9-3df6ed431bf7" />

<img width="418" height="383" alt="Screenshot 2026-10-10 at 5 21 21 PM" src="https://github.com/user-attachments/assets/0b11fe6d-7eba-4660-a16e-4fb1d26613ce" />

