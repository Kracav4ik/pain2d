#pragma once

#include <QOpenGLWidget>
#include <stdio.h>
#include <QPainter>
#include <Box2D/Box2d.h>

class GLOutput : public QOpenGLWidget {
Q_OBJECT
private:
    b2Body* body;

protected:
    virtual void paintGL() override {
        QPainter painter(this);
        painter.setPen(Qt::white);
        if (body) {
            const b2Vec2& p = body->GetPosition();
            painter.drawEllipse(100+p.x*5, 100+p.y*30, 50, 50);
        }
    }

    virtual void resizeGL(int w, int h) override {
    }

    virtual void initializeGL() override {
    }

public:
    GLOutput(QWidget* parent) : QOpenGLWidget(parent), body(nullptr) {
    }

    void setBody(b2Body* b) {
        body = b;
    }
};

