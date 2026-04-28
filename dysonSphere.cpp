#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include <windows.h>

//   //   //   Global Variables   //   //   //

double maxSize = 130; // Max size for all components
double minSize = 13; // Min size for all components
const int boardSize = 20;

//   //   //   Position Struct   //   //   //

struct Position {
    int x; 
    int y;
    int dyson; // How many dyson components are presnt on the the space
    bool obstruction; // If an obstruction is present on the space
    int timeUntilClear;

    Position();
    void setPosition(int dx, int dy);
};

Position board[boardSize][boardSize];

Position::Position() {
    x = 0; 
    y = 0;
    dyson = 0; // How many dyson components are presnt on the the space
    obstruction = false; // If an obstruction is present on the space
    timeUntilClear = 0;
}
void Position::setPosition(int dx, int dy) {
    x = dx;
    y = dy;
}

//   //   //   Dyson Component Class   //   //   //

class dysonComponent {
    private:
        double size; 
        double sensorRange = 3;
        double thrusterSpeed = 1;
        bool alive;
        int split; // -1 = converge; 0 = remain normal; 1 = split;
        int direction; // -1 = down; 0 foward (normal); 1 = up
        Position location;
    public:
        //Constructors:
            dysonComponent();
        //Setters:
            void setSize(double x);
            void setSensorRange(double x);
            void setThrusterSpeed(double x);
            void setAlive(bool x);
            void setSplit(int x);
            void setDirection(int x);
            void setLocation(int x, int y);
        //Getters:
            double getSize();
            double getSensorRange();
            double getThrusterSpeed();
            bool getAlive();
            int getSplit();
            int getDirection();
            Position getLocation();
        //Utilities:
            void seperate();
            void converge();
            void glide(); //Moves normally due to orbitting the sun (to the left)
            void thrust(bool up); // Engages the component's thrusters to move up or down
            void run(); // Performs one turn worth of actions and checks
};
//Constructors:
    dysonComponent::dysonComponent() {
        Position x;
        x.setPosition(0, 0);

        size = 13; 
        sensorRange = 3;
        thrusterSpeed = 1;
        alive = true;
        split = 0;
        location = x;
    }
//Setters:
    void dysonComponent::setSize(double x) {
        size = x;
    }
    void dysonComponent::setSensorRange(double x) {
        sensorRange = x;
    }
    void dysonComponent::setThrusterSpeed(double x) {
        thrusterSpeed = x;
    }
    void dysonComponent::setAlive(bool x) {
        alive = x;
    }
    void dysonComponent::setSplit(int x) {
        split = x;
    }
    void dysonComponent::setDirection(int x) {
        direction = x;
    }
    void dysonComponent::setLocation(int x, int y) {
        location.setPosition(x, y);
    }
//Getters:
    double dysonComponent::getSize() {
        return size;
    }
    double dysonComponent::getSensorRange() {
        return sensorRange;
    }
    double dysonComponent::getThrusterSpeed() {
        return thrusterSpeed;
    }
    bool dysonComponent::getAlive() {
        return alive;
    }
    int dysonComponent::getSplit() {
        return split;
    }
    int dysonComponent::getDirection() {
        return direction;
    }
    Position dysonComponent::getLocation() {
        return location;
    }
