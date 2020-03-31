//
//  myCar.h
//  RaceCar
//
//  Created by Alan on 2020/3/29.
//  Copyright © 2020 Mac. All rights reserved.
//

#ifndef myCar_h
#define myCar_h
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <queue>
#include <vector>


enum class Car_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

class myCar {
private:
    // position
    glm::vec3 Position;
    // direction
    glm::vec3 Front = glm::vec3(-1.0f,0.0f,0.0f);
    // Euler Angles
    float Yaw = 0.0f;
    float Pitch = 0.0f;
    float Speed = 0.0f;
    //Acceleration
    float a = 0.03f;
    
//    float rotaA = 3.0f;
    float maxSpeed = 15.0f;
    float turningSpeed = 90.0f;
public:
    
    
    myCar(glm::vec3 position):Position(position){
        updateFront();
    }
    glm::vec3 getPosition(){
        return Position;
    }
    void setA(float a){
        this->a = a;
    }
    float getYaw(){
        return Yaw;
    }
    glm::vec3 getFront(){
        return Front;
    }
    void changePosition(float deltaTime){
        float velocity = Speed * deltaTime;
        Position += Front * velocity;
    }
    void updateFront(){
        glm::vec3 front;
        front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        front.y = sin(glm::radians(Pitch));
        front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        Front = glm::normalize(front);
        Front.x = Front.x*(-1);
    }
    //Friction simulation
    void friction(){
        //Coefficient of friction
        float cf = a/3;
        if(Speed > 0){
            if(Speed >= cf){
                Speed -= cf;
            }else{
                Speed = 0.0;
            }
        }else if(Speed < 0){
            if(Speed <= -cf){
                Speed += cf;
            }else{
                Speed = 0.0;
            }
        }
        
    }
//    void directionFri(){
//        if(Yaw>0){
//            if(Yaw>=rotaA){
//                Yaw -= rotaA;
//            }else{
//                Yaw = 0.0;
//            }
//        }else if(Yaw<0){
//            if(Yaw<=-rotaA){
//                Yaw +=rotaA;
//            }else{
//                Yaw = 0.0;
//            }
//        }
//        updateFront();
//    }
    void ProcessKeyboard(Car_Movement direction, float deltaTime)
    {
        
//        std::cout<< Position.x<<std::endl;
        if (direction == Car_Movement::FORWARD){
            float velocity = Speed * deltaTime + 0.5*a*deltaTime*deltaTime;
            if(Speed<=maxSpeed){
                Speed += a;
            }else{
                Speed = maxSpeed;
            }
            
            Position += Front * velocity;
        }
        if (direction == Car_Movement::BACKWARD){
            float velocity = Speed * deltaTime - 0.5*a*deltaTime*deltaTime;
            if(Speed>=-maxSpeed){
                Speed -= a;
            }else{
                Speed = -maxSpeed;
            }
            Position += Front * velocity;
        }
        if (direction == Car_Movement::LEFT){
            if(Speed >= 0.005 ||Speed<=-0.005){
                Yaw += turningSpeed*deltaTime;
                updateFront();
            }
            
            
        }
            
        if (direction == Car_Movement::RIGHT){
            if(Speed >= 0.005 ||Speed<=-0.005){
                Yaw -= turningSpeed*deltaTime;
                updateFront();
            }
         
        }
            
    }
    
    
};
#endif /* myCar_h */
