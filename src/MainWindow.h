#pragma once

#include <QMainWindow>
#include <QFontDialog>
#include <QFileDialog>

#include "ui_main.h"

class MainWindow : public QMainWindow, private Ui::MainWindow {
Q_OBJECT
public:
    MainWindow() {
        setupUi(this);
        show();
    }

};

