#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <tuple>
#include <chrono>
#include <ctime>
#include <cmath>
#include <vector>
#include <stdio.h>
#include <string.h>
#include <iomanip>
using namespace std;
/*
THIS IS THE ENTIRE SYSTEM
*/

/* 
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
SYSTEM MANAGEMENT MODULE
*/
class systemManagementModule{
    public: 
        static vector<string> sysLog;
        void receiveLog(string entry){//Records the sent log of data
            sysLog.push_back(entry);
        }

        /* old displayLog
        void displayLog(){//Displays the entire log one entry at a time
            for(int i = 0; i < (long)sysLog.size(); i++){
                cout << sysLog[i] << endl;
            }
        } */

        /* 
        sends the log after 1 exec of the code to a file
        takes a filename as an input */
        void logToFile(string filename) {
            ofstream outFile(filename, ios::app); // appends log to end of previous one if it exists
            if (outFile.is_open()) {
                outFile << "\nNew entry:\n------------------------\n";
                for (int i = 0; i < (long)sysLog.size(); i++) {
                    outFile << sysLog[i] << endl;
                }
                outFile.close();
                cout << "Log written to file: " << filename << endl;
            }
            else {
                cout << "Error: could not open file " << filename << " for writing" << endl;
            }
        }

};
vector<string> systemManagementModule::sysLog;// Enables static vector (compile error without)

/* 
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
VEHICLE CONTROL SYSTEM MODULE
*/
class vehicleControlModule{
    public:
        void adjustWiperLevel(int wiperStatus, bool increaseWiper, bool decreaseWiper){
            if (increaseWiper) {
                wiperStatus++;
                std::cout << "Wiper level increased" << std::endl;
            }
            else if (decreaseWiper) {
                wiperStatus--;
                std::cout << "Wiper level decreased" << std::endl;
            }
            else {
                std::cout << "Wiper level stayed the same" << std::endl;
            }
        }

        void adjustTemperature(int internalTemperature, bool increaseTemperature, bool decreaseTemperature){
            if (increaseTemperature) {
                internalTemperature++;
                std::cout << "Temperature increased" << std::endl;
            }
            else if (decreaseTemperature) {
                internalTemperature--;
                std::cout << "Temperature decreased" << std::endl;
            }
            else {
                std::cout << "Temperature stayed the same" << std::endl;
            }
        }

        void adjustHeadlights(bool state){
            if (state){//Turns headlights on
                //headlightsState = true;
                std::cout << "Headlights on" << std::endl;
            }
            else{//Turns headlights off
                //headlightsState = false;
                std::cout << "Headlights off" << std::endl;
            }
        }


        void activateLocks(){   
            //door1 = locked;
            //door2 = locked;
            //door3 = locked;
            //door4 = locked;
            std::cout << "Doors locked" << std::endl;
        }


        void laneCorrection(float steeringAngle){
            //steeringWheelStatus = steeringAngle
            std::cout << "Steering changed to: " << steeringAngle << std::endl;
        }

        void applyBrake(int brakeLevel){
            //brakeStatus = brakeLevel;
            std::cout << "Brake level applied: " << brakeLevel << std::endl;
        }
   
        void trafficAction(string action) {
            if(action == "continueOn") {
                cout << "Light was Green, Continue!" << endl;
            }
            else if(action == "slowDown") {
                cout << "Light was Yellow, Slow Down!" << endl;
            }
            else if(action == "comeToStop") {
                cout << "Light was Red, Come to a Stop!" << endl;
            }
            else {
                cout << "Light unidentifiable. Requires driver action." << endl;
            }
            return;
        }
};

/* 
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PLANNING MODULE
*/
class PlanningModule{
    
