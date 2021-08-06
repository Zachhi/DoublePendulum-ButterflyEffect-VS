#include "Simulation.h"

//constructor
Simulation::Simulation() : window(sf::VideoMode(1000, 1000), "Double Pendulum", sf::Style::Fullscreen, settings)
{

}
//initialize variables
void Simulation::initialize() 
{
    //window.setFramerateLimit(100);
    //window.setVerticalSyncEnabled(true);
    settings.antialiasingLevel = 8; //antialiasing ensures smooth rotations and less pixelation

    //initialize text boxes
    font.loadFromFile("DoublePendulum/resources/mainFont.otf");
    simSpeedText.setFont(font);
    simSpeedText.setCharacterSize(16);
    simSpeedText.setFillColor(sf::Color::White);
    simSpeedText.setString("Simulation Speed: 1.0x");
    simSpeedText.setPosition(window.getSize().x - 250, window.getSize().y - 20);

    currStyleText.setFont(font);
    currStyleText.setCharacterSize(16);
    currStyleText.setFillColor(sf::Color::White);
    currStyleText.setString("Current Style: " + currStyle);
    currStyleText.setPosition(window.getSize().x - 250, window.getSize().y - 60);

    trailTypeText.setFont(font);
    trailTypeText.setCharacterSize(16);
    trailTypeText.setFillColor(sf::Color::White);
    trailTypeText.setString("Trail Type: " + trailType);
    trailTypeText.setPosition(window.getSize().x - 250, window.getSize().y - 40);

    controlsText.setFont(font);
    controlsText.setCharacterSize(16);
    controlsText.setFillColor(sf::Color::White);
    controlsText.setString("Shift for controls");
    controlsText.setPosition(10, 10);

    //initialize pendulum holder (the circle in middle that appears to "hold" the pendulums
    pendulumHolder.setRadius(10);
    pendulumHolder.setOrigin(pendulumHolder.getRadius(), pendulumHolder.getRadius());
    pendulumHolder.setFillColor(sf::Color::Black);
    pendulumHolder.setOutlineColor(sf::Color::White);
    pendulumHolder.setOutlineThickness(2);
    pendulumHolder.setPosition(sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2));

    //background color
    bgColor = sf::Color::Black;
}
//function to run the entire thing
void Simulation::runSimulation() 
{
    initialize(); //init variables

    while (window.isOpen())
    {

        checkForInput(); //check for user input

        if(!isPaused)
            updatePendulums(); //update the pendulums

        updateText(); //update text objects

        window.clear(bgColor); //clear and set background color

        drawObjects(); //draw bodies, arms, trails, text

        window.display(); //display results
    }
}
// //check for user input
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

        //add pendulum(s) when "A" is clicked
        else if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::A)
        {
            if (currStyle == "3") //if style 3, spawn multiple double pendulums with a total angle difference of .000001 radians between first pendulum spawned and last pendulum spawned
                addMultiplePendulums(0.000001, 1000); //isStarting variable as true, as this will be making new pendulums
            else
                addSinglePendulum(-1, -1); //else just add a double pendulum with random angle
        }

        //add section(s) to pendulum(s) when "S" is clicked
        else if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::S)
        {
            if (currStyle == "3") //if style 3, spawn a section on each existing pendulum
                addMultipleSections(0.000001); //isStarting variable as false, as this will be adding new sections to existing pendulums
            else
                addSingleSection(-1); //else just add a section to the current pendulum with random angle
        }

        //increase game speed when up arrow is clicked
        else if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Up)
        {
            if (currSimulationSpeed <= 3.9) //4 is bound for max speed
                changeSimulationSpeed(1); //1 for increasing speed
        }

        //decrease game speed when down arrow is clicked
        else if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Down)
        {
            if (currSimulationSpeed > .1) //0.1 is bound for min speed
                changeSimulationSpeed(-1); //-1 for decreasing speed
        }

        //Pause the game when space is clicked
        else if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Space)
            togglePause();

        //change to style 1 when "1" is clicked. Normal pendulums
        else if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Num1)
            styleOne();

        //change to style 2 when "2" is clicked. Make only second, third, fourth, etc bodies visible with a bright color
        else if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Num2)
            styleTwo();

        //Change style3 when "3" is clicked. Butterfly style. Allows us to see butterfly effect
        else if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Num3)
            styleThree();

        //Change trail type when "T" is clicked
        else if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::T)
            changeTrailType();

        //clear screen when "C" is clicked
        else if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::C)
            clear();

        //show rules when "Lshift" is clicked
        else if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::LShift)
            toggleControls();
    }
}

