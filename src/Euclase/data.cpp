#include "data.h"

/**
 * Describes names for all buttons in program
 */
namespace Data {
QString language = "Ru";
int version = 2;
int build = 7;

namespace btnNames {
QString Reg = "Registration";
QString Nav = "Navigation";
QString Demo = "Camera demo";
QString Ttbl = "Timetable";
QString Partn = "Partners";
QString Info = "Info";
QString Return = "Return";
QString Instr = "Instruction";
}  // namespace btnNames

namespace navBtns {
QString saveMap = "Save map";
QString loadMap = "Open map";
QString loadBgnd = "Open background";
QString lock = "Lock for editing";
QString print = "Print";
QString cancel = "Cancel";
}  // namespace navBtns

namespace navBlock {
QString head = "Blocking";
QString text = "Editing will be available by pressing Esc button";
QString ok = "Ok";
QString cancel = "Cancel";
}  // namespace navBlock

namespace regForm {
QString regBtn = "Register";
QString enterLbl = "Enter id:";
QString nameLbl = "Name:";
QString reqBtn = "Request";
}  // namespace regForm

}  // namespace Data

/**
 * Loads names of all buttons in specified language
 * Language setting can be changed in file Laguage.txt in settings folder
 */
void loadLocale() {
    QFile file2("Settings/Language.txt");
    if (file2.open(QIODevice::ReadOnly)) {
        QTextStream in(&file2);
        in >> Data::language;
    } else {
        qDebug() << "Cannot open language settings file";
    }
    QString path;
    qDebug() << Data::language;
    if (Data::language == "Ru") {
        path = "languageData/Ru.txt";
    } else if (Data::language == "En") {
        path = "languageData/En.txt";
    }
    QFile file(path);
    if (file.open(QIODevice::ReadOnly)) {
        QTextStream in(&file);
        QString s = in.readLine();

        // btnNames
        Data::btnNames::Return = s;
        s = in.readLine();
        Data::btnNames::Reg = s;
        s = in.readLine();
        Data::btnNames::Nav = s;
        s = in.readLine();
        Data::btnNames::Demo = s;
        s = in.readLine();
        Data::btnNames::Ttbl = s;
        s = in.readLine();
        Data::btnNames::Partn = s;
        s = in.readLine();
        Data::btnNames::Info = s;
        s = in.readLine();
        Data::btnNames::Instr = s;
        s = in.readLine();

        // navBtns
        Data::navBtns::saveMap = s;
        s = in.readLine();
        Data::navBtns::loadMap = s;
        s = in.readLine();
        Data::navBtns::loadBgnd = s;
        s = in.readLine();
        Data::navBtns::lock = s;
        s = in.readLine();
        Data::navBtns::print = s;
        s = in.readLine();
        Data::navBtns::cancel = s;
        s = in.readLine();

        // navBlock
        Data::navBlock::head = s;
        s = in.readLine();
        Data::navBlock::text = s;
        s = in.readLine();
        Data::navBlock::ok = s;
        s = in.readLine();
        Data::navBlock::cancel = s;
        s = in.readLine();

        // regForm
        Data::regForm::regBtn = s;
        s = in.readLine();
        Data::regForm::enterLbl = s;
        s = in.readLine();
        Data::regForm::nameLbl = s;
        s = in.readLine();
        Data::regForm::reqBtn = s;
    } else {
        qDebug() << "Cannot open language file";
    }
}
