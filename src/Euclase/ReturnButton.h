#pragma once

#include <QSound>
#include <QWidget>
#include "ui_ReturnButton.h"

namespace Ui {
class ReturnButton;
}

class Menu;
class Navig;

/**
 * Describes button that returns to menu
 */
class ReturnButton : public QWidget {
    Q_OBJECT

  public:
    explicit ReturnButton(QWidget *parent = 0);
    ~ReturnButton();
    Menu *menu;
    Navig *nav;
    QSound *curSound;
    QSound *retSound;
    QTimer *soundTimer;
    class InfoView *info;
    class Partners *prtn;
    class Description *descr;
    class Timetable *tmtbl;
    class RegistrationForm *reg;
    class Instruct *instr;

  private slots:
    void Return();

  private:
    Ui::ReturnButton *ui;
};
