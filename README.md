# Stress_Reliever
fun terminal stress reliever game

Terminal Stress Reliever - README
=============================

Description:
------------
This is a light-hearted, terminal-based stress reliever written in C. 
When you smash the keyboard, colourful ASCII "fireworks" appear in the console. 
The faster and harder you mash keys, the higher your "rage level" becomes. 
When rage levels climb too high, the programme offers calming messages 
such as "Take a deep breath..." or "Sip some water."

It works on both Windows and Linux/macOS, with the appropriate code 
compiled depending on your system.

Features:
---------
1. ASCII Fireworks:
   - Randomly drawn across the screen when keys are pressed.
2. Rage Bar:
   - Fills up as you mash keys, and slowly decreases if you pause.
3. Calming Messages:
   - Appear when rage levels exceed a threshold, reminding you to relax.
4. Cross-platform Support:
   - Works on Windows (via console output).
   - Works on Linux/macOS (via ncurses).

Controls:
---------
- Press any key repeatedly to trigger fireworks and increase rage.
- Quit at any time by pressing 'q'.

Requirements:
-------------
Windows:
- GCC (e.g. via MinGW or TDM-GCC)

Linux/macOS:
- GCC
- ncurses library (usually installed by default; otherwise install via your package manager)

Files:
------
1. stress_reliever.c - Source code for the programme.
2. README.txt - This file.

Instructions to Build and Run:
------------------------------

Windows (PowerShell or Command Prompt):
---------------------------------------
1. Compile the programme:
   gcc stress_reliever.c -o stress_reliever.exe
2. Run it:
   .\stress_reliever.exe

Linux/macOS (Terminal):
-----------------------
1. Compile the programme:
   gcc stress_reliever.c -lncurses -o stress_reliever
2. Run it:
   ./stress_reliever

Notes:
------
- On Windows, the programme uses raw console output for fireworks.
- On Linux/macOS, the programme uses ncurses for colour and positioning.
- Rage decreases gradually if you stop pressing keys.
- The programme is designed for fun and stress relief; it does not 
  affect your system beyond drawing to the console.

Licence:
--------
This software is provided for educational and recreational purposes. 
Use at your own risk.


End of README
=============================
