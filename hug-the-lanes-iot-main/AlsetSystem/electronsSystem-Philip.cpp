#include <iostream>
#include <string>
#include <tuple>

/*
THIS IS THE ENTIRE SYSTEM
*/

/* 
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
SENSOR FUSION MODULE
*/
class sensorFusion{


};


/* 
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PLANNING MODULE
*/
class planningModule{
    
    public:
        void automaticHeadlights(float lightLevel, bool state){
            if (lightLevel < 400){//Tells VCS to turn on headlights.
                //sendLog(std::chrono::system_clock::now(), std::make_tuple("automaticHeadlights", "lightLevel", lightLevel, "state", state), std::make_tuple("on"))
                //adjustHeadlights(true);
                return;
            }
            else if (lightLevel >= 450){//Tells VCS to turn off headlights.
                //sendLog(std::chrono::system_clock::now(), std::make_tuple("automaticHeadlights", "lightLevel", lightLevel, "state", state), std::make_tuple("off"))
                //adjustHeadlights(false);
                return;
            }
            //Tells VCS to keep the headlights as they are.
            //sendLog(std::chrono::system_clock::now(), std::make_tuple("automaticHeadlights", "lightLevel", lightLevel, "state", state), std::make_tuple("none"))
            //adjustHeadlights(state);
            return;
        }


        void automaticDoorLocks(float speed, bool doorsClosed){
            if (doorsClosed && speed >= 12){//Locks all doors
                //sendLog(std::chrono::system_clock::now(), std::make_tuple("automaticDoorLocks", "speed", speed, "doorsClosed", doorsClosed), std::make_tuple("lock"))
                //activateLocks();
                return;
            }
            //sendLog(std::chrono::system_clock::now(), std::make_tuple("automaticDoorLocks", "speed", speed, "doorsClosed", doorsClosed), std::make_tuple("none"))
            return;
        }

        
        //Keeps the vehicle as centered in the lane as possible
        void laneCorrection(float speed, float leftLaneAngle, float rightLaneAngle, bool beingSteered){
            if (beingSteered || speed == 0 || (leftLaneAngle + rightLaneAngle) == 0){
                //sendLog(std::chrono::system_clock::now(), std::make_tuple(speed, leftLaneAngle, rightLaneAngle, beingSteered), std::make_tuple("none"))
                return;
            }
            //Assumes that a positive angle means intersection if the vehicle continues forward
            float steerAngle = ((rightLaneAngle - leftLaneAngle)/2) * 4;//Gets the direction needed to steer then multiplies by 4 for full 360 wheel rotation
            //sendLog(std::chrono::system_clock::now(), std::make_tuple(speed, leftLaneAngle, rightLaneAngle, beingSteered), std::make_tuple("Angle", steeringAngle))
            //laneCorrection(steeringAngle);
            return;
        }
};

/* 
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
VEHICLE CONTROL SYSTEM MODULE
*/
class vehicleControlModule{
public:
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
};

/* 
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
SYSTEM MANAGEMENT MODULE
*/
class systemManagementModule{
    public: 

};


/* 
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DISPLAY MODULE
*/
class displayModule{ /* Just printing all the data that is necessary*/
    public: 

};


/* 
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
SYSTEM ADMIN MODULE
*/
class systemAdminModule{ /* This is where we can create a function like if the password is equal then they can create a log output*/
    public: 

};
int main() {
    std::cout << "Hello World!\n";
}
