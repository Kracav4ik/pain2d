#include <QApplication>
#include <Box2D/Box2d.h>

#include "MainWindow.h"


b2Vec2 gravity(.0f, 10.0f);
b2World world(gravity);

int main(int argc, char* argv[]) {
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(0.0f, 5.0f);
    b2Body* groundBody = world.CreateBody(&groundBodyDef);
    b2PolygonShape groundBox;
    groundBox.SetAsBox(50.0f, 10.0f);
    groundBody->CreateFixture(&groundBox, 0.0f);

    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(0.0f, 4.0f);
    b2Body* body = world.CreateBody(&bodyDef);
    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(1.0f, 1.0f);
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;
    body->CreateFixture(&fixtureDef);

    b2BodyDef bodyDef2;
    bodyDef2.type = b2_dynamicBody;
    bodyDef2.position.Set(10.0f, -50.0f);
    b2Body* body2 = world.CreateBody(&bodyDef2);

    b2PolygonShape dynamicBox2;
    dynamicBox2.SetAsBox(4.0f, 3.0f);
    b2FixtureDef fixtureDef2;
    fixtureDef2.shape = &dynamicBox2;
    fixtureDef2.density = 2.0f;
    fixtureDef2.friction = 3;
    body2->CreateFixture(&fixtureDef2);

    b2PolygonShape dynamicBox3;
    dynamicBox3.SetAsBox(5.0f, 4.0f, b2Vec2(70, 0), .0);
    b2FixtureDef fixtureDef3;
    fixtureDef3.shape = &dynamicBox3;
    fixtureDef3.density = 10.0f;
    fixtureDef3.friction = 0.3f;
    body2->CreateFixture(&fixtureDef3);

    QApplication app(argc, argv);
    MainWindow* window = new MainWindow(body, &world);
    return app.exec();
}
