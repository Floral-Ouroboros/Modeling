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
    }
    void dysonComponent::run() {
        bool obstructionDetected = false; //If the probe has found an obstruction, this will be true
        //Check for obstructions:
        for (int cx = 1; cx <= sensorRange; cx++) {
            if (board[location.x - cx][location.y].obstruction) { //If obstructed in front within range
                obstructionDetected = true; //Record obstruction
                for (int cy = 1; cy <= sensorRange; cx++) { // Then check surrounding tiles
                    if (board[location.x - cx][location.y - cy].obstruction) { //Check if above is obstructed (once)
                        if (board[location.x - cx][location.y - cy].obstruction) { //If so, check if below is obstructed (once)
                            //If so, move in a random direction:
                            srand(time(0)); 
                            if (rand() % 2 == 1) {
                                direction = 1;
                            }
                            else {
                                direction = -1;
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
        for (int i = 0; i < (sqrt(obstructionSize) - 1); i++) { 
            board[dx - i][dy - i].obstruction = true;
            board[dx - i][dy].obstruction = true; 
            board[dx][dy - i].obstruction = true;
            board[dx - i][dy - i].timeUntilClear = lingeringConstant;
            board[dx - i][dy].timeUntilClear = lingeringConstant; 
            board[dx][dy - i].timeUntilClear = lingeringConstant;
        }
    }
    void Sun::print() {
        for (int dy = 0; dy < boardSize; dy++) {
            for (int dx = 0; dx < boardSize; dx++) {
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

                std::cout << std::endl;
            }
        }
    }
    void Sun::update() {
        srand(time(0));

        if ((rand() % 100) + 1 <= volatility) { //Random chance for eruption to occur
            eruptRandom(); // Erupt if chance triggers
        }

    }

//   //   //   Main Function   //   //   //

int main() {
    Sun a;
    a.setVolatility(100);

    a.update();
    a.update();
    a.print();

    return 0;
}