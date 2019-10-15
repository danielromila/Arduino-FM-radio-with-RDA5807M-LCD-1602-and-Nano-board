# Arduino-FM-radio-with-RDA5807M-LCD-1602-and-Nano-board

I modified the schematics and code made by Alexander Liman. You can see his work at:

https://www.youtube.com/watch?v=gMmRLU60gho

I modified the schematics by using the standard pins to connect the LCD1602 with the Arduino Nano board. This means that all examples from Arduino IDE, like the “Hello World” sketch will work in my schematics (but not in his), because I use the pins as those examples use them. From the functional point of view, if you want to dedicate the Arduino board and the LCD only for this radio and not to reuse the assemble Alexander’s schematics is fine. My schematics also allows verifying step by step: attach the Arduino board to the LCD and see if displays OK, and after go into the buttons and the radio part.
Alexander’s version was very ambitious and implemented 10 memories for stations, plus one for the last used level of audio volume, memories that could remain even if the power supply was disconnected. Unfortunately his code worked on his old Arduino Nano boards but not on mine and not on the boards of some readers of his posting. Alexander made a patch, which requires first to load an initial program into Arduino Nano, and after to load the real useful sketch. I still had some problems – which can be from my built – and I completely eliminated the EEPROM things. I did not consider safe and replicable by others a sketch that works on some boards and does not work in other boards.
I implemented an autoscan which can keep up to 50 memorized stations, as long as the power is not disconnected. I really need more than 30 memories in Vancouver area. 10 memories, as in Alexander’s version, would have allowed me to hear only the first stations, from the lower side of the band.
I added the bass boost as the 5th menu.
I completely remade the manual search. Now it does not go anymore outside the 88 MHz – 108 MHz band. The manual search has a step of 100 KHz for short pushes of the buttons and 1 MHz for long or continuous pushes of the buttons. This is very useful, and I really needed to implement it, because going from 88 MHz manually to 108 MHz would have required a long time otherwise.
I changed various displays, to give indications to the user what the radio expects to be pushed and why.
While all modifications I did took me many hours and seam major modifications, everything was done based on Alexander’s work. It was much easier to modify a program that already worked than to start from zero.  
Please see the user's manual file user.docx to understand how to navigate through the menus and what it is possible to do with this radio.
