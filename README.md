# LogIn-System to Motor Dash board:
1.The system will wait until someone write Password to start the system.                                                                  2.Then give the user tries to enter the right password [DEFAULT_PW = 1234].

# Program Flow
  1.If the password is correct the Green Led ON.
    else Red Led ON, and re try to write the password.
  2.the user should choose whether it wants to [1-DC Motor operations | 2-Exit Program].
    1.1 Clock wise Rotation.
    1.2 Counter Clock wise Rotation.
    1.3 Back = to the previous menu [ 1-DC Motor | 2-Exit ]

# The hardware that has been used is:
    AVR-Atmega32.
    Keypad.
    LED Display.
    LCD Display.
    DC Motor.
    H-Bridge Design based on transistor npn [2N2222].
    Architecture Layer Applied:
# APP Folder has the Main Application --> main.c

# HAL Folder has :
  LED Display Driver.
  Keypad Driver.
  LED Display Driver.
  LCD Display Driver.
  DC Motor.
# MCAL Folder has:
  DIO Driver (which is needed because HAL Layer Connecting to MCAL Layer).
# LIB Folder has .h Files has:
  useful Macros to make the code easier and more readable.
