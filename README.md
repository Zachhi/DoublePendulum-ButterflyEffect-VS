# DoublePendulum-ButterflyEffect-VS
Simulates a plethora of visually pleasing ways to see how a double pendulum behaves and it's chaotic nature, including the butterfly effect.

# About
This program simulates a physically accurate double pendulum. However, we are assuming there are no external forces other than gravity. Things like friction and air resistance are non-existenet. This is to make the simulation more interesting...especially the butterfly effect. I added 3 different style's, as well as 3 different trail types, in order to help us visualize the behavior and qualities of a double pendulum better. Note: Imagine a single pendulum; the bar holding the weight at the bottom is the "arm". The weight at the bottom is the "body". You also have the ability to make the double pendulums a triple, quad, etc. pendulum. However, only the double pendulum is physically accurate, but the others lead to some interesting results.

**Style 1**

The first style you can just think of as "normal". You can see the whole pendulum (arm + body) where the bodies are white and the arms are gray. This allows us to see how the double pendulum behaves under normal circumstances and how the arms and bodies move together. This shows us how a real-life pendulum were to look if it were in front of us.

**Style 2**

The second style you can think of as turning the lights off. Eveything becomes invisible except the second body. This is because the second body shows the entire double pendulum's movement. It is the main point of the pendulum. The first body simply moves within the same circle, and the arms are there just to hold and connect the bodies. The second body also takes on a random pastel color, instead of being white. This allows us to simulate the difference of movement between double pendulums, and allows us to see the randomness of the different bodies compared to each other. Say we spawn 5 double pendulums in style 2. We will only see 5 bodies, but you will see these 5 bodies move in completley different ways. Changing to style 2 while already in style 2 will change the bodies colors if you don't like them.

**Style 3**

Style 3 is the most interesting by far, and it simulates the butterfly affect. This style makes the bodies invisible and only the arms are visible. This is simply because it looks much better like this. When you click "A", 10,000 pendulums spawn, with a total angle difference of .0001 radians between the first and last pendulum. The amount of pendulums spawning and the angle difference can be changed. This allows us to see the complete chaos of doubule pendulums, as well as adding some stunning visual affects. Each pendulum will move nearly the same for the first 15-30 seconds. After a while, the pendulums start breaking up and going all over the place. This simulateds how pendulums that are spaced a millionth of a radian apart  will still be in comopletley different positions after some time. This shows the statement of "the slightest difference in the starting position leads to completley different results over time", hence the name "butterfly effect". Changing to style 3 while already in style 3 will change the colors if you dont like them. Changing colors also changes transparency in this order: Very transparent->slightly transparent->not transparent. Colors are chosen at random with an algorithm I created. It will either be a random color that fades from white->color->black, or random colors that fade from white->color->color->color->black. These different options lead to very visually pleasing results.

**Trails**

There are 3 different types of trails. The first one is fade. Trails have a set length and the back of the tail will always fade away to keep this length. The second one is always. The trail is always on screen and never dissapears. The last one is none. There is no trail. Mixing these trail types with the different styles lead to interesting results.

**Note: This version requires Visual Studio. If you do not have access to Visual Studio, here is a version for linux and windows that requires no setup: https://github.com/Zachhi/DoublePendulum-ButterflyEffect-Windows-Linux**

## Demo

https://www.youtube.com/watch?v=sKC-cpFBwPs

## Controls

#### GUI
* Bottom Right:
  * Shows current game speed
  * Shows the current "style"
  * Shows current trail type
* Top Left: Shows the rules

#### Input
* LShift: See all the controls (will show in top left)
* A: Add a double pendulum. When on style 3, this will add 10,000 double pendulums with a total angle difference of .0001 radians so we can see the butterfly effect
* S: Add a section to the last pendulum spawned. This allows you to make triple/quad/etc pendulums. When on style 3, this will add a section to every existing pendulum
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
