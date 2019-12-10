## Installing OpenCV
The GUI was developed with OpenCV which can be installed running the following command: 

    $ sudo apt-get install libopencv-dev

## Macros
The program can be executed with or whithout the GUI. In order to run the program with the interface the following macro on the _main.cpp_ file must be set to 1:

```cpp
#define GUI_ON 1
```
Setting the macro to 0 turns off the GUI:

```cpp
#define GUI_ON 0
```

## Execution
Compile and run the program with:
```
$ make
$ make run
```
In case the GUI is turned on, to start the program click on the GUI window and press the _enter_ key, to exit the program press the _esc_ key.