//-------ADDING OBJECTS----------
//add a new double pendulum
void Simulation::addSinglePendulum(float firstDesiredAngle, float secondDesiredInc)
{
    //if one of the passed arguments is -1, give first section either angle of 270 or 90
    if (firstDesiredAngle == -1)
    {
        int randPick = rand() % 2 + 1;
        if (randPick == 1)
            firstDesiredAngle = 90;//rand() % 190 + 100;
        else
            firstDesiredAngle = 270;
    }
    if(secondDesiredInc == -1) //give second angle random val 0-65. second angle will be firstAngle + this value
        secondDesiredInc = rand() % 360 + 0;

    Pendulum firstSection(133.33, firstDesiredAngle, 400, window.getSize().x / 2, window.getSize().y / 2); //mass, angle, armlength, x, y, trails
    pendulums.push_back(firstSection); //add first section

    //update the first section to correct style
    if (currStyle == "2")
        pendulums[pendulums.size() - 1].styleTwo(); //only apply to pendulm we just created
    else if (currStyle == "3")
    {
        //apply style 3 to pendulum we just created

        if (pendulums.size() > 1) //only do this if this isnt the first pendulum created
            pendulums[pendulums.size() - 1].styleThree(pendulums[pendulums.size() - 2].getArmColor()); //this is saying to set the pendulum we just pushed back to style three, with the color of the previous pendulum
        else //if this is first pendulum, make it a random color
            pendulums[pendulums.size() - 1].styleThree(getRandomColor());
    }

    //now add a section to this pendulum we just made, so we have a double pendulum
    if (firstDesiredAngle == 90) //we do this to make sure the second pendulum is always facing more up than down
        addSingleSection(firstDesiredAngle + secondDesiredInc); 
    else
        addSingleSection(firstDesiredAngle - secondDesiredInc);

}
//add another section(arm+body) to current pendulum we are on
void Simulation::addSingleSection(float desiredAngle)
{
    if (pendulums.size() > 0) //make sure theres a pendulum we can add a section to
    {
        if (desiredAngle == -1) //if passed angle is -1, give it a random angle
            desiredAngle = rand() % 360 + 0;

        pendulums[pendulums.size() - 1].add(133.33, desiredAngle, 400); //add section to the last pendulum in pendulums

        //update style
        if (currStyle == "2")
            pendulums[pendulums.size() - 1].styleTwo();  //only apply to pendulm we just created
        else if (currStyle == "3")
            pendulums[pendulums.size() - 1].styleThree(pendulums[pendulums.size() - 1].getArmColor()); //apply style three to pendulum we just created, with the same color as its first section. first section is created in addPendulum()
    }
}
//spawn multiple double pendulums at once. Helps with style 3 for the butterfly effect
void Simulation::addMultiplePendulums(float totalAngleDifference, float numPendulums)
{
    if (currStyle == "3") //only spawnMultiple if current stlye is 3. This is the style it is meant for. The other styles look trash when you spawn 1000+ pendulums
    {
        float angleIncRad = totalAngleDifference / numPendulums;
        float angleIncDeg = angleIncRad * (180 / PI); //amount we have to increment each pendulum's angle by, in order to get the "totalAngleDifference" in radians between all pendulums

        float startingAngle = rand() % 170 + 100; //give it a random starting angle
        float secondAngleIncrement = rand() % 45 + 0; //give the second sections a random increment
        //float startingAngle = 235;

        for (int i = 0; i < numPendulums; i++)
        {
           addSinglePendulum(startingAngle, 0);
           startingAngle += angleIncDeg;
        }
        styleThree(); //so we can get a nice color gradient between the pendulums. Lets us have nice visuals for the butterfly effect
    }
}
//spawn a section on each existing pendulum. Helps with style 3 for the butterfly effect
void Simulation::addMultipleSections(float totalAngleDifference)
{
    float numPendulums = pendulums.size();
    float angleIncRad = totalAngleDifference / numPendulums;
    float angleIncDeg = angleIncRad * (180 / PI); //amount we have to increment each pendulum's angle by, in order to get the "totalAngleDifference" in radians between all pendulums

    if (numPendulums > 0 && currStyle == "3") //make sure at least one pendulum exists, and that we are on style 3
    {
        float startingAngle = rand() % 45 + 0;
        for (int i = 0; i < numPendulums; i++)
        {
            pendulums[i].add(100, startingAngle, 300);
            startingAngle += angleIncDeg;
        }
        styleThree();
    }
}

