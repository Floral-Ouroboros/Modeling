#include <iostream>
#include <fstream>

class reaction {
    private:
        float substrate; //Amount of substrate, measured in Molar.
        float enzyme; //Amount of enzyme, measured in Molar.
        float enzymeComplex; //Amount of combined enzyme and substrate, measured in Molar.
        float product; //Amount of product, measured in Molar.
        float k1; //Rate of change of E + S --> Es
        float k2; //Rate of change of ES --> E + S
        float k3; //Rate of change of ES --> E + P
        float k4; //Rate of change of E + P --> Es
    public:
        //Constructors:
        reaction();
        //Setters:
        void setSubstrate(float x); 
        void setEnzyme(float x); 
        void setEnzymeComplex(float x); 
        void setProduct(float x);
        void setK1(float x); 
        void setK2(float x); 
        void setK3(float x); 
        void setK4(float x); 
        //Getters:
        float getSubstrate(); 
        float getEnzyme(); 
        float getEnzymeComplex(); 
        float getProduct();
        float getK1(); 
        float getK2(); 
        float getK3(); 
        float getK4(); 
        //Utility:
        void model(float time, float delt); //The amount of time we want to model (seconds) and the timestep length
};

//Constructors:
reaction::reaction() {
    substrate = 0; 
    enzyme = 0; 
    enzymeComplex = 0;
    product = 0; 
    k1 = 0;
    k2 = 0; 
    k3 = 0;
    k4 = 0;
}
//Setters:
void reaction::setSubstrate(float x) {
    substrate = x;
}
void reaction::setEnzyme(float x) {
    enzyme = x;
}
void reaction::setEnzymeComplex(float x) {
    enzymeComplex = x;
}
void reaction::setProduct(float x) {
    product = x;
}
void reaction::setK1(float x) {
    k1 = x;
}
void reaction::setK2(float x) {
    k2 = x;
}
void reaction::setK3(float x) {
    k3 = x;
}
void reaction::setK4(float x) {
    k4 = x;
}
//Getters:
float reaction::getSubstrate() {
    return substrate;
}
float reaction::getEnzyme() {
    return enzyme;
}
float reaction::getEnzymeComplex() {
    return enzymeComplex;
}
float reaction::getProduct() {
    return product;
}
float reaction::getK1() {
    return k1;
}
float reaction::getK2() {
    return k2;
}
float reaction::getK3() {
    return k3;
}
float reaction::getK4() {
    return k4;
}
//Utility:
void reaction::model(float time, float delt) { //The amount of time we want to model (seconds) and the timestep length
    std::ofstream sub, com, pro, enz;
    //The vairables are so we don't change things we need for further calculation
    float complexStorage; 
    float substrateStorage;
    float productStorage;
    float enzymeStorage;

    sub.open("enzymeModel_Substrate.txt");
    com.open("enzymeModel_Complex.txt");
    pro.open("enzymeModel_Product.txt");
    enz.open("enzymeModel_Enzyme.txt");

    for (float t = 0; t <= time; t += delt) {
        complexStorage = enzymeComplex; 
        substrateStorage = substrate;
        productStorage = product;
        enzymeStorage = enzyme;

        sub << substrate << std::endl;
        com << enzymeComplex << std::endl;
        pro << product << std::endl;
        enz << enzyme << std::endl;

        substrate += (k2 * complexStorage) - (k1 * enzymeStorage * substrateStorage);
        product += (k3 * complexStorage) - (k4 * enzymeStorage * productStorage);
        enzyme += ((k2 + k3) * complexStorage) -(k1 * enzymeStorage * substrateStorage) - (k4 * enzymeStorage * productStorage);
        enzymeComplex += (k1 * enzymeStorage * substrateStorage) + (k4 * enzymeStorage * productStorage) - ((k2 + k3) * complexStorage);

    }

    sub.close();
    com.close();
    pro.close();
    enz.close();
}


int main() {
    reaction a;

    a.setK1(0.05);
    a.setK2(0.1);
    a.setK3(0.02);
    a.setK4(0.0);

    a.setSubstrate(1);
    a.setEnzyme(1);

    a.model(30, 0.05);
    
    return 0;
}