    public:
        vehicleControlModule vcm;
        systemManagementModule smm;
        float forwardCollision, backCollision, lightSensor, accelerometer, breakStatus, gasPedal, interiorThermometer, exteriorThermometer, desiredThermometer, rainSensor, wiperStatus, steeringWheelStatus, roadAngleCamera1, roadAngleCamera2;
        string trafficCamera;
        bool cruiseControlButtonPressed, autoTemperatureStatus, autoWiperStatus, autoTrafficDetection, driverSteering, emergencyVehicleCamera1, emergencyVehicleCamera2, doorLockButtonPressed1, doorLockButtonPressed2, doorLockButtonPressed3, doorLockButtonPressed4;
        bool headlightState = false;
        float time;

        void ReceiveData(float _time, float _forwardCollision, float _backCollision, float _lightSensor, float _accelerometer, float _breakStatus, float _gasPedal, float _interiorThermometer, float _exteriorThermometer, float _desiredThermometer, float _rainSensor, float _wiperStatus, float _steeringWheelStatus, float _roadAngleCamera1, float _roadAngleCamera2, string _trafficCamera, bool _cruiseControlButtonPressed, bool _autoTemperatureStatus, bool _autoWiperStatus, bool _autoTrafficDetection, bool _driverSteering, bool _emergencyVehicleCamera1, bool _emergencyVehicleCamera2, bool _doorLockButtonPressed1, bool _doorLockButtonPressed2, bool _doorLockButtonPressed3, bool _doorLockButtonPressed4 ){
            time = _time;
            forwardCollision = _forwardCollision;
            backCollision = _backCollision;
            lightSensor = _lightSensor;
            accelerometer = _accelerometer;
            breakStatus = _breakStatus;
            gasPedal = _gasPedal;
            interiorThermometer = _interiorThermometer;
            exteriorThermometer = _exteriorThermometer;
            desiredThermometer = _desiredThermometer;
            rainSensor = _rainSensor;
            wiperStatus = _wiperStatus;
            steeringWheelStatus = _steeringWheelStatus;
            roadAngleCamera1 = _roadAngleCamera1;
            roadAngleCamera2 = _roadAngleCamera2;
            trafficCamera = _trafficCamera;
            cruiseControlButtonPressed = _cruiseControlButtonPressed;
            autoTemperatureStatus = _autoTemperatureStatus;
            autoWiperStatus = _autoWiperStatus;
            autoTrafficDetection = _autoTrafficDetection;
            driverSteering = _driverSteering;
            emergencyVehicleCamera1 = _emergencyVehicleCamera1;
            emergencyVehicleCamera2 = _emergencyVehicleCamera2;
            doorLockButtonPressed1 = _doorLockButtonPressed1;
            doorLockButtonPressed2 = _doorLockButtonPressed2;
            doorLockButtonPressed3 = _doorLockButtonPressed3;
            doorLockButtonPressed4 = _doorLockButtonPressed4;


            Plan();
        }

        // function that calls the actual functions
        void Plan(){
            automaticHeadlights(lightSensor, headlightState);
            automaticDoorLocks(accelerometer, (doorLockButtonPressed1 && doorLockButtonPressed2 && doorLockButtonPressed3 && doorLockButtonPressed4));
            laneCorrection(accelerometer, roadAngleCamera1, roadAngleCamera2, driverSteering);
            ForwardCollision(forwardCollision);
            RearCollision(backCollision);
            automaticWindshield(rainSensor, wiperStatus, autoWiperStatus, cruiseControlButtonPressed, autoTemperatureStatus, autoTrafficDetection);
            automaticTemperature(interiorThermometer, exteriorThermometer, desiredThermometer, autoTemperatureStatus);
            trafficLightRecognition(trafficCamera, autoTrafficDetection);
            emergencyVehicleDetection(emergencyVehicleCamera1, emergencyVehicleCamera2);
        }

        /*
        string getTime(){
            char buff[70];
            std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
            std::time_t now_c = std::chrono::system_clock::to_time_t(now);
            std::tm now_tm = *std::localtime(&now_c);
            strftime(buff, sizeof buff, "%c", &now_tm);
            return buff;
        }*/

