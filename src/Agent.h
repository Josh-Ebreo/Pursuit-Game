#pragma once

#include "ofMain.h"

class Agent {
public:
    Agent();
    void setup(ofPoint spawnPoint, float maxSpeed, float turningSpeed);
    void update(ofPoint playerPosition);
    void draw();
    bool isOffScreen();
    void setLifeSpan(float lifeSpan);
    bool isDead();
    void kill();
    float lerpAngle(float current, float target, float factor);
    static bool drawSpriteMode;

    ofPoint getPosition() const { return position; }
    void setTurningSpeed(float turningSpeed) { this->turningSpeed = turningSpeed; }
    void applyForce(ofPoint force);
    void applyTorque(float torque);

    ofImage agentSprite;
    ofPoint position;
    ofVec2f velocity;
    ofVec2f acceleration;
    float rotation;
    float turningSpeed;
    float maxSpeed;
    float damping;
    float angularVelocity;
    float angularAcceleration;
    float angle;
    float lifespan;
    float birthTime;
    bool dead;

    void updateMovement(ofPoint playerPosition);
    void updatePhysics();
};