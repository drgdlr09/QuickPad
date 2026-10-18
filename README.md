# QuickPad - A Brief Overview
For Half-Life Week One, I designed QuickPad, a six-key macropad with a rotary encoder and 0.91" OLED screen. I designed QuickPad because my keyboard doesn't have any function keys, so I wanted to add some in the form of a macropad. During the design process, I also decided to add a rotary encoder for volume control. The OLED screen displays the date and time with the help of a DS3231 time module, which will keep track of time even when QuickPad is unplugged thanks to its coin cell battery.

<img width="773" height="703" alt="Screenshot 2026-10-18 at 1 54 11 PM" src="https://github.com/user-attachments/assets/8fb58b02-8b19-40c6-96a1-84ff40e56a3e" />

# How it Works
QuickPad has:
- XIAO RP2040 microcontroller with 11 GPIO pins, all of which are used
- Six mechanical switches for function keys
- Rotary encoder for volume control
- 0.91" OLED screen for displaying date and time
- DS3231 clock module to keep time

QuickPad is built around the SEEED XIAO RP2040, a small microcontroller with 11 GPIO pins.

The switches use a direct pin layout, with each pin wired directly between a GPIO pin and ground. Switch 1 is mapped to pin D0, switch 2 is mapped to pin D1, switch 3 is mapped to pin D2, switch 4 is mapped to pin D3, switch 5 is mapped to D8, and switch 6 is mapped to D9. The firmware matches each switches 1-6 to F1-F6 respectively. When a key is pressed, the firmware sends the HID code for that key.

<img width="572" height="393" alt="Screenshot 2026-10-10 at 5 21 00 PM" src="https://github.com/user-attachments/assets/b5a613c4-f8b9-4149-b4b9-3df6ed431bf7" />

<img width="300" height="289" alt="Screenshot 2026-10-18 at 1 54 40 PM" src="https://github.com/user-attachments/assets/529b80e9-c0b6-4b09-a23b-9f5df821f4da" />

# Bill of Materials

| Part | Quantity | Unit Price | Total | Vendor |
| --- | --- | --- | --- | --- |
| XIAO RP2040 | 1 | 3.99 | 3.99 | Seeed |
| Keycaps | 24 | 0.37 | 8.88 | Amazon |
| PCB | 5 | 0.23 | 1.15 | JLCPCB |
| 0.91" OLED Screen | 2 | 4.00 | 8.00 | Amazon |
| DS3231 | 2 | 4.00 | 8.00 | Amazon |

TOTAL PRICE (INCLUDING $2.22 SHIPPING/TAX): $28.25