        /* 
        testing out this new getTime() that includes milliseconds, as well as changes format to: 
        year-mon-day hour:minute:seconds.milliseconds */
        string getTime() {
            chrono::system_clock::time_point now = chrono::system_clock::now();
            auto now_ms = chrono::duration_cast<chrono::milliseconds>(now.time_since_epoch()) % 1000;
            time_t now_c = chrono::system_clock::to_time_t(now);
            tm now_tm = *localtime(&now_c);
            ostringstream oss;
            oss << put_time(&now_tm, "%Y-%m-%d %H:%M:%S.") << setfill('0') << setw(3) << now_ms.count();
            return oss.str();
        }


        std::tuple<bool, bool, bool> automaticWindshield(int rainSensor, int wiperStatus, bool autoWiperStatus, bool increaseWiper, bool decreaseWiper, bool stayWiper){
            // If automaticWiperStatus is false, automatically print "Automatic wipers are off"
            ostringstream log;
            if (autoWiperStatus == false){
                log << getTime() << " - " << "Wipers off";
                smm.receiveLog(log.str());
                return std::make_tuple(false, false, false);
            }
            else{
                // depending on the rainSensor value, the wiperStatus has to increase or decrease to match it
                if (rainSensor > wiperStatus){
                    increaseWiper = true;
                    log << getTime() << ": " << "Wiper status increased to" << wiperStatus;
                    smm.receiveLog(log.str());
                    vcm.adjustWiperLevel(2, true, false);
                    return std::make_tuple(true, false, false);
                }
                else if (rainSensor < wiperStatus){
                    decreaseWiper = true;
                    log << getTime() << ": " << "Wiper status decreased to" << wiperStatus;
                    smm.receiveLog(log.str());
                    vcm.adjustWiperLevel(2, false, true);
                    return std::make_tuple(false, true, false);
                }else if (rainSensor == wiperStatus){
                    stayWiper = true;
                    log << getTime() << ": " << "Wiper status stayed the same" << wiperStatus;
                    smm.receiveLog(log.str());
                    vcm.adjustWiperLevel(4, false, false);
                    return std::make_tuple(false, false, true);
                }
            }
            
            // If none of the flags match, return "stayWiper" flag
            return std::make_tuple(false, false, true);
        }


        std::tuple<bool, bool, bool> automaticTemperature(int interiorTemperature, int exteriorTemperature, int desiredTemperature, bool autoTemperatureStatus) {
            // If autoTemperatureStatus is false, automatically print "Automatic temperature is off"
            ostringstream log;
            bool increaseTemperature = false;
            bool decreaseTemperature = false;
            bool stayTemperature = false;
            if (autoTemperatureStatus == false) {
                std::cout << "Automatic temperature is off";
                log << getTime() << ": " << "Automatic temperature is off";
                smm.receiveLog(log.str());

                return std::make_tuple(false, false, false);
            }
            else {
                // increase or decrease the interiorTemperature to match the desiredTemperature
                if (interiorTemperature < desiredTemperature) {
                    increaseTemperature = true;
                    if (increaseTemperature) {
                        log << getTime() << ": " << "Interior temperature increased" << interiorTemperature;
                        smm.receiveLog(log.str());
                        vcm.adjustTemperature(67, true, false);
                        return std::make_tuple(true, false, false);
                    }
                }
                else if (interiorTemperature > desiredTemperature) {
                    decreaseTemperature = true;
                    if (decreaseTemperature) {
                        log << getTime() << ": " << "Interior temperature decreased" << interiorTemperature;
                        smm.receiveLog(log.str());
                        vcm.adjustTemperature(70, false, true); 
                        return std::make_tuple(false, true, false);
                    }
                }
            }

            // If the interiorTemperature and desiredTemperature match, return a "stayTemperature" flag
            if (stayTemperature) {
                log << getTime() << ": " << "Interior temperature stayed the same";
                smm.receiveLog(log.str());
                vcm.adjustTemperature(65, false, false);
                return std::make_tuple(false, false, true);
            }

            // If none of the flags match, return "stayTemperature" flag
            return std::make_tuple(false, false, true);
        }

