#pragma once

#include <QMainWindow>
#include <QFontDialog>
#include <QFileDialog>
#include <QTimer>
#include <Box2D/Box2d.h>

#include "ui_main.h"

extern const float RADIUS;

class MainWindow : public QMainWindow, private Ui::MainWindow {
Q_OBJECT
private:
    QTimer timer;
    b2World* world;
    b2Body* body;
    b2Timer fps_timer;
    float k;
    std::vector<b2Body*> vector_of_balls;

public:
    MainWindow(b2World* pWorld, b2Body* pBody, std::vector<b2Body*> vector_of_balls) 
            : world(pWorld)
            , body(pBody)
            , vector_of_balls(vector_of_balls) 
    {
        setupUi(this);
        glWidget->setWorld(pWorld);
        world->SetDebugDraw(glWidget);
        show();
        QObject::connect(&timer, SIGNAL(timeout()), this, SLOT(tick()));
        timer.start(10);
        k = (float)floatSpinBox->value();
    }
    
    void force(float k){
        int len = vector_of_balls.size();
        for (int i = 0; i < len; ++i) {
            for (int j = i+1; j < len; ++j) {
                b2Body& ball_one = *vector_of_balls[i];
                b2Body& ball_two = *vector_of_balls[j];
                const b2Vec2& x = ball_one.GetPosition();
                const b2Vec2& y = ball_two.GetPosition();
                b2Vec2 _r = x - y;
                float R = _r.Normalize();
                if (R > 10*RADIUS) {
                    continue;
                }
                if (R < 0.4f*RADIUS) {
                    R = 0.4f*RADIUS;
                }
                float F = ball_one.GetMass() * k / (R * R * R);
                ball_one.ApplyForceToCenter(F*-_r, true);
                ball_two.ApplyForceToCenter(F*_r, true);
            }
        }
    }
    

public slots:
    void tick() {
        float passed_time = fps_timer.GetMilliseconds();
        fps_timer.Reset();
        float32 timeStep = passed_time/1000;
        int32 velocityIterations = 4;
        int32 positionIterations = 2;
        force(k);
        world->Step(timeStep/3, velocityIterations, positionIterations);
        float world_time = fps_timer.GetMilliseconds();
        glWidget->update();
        float render_time = fps_timer.GetMilliseconds();
//        printf("world time %.2f render time %.2f\n", world_time, render_time-world_time);
    };

    void on_verticalSlider_valueChanged(int count){
        body->SetTransform(body->GetPosition(), b2_pi * count/1800.f);
    }

    void on_floatSpinBox_valueChanged(double i){
        k = (float)i;
    }
};