//----------STYLE FUNCTIONS-----------
//change to normal style (style 1) just normal pendulums
void Simulation::styleOne()
{
    currStyle = "1";
    for (int i = 0; i < pendulums.size(); i++)
    {
        pendulums[i].styleOne();
    }
}
//change to hidden style (style 2). change arms and first bodies to transparent and make only the second, third, etc. bodies visible with bright colors
void Simulation::styleTwo()
{
    currStyle = "2";
   for (int i = 0; i < pendulums.size(); i++)
   {
       pendulums[i].styleTwo();
   }
}
//change to burtteryfly style (style 3). lets us see butterfly effect
void Simulation::styleThree()
{
    currStyle = "3"; //update currStyle

    int colorPicker = rand() % 2 + 1; //theres 2 diff color selecting methods. Each lead to nice looking colors. This gives it a 50/50 chance to pick either one
    if (colorPicker == 1)
        styleThreeColorHelpOne();
    else
        styleThreeColorHelpTwo();
}
//help for changing style 3 transparency
int Simulation::styleThreeTransparencyHelp()
{
    //this helps us change level of transparency after every click. Very transparent for one, in the midde for two and very solid for 3
    //update transparency and "style3TransparencyHelp"
    int transparency;
    if (style3TransparencyHelp == 1)
    {
        transparency = rand() % 10 + 1; //help make very transparent
        style3TransparencyHelp += 1;
    }
    else if (style3TransparencyHelp == 2)
    {
        transparency =  rand() % 20 + 60; //everything in between
        style3TransparencyHelp += 1;
    }
    else
    {
        transparency = 255; //help make solid
        style3TransparencyHelp = 1;
    }
    return transparency;
}
//help selecting style 3 colors with method 1 and applying
void Simulation::styleThreeColorHelpOne()
{
    sf::Color newColor; //color we will be setting the pendulum to
    int transparency = styleThreeTransparencyHelp(); //update the transparency the arms will be

    int colorPicker = rand() % 360 + 0;
    float H = colorPicker;//H = 205   This is the desiredColor that we want to reach. we go from white->desiredColor->black
    float S = 0; //S = 0%
    float V = 100; //V = 100%
    float amtOfIncS = (100.0f / pendulums.size()) * 2.0f; //amt of changes to get from white->desiredColor. equation is ((amount of floats to move in all / total pendulums)) * (inverse of how long we want it to go on for)
    float amtOfIncV = (100.0f / pendulums.size()) * 2.0f; // amt of changes to get from desiredColor->black after                                               so if we want it to go for half the time, do the inverese of 1/2, or 2
    for (int i = pendulums.size(); i > 0; i--)
    {
        if (S < 100)
        {
            S += amtOfIncS;
            if (S > 100)
                S = 100;
        }
        else
        {
            V -= amtOfIncV;
            if (V < 15)
                V = 15;
        }
        newColor = HSVtoRGB(H, S, V);
        newColor.a = transparency;
        pendulums[i-1].styleThree(newColor); //gives all the arms of the pendulum we are currently on the color "editedColor", and sets the bodies to transparent
    }
}
//help selecting style 3 colors with method 2 and applying
void Simulation::styleThreeColorHelpTwo()
{
    sf::Color newColor; //color we will be setting the pendulum to
    int transparency = styleThreeTransparencyHelp(); //update the transparency the arms will be

    int colorPicker = rand() % 360 + 0;
    float desiredColor = colorPicker;
    float H = desiredColor;//H = 205   This is the desiredColor that we want to reach. we go from white->desiredColor->black
    float S = 0; //S = 0%
    float V = 100; //V = 100%
    bool check1 = false, check2 = false, check3 = false, check4 = false;

    float check1Inc = (25.0f / pendulums.size()) * 15.0f;
    float check2Inc = (100.0f / pendulums.size()) * 4.0f;
    float check3Inc = (35.0f / pendulums.size()) * 3.0f;
    float check4Inc = (75.0f / pendulums.size()) * 1.538f;

    for (int i = pendulums.size(); i > 0; i--)
    {
        if (!check1)
        {
            V -= check1Inc;
            if (V <= 75)
                check1 = true;
        }
        else if (!check2)
        {
            S += check2Inc;
            if (S >= 100)
                check2 = true;
        }
        else if (!check3)
        {
            H += check3Inc;
            if (H >= (desiredColor + 55))
                check3 = true;
        }
        else
        {
            V -= check4Inc;
        }

        newColor = HSVtoRGB(H, S, V);
        newColor.a = transparency;
        pendulums[i - 1].styleThree(newColor); //gives all the arms of the pendulum we are currently on the color "editedColor", and sets the bodies to transparent
    }
}

