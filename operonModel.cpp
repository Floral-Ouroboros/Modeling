#include <iostream>
#include <fstream>
#include "enzyme.h"

/*
*/

struct environment {
    double glucose; //Amount of glucose, measured in Molar.
    double lactose; //Amount of lactose, measured in Molar.
    double galactose; //Amount of galactose, measured in Molar.
    void set(double gl, double l, double ga); //Sets all variables of environment.
};

void environment::set(double gl, double l, double ga) {
    glucose = gl;
    lactose = l;
    galactose = ga;
}

class organism {
    private:
        //Amount Variables:
        double glucose; //Amount of glucose, measured in Molar.
        double lactose; //Amount of lactose, measured in Molar.
        double galactose; //Amount of galactose, measured in Molar.
        double mRNALactose; //The amount of mRNALactose (M)
        double mRNAGlucose;
        //Rate Variables:
        double transportEfficiencyLactose; //The percent of lactose available in environment that is taken in
        double transportEfficiencyGlucose; //The percent of glucose available in environment that is taken in
        double transcriptionRateLactose; //Rate at which transcription of the Lac operon occurs (sec)
        double translationRateLactose; //Rate at which the translation of the Lac operon mRNALactose occurs (sec)
        double transcriptionRateGlucose; //Rate at which transcription of the Glu operon occurs (sec)
        double translationRateGlucose; //Rate at which the translation of the Glu operon mRNALactose occurs (sec)
        //Proportionality Constant Variables:
        double glucoseLactoseCompetition; //A proportionality constant used to hamper lactase production according to glucose concentration
        double LactoseMRNADegradation; //A proportionality constant used to degrade the mRNA associated with the Lac operon ( % per sec)
        double GlucoseMRNADegradation;
        //Class Variables:
        reaction lactoseDecom; //Enzyme model defined in "enzyme.h" used for the lactose reaction
        reaction glucoseOperon;

    public:
        environment stage;

        //Constructors:
        organism(); //Default Constructor

        //Setters:
        void setGlucose(double x);
        void setGlucose(double x, bool y); //Only updates the glucose operon
        void setLactose(double x);
        void setGalactose(double x);
        void setSubstrate(double x);
        void setProduct(double x);
        void setEnzyme(double x);
        void setGlucoseLactoseCompetition(double x);

        void setmRNALactose(double x);
        void setK1Lactose(double x); //Rate of change of Enzyme + Substrate --> Enzyme_ Complex
        void setK2Lactose(double x); //Rate of change of Enzyme_Complex --> Enzyme + Substrate
        void setK3Lactose(double x); //Rate of change of Enzyme_ Complex --> Enzyme + Product
        void setK4Lactose(double x); //Rate of change of Enzyme + Product --> Enzyme_ Complex
        void setTransportEfficiencyLactose(double x);
        void settranscriptionRateLactose(double x);
        void settranslationRateLactose(double x);
        void setLactoseMRNADegradation(double x);
        void setLactaseDegradation(double x);

        void setmRNAGlucose(double x);
        void setK1Glucose(double x); //Rate of change of Enzyme + Substrate --> Enzyme_ Complex
        void setK2Glucose(double x); //Rate of change of Enzyme_Complex --> Enzyme + Substrate
        void setK3Glucose(double x); //Rate of change of Enzyme_ Complex --> Enzyme + Product
        void setK4Glucose(double x); //Rate of change of Enzyme + Product --> Enzyme_ Complex
        void setTransportEfficiencyGlucose(double x);
        void setTranscriptionRateGlucose(double x);
        void setTranslationRateGlucose(double x);
        void setGlucoseMRNADegradation(double x);
        void setGlucoseEnzymeDegradation(double x);
        

        //Getters:
        double getGlucose();
        double getLactose();
        double getGalactose();
        double getSubstrate();
        double getEnzyme();
        double getGlucoseLactoseCompetition();

