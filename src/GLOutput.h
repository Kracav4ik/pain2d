#pragma once

#include <QOpenGLWidget>
#include <stdio.h>

class GLOutput : public QOpenGLWidget {
Q_OBJECT
public:
    GLOutput(QWidget* parent) : QOpenGLWidget(parent) {
    }
};

