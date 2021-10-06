# GPIO emulator example

This example emulates General Purpose Input Output (GPIO) in Linux environment:

  - 10 GPIOs are emulated: from 0 to 9. They are displayed as a value in GPIO register reg.
  - Initially, GPIO 0-4 are set to 1.
  - You can toggle the status of GPIOs using keyboard buttons 0-9.
  - When GPIO i is pressed, GPIO i and GPIO 9-i are both toggled.
  - Press Esc to exit.

### To compile

```sh
$ gcc -pthread -o test *.c 
```

### To run

Run the executable:
```sh
$ ./test
reg=0000000001
reg=0000000011
reg=0000000111
reg=0000001111
reg=0000011111
```

Press the keyboard buttons, e.g. from 0 to 9:
```sh
reg=1000011110
reg=1100011100
reg=1110011000
reg=1111010000
reg=1111100000
reg=1111010000
reg=1110011000
reg=1100011100
reg=1000011110
reg=0000011111
```

Press Esc to exit the program.


