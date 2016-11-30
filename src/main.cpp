#include <QApplication>
#include <Box2D/Box2d.h>

#include "MainWindow.h"


b2Vec2 gravity(-.2f, 2.0f);
b2World world(gravity);

float frand(float from=0, float to=1) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dist(from, to);
    return dist(gen);
}

int main(int argc, char* argv[]) {
    b2BodyDef groundBodyDefw;
    groundBodyDefw.position.Set(0.0f, 50.0f);
    b2Body* groundBody = world.CreateBody(&groundBodyDefw);
    b2PolygonShape groundBox;
    groundBox.SetAsBox(100.0f, 1.0f);
    groundBody->CreateFixture(&groundBox, 0.0f);

    for (int i = -1; i < 2; i+=2) {
        b2BodyDef groundBodyDefh;
        groundBodyDefh.position.Set(i*100.0f, 30.0f);
        b2Body* groundBodyh = world.CreateBody(&groundBodyDefh);
        b2PolygonShape groundBoxh;
        groundBoxh.SetAsBox(1.0f, 20.0f);
        groundBodyh->CreateFixture(&groundBoxh, 0.0f);
    }
    for (int x = 0; x < 50; ++x) {
        for (int y = 0; y < 20; ++y) {
            b2BodyDef bodyDef;
            bodyDef.type = b2_dynamicBody;
            bodyDef.position.Set(-50.0f + 2*x, -50.0f + 2*y );
            b2Body* body = world.CreateBody(&bodyDef);
            b2CircleShape dynamicBox;
            b2FixtureDef fixtureDef;
            fixtureDef.shape = &dynamicBox;
            dynamicBox.m_radius = 0.8;
            fixtureDef.density = 0.3f;
            fixtureDef.friction = 0.01f;
            body->CreateFixture(&fixtureDef);
            body->ApplyLinearImpulseToCenter(0.3*b2Vec2(frand(), frand()), true);
        }
    }

    QApplication app(argc, argv);
    MainWindow* window = new MainWindow(&world);
    return app.exec();
}
