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

public:
    MainWindow(b2Body* pBody, b2World* pWorld) : world(pWorld) {
        setupUi(this);
        glWidget->setBody(pBody);
        show();
        QObject::connect(&timer, SIGNAL(timeout()), this, SLOT(tick()));
        timer.start(1);
    }

public slots:
    void tick() {
        float32 timeStep = 0.5 / 60.0f;
        int32 velocityIterations = 6;
        int32 positionIterations = 2;

        world->Step(timeStep, velocityIterations, positionIterations);
        glWidget->update();
    };
};

