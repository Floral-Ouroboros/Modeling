#include <iostream>
#include <fstream>
#include "enzyme.h"

/*
*/

struct environment {
    float glucose; //Amount of glucose, measured in Molar.
    float lactose; //Amount of lactose, measured in Molar.
    float galactose; //Amount of galactose, measured in Molar.
    void set(float gl, float l, float ga); //Sets all variables of environment.
};

void environment::set(float gl, float l, float ga) {
    glucose = gl;
    lactose = l;
    galactose = ga;
}

class organism {
    private:
        float glucose; //Amount of glucose, measured in Molar.
        float lactose; //Amount of lactose, measured in Molar.
        float galactose; //Amount of galactose, measured in Molar.
        float mRNA; //The amount of mRNA (M)
        float transportEfficiencyLactose; //The percent of lactose available in environment that is taken in
        float transportEfficiencyGlucose; //The percent of glucose available in environment that is taken in
        float transcriptionRate; //Rate at which transcription of the Lac operon occurs (sec)
        float translationRate; //Rate at which the translation of the Lac operon mRNA occurs (sec)
        float glucoseLactoseCompetition; //A proportionality constant used to hamper lactase production according to glucose concentration
        reaction lactoseDecom; //Enzyme model defined in "enzyme.h"

    public:
        environment stage;

        //Constructors:
        organism(); //Default Constructor

        //Setters:
        void setGlucose(float x);
        void setLactose(float x);
        void setGalactose(float x);
        void setSubstrate(float x);
        void setProduct(float x);
        void setEnzyme(float x);
        void setMRNA(float x);
        void setK1(float x); //Rate of change of Enzyme + Substrate --> Enzyme_ Complex
        void setK2(float x); //Rate of change of Enzyme_Complex --> Enzyme + Substrate
        void setK3(float x); //Rate of change of Enzyme_ Complex --> Enzyme + Product
        void setK4(float x); //Rate of change of Enzyme + Product --> Enzyme_ Complex
        void setTransportEfficiencyLactose(float x);
        void setTranscriptionRate(float x);
        void setTranslationRate(float x);
        void setGlucoseLactoseCompetition(float x);

        //Getters:
        float getGlucose();
        float getLactose();
        float getGalactose();
        float getSubstrate();
        float getEnzyme();
        float getMRNA();
        float getK1();
        float getK2();
        float getK3();
        float getK4();
        float getTransportEfficiencyLactose();
        float getTranscriptionRate();
        float getTranslationRate();
        float getGlucoseLactoseCompetition();

        //Utility:
        void transport(); //Allows the organism to take in lactose from the environment
        void model(float time, float delt); //Models for a specified amount of time using specified time-steps.
        void update(); //Updates the organism variables in accordance with the enzyme model's
};

//Constructors:
organism::organism() { //Default Constructor
    glucose = 0; 
    lactose = 0; 
    galactose = 0; 
    mRNA = 0;
    transportEfficiencyLactose = 0; 
    transcriptionRate = 0;
    translationRate = 0;
    glucoseLactoseCompetition = 1;
    lactoseDecom; //Uses default constructor in its header file.
    stage; //Uses compiler-provided default constructor.
}

//Setters:
void organism::setGlucose(float x) {
    glucose = x;
    setProduct(x); //Sets the product variable in the enzyme model eqal to input.
}
void organism::setLactose(float x) {
    lactose = x;
    setSubstrate(x); //Sets the substrate variable in the enzyme model eqal to input.
}
void organism::setGalactose(float x) {
    galactose = x;
}
void organism::setSubstrate(float x) {
    lactoseDecom.setSubstrate(x);
}
void organism::setProduct(float x) {
    lactoseDecom.setProduct(x);
}
void organism::setEnzyme(float x) {
    lactoseDecom.setEnzyme(x);
}
void organism::setMRNA(float x) {
    mRNA = x;
}
void organism::setK1(float x) {
    lactoseDecom.setK1(x);
}
void organism::setK2(float x) {
    lactoseDecom.setK2(x);
}
void organism::setK3(float x) {
    lactoseDecom.setK3(x);
}
void organism::setK4(float x) {
    lactoseDecom.setK4(x);
}
void organism::setTransportEfficiencyLactose(float x) {
    transportEfficiencyLactose = x;
}
void organism::setTranscriptionRate(float x) {
    transcriptionRate = x;
}
void organism::setTranslationRate(float x) {
    translationRate = x;
}
void organism::setGlucoseLactoseCompetition(float x) {
    glucoseLactoseCompetition = x;
}