        void automaticHeadlights(float lightLevel, bool state){
            ostringstream log;
            if (lightLevel < 400){//Tells VCS to turn on headlights.
                log << getTime() << ": automaticHeadLights{lightLevel: " << lightLevel << " state: " << state << " Decision: " << "on}";
                smm.receiveLog(log.str());
                vcm.adjustHeadlights(true);
                return;
            }
            else if (lightLevel >= 450){//Tells VCS to turn off headlights.
                log << getTime() << ": automaticHeadLights{lightLevel: " << lightLevel << " state: " << state << " Decision: " << "off}";
                smm.receiveLog(log.str());
                vcm.adjustHeadlights(false);
                return;
            }
            //Tells VCS to keep the headlights as they are.
            log << getTime() << ": automaticHeadLights{lightLevel: " << lightLevel << " state: " << state << " Decision: " << "none}";
            smm.receiveLog(log.str());
            vcm.adjustHeadlights(state);
            return;
        }


        void automaticDoorLocks(float speed, bool closeDoors){
            ostringstream log;
            if (closeDoors && speed >= 12){//Locks all doors
                log << getTime() << ": automaticDoorLocks{speed: " << speed << " closeDoors: " << closeDoors << " Decision: " << "lock}";
                smm.receiveLog(log.str());
                vcm.activateLocks();
                return;
            }
            log << getTime() << ": automaticDoorLocks{speed: " << speed << " closeDoors: " << closeDoors << " Decision: " << "none}";
            smm.receiveLog(log.str());
            return;
        }

        
        //Keeps the vehicle as centered in the lane as possible
        void laneCorrection(float speed, float leftLaneAngle, float rightLaneAngle, bool beingSteered){
            ostringstream log;
            if (beingSteered || speed == 0 || (leftLaneAngle + rightLaneAngle) == 0){
                log << getTime() << ": laneCorrection{speed: " << speed << " leftLaneAngle: " << leftLaneAngle << " rightLaneAngle: " << rightLaneAngle << " beingSteered: " << beingSteered << " Decision: " << "none}";
                smm.receiveLog(log.str());
                return;
            }
            //Assumes that a positive angle means intersection if the vehicle continues forward
            float steerAngle = ((rightLaneAngle - leftLaneAngle)/2) * 4;//Gets the direction needed to steer then multiplies by 4 for full 360 wheel rotation
            log << getTime() << ": laneCorrection{speed: " << speed << " leftLaneAngle: " << leftLaneAngle << " rightLaneAngle: " << rightLaneAngle << " beingSteered: " << beingSteered << " Decision: " << "Steer " << steerAngle << "}";
            smm.receiveLog(log.str());
            vcm.laneCorrection(steerAngle);
            return;
        }

