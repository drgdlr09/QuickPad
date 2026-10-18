# QuickPad - A Brief Overview
For Half-Life Week One, I designed QuickPad, a six-key macropad with a rotary encoder and 0.91" OLED screen. I designed QuickPad because my keyboard doesn't have any function keys, so I wanted to add some in the form of a macropad. During the design process, I also decided to add a rotary encoder for volume control. The OLED screen displays the date and time with the help of a DS3231 time module, which will keep track of time even when QuickPad is unplugged thanks to its coin cell battery.

<img width="773" height="703" alt="Screenshot 2026-10-18 at 1 54 11 PM" src="https://github.com/user-attachments/assets/8fb58b02-8b19-40c6-96a1-84ff40e56a3e" />
Front of board
<img width="788" height="712" alt="Screenshot 2026-10-18 at 2 46 05 PM" src="https://github.com/user-attachments/assets/4135c998-10ca-40f8-ac9d-f402318d7bcd" />
Back of board

# How it Works
QuickPad has:
- XIAO RP2040 microcontroller with 11 GPIO pins, all of which are used
- Six mechanical switches for function keys
- Rotary encoder for volume control
- 0.91" OLED screen for displaying date and time
- DS3231 clock module to keep time

QuickPad is built around the SEEED XIAO RP2040, a small microcontroller with 11 GPIO pins.

The switches use a direct pin layout, with each pin wired directly between a GPIO pin and ground. Switch 1 is mapped to pin D0, switch 2 is mapped to pin D1, switch 3 is mapped to pin D2, switch 4 is mapped to pin D3, switch 5 is mapped to D8, and switch 6 is mapped to D9. The firmware matches each switches 1-6 to F1-F6 respectively. When a key is pressed, the firmware sends the HID code for that key, thus triggering the response.

The rotary encoder is what controls volume. Turning clockwise turns the volume up and turning counterclockwise turns the volume down. Pressing the rotary encoder mutes the volume. Similarly to the switches, each input sends an HID code to get a response that triggers volume up/down or mute. The encoder's A pin is on D6, the B pin is on D7, and S1 is on D10.

The OLED Display and clock module work hand-in-hand. The display displays the current time and the clock module keeps track of time, even when QuickPad is unplugged. As soon as the firmware is compiled, the time is set and saved. This is a great feature for when I need to unplug the macropad to plug in other devices, like my phone or desk lamp. Both components use D4 and D5 for SDA and SCL capabilities.

<img width="572" height="393" alt="Screenshot 2026-10-10 at 5 21 00 PM" src="https://github.com/user-attachments/assets/b5a613c4-f8b9-4149-b4b9-3df6ed431bf7" />

<img width="300" height="289" alt="Screenshot 2026-10-18 at 1 54 40 PM" src="https://github.com/user-attachments/assets/529b80e9-c0b6-4b09-a23b-9f5df821f4da" />

*NOTE: Based on what I saw, although it looks like the microcontroller collides with switch 2 in the PCB layout, it shouldn't because the microcontroller is on the back of the board, not the front, so there shouldn't be any collisions (See 3D rendering above to confirm please; I could be wrong).

# The Case
The case has a similar design to my actual keyboard. It is comprised of 3 main parts: the main body, the top enclosure, and the rotary encoder knob. The main body has a sleep angular design with rounded edges for ergonomics when it needed to be moved. It also has a small hole for the USB port. The PCB is slightly raised to make room for the bottom components and also to create an inclined angled of typing.

<img width="231" height="143" alt="Screenshot 2026-10-18 at 2 56 54 PM" src="https://github.com/user-attachments/assets/5945db5f-f810-450c-a505-e1bb8285988f" />

The top enclosure has 3 cutouts: one for the keys, one for the rotary encoder, and one for the OLED screen. The one for the OLED screen has a small enclosure around it to stabilize the screen and keep it flush against the top enclosure. If the included pins do not reach the OLED screen, I will cut wires to the size needed to attach the screen to the board. The enclosure has a very tight fit so it can easily snap in place without the need of screws.

<img width="360" height="193" alt="Screenshot 2026-10-18 at 2 56 31 PM" src="https://github.com/user-attachments/assets/f16659f3-0b74-4a7a-ac6d-9dcda1a08190" />

Finally, the rotary encoder knob has a filleted top edge for ergonomics. it is 10mm tall and 12mm wide. I was intending to add a textured surface, but I had trouble adding it so I left it smooth.

<img width="360" height="361" alt="Screenshot 2026-10-18 at 2 55 43 PM" src="https://github.com/user-attachments/assets/92f8cf6c-c4f7-44b4-a04d-09ac8d63dc81" />

# Bill of Materials

| Part | Quantity | Unit Price | Total | Vendor |
| --- | --- | --- | --- | --- |
| XIAO RP2040 | 1 | 3.99 | 3.99 | Seeed |
| Keycaps | 24 | 0.37 | 8.88 | Amazon |
| PCB | 5 | 0.23 | 1.15 | JLCPCB |
| 0.91" OLED Screen | 2 | 4.00 | 8.00 | Amazon |
| DS3231 | 2 | 4.00 | 8.00 | Amazon |

TOTAL PRICE (INCLUDING $2.22 SHIPPING/TAX): $28.25