//Getters:
float organism::getGlucose() {
    return glucose;
}
float organism::getLactose() {
    return lactose;
}
float organism::getGalactose() {
    return galactose;
}
float organism::getSubstrate() {
    return lactoseDecom.getSubstrate();
}
float organism::getEnzyme() {
    return lactoseDecom.getEnzyme();
}
float organism::getMRNA() {
    return mRNA;
}
float organism::getK1() {
    return lactoseDecom.getK1();
}
float organism::getK2() {
    return lactoseDecom.getK2();
}
float organism::getK3() {
    return lactoseDecom.getK3();
}
float organism::getK4() {
    return lactoseDecom.getK4();
}
float organism::getTransportEfficiencyLactose() {
    return transportEfficiencyLactose;
}
float organism::getTranscriptionRate() {
    return transcriptionRate;
}
float organism::getTranslationRate() {
    return translationRate;
}
float organism::getGlucoseLactoseCompetition() {
    return glucoseLactoseCompetition;
}

//Utility:
void organism::transport() {
    //Transport Lactose from external environment to internal environemnt:
    setLactose(lactose + (transportEfficiencyLactose * stage.lactose));
    stage.lactose = (1 - transportEfficiencyLactose) * stage.lactose;

    setGlucose(glucose);
    // ! ! ! Add a separate one for glucose ! ! !
}
void organism::model(float time, float delt) {
    // Place holder
    std::ofstream sub, com, pro, enz, rna;

    //Opening data files for output:
    sub.open("operonModel_Substrate.txt");
    com.open("operonModel_Complex.txt");
    pro.open("operonModel_Product.txt");
    enz.open("operonModel_Enzyme.txt");
    rna.open("operonModel_MRNA.txt");

    //Actual Calculation:
    for (float t = 0; t <= time; t += delt) {
        transport();

        if (lactose >= 0) {
            //Data Handling:
            update();
            sub << lactoseDecom.getSubstrate() << std::endl;
            com << lactoseDecom.getEnzymeComplex() << std::endl;
            pro << lactoseDecom.getProduct() << std::endl;
            enz << lactoseDecom.getEnzyme() << std::endl;
            rna << mRNA << std::endl;

            //Translation:
            if (stage.glucose > 0) {
                mRNA += glucoseLactoseCompetition * (transcriptionRate * delt); //Translation with competition
            }
            else {
                mRNA += (transcriptionRate * delt); //Translation without competition
            }
            
            //Transcription:
            lactoseDecom.setEnzyme(lactoseDecom.getEnzyme() + (translationRate * delt));

            //Catalysis:
            lactoseDecom.model();
        }
    }

    //Closing logging files:
    sub.close();
    com.close();
    pro.close();
    enz.close();
    rna.close();
}
void organism::update() {
    lactose = lactoseDecom.getSubstrate();
    glucose = lactoseDecom.getProduct();
    galactose = lactoseDecom.getProduct(); // ASSUMES SAME INITIAL AMOUNT OF GLUCOSE AND GALACTOSE
}



int main() {
    organism x;

    //Conditions:
    x.stage.set(10, 10, 10);
    x.setK1(0.05);
    x.setK2(0.1);
    x.setK3(0.02);
    x.setK4(0);
    x.setTransportEfficiencyLactose(0.2);
    x.setTranscriptionRate(0.05);
    x.setTranslationRate(0.01);
    x.setGlucoseLactoseCompetition(0.8);

    x.model(100, 0.05);

    return 0;
}