        void ForwardCollision(double dist){
            ostringstream log;
            if ( dist < 0 ){
                std::cout << "ERROR:  Distance is negative" << std::endl;
                log << getTime() << ": ForwardCollision ERROR: Distance is negative " << dist;
                smm.receiveLog(log.str());
                return;
            }
            if ( dist  < 250 ){
                if ( dist  < 25 ){
                    log << getTime() << ": ForwardCollision: Distance : " << dist << " - Applying Brake level 5" ;
                    vcm.applyBrake(5);
                }
                else if ( dist  < 50 ){
                    log << getTime() << ": ForwardCollision: Distance : " << dist << " - Applying Brake level 4" ;
                    vcm.applyBrake(4);
                }
                else if ( dist  < 100 ){
                    log << getTime() << ": ForwardCollision: Distance : " << dist << " - Applying Brake level 3" ;
                    vcm.applyBrake(3);
                }
                else if ( dist  < 200 ){
                    log << getTime() << ": ForwardCollision: Distance : " << dist << " - Applying Brake level 2" ;
                    vcm.applyBrake(2);
                }
                else{
                    log << getTime() << ": ForwardCollision: Distance : " << dist << " - Applying Brake level 1" ;
                    vcm.applyBrake(1);
                }
                smm.receiveLog(log.str());
            }
        }
        void RearCollision(double dist){
            ostringstream log;
            if ( dist < 0 ){
                std::cout << "RearCollision ERROR:  Distance is negative" << std::endl;
                log << getTime() << ": RearCollision ERROR: Distance is negative " << dist;
                smm.receiveLog(log.str());
                return;
            }
            if ( dist  < 250 ){
                if ( dist  < 25 ){
                    log << getTime() << ": RearCollision: Distance : " << dist << " - Applying Brake level 5" ;
                    vcm.applyBrake(5);
                }
                else if ( dist  < 50 ){
                    log << getTime() << ": RearCollision: Distance : " << dist << " - Applying Brake level 4" ;
                    vcm.applyBrake(4);
                }
                else if ( dist  < 100 ){
                    log << getTime() << ": RearCollision: Distance : " << dist << " - Applying Brake level 3" ;
                    vcm.applyBrake(3);
                }
                else if ( dist  < 200 ){
                    log << getTime() << ": RearCollision: Distance : " << dist << " - Applying Brake level 2" ;
                    vcm.applyBrake(2);
                }
                else{
                    log << getTime() << ": RearCollision: Distance : " << dist << " - Applying Brake level 1" ;
                    vcm.applyBrake(1);
                }
                smm.receiveLog(log.str());
            }
        }

        void trafficLightRecognition(string color, bool autoTrafficDetection) {
            ostringstream log;
            //bool obstacle = false;
            string action;

            // If the driver has this function disabled:
            if(autoTrafficDetection == 0) {
                log << getTime() << ": trafficLightRecognition{ Traffic Light Recognition is off }";
                smm.receiveLog(log.str());
                return; 
            }
            // using the camera, the type of signal displayed determines the action
            if (color == " green") {
                action = "continueOn";
                log << getTime() << ": trafficLightRecognition{ GREEN traffic light detected! }";
                smm.receiveLog(log.str());
                /*
                if(obstacle) {
                    comeToStop()
                    cout << "There is an obstacle blocking the intersection!"
                }*/
            }
            else if (color == " yellow") {
                action = "slowDown";
                log << getTime() << ": trafficLightRecognition{ YELLOW traffic light detected! }";
                smm.receiveLog(log.str());
                return;
            }
            else if(color == " red") {
                action = "comeToStop";
                log << getTime() << ": trafficLightRecognition{ RED traffic light detected! }";
                smm.receiveLog(log.str());
                return;
            }
            else if (color == " unidentifiable") {
                // updateDisplay
                log << getTime() << ": trafficLightRecognition{ UNIDENTIFIABLE traffic light detected! }";
                smm.receiveLog(log.str());
                
            } 

            cout << action << endl;
            vcm.trafficAction(action); // decides which action to take depending on the light color
            return;
        }

        void emergencyVehicleDetection(bool emergencyVehicleCamera1, bool emergencyVehicleCamera2) {
            // if either camera detects an active emergency vehicle,
            ostringstream log;
            if(emergencyVehicleCamera1 || emergencyVehicleCamera2) {
                log << getTime() << ": emergencyVehicleDetection{ Emergency Vehicle is Approaching! }";
                smm.receiveLog(log.str());
                return;
            }
            else if (!emergencyVehicleCamera1 && !emergencyVehicleCamera2) {
                log << getTime() << ": emergencyVehicleDetection{ No Emergency Vehicle Present. }";
                smm.receiveLog(log.str());
                return;
            }
            return;
        }

};



class SensorFusion{
    public:

        float forwardCollision1, forwardCollision2;
        float backCollision1, backCollision2;
        float lightSensor1, lightSensor2, lightSensor3, lightSensor4;
        bool cruiseControlButtonPressed;
        float accelerometer, breakStatus, gasPedal;
        float interiorThermometer, exteriorThermometer, desiredThermometer;
        bool autoTemperatureStatus, autoWiperStatus, autoTrafficDetection, driverSteering;
        float rainSensor, wiperStatus, steeringWheelStatus;
        string trafficCamera;
        float roadAngleCamera1, roadAngleCamera2;
        bool emergencyVehicleCamera1, emergencyVehicleCamera2, doorLockButtonPressed1, doorLockButtonPressed2, doorLockButtonPressed3, doorLockButtonPressed4;
        float time;

        float forwardCollision, backCollision, lightSensor;
        PlanningModule planningModule;


        void normalizeData(){
            if((isnan(forwardCollision1) || forwardCollision1 <0) ){
                if(!(isnan(forwardCollision2)) && forwardCollision2 > 0){
                    forwardCollision1 = forwardCollision2;
                }
                else{
                    forwardCollision1 = 250;
                }
            }
            if((isnan(forwardCollision2) || forwardCollision2 <0) ){
                if(!(isnan(forwardCollision1)) && forwardCollision1 > 0){
                    forwardCollision2 = forwardCollision1;
                }
                else{
                    forwardCollision2 = 250;
                }
            }
            if((isnan(backCollision1) || backCollision1 <0) ){
                if(!(isnan(backCollision2)) && backCollision2 > 0){
                    backCollision1 = backCollision2;
                }
                else{
                    backCollision1 = 250;
                }
            }
            if((isnan(backCollision2) || backCollision2 <0) ){
                if(!(isnan(backCollision1)) && backCollision1 > 0){
                    backCollision2 = backCollision1;
                }
                else{
                    backCollision2 = 250;
                }
            }

            autoWiperStatus = true;
            autoTemperatureStatus = true;
            forwardCollision = (forwardCollision1+forwardCollision2)/2;
            backCollision = (backCollision1+backCollision2)/2;
            lightSensor = (lightSensor1 + lightSensor2 + lightSensor3 + lightSensor4)/4;

            sendData();

        }

        void sendData(){
            planningModule.ReceiveData(time, forwardCollision,backCollision, lightSensor, accelerometer, breakStatus, gasPedal, interiorThermometer, exteriorThermometer, desiredThermometer, rainSensor, wiperStatus, steeringWheelStatus, roadAngleCamera1, roadAngleCamera2,trafficCamera, cruiseControlButtonPressed, autoTemperatureStatus, autoWiperStatus, autoTrafficDetection, driverSteering, emergencyVehicleCamera1, emergencyVehicleCamera2, doorLockButtonPressed1, doorLockButtonPressed2, doorLockButtonPressed3, doorLockButtonPressed4);
        }


};



/* 
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Technician Interface
*/
class technicianInterface{ /* Just printing all the data that is necessary*/
    public: 
        //a function showSystemLog()
        void showSystemLog(){
            std::cout << "System Log" << std::endl;
        }

        //a function checkSensorHealth(sensorList)
        void checkSensorHealth(std::string sensorList){
            std::cout << "Sensor Health" << std::endl;
        }

        //a function checkSoftwareHealth() shows if the there are any issues
        void checkSoftwareHealth(){
            std::cout << "Software Health" << std::endl;
        }

        //a function installUpdate() that just prints "Update currently up to date: " and the current time and date
        void installUpdate(){
            auto currentTime = std::chrono::system_clock::now();
            std::time_t time = std::chrono::system_clock::to_time_t(currentTime);
            std::cout << "Update currently up to date: " << std::ctime(&time) << std::endl;
        }

        //a function uploadLogToServer() that just prints "Log uploaded to server: " and the current time and date
        void uploadLogToServer(){
            auto currentTime = std::chrono::system_clock::now();
            std::time_t time = std::chrono::system_clock::to_time_t(currentTime);
            std::cout << "Log uploaded to server: " << std::ctime(&time) << std::endl;
        }
};