//---------MISC CONTROLS----------
//clear screen
void Simulation::clear()
{
    pendulums.clear();
}
//change game speed
void Simulation::changeSimulationSpeed(float upOrDown)
{
    currSimulationSpeed += upOrDown * .1f;
}
//helps us change trail type
void Simulation::changeTrailType()
{
    if (trailType == "Fade")
        trailType = "Always";
    else if (trailType == "Always")
        trailType = "None";
    else
        trailType = "Fade";

    trailTypeText.setString("Trail Type: " + trailType);
}
//pause and unpause game
void Simulation::togglePause()
{
    if (isPaused) //if currently paused, unpause game
    {
        isPaused = false;
        clock.restart();
    }
    else //if currently unpaused, pause the game
        isPaused = true;
}
//show and hide controls
void Simulation::toggleControls()
{
    if (isControlsShowing)
    {
        controlsText.setString("Shift for controls");
        isControlsShowing = false;
    }
    else
    {
        controlsText.setString("A: Add double pendulum\nS: Add section to current pendulum\nC: Clear screen\n1: Toggle style 1\n2: Toggle style 2\n3: Toggle style 3\nSpace: Pause game\nUp Arrow: Increase game speed\nDown Arrow: Decrease game speed\nT: Toggle trail type\nShift: Show/hide controls\nEscape: Exit program\nNote: When in style 3, the A key will add multiple double pendulums, and the S key will add sections to every double pendulum");
        isControlsShowing = true;
    }
}

