#pragma once

#include <QDebug>
#include <QFile>
#include <QString>
#include <QTextStream>

namespace Data {
extern QString language;
extern int version;
extern int build;

namespace btnNames {
extern QString Reg;
extern QString Nav;
extern QString Demo;
extern QString Ttbl;
extern QString Partn;
extern QString Info;
extern QString Return;
extern QString Instr;
}  // namespace btnNames

namespace navBlock {
extern QString head;
extern QString text;
extern QString ok;
extern QString cancel;
}  // namespace navBlock

namespace navBtns {
extern QString saveMap;
extern QString loadMap;
extern QString loadBgnd;
extern QString lock;
extern QString print;
extern QString cancel;
}  // namespace navBtns

namespace regForm {
extern QString regBtn;
extern QString enterLbl;
extern QString nameLbl;
extern QString reqBtn;
}  // namespace regForm

}  // namespace Data
