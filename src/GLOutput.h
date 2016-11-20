#pragma once

#include <QOpenGLWidget>
#include <stdio.h>
#include <QPainter>
#include <Box2D/Box2d.h>

class GLOutput : public QOpenGLWidget, public b2Draw {
Q_OBJECT
private:
    b2Body* body;
    b2World* world;

protected:
    virtual void paintGL() override {
        if (world) {
            world->DrawDebugData();
        }
    }

    virtual void resizeGL(int w, int h) override {
    }

    virtual void initializeGL() override {
    }

public:
    GLOutput(QWidget* parent)
            : QOpenGLWidget(parent)
            , body(nullptr)
            , world(nullptr)
    {}

    void setBody(b2Body* b) {
        body = b;
    }

    void setWorld(b2World* b) {
        world = b;
        SetFlags(b2Draw::e_shapeBit);
    }

    virtual void DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) override {
        printf("DrawPolygon\n");
    }

    virtual void DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) override {
        QPainter painter(this);
        painter.setPen(QPen(QColor::fromRgbF(color.r, color.g, color.b, color.a)));
        QPolygonF p;

        //for (;vertexCount-->0; ++vertices){
        for (int i = 0; i < vertexCount; ++i){
            p.append(QPointF(vertices[i].x*3.7 + 300, vertices[i].y*5.9 + 200));
        }
        painter.drawPolygon(p);

        printf("DrawSolidPolygon\n");
    }

    virtual void DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color) override {
        printf("DrawCircle\n");
    }

    virtual void
    DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color) override {
        printf("DrawSolidCircle\n");
    }

    virtual void DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color) override {
        printf("DrawSegment\n");
    }

    virtual void DrawTransform(const b2Transform& xf) override {
        printf("DrawTransform\n");
    }

    virtual void DrawPoint(const b2Vec2& p, float32 size, const b2Color& color) override {
        printf("DrawPoint\n");
    }
};

