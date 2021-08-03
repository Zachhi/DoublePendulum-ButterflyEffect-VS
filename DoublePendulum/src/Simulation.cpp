#include "Simulation.h"

//constructor
Simulation::Simulation() : window(sf::VideoMode(100, 100), "Double Pendulum", sf::Style::Fullscreen, settings)
{

}
//initialize variables
void Simulation::initialize() 
{
    settings.antialiasingLevel = 8; //antialiasing ensures smooth rotations and less pixelation

    font.loadFromFile("DoublePendulum/resources/mainFont.otf");
    text.setFont(font);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::Black);

    pendulumHolder.setRadius(10);
    pendulumHolder.setOrigin(pendulumHolder.getRadius(), pendulumHolder.getRadius());
    pendulumHolder.setFillColor(sf::Color::Black);
    pendulumHolder.setOutlineColor(sf::Color::White);
    pendulumHolder.setOutlineThickness(2);
    pendulumHolder.setPosition(sf::Vector2f(window.getSize().x / 2, 300));
}
//function to run the entire thing
void Simulation::runSimulation() 
{
    initialize(); //init variables

    while (window.isOpen())
    {

        checkForInput(); //check for user input

        updatePendulums(); //update the pendulums

        window.clear(sf::Color(188, 201, 235)); //clear and set background color

        drawObjects(); //draw balls, lines, and trails

        window.display(); //display results
    }
}

//--------FUNCTIONS THAT HELP WITH CHECKING INPUT----------
//add another pendulum
void Simulation::addPendulum()
{
    std::vector <PendulumSection*> tempPendulum; //create a empty pendulum and add to pendulums vector
    pendulums.push_back(tempPendulum);

    PendulumSection* tempPendulumSection = new PendulumSection(100, 90, 300, window.getSize().x / 2, 300); //create the first section in this new pendulum and add it to the pendulum we just created
    pendulums[pendulums.size() - 1].push_back(tempPendulumSection);

    trails.push_back(singularTrail);
}
//add another section(arm+body) to current pendulum we are on
void Simulation::addSection()
{
    PendulumSection* tempPendulumSection = new PendulumSection(100, 90, 300, pendulums[pendulums.size() - 1][pendulums[pendulums.size() - 1].size() - 1]); //create a pendulum section connected to its parent pendulum section
    pendulums[pendulums.size() - 1].push_back(tempPendulumSection); //add the section to the most recent pendulum created
    trails.push_back(singularTrail);
}
//clear screen
void Simulation::clear()
{
    pendulums.clear();
    trails.clear();
}
//change game speed
void Simulation::changeSimulationSpeed(int upOrDown)
{
    currSimulationSpeed += upOrDown * 2.5f;
}
//pause game
void Simulation::togglePause()
{
    if (currSimulationSpeed == 0) //if currently paused, unpause game with our previous simulation speed
    {
        currSimulationSpeed = prevSimulationSpeed;
    }
    else //if currently unpaused, save the current speed to the prev speed and pause the game
    {
        prevSimulationSpeed = currSimulationSpeed;
        currSimulationSpeed = 0;
    }
}
//fade background to black and make only the bodies visible (not the arms)
void Simulation::fadeToBlack()
{

}
//check for user input
void Simulation::checkForInput() 
{
    sf::Event event;

    while (window.pollEvent(event))
    {
        //close window when the x at top right is clicked
        if (event.type == sf::Event::Closed)
            window.close();

        //close window when esc is pressed
        else if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Escape)
            window.close();

        //add pendulum when "A" is clicked
        else if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::A)
            addPendulum();

        //add another section(arm+body) to current pendulum we are on when "S" is clicked
        else if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::S)
            addSection();

        //increase game speed when up arrow is clicked
        else if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Up)
        {
            if (currSimulationSpeed <= 27.5) //30 is bound for max speed
                changeSimulationSpeed(1); //1 for increasing speed
        }

        //decrease game speed when down arrow is clicked
        else if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Down)
        {
            if (currSimulationSpeed > 2.5) //0.1 is bound for min speed
                changeSimulationSpeed(-1); //-1 for decreasing speed
        }

        //Pause the game when space is clicked
        else if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Space)
            togglePause();

        //fade background to black and make only the bodies visible (not the arms) when "B" is clicked
        else if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::B)
            fadeToBlack();

        //clear screen when "C" is clicked
        else if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::C)
            clear();
    }
}

//--------DRAW AND UPDATE FUNCTIONS---------------------
void Simulation::updatePendulums() //update the pendulums
{
    sf::Vertex singularVertex; //holder for vertex's we will use in each trail. each singularTrail will require multiple. Muliple singularTrails go into the variable "trails"
    for (int i = 0; i < pendulums.size(); i++)
    {
        for (int j = pendulums[i].size(); j > 1; j--) //start from bottom pendulum up, dont do top pendulum
        {
            pendulums[i][j - 1]->updatePendulum();
        }
    }

    for (int i = 0; i < pendulums.size(); i++)
    {
        for (int j = 0; j < pendulums[i].size(); j++)
        {
            pendulums[i][j]->updatePos(clock.getElapsedTime().asSeconds() * currSimulationSpeed); //update position with desired simulationSpeed
            singularVertex.position = pendulums[i][j]->getEndingPosition(); //update a vertex
            singularVertex.color = sf::Color::Red;
            trails[j].push_back(singularVertex); //add vertex to the trail
        }
    }
    clock.restart();
}
void Simulation::drawObjects() //draw objects (lines, balls, trails)
{   
    for (int i = 0; i < trails.size(); i++) //draw trails
    {
        if (trails[i].size() > 0)
            window.draw(&trails[i][0], trails[i].size(), sf::Lines);
    }

    for (int i = 0; i < pendulums.size(); i++)
    {
        for (int j = 0; j <pendulums[i].size(); j++)
        {
            pendulums[i][j]->drawArm(window); //draw arms first
        }
    }

    for (int i = 0; i < pendulums.size(); i++)
    {
        for (int j = 0; j < pendulums[i].size(); j++)
        {
            pendulums[i][j]->drawBody(window); //draw bodies second
        }
    }

    window.draw(pendulumHolder); //draw the pendulum holder
}