        double getmRNALactose();
        double getK1Lactose();
        double getK2Lactose();
        double getK3Lactose();
        double getK4Lactose();
        double getTransportEfficiencyLactose();
        double gettranscriptionRateLactose();
        double gettranslationRateLactose();
        double getLactoseMRNADegradation();
        double getLactaseDegradation();

        double getmRNAGlucose();
        double getK1Glucose(); //Rate of change of Enzyme + Substrate --> Enzyme_ Complex
        double getK2Glucose(); //Rate of change of Enzyme_Complex --> Enzyme + Substrate
        double getK3Glucose(); //Rate of change of Enzyme_ Complex --> Enzyme + Product
        double getK4Glucose(); //Rate of change of Enzyme + Product --> Enzyme_ Complex
        double getTransportEfficiencyGlucose();
        double getTranslationRateGlucose();
        double getTranscriptionRateGlucose();
        double getGlucoseMRNADegradation();
        double getGlucoseEnzymeDegradation();

        //Utility:
        void transport(); //Allows the organism to take in lactose from the environment
        void model(double time, double delt); //Models for a specified amount of time using specified time-steps.
        void update(); //Updates the organism variables in accordance with the enzyme model's
};

//Constructors:
organism::organism() { //Default Constructor
    glucose = 0; 
    lactose = 0; 
    galactose = 0; 
    mRNALactose = 0;
    mRNAGlucose = 0;
    transportEfficiencyLactose = 0; 
    transcriptionRateLactose = 0;
    translationRateLactose = 0;
    transcriptionRateGlucose = 0;
    translationRateGlucose = 0;
    glucoseLactoseCompetition = 1;
    LactoseMRNADegradation = 1;
    GlucoseMRNADegradation = 1;
    lactoseDecom; //Uses default constructor in its header file.
    stage; //Uses compiler-provided default constructor.
}

//Setters:
void organism::setGlucose(double x) {
    glucose = x;
    setProduct(x); //Sets the product variable in the enzyme model eqal to input.
    glucoseOperon.setSubstrate(x);
}
void organism::setGlucose(double x, bool y) {
    glucoseOperon.setSubstrate(x);
}
void organism::setLactose(double x) {
    lactose = x;
    setSubstrate(x); //Sets the substrate variable in the enzyme model eqal to input.
}
void organism::setGalactose(double x) {
    galactose = x;
}
void organism::setSubstrate(double x) {
    lactoseDecom.setSubstrate(x);
}
void organism::setProduct(double x) {
    lactoseDecom.setProduct(x);
}
void organism::setEnzyme(double x) {
    lactoseDecom.setEnzyme(x);
}
void organism::setmRNALactose(double x) {
    mRNALactose = x;
}
void organism::setK1Lactose(double x) {
    lactoseDecom.setK1(x);
}
void organism::setK2Lactose(double x) {
    lactoseDecom.setK2(x);
}
void organism::setK3Lactose(double x) {
    lactoseDecom.setK3(x);
}
void organism::setK4Lactose(double x) {
    lactoseDecom.setK4(x);
}
void organism::setTransportEfficiencyLactose(double x) {
    transportEfficiencyLactose = x;
}
void organism::settranscriptionRateLactose(double x) {
    transcriptionRateLactose = x;
}
void organism::settranslationRateLactose(double x) {
    translationRateLactose = x;
}
void organism::setGlucoseLactoseCompetition(double x) {
    glucoseLactoseCompetition = x;
}
void organism::setLactoseMRNADegradation(double x) {
    LactoseMRNADegradation = x;
}
void organism::setLactaseDegradation(double x) {
    lactoseDecom.setEnzymeDegradation(x);
}
void organism::setmRNAGlucose(double x) {
    mRNAGlucose = x;
}
void organism::setK1Glucose(double x) {
    glucoseOperon.setK1(x);
}
void organism::setK2Glucose(double x) {
    glucoseOperon.setK2(x);
}
void organism::setK3Glucose(double x) {
    glucoseOperon.setK3(x);
}
void organism::setK4Glucose(double x) {
    glucoseOperon.setK4(x);
}
void organism::setTransportEfficiencyGlucose(double x) {
    transportEfficiencyGlucose = x;
}
void organism::setTranscriptionRateGlucose(double x) {
    transcriptionRateGlucose = x;
}
void organism::setTranslationRateGlucose(double x) {
    translationRateGlucose = x;
}
void organism::setGlucoseMRNADegradation(double x) {
    GlucoseMRNADegradation = x;
}
void organism::setGlucoseEnzymeDegradation(double x) {
    glucoseOperon.setEnzymeDegradation(x);
}