/* 
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Driver Interface 
*/
class driverInterface{ /* This is where we can create a function like if the password is equal then they can create a log output*/
    public: 
        //a function displaySpeed(speed)
        void displaySpeed(int speed){
            cout << "Speed: " << speed << endl;
        }

        //a function that toggles cruise control
        void toggleCruiseControl(bool cruiseControlStatus){
            if (cruiseControlStatus) {
                cout << "Cruise control is on" << endl;
            }
            else {
                cout << "Cruise control is off" << endl;
            }
        }

        //a function that shows the fuel level
        void displayFuelLevel(int fuelLevel){
            cout << "Fuel level: " << fuelLevel << endl;
        }

        //a function that shows the temperature
        void displayTemperature(int temperature){
            cout << "Temperature: " << temperature << endl;
        }

        //a function collisionAlert
        void collisionAlert(int collisionAlert){
            if (collisionAlert > 200){
                cout << "Collision Alert: " << collisionAlert << endl;
            } else {
                cout << "No collision detected" << endl;
            }
        }
};

class testingInterface{
    public:
        //test()
        void test(){
            cout << "Test" << endl;
        }

        //showSystemLog()
        void showSystemLog(){
            cout << "System Log" << endl;
        }
};



int main() {
    SensorFusion sensorFusion;
    sensorFusion.time = 0;
    PlanningModule planningModule;
    sensorFusion.planningModule = planningModule;
    systemManagementModule sysMan;
    planningModule.smm = sysMan;
    vehicleControlModule vcm;
    planningModule.vcm = vcm;
    string filename = "rawData.txt";
    ifstream file(filename);

    if (!file) {
        cerr << "Error: Cannot open file " << filename << endl;
        return 1;
    }

    vector<string> sensor_data;

    string line;

    while (getline(file, line)) {
        char *c = new char[line.length() + 1];
        std::copy(line.begin(), line.end(), c);
        c[line.length()] = '\0';
        string sensorName = strtok(c,",");
        string sensorValue = strtok(NULL, ",");


        
        if(sensorName == "forwardCollision1"){
            sensorFusion.forwardCollision1 = stof(sensorValue);
        }
        else if(sensorName == "forwardCollision2"){
            sensorFusion.forwardCollision2 = stof(sensorValue);
        }
        else if(sensorName == "backCollision1"){
            sensorFusion.backCollision1 = stof(sensorValue);
        }
        else if(sensorName == "backCollision2"){
            sensorFusion.backCollision2 = stof(sensorValue);
        }
        else if(sensorName == "lightSensor1"){
            sensorFusion.lightSensor1 = stof(sensorValue);
        }
        else if(sensorName == "lightSensor2"){
            sensorFusion.lightSensor2 = stof(sensorValue);
        }
        else if(sensorName == "lightSensor3"){
            sensorFusion.lightSensor3 = stof(sensorValue);
        }
        else if(sensorName == "lightSensor4"){
            sensorFusion.lightSensor4 = stof(sensorValue);
        }
        else if(sensorName == "cruiseControlButtonPressed"){
            if(strcmp(sensorValue.c_str(),"true") == 0){
                sensorFusion.cruiseControlButtonPressed = true;
            }
            else{
                sensorFusion.cruiseControlButtonPressed = false;
            }
        }
        else if(sensorName == "accelerometer"){
            sensorFusion.accelerometer = stof(sensorValue);
        }
        else if(sensorName == "breakStatus"){
            sensorFusion.breakStatus = stof(sensorValue);
        }
        else if(sensorName == "gasPedal"){
            sensorFusion.gasPedal = stof(sensorValue);
        }
        else if(sensorName == "interiorThermometer"){
            sensorFusion.interiorThermometer = stof(sensorValue);
        }
        else if(sensorName == "exteriorThermometer"){
            sensorFusion.exteriorThermometer = stof(sensorValue);
        }
        else if(sensorName == "desiredThermometer"){
            sensorFusion.desiredThermometer = stof(sensorValue);
        }
        else if(sensorName == "autoTemperatureStatus"){
            if(strcmp(sensorValue.c_str(),"true") == 0){
                sensorFusion.autoTemperatureStatus = true;
            }
            else{
                sensorFusion.autoTemperatureStatus = false;
            }
        }
        else if(sensorName == "rainSensor"){
            sensorFusion.rainSensor = stof(sensorValue);
        }
        else if(sensorName == "wiperStatus"){
            sensorFusion.wiperStatus = stof(sensorValue);
        }
        else if(sensorName == "autoWiperStatus"){
            if(strcmp(sensorValue.c_str(),"true") == 0){
                sensorFusion.autoWiperStatus = true;
            }
            else{
                sensorFusion.autoWiperStatus = false;
            }
        }
        else if(sensorName == "trafficCamera"){
            sensorFusion.trafficCamera = sensorValue;
        }
        // changed if(strcmp(sensorValue.c_str(),"true") == 0) 
        // THIS might be why some variables aren't read correctly
        else if(sensorName == "autoTrafficDetection"){
            if(strcmp(sensorValue.c_str()," True") == 0){
                sensorFusion.autoTrafficDetection = true;
            }
            else{
                sensorFusion.autoTrafficDetection = false;
            }
        }
        else if(sensorName == "driverSteering"){
            if(strcmp(sensorValue.c_str(),"true") == 0){
                sensorFusion.driverSteering = true;
            }
            else{
                sensorFusion.driverSteering = false;
            }
        }
        else if(sensorName == "steeringWheelStatus"){
            sensorFusion.steeringWheelStatus = stof(sensorValue);
        }
        else if(sensorName == "roadAngleCamera1"){
            sensorFusion.roadAngleCamera1 = stof(sensorValue);
        }
        else if(sensorName == "roadAngleCamera2"){
            sensorFusion.roadAngleCamera2 = stof(sensorValue);
        }
        else if(sensorName == "emergencyVehicleCamera1"){
            if(strcmp(sensorValue.c_str()," True") == 0){
                sensorFusion.emergencyVehicleCamera1 = true;
            }
            else{
                sensorFusion.emergencyVehicleCamera1 = false;
            }
        }
        else if(sensorName == "emergencyVehicleCamera2"){
            if(strcmp(sensorValue.c_str()," True") == 0){
                sensorFusion.emergencyVehicleCamera2 = true;
            }
            else{
                sensorFusion.emergencyVehicleCamera2 = false;
            }
        }
        else if(sensorName == "doorLockButtonPressed1"){
            if(strcmp(sensorValue.c_str(),"true") == 0){
                sensorFusion.doorLockButtonPressed1 = true;
            }
            else{
                sensorFusion.doorLockButtonPressed1 = false;
            }
        }
        else if(sensorName == "doorLockButtonPressed2"){
            if(strcmp(sensorValue.c_str(),"true") == 0){
                sensorFusion.doorLockButtonPressed2 = true;
            }
            else{
                sensorFusion.doorLockButtonPressed2 = false;
            }
        }
        else if(sensorName == "doorLockButtonPressed3"){
            if(strcmp(sensorValue.c_str(),"true") == 0){
                sensorFusion.doorLockButtonPressed3 = true;
            }
            else{
                sensorFusion.doorLockButtonPressed3 = false;
            }
        }
        else if(sensorName == "doorLockButtonPressed4"){
            if(strcmp(sensorValue.c_str(),"true") == 0){
                sensorFusion.doorLockButtonPressed4 = true;
            }
            else{
                sensorFusion.doorLockButtonPressed4 = false;
            }


            sensorFusion.normalizeData();
            sensorFusion.time += .05;
        }
         
        sensor_data.push_back(line);
    }

    file.close();
    /* old displayLog() which only put it in the terminal
    planningModule.smm.displayLog();
    */
    planningModule.smm.logToFile("log.txt");
    return 0;
}
