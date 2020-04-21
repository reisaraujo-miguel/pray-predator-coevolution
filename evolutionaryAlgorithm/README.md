### Compile and run

    make clean
    make 
    make run

Or run with debugger:

    make debug
  
### GUI

The graphic interface was developed with OpenCV, which can be installed with:

    $ sudo apt-get install libopencv-dev

The graphical simulation can be turned _on_ or _off_ by setting the following macro on the file _macro.h_ to 1 or 0 respectively:
```cpp
#define GUI_ON 0
```
When the GUI is turned _on_, in order to start the simulation, click _enter_. While the simulation is running the following keys can be used:
- _esc_: stop program;
- _x_: turn off GUI, but continue running program;
- _up arrow_: speed up frame rate;
- _down arrow_: slow down frame rate.