//Getters:
double organism::getGlucose() {
    return glucose;
}
double organism::getLactose() {
    return lactose;
}
double organism::getGalactose() {
    return galactose;
}
double organism::getSubstrate() {
    return lactoseDecom.getSubstrate();
}
double organism::getEnzyme() {
    return lactoseDecom.getEnzyme();
}
double organism::getmRNALactose() {
    return mRNALactose;
}
double organism::getK1Lactose() {
    return lactoseDecom.getK1();
}
double organism::getK2Lactose() {
    return lactoseDecom.getK2();
}
double organism::getK3Lactose() {
    return lactoseDecom.getK3();
}
double organism::getK4Lactose() {
    return lactoseDecom.getK4();
}
double organism::getTransportEfficiencyLactose() {
    return transportEfficiencyLactose;
}
double organism::gettranscriptionRateLactose() {
    return transcriptionRateLactose;
}
double organism::gettranslationRateLactose() {
    return translationRateLactose;
}
double organism::getGlucoseLactoseCompetition() {
    return glucoseLactoseCompetition;
}
double organism::getLactoseMRNADegradation() {
    return LactoseMRNADegradation;
}
double organism::getLactaseDegradation() {
    return lactoseDecom.getEnzymeDegradation();
}
double organism::getmRNAGlucose() {
    return mRNAGlucose;
}
double organism::getK1Glucose() {
    return glucoseOperon.getK1();
}
double organism::getK2Glucose() {
    return glucoseOperon.getK2();
}
double organism::getK3Glucose() {
    return glucoseOperon.getK3();
}
double organism::getK4Glucose() {
    return glucoseOperon.getK4();
}
double organism::getTransportEfficiencyGlucose() {
    return transportEfficiencyGlucose;
}
double organism::getTranslationRateGlucose() {
    return translationRateGlucose;
}
double organism::getTranscriptionRateGlucose() {
    return transcriptionRateGlucose;
}
double organism::getGlucoseMRNADegradation() {
    return GlucoseMRNADegradation;
}
double organism::getGlucoseEnzymeDegradation() {
    return glucoseOperon.getEnzymeDegradation();
}

