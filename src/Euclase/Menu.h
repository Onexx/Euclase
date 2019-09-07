#pragma once
#include <QMainWindow>
#include <QSound>
#include <QSoundEffect>
#include <QWidget>
#include "MenuInfoPages/Description.h"
#include "MenuInfoPages/InfoView.h"
#include "MenuInfoPages/Instruct.h"
#include "MenuInfoPages/Partners.h"
#include "MenuInfoPages/Timetable.h"
#include "Navig/Navig.h"
#include "RegistrationForm.h"
#include "ReturnButton.h"
#include "ui_Menu.h"

namespace Ui {
class Menu;
}

class Menu : public QMainWindow {
    Q_OBJECT

  public:
    explicit Menu(QWidget *parent = nullptr);
    ~Menu();
    void keyPressEvent(QKeyEvent *event) Q_DECL_OVERRIDE;

  private slots:
    void Navig();
    void Info();
    void Partners();
    void Description();
    void Hide();
    void Timetable();
    void Register();
    void Instruct();
    void PlayRet();

  private:
    Ui::Menu *ui;
    class Navig *nav;
    class InfoView *info;
    class ReturnButton *rb;
    class Description *descr;
    class Partners *prtn;
    class Timetable *tmtbl;
    class RegistrationForm *reg;
    class Instruct *instr;
    QTimer *soundTimer;
};
