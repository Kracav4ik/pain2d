#pragma once

#include <QOpenGLWidget>
#include <stdio.h>
#include <math.h>
#include <QPainter>
#include <Box2D/Box2d.h>

class GLOutput : public QOpenGLWidget, public b2Draw {
Q_OBJECT
private:
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
            , world(nullptr)
    {}

    void setWorld(b2World* b) {
        world = b;
        SetFlags(b2Draw::e_shapeBit);
    }

    virtual void DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) override {
        printf("DrawPolygon\n");
    }

    virtual void DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) override {
        QPainter painter(this);
        painter.translate(350, 200);
        painter.setPen(QPen(QColor::fromRgbF(color.r, color.g, color.b, color.a), 0.4));
        painter.scale(3, 3);
        QPolygonF p;

        for (int i = 0; i < vertexCount; ++i) {
            p.append(QPointF(vertices[i].x, vertices[i].y));
        }
        painter.drawPolygon(p);
    }

    virtual void DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color) override {
        printf("DrawCircle\n");
    }

    virtual void
    DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color) override {
        std::vector<b2Vec2> vertices;
        float a = 0;

        const int VERTICES_COUNT = 64;
        for (int _ = 0; _ < VERTICES_COUNT; ++_) {
            a += 2 * b2_pi / VERTICES_COUNT;
            b2Vec2 point(cosf(a), sinf(a));
            vertices.push_back(center + radius*point);
        }
        DrawSolidPolygon(vertices.data(), vertices.size(), color);

        std::vector<b2Vec2> sun;
        sun.push_back(center);
        sun.push_back(center + radius*axis);
        DrawSolidPolygon(sun.data(), sun.size(), color);
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

