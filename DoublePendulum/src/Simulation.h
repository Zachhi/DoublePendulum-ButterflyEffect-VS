#ifndef SIMULATION_H
#define SIMULATION_H

#define PI 3.14159265
#define LOG(x) std::cout << x << std::endl
#include <iostream>
#include <string>
#include <vector>
#include "PendulumSection.h"
#include "Pendulum.h"

class Simulation
{
private:

    sf::ContextSettings settings; //settings so we can add anti aliasing
    sf::RenderWindow window; //the window we will run simulation in
    sf::Clock clock; //clock so we can have time variables

    sf::Font font; //font we will use
    sf::Text text; //text we will use

    std::vector<std::vector <PendulumSection*>> pendulums;

    std::vector<std::vector<sf::Vertex>> trails; //vector of all trails
    std::vector<sf::Vertex> singularTrail; //holder for a single trail

    sf::CircleShape pendulumHolder; //this will be the circle shape to appear to "hold" the pendulums. Purely for aesthetical reasons

    float currSimulationSpeed = 15; //tracks the current simulation speed we want to run at
    float prevSimulationSpeed = 15; //tracks the previous speed we were running at. This helps us be able to unpause the game

public:
    Simulation(); //constructor
    void initialize(); //initialize variables
    void runSimulation(); //function to run the program

    //--------FUNCTIONS THAT HELP WITH CHECKING INPUT----------
    void addPendulum(); //add another pendulum
    void addSection(); //add another section (arm+body) to current pendulum we are on
    void clear(); //clear screen when called
    void changeSimulationSpeed(int upOrDown); //helps change the simulation speed
    void togglePause(); //helps pause and unpause game
    void fadeToBlack();
    void checkForInput(); //check for user input

    //--------DRAW AND UPDATE FUNCTIONS---------------------
    void updatePendulums(); //update the pendulums
    void drawObjects(); //draw objects (lines, balls, trails)




};

#endif //SIMULATION_H