#pragma once

#include <QMainWindow>
#include <QFontDialog>
#include <QFileDialog>
#include <QTimer>
#include <Box2D/Box2d.h>

#include "ui_main.h"

class MainWindow : public QMainWindow, private Ui::MainWindow {
Q_OBJECT
private:
    QTimer timer;
    b2World* world;
    b2Timer fps_timer;

public:
    MainWindow(b2World* pWorld) : world(pWorld) {
        setupUi(this);
        glWidget->setWorld(pWorld);
        world->SetDebugDraw(glWidget);
        show();
        QObject::connect(&timer, SIGNAL(timeout()), this, SLOT(tick()));
        timer.start(10);
    }

public slots:
    void tick() {
        float passed_time = fps_timer.GetMilliseconds();
        fps_timer.Reset();
        float32 timeStep = passed_time/1000;
        int32 velocityIterations = 6;
        int32 positionIterations = 2;

        world->Step(timeStep/3, velocityIterations, positionIterations);
        float world_time = fps_timer.GetMilliseconds();
        glWidget->update();
        float render_time = fps_timer.GetMilliseconds();
        printf("world time %.2f render time %.2f\n", world_time, render_time-world_time);
    };
};