//Utility:
void organism::transport() {
    //Transport Lactose from external environment to internal environemnt:
    setLactose(lactose + (transportEfficiencyLactose * stage.lactose));
    stage.lactose = (1 - transportEfficiencyLactose) * stage.lactose;

    //glucose += transportEfficiencyGlucose * stage.glucose;
    //stage.lactose = (1 - transportEfficiencyGlucose) * stage.glucose;
    setGlucose(glucose);

    // ! ! ! Add a separate one for glucose ! ! !
}
void organism::model(double time, double delt) {
    // Place holder
    std::ofstream Lsub, Gsub, Lcom, Gcom, Lpro, Gpro, Lenz, Genz, Lrna, Grna;
    double productTransfer;

    //Opening data files for output:
    Lsub.open("operonModel_SubstrateLactose.txt");
    Gsub.open("operonModel_SubstrateGlucose.txt");
    Lcom.open("operonModel_ComplexLactose.txt");
    Gcom.open("operonModel_ComplexGlucose.txt");
    Lpro.open("operonModel_ProductLactose.txt");
    Gpro.open("operonModel_ProductGlucose.txt");
    Lenz.open("operonModel_EnzymeLactose.txt");
    Genz.open("operonModel_EnzymeGlucose.txt");
    Lrna.open("operonModel_mRNALactose.txt");
    Grna.open("operonModel_mRNAGlucose.txt");

    //Actual Calculation:
    for (double t = 0; t <= time; t += delt) {
        transport();

        if (lactose >= 0) {
            //Data Handling:
            update();
            Lsub << lactoseDecom.getSubstrate() << std::endl;
            Gsub << glucoseOperon.getSubstrate() << std::endl;
            Lcom << lactoseDecom.getEnzymeComplex() << std::endl;
            Gcom << glucoseOperon.getEnzymeComplex() << std::endl;
            Lpro << lactoseDecom.getProduct() << std::endl;
            Gpro << glucoseOperon.getProduct() << std::endl;
            Lenz << -lactoseDecom.getEnzyme() << std::endl;
            Genz << -glucoseOperon.getEnzyme() << std::endl; //There is a negative sign somewhere that messes this up, hence the negative here
            Lrna << mRNALactose << std::endl;
            Grna << mRNAGlucose << std::endl;

            //Degradation of mRNA from previous step:
            /*
            if (GlucoseMRNADegradation && LactoseMRNADegradation) {
                mRNALactose *= (1 - LactoseMRNADegradation) * delt;
                mRNAGlucose *= (1 - GlucoseMRNADegradation) * delt;
            }
            else if (GlucoseMRNADegradation) {
                mRNAGlucose *= (1 - GlucoseMRNADegradation) * delt;
            }
            else if (LactoseMRNADegradation) {
                mRNALactose *= (1 - LactoseMRNADegradation) * delt;
            }
            */

            //Transcription:
            if (stage.glucose > 0) {
                mRNALactose += transcriptionRateLactose * delt;
                mRNAGlucose += transcriptionRateGlucose * delt;

                if (lactose > 0) {
                    mRNALactose += glucoseLactoseCompetition * (transcriptionRateLactose * delt); //Translation with competition
                }
            }
            else if (lactose > 0) {
                mRNALactose += (transcriptionRateLactose * delt); //Translation without competition
            }
            
            //Translation:
            lactoseDecom.setEnzyme(lactoseDecom.getEnzyme() + (translationRateLactose * delt));
            glucoseOperon.setEnzyme(glucoseOperon.getEnzyme() + (translationRateGlucose));

            //Catalysis:
            glucoseOperon.twoPartModel(delt, productTransfer);
            productTransfer = glucoseOperon.getProduct();
            lactoseDecom.twoPartModel(delt, productTransfer);

            update();
        }
    }

    //Closing logging files:
    Lsub.close();
    Gsub.close();
    Lcom.close();
    Gcom.close();
    Lpro.close();
    Gpro.close();
    Lenz.close();
    Genz.close();
    Lrna.close();
    Grna.close();
}
void organism::update() {
    lactose = lactoseDecom.getSubstrate();
    glucose = lactoseDecom.getProduct(); //replace with glu op (Maybe?)
    galactose = lactoseDecom.getProduct(); // ASSUMES SAME INITIAL AMOUNT OF GLUCOSE AND GALACTOSE
}



int main() {
    organism x;

    //Conditions:
    x.stage.set(10, 10, 10);
    x.setK1Lactose(0.05);
    x.setK2Lactose(0.1);
    x.setK3Lactose(0.02);
    x.setK4Lactose(0);
    x.setTransportEfficiencyLactose(0.2);
    x.settranscriptionRateLactose(0.05);
    x.settranslationRateLactose(0.01);
    x.setGlucoseLactoseCompetition(0.8);
    //Define the MRNA degradation
    //Define the enzyme degradation
    x.setK1Glucose(0.05);
    x.setK2Glucose(0.1);
    x.setK3Glucose(0.02);
    x.setK4Glucose(0);
    x.setTransportEfficiencyGlucose(0.2);
    x.setTranscriptionRateGlucose(0.05);
    x.setTranslationRateGlucose(0.05);

    x.model(6000, 0.05);

    return 0;
}