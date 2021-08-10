# DoublePendulum-VS
Simulates a plethora of ways a double pendulum behaves

**Note: This version requires Visual Studio. If you do not have access to Visual Studio, here is a version that works for linux and windows that requires no setup: https://github.com/Zachhi/DoublePendulum-Windows-Linux**

## Demo

## Controls

#### GUI
* Bottom Right:
  * Shows current game speed
  * Shows the current "style"
    * Style 1: Shows full pendulum, arms and bodies
    * Style 2: Only shows the second bodies, hides the arms and first bodies. Colors the second bodies a random color
    * Style 3: Meant to show the butterfly effect. Only shows arms.
  * Shows current trail type
    * fade: Trails have certain length, and constantly fades away to keep this length
    * always: Trails never fade away, shows the entire length of trail
    * none: No trail shown
* Top Left: Shows the rules

#### Input
* LShift: See all the controls (will show in top left)
* A: Add a double pendulum. When on style 3, this will add 10,000 double pendulums with a total angle difference of .0001 radians so we can see the butterfly effect
* S: Add a section to the last pendulum spawned. This allows you to make triple/quad/etc pendulums. However, these are not physically accurate, and only the double pendulum is physically accurate. When on style 3, this will add a section to every existing pendulum
* Space: Pause the game
* Up/down arrow: Increase/decrease game speed
* 1: Change to style 1
* 2: Change to style 2
* 3: Change to style 3
* T: Change trail type
* Esc: Exit program

### Dependencies

* Windows
* Visual Studio 19 or above
* SFML (Simple and Fast Multi-Media Library) 2.5.1 or later is required in order to run this program. You can install SFML here: https://www.sfml-dev.org/download/sfml/2.5.1/
* Since we are using Visual Studio, download the Visual c++ 15 from the sfml website

**If you don't have access to Visual Studio, or you are on linux, scroll to the top to find the other version**

### Installing and Executing

* Download the source code from github, or clone the repository into Visual Studio
* Import into Visual Studio
* Build according to your need (x86 or x64)
* In project settings
  * Add the `/path/to/sfml/include` to your c++ include path
  * Add the `/path/to/sfml/libray` to the linker library path
  * Link the following sfml libraries: `sfml-graphics.lib, sfml-windows.lib, sfml-system.lib, sfml-audio.lib`
  * Link the following debug libraries: `sfml-graphics-d.lib, sfml-windows-d.lib, sfml-system-d.lib, sfml-audio-d.lib`
  * Copy the sfml dlls (in the `sfml/bin` folder) to your project folder
* A very easy and simple 5 minute tutorial for linking SFML with a Visual Studio project can be found here: https://www.youtube.com/watch?v=YfMQyOw1zik
* Click the run button at the top and the program should start

**If you would prefer not having to link libraries, and would prefer a version fully set up, see the link at the top**

## Authors

Zachary Chi
zachchi@tamu.edu

## License

This project is licensed under the MIT License - see the LICENSE.md file for details
