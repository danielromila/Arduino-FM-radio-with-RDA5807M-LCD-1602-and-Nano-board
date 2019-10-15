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

Functioning:
There are 3 buttons:
-	MENU; 
-	PLUS
-	MINUS
There are 5 possible cases for menu:
-	Volume ; 
o	The first line of the displays shows the frequency that it is received in that moment.
o	The second line of the display shows less or more of vertical lines. When the second line shows only 2 lines the volume is at the minimum. The maximum volume is for 32 lines.
       By default, without touching anything, the display is something like:

                88.00 MHz
           - - - - -   MONO
       Or
	  88.10 MHz
          TUNED  STEREO
		
While in the Volume menu the user can push the UP and DOWN buttons for adjusting the volume.
The display will become something like:
	  88.10 MHz
          IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII

-	Memorized stations;
When entering into this menu the display shows on 2 lines:
Push UP or Down
to access memory
The frequency that it is received in this moment, while seeing the above 2 lines, is the last frequency setup previously, either by manual scan or by accessing a memorized station.
If there are stations already memorized and the UP or DOWN buttons are pushed the display will become:
      M1 88.10 MHz
      TUNED  SIGNAL 27
If there are no stations memorized and the UP or DOWN buttons are pushed the display will become something like:
      M50 N/A
      -----  SIGNAL 11
The frequency heard will become the frequency displayed, if there is anything in that memory, as displayed. If N/A is displayed only some noise will be heard, because there is no memorized station there.
If you do not want to loose the station you already setup before seeing entering the memorized stations menu, do not push the UP or DOWN buttons! Just go forward to other menus, by pushing the MENU button again and get in the menu you want!
-	Autoscan
o	While in this menu the display will show
       AUTOSCAN if you
       Push UP or DOWN
o	If you are in the autoscan menu and push either UP or DOWN buttons the second line will change from showing nothing into
        AUTOSCAN 88.10
        1   89.10 MHz
In the first line the frequency advances from 88.00 to 108.00. Every time a strong enough station is found the second line shows the number of memory where the new station is memorized, and the frequency it was memorized. There are maximum 50 memories. When the scanning reaches 108.00 MHz the filling of memories stop. All the remaining from the 50 memory locations will show N/A when going through them in the previous “Memorized stations” menu.
After the AUTOSCAN operation the radio will go into the first memorized station. The memories are lost if the power supply is disconnected.
-	Manual
o	The display will show something like 
      manual 88.10 MHz
      TUNED  SIGNAL 27
Or
      manual 88.00 MHz
      - - - - - -  SIGNAL 11
Short pushes on the Up or DOWN buttons will change the frequency in steps of 100 KHz. Long and continuous pushes of those buttons will change the frequency in steps of 1 MHz.
The frequency displayed and heard when entering the manual menu is the last frequency it was setup by the user, either by a manual operation or by an Autoscan operation.
-	Bass boost
o	This menu will display
     Bass Boost
                        OFF
And can be changed into ON or OFF by pressing the UP button for ON or the Down button for OFF

In whatever menu the radio would be, after around 15 seconds of doing nothing the radio will automatically go into the Volume menu.
After a while the second line of the display will show the information the station eventually broadcasts in digital format, like the name of the station, the song played at that moment and so on. The majority of the Vancouver stations have this kind of digital information.
 