//Utilities:
    void dysonComponent::seperate() {
        split = 1;
    }
    void dysonComponent::converge() {
        split = -1;
    }
    void dysonComponent::glide() {
        Position x;
        x = location;
        location.setPosition(x.x - 1, x.y);
        if (location.x < 0) {
            location.x = boardSize - 1 ;
        }
        board[x.x][x.y].dyson -=1;
        board[location.x][location.y].dyson += 1;
    }
    void dysonComponent::thrust(bool up) {
        Position x;
        x = location;
        if (up) {
            location.setPosition(x.x, x.y - 1);
        }
        if (!up) {
            location.setPosition(x.x, x.y + 1);
        }
        if (location.y < 0) {
            location.x = boardSize - 1 ;
        }
        if (location.y > boardSize) {
            location.x = 0 ;
        }
        board[x.x][x.y].dyson -=1;
        board[location.x][location.y].dyson += 1;
    }
    void dysonComponent::run() {
        bool obstructionDetected = false; //If the probe has found an obstruction, this will be true
        //Check for obstructions:
        for (int cx = 1; cx <= sensorRange; cx++) {
            if (board[location.x - cx][location.y].obstruction) { //If obstructed in front within range
                obstructionDetected = true; //Record obstruction
                for (int cy = 1; cy <= sensorRange; cy++) { // Then check surrounding tiles
                    if ((location.y - cx < 0) && (location.x - cx < 0)) { //Check if above is obstructed (once)
                        if (board[location.x - cx][location.y - cy].obstruction) {
                            if ((location.y - cx < 0) && (location.x - cx < 0) && board[location.x - cx][location.y - cy].obstruction) { //If so, check if below is obstructed (once)
                                //If so, move in a random direction:
                                srand(time(0)); 
                                if (rand() % 2 == 1) {
                                    direction = 1;
                                }
                                else {
                                    direction = -1;
                                }
                            }
                        }
                        else{ //If below isn't obstructed, then tell component to go down
                            direction = -1;
                        }
                    }
                    else{ //If above isn't obstructed, then tell component to go up
                        direction = 1;
                    }
                    
                }
            }
            else if (!obstructionDetected) {
                direction = 0;
            }
        }

        //Movement:
        if (!obstructionDetected) { //If there is no obstruction, don't engage thrusters
            glide(); //Allow the orbit around the sun to carry you like normal
        }
        else { // If an obstruction was detected and recorded
            if (direction == 1) { //If dyson records to move up, then move up
                thrust(true);
                glide();
            }
            else if (direction == -1) { // If dyson records to move down, then move down
                thrust(false);
                glide();
            }
        }

        //Check for destruction:
        if (board[location.x][location.y].obstruction) {
            alive = false;
        }
        else {
            alive = true;
        }

        //Check if above max size:
        if (size > maxSize) {
            split = 1;
        }
        else {
            split = 0; 
        }

        if (board[location.x][location.y].dyson > 1) {
            split = -1;
        }

    }

//   //   //   Sun Class   //   //   //

class Sun {
    private:
        float volatility; // Percent chance for solar obstruction
        float lingeringConstant; // How long it takes for a solar obstruction to dissipate
        int obstructionSize; // How big the obstructions 
        std::vector<dysonComponent> swarm; //List of compenents in the swarm
    public:
        //Constructors:
        Sun();
        //Setters:
        void setVolatility(float x);
        void setLingeringConstant(float x);
        void setObstructionSize(float x);

        //Getters:
        float getVolatility();
        float getLingeringConstant();
        int getObstructionSize();

        //Utilities:
        void generateComponent(int x, int y, double size); // Creates a new dyson component
        void deleteComponent(int x, int y); // Deletes a dyson components
        void converge(); //Adds two components together
        void split(); //Splits a component into two
        void eruptRandom();
        void print();
        void update();
        
};

//Constructors:
    Sun::Sun() {
        volatility = 0; // Percent chance for solar obstruction
        lingeringConstant = 10; // How long it takes for a solar obstruction to dissipate
        obstructionSize = 4;
        swarm; //List of compenents in the swarm
    }
//Setters:
    void Sun::setVolatility(float x) {
        volatility = x;
    }
    void Sun::setLingeringConstant(float x) {
        lingeringConstant = x;
    }
    void Sun::setObstructionSize(float x) {
        obstructionSize = x;
    }

//Getters:
    float Sun::getVolatility() {
        return volatility;
    }
    float Sun::getLingeringConstant() {
        return lingeringConstant;
    }
    int Sun::getObstructionSize() {
        return obstructionSize;
    }

