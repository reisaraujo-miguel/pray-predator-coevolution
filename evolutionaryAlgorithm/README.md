### Compile and run

    make clean
    make 
    make run

Or run with debugger:

    make debug
  
### GUI

The graphic interface was developed with OpenCV, which can be installed with:

    $ sudo apt-get install libopencv-dev

The graphical simulation can be turned _on_ or _off_ by setting the following macro on _main.cpp_ to 1 or 0 respectively:
```cpp
#define GUI_ON 0
```
