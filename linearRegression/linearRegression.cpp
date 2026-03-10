#include <iostream>
#include <fstream>
#include <cmath>
class linearRegression {
    private:
        double m;
        double b;
        double gradientM;
        double gradientB;
        double learningRate;
        long maxIterations;
        double* data[3];
        double rSquared;
        double squareError; //The squares of the errors
        int entries;
        double totalError;
    public:
    //Constructors:
    linearRegression();

    //Setters:
    void setM(double x);
    void setB(double x);
    void setGradientM(double x);
    void setGradientB(double x);
    void setLearningRate(double x);
    void setMaxIterations(long x);
    void setSquareError(double x);
    void setTotalError(double x);
    void setRSquared(double x);
    void setEntries(int x);

    //Getters:
    double getM();
    double getB();
    double getGradientM();
    double getGradientB();
    double getLearningRate();
    long getMaxIterations();
    double getSquareError();
    double getTotalError();
    double getRSquared();
    int getEntries();

    //Utility:
    void uploadData(int entries);
    void calculateRSquared();
    void calculateError();
    void iterate();
    void guess();
};

//Constructors:
linearRegression::linearRegression() {
    m = 0;
    b = 0;
    gradientM = 0;
    gradientB = 0;
    learningRate = 0;
    maxIterations = 0;
    data;
    rSquared = 0;
    squareError = 0; 
    totalError = 0;
    entries = 0;
}

//Setters:
void linearRegression::setM(double x) {
    m = x;
}
void linearRegression::setB(double x) {
    b = x;
}
void linearRegression::setGradientM(double x) {
    gradientM = x;
}
void linearRegression::setGradientB(double x) {
    gradientB = x;
}
void linearRegression::setLearningRate(double x) {
    learningRate = x;
}
void linearRegression::setMaxIterations(long x) {
    maxIterations = x;
}
void linearRegression::setRSquared(double x) {
    rSquared = x;
}
void linearRegression::setSquareError(double x) {
    squareError = x;
}
void linearRegression::setTotalError(double x) {
    totalError = x;
}
void linearRegression::setEntries(int x) {
    entries = x;
}

//Getters:
double linearRegression::getM() {
    return m;
}
double linearRegression::getB() {
    return b;
}
double linearRegression::getGradientM() {
    return gradientM;
}
double linearRegression::getGradientB() {
    return gradientB;
}
double linearRegression::getLearningRate() {
    return learningRate;
}
long linearRegression::getMaxIterations() {
    return maxIterations;
}
double linearRegression::getSquareError() {
    return squareError;
}
double linearRegression::getRSquared() {
    return rSquared;
}
double linearRegression::getTotalError() {
    return totalError;
}
int linearRegression::getEntries() {
    return entries;
}

//Utility:
void linearRegression::uploadData(int entries) {
    setEntries(entries); //Needs to be done so that we can deallocate memory later

    std::ifstream xin, yin, zin;
    xin.open("linearRegressionX.txt");
    yin.open("linearRegressionY.txt");
    zin.open("linearRegressionCategory.txt");

    data[0] = new double [entries];
    data[1] = new double [entries];
    data[2] = new double [entries];

    for (int i = 0; i < entries; i++) {
        xin >> data[0][i];
        yin >> data[1][i];
        zin >> data[2][i];
    }

    xin.close();
    yin.close();
    zin.close();
}
void linearRegression::calculateRSquared() {
    double RSS = 0, TSS = 0;
    double meanOfData = 0, placeholder = 0;

    for (int i = 0; i < entries; i++) {
        meanOfData += data[1][i];
    }
    
    meanOfData *= 1.0 / entries;
    
    for (int i = 0; i < entries; i++) {
        RSS += pow(data[1][i] - ((m * data[0][i]) + b), 2);
        TSS += pow((data[1][i] - meanOfData), 2);
    }

    rSquared = 1 - (RSS / TSS);
}
void linearRegression::calculateError() {
    double tempSquareError = 0;
    double tempTotalError = 0;
    for (int i = 0; i < entries; i++) {
        tempSquareError += pow(((m * data[0][i]) + b) - data[1][i], 2);
        tempTotalError += 2 * (m * data[0][i] + b - data[1][i]);
    }
    squareError = tempSquareError;
    totalError = tempTotalError;
    
}
void linearRegression::iterate() {
    for (int i = 0; i < maxIterations; i++) {
        calculateError();

        if (totalError > 0) {
            m -= gradientM;
            b -= gradientB;
        }
        else {
            m += gradientM;
            b += gradientB;
        }
    }

    //free up memory
    delete[entries] data[0];
    delete[entries] data[1];
    delete[entries] data[2];
}


int main() {
    linearRegression x;
    x.uploadData(92);


    x.setB(-200);
    x.setMaxIterations(10000000);
    x.setGradientM(0.00001);
    x.setGradientB(0.00001);
    x.setLearningRate(0.0001);


    //Actual Least Square Line:
    /*
    x.setM(5.09596);
    x.setB(-205.40931);
    //R^2: 0.622831
    */
    
    //b = -200:
    /*
    x.setM(4.94528);
    x.setB(-195.055);
    //R^2: 0.622287
    */

    //b = 200:
    /*
    x.setM(-0.79218);
    x.setB(199.208);
    //R^2: 0.208692
    */

    //b = 400:
    /*
    x.setM(3.6609);
    x.setB(396.339);
    //R^2: -457.821
    */

    //b = -400:
    /*
    x.setM(7.814);
    x.setB(-392.186);
    //R^2: 0.445645
    */


    //x.iterate();
    
    x.calculateRSquared();

    std::cout << x.getM() << "x +" << x.getB() << std::endl;
    std::cout << "R^2: " << x.getRSquared();
    return 0;
}