//--------DRAW UPDATE FUNCTIONS---------------------
//update the pendulums. Calculate the physics of each pendulum and update the position/angle of each pendulum accordingly
void Simulation::updatePendulums() 
{
    for (int i = 0; i < pendulums.size(); i++) //first calculate all of the pendulums physics (angular acceleration)
        pendulums[i].calculatePendulum(); 

    for (int i = 0; i < pendulums.size(); i++) //now update all of the pendulums positions (basically update position/angle for each pendulum, based on values calculated in .calculatePendulum())
        pendulums[i].updatePos(clock.getElapsedTime().asSeconds() * currSimulationSpeed * 13); //update position with desired simulationSpeed, or change in time. 13 is arbritray number that works
   
    clock.restart(); //so we can keep constant time variable.

    if (trailClock.getElapsedTime().asMilliseconds() > 0.1f) //update trails after a certain time so we dont have a ton of uneeded trails
    {
        for (int i = 0; i < pendulums.size(); i++)
        {
            pendulums[i].updateTrails(trailType);
        }
        trailClock.restart();
    }

}
//update text objects
void Simulation::updateText()
{
    //update simSpeed text
    if (isPaused)
        simSpeedText.setString("Simulation Speed: 0.0x");
    else //make the value rounded to 2 decimals
    {
        std::string simSpeedString = std::to_string(currSimulationSpeed);
        std::string rounded = simSpeedString.substr(0, simSpeedString.find(".") + 3);
        simSpeedText.setString("Simulation Speed: " + rounded + "x");
    }
    //update currStyleText
    currStyleText.setString("Current Style: " + currStyle);
}
//draw everything (arms, bodies, trails, text)
void Simulation::drawObjects() 
{   
    for (int i = 0; i < pendulums.size(); i++) //draw trails first. Everything else should show "above" trails
        pendulums[i].drawTrail(window);
    
    for (int i = 0; i < pendulums.size(); i++)
        pendulums[i].drawArm(window); //draw arms next

    window.draw(pendulumHolder); //draw the pendulum holder above arms but under bodies

    for (int i = 0; i < pendulums.size(); i++)
            pendulums[i].drawBody(window); //draw bodies last

    //draw all text boxes
    window.draw(currStyleText); //draw curr ctyle text
    window.draw(simSpeedText); //draw simulation speed text
    window.draw(trailTypeText); //draw the trail type text
    window.draw(controlsText); //draw controls
}

//---------COLOR FUNCTIONS----------
//get a nice looking bright and random color
sf::Color Simulation::getRandomColor()
{
    //get a random bright color for the body
    int picker = rand() % 3 + 1;
    int secondPicker = rand() % 2 + 1;
    float r, g, b;

    if (picker == 1)
    {
        if (secondPicker == 1)
        {
            r = 52;
            g = 235;
            b = rand() % 234 + 51;
        }
        else
        {
            r = 52;
            g = rand() % 234 + 51;
            b = 235;
        }
    }
    else if (picker == 2)
    {
        if (secondPicker == 1)
        {
            r = 235;
            g = 52;
            b = rand() % 234 + 51;
        }
        else
        {
            r = rand() % 234 + 51;
            g = 52;
            b = 235;
        }
    }
    else
    {
        if (secondPicker == 1)
        {
            r = rand() % 234 + 51;
            g = 235;
            b = 52;
        }
        else
        {
            r = 235;
            g = rand() % 234 + 51;
            b = 52;
        }
    }

    return sf::Color(r, g, b);
}
//converts hsv colors to rgb colors
sf::Color Simulation::HSVtoRGB(float H, float S, float V)
{
    float s = S / 100;
    float v = V / 100;
    float C = s * v;
    float X = C * (1 - abs(fmod(H / 60.0, 2) - 1));
    float m = v - C;
    float r, g, b;
    if (H >= 0 && H < 60) {
        r = C, g = X, b = 0;
    }
    else if (H >= 60 && H < 120) {
        r = X, g = C, b = 0;
    }
    else if (H >= 120 && H < 180) {
        r = 0, g = C, b = X;
    }
    else if (H >= 180 && H < 240) {
        r = 0, g = X, b = C;
    }
    else if (H >= 240 && H < 300) {
        r = X, g = 0, b = C;
    }
    else {
        r = C, g = 0, b = X;
    }
    float R = (r + m) * 255;
    float G = (g + m) * 255;
    float B = (b + m) * 255;
    
    return sf::Color(R, G, B);
}