//Utilities:
    void Sun::generateComponent(int x, int y, double size) {
        dysonComponent placeholder;

        placeholder.setSize(size);
        placeholder.setLocation(x, y);
        swarm.push_back(placeholder);
        board[x][y].dyson += 1; 
    }
    void Sun::deleteComponent(int x, int y) {
        Position location;
        bool completion = false;
        for (int i = 0; i < swarm.size(); i++) {
            location = swarm[i].getLocation();
            if (location.x == x && location.y == y) {
                board[x][y].dyson -= 1; 
                swarm.erase(swarm.begin() + i);
                completion = true;
                return;
            }
        }
        if (!completion) {
            std::cout << "Could not find the component attempting to be deleted. ";
        }
    }
    void Sun::converge() {

    }
    void Sun::split() {

    }
    void Sun::eruptRandom() {
        int dx, dy;
        srand(time(0));
        dx = (rand() % boardSize);
        Sleep(rand() % 201); //Sleep for 1-2 seconds
        dy = (rand() % boardSize);
        //ONLY WORKS FOR SIZE 4 AND DOESN'T SELECT OUTER EDGES:
        if (dx == 0) {
            dx += 1;
        }
        if (dy == 0) {
            dy += 1;
        }

        //Obstructes spaces within obstruction range:
        for (int i = 0; i <= (sqrt(obstructionSize) - 1); i++) { 
            board[dx - i][dy - i].obstruction = true;
            board[dx - i][dy].obstruction = true; 
            board[dx][dy - i].obstruction = true;
            board[dx - i][dy - i].timeUntilClear = lingeringConstant;
            board[dx - i][dy].timeUntilClear = lingeringConstant; 
            board[dx][dy - i].timeUntilClear = lingeringConstant;
        }
    }
    void Sun::print() {
        for (int dy = -1; dy <= boardSize; dy++) {
            for (int dx = -1; dx <= boardSize; dx++) {
                if (dx != -1 && dx != boardSize && dy != boardSize && dy != -1) {
                    switch (board[dx][dy].obstruction) {
                        case true:
                            std::cout << '*';
                            break;
                        case false:
                            if (board[dx][dy].dyson == 0) {
                                std::cout << ' ';
                            }
                            if (board[dx][dy].dyson > 0) {
                                std::cout << '#';
                            }
                            break;
                    }
                }
                else {
                    std::cout << '@';
                }
            }
            std::cout << std::endl;
        }
    }
    void Sun::update() {
        for (int y = 0; y < boardSize; y++) {
            for (int x = 0; x < boardSize; x++) {
                if (board[x][y].obstruction) {
                    board[x][y].timeUntilClear -= 1;
                }
            }
        }

        srand(time(0));
        if ((rand() % 100) + 1 <= volatility) { //Random chance for eruption to occur
            eruptRandom(); // Erupt if chance triggers
        }
        
        for (int i = 0; i < swarm.size(); i++) {
            swarm[i].run(); //Includes movement and death checks

            //If a component is dead, then delete it:
            switch(swarm[i].getAlive()) {
                case true:
                    break;
                case false:
                    deleteComponent(swarm[i].getLocation().x, swarm[i].getLocation().y);
                    break;
            }

            //Handling splits and convergences
            Position x;
            float size = 0;
            switch (swarm[i].getSplit()) {
                case -1:
                    //Converge
                    x = swarm[i].getLocation();
                    size += swarm[i].getSize();

                    for (int check = i; check < swarm.size(); check++) {
                        if (x.x == swarm[check].getLocation().x && x.y == swarm[check].getLocation().y) {
                            size += swarm[check].getSize();
                        }
                    }
                    deleteComponent(x.x, x.y);
                    generateComponent(x.x, x.y, size);
                    break;
                case 0:
                    //Nothing happens
                    break;
                case 1:
                    //Split
                    break;
            }
        }
        
    }

//   //   //   Main Function   //   //   //

int main() {
    Sun a;
    a.setVolatility(100);

    // a.update();
    // a.update();

    for (int i = 0; i < 1; i) {
        system("cls");
        a.generateComponent(1, 1, 100);
        a.update();
        a.print();
        Sleep(100);
    }


    return 0;
}