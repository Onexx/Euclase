#include "Menu.h"

#include <shellapi.h>
#include "data.h"

Menu::Menu(QWidget *parent) : QMainWindow(parent), ui(new Ui::Menu) {
    ui->setupUi(this);                              // Connecting with UI
    this->setWindowFlags(Qt::FramelessWindowHint);  // Deleting frames

    // Connecting all buttons
    connect(ui->PbNavig, &QPushButton::clicked, this, &Menu::Navig);
    connect(ui->PbInfo, &QPushButton::clicked, this, &Menu::Info);
    connect(ui->PbPartners, &QPushButton::clicked, this, &Menu::Partners);
    connect(ui->PbHeader, &QPushButton::clicked, this, &Menu::Description);
    connect(ui->PbTimetable, &QPushButton::clicked, this, &Menu::Timetable);
    connect(ui->PbCamera, &QPushButton::clicked, this, &Menu::Hide);
    connect(ui->PbReg, &QPushButton::clicked, this, &Menu::Register);
    connect(ui->PbInstruction, &QPushButton::clicked, this, &Menu::Instruct);

    // Setting names to buttons from language file
    ui->PbNavig->setText(Data::btnNames::Nav);
    ui->PbInfo->setText(Data::btnNames::Info);
    ui->PbPartners->setText(Data::btnNames::Partn);
    ui->PbTimetable->setText(Data::btnNames::Ttbl);
    ui->PbReg->setText(Data::btnNames::Reg);
    ui->PbCamera->setText(Data::btnNames::Demo);
    ui->PbInstruction->setText(Data::btnNames::Instr);

    // Creating widgets for all functions
    // Saving shortcuts to them
    nav = new class Navig();
    reg = new class RegistrationForm();
    info = new class InfoView();
    prtn = new class Partners();
    descr = new class Description();
    tmtbl = new class Timetable();
    instr = new class Instruct();

    // Creating timer for return sound
    soundTimer = new QTimer();
    soundTimer->setInterval(100);
    connect(soundTimer, SIGNAL(timeout()), this, SLOT(PlayRet()));

    // Creating return button
    rb = new class ReturnButton();
    rb->setGeometry((this->size().width() - rb->size().width() - 10), 10, 60,
                    60);
    rb->move((info->size().width() - rb->size().width() - 10), 10);

    // Saving shortcuts to functions in return button class
    rb->menu = this;
    rb->nav = nav;
    rb->info = info;
    rb->prtn = prtn;
    rb->descr = descr;
    rb->tmtbl = tmtbl;
    rb->reg = reg;
    rb->instr = instr;
    rb->soundTimer = soundTimer;

    // Setting sound for click on return button
    QString str = QFileInfo("Euclase").absolutePath();
    str += "/Materials/BtnSounds/Return.wav";
    rb->retSound = new QSound(str);
}

void Menu::keyPressEvent(QKeyEvent *event) {
    // Close application if 'delete' button pressed
    if (event->key() == Qt::Key_Delete) {
        this->close();
    } else {
        QWidget::keyPressEvent(event);
    }
}

void Menu::Navig() {
    // If pressed navigatin button in menu

    // Showing navigation and return button widgets
    rb->show();
    nav->show();

    // Hiding menu
    this->hide();

    // Setting picture for stand names in navigation
    auto scene = new QGraphicsScene;
    nav->ui->GvNames->setScene(scene);
    scene->clear();
    QString str;
    str = QFileInfo("Euclase").absolutePath();
    str += "/Materials/Names.jpg";
    QPixmap Map3(str);
    QSize MapSize(400, this->size().height());
    Map3 = Map3.scaled(MapSize, Qt::KeepAspectRatio);
    scene->addPixmap(Map3);

    // Playing sound for click on 'Navigation' button in menu
    str = QFileInfo("Euclase").absolutePath();
    str += "/Materials/BtnSounds/Navig.wav";
    rb->curSound = new QSound(str);
    rb->curSound->play();
    soundTimer->start();
}

void Menu::Info() {
    // Showing information and return button widgets
    rb->show();
    info->show();

    // Hiding menu
    this->hide();

    // Playing sound for click on 'Info' button in menu
    QString str = QFileInfo("Euclase").absolutePath();
    str += "/Materials/BtnSounds/Info.wav";
    rb->curSound = new QSound(str);
    rb->curSound->play();
    soundTimer->start();
}

void Menu::Partners() {
    rb->show();
    prtn->show();
    this->hide();
    QString str = QFileInfo("Euclase").absolutePath();
    str += "/Materials/BtnSounds/Partners.wav";
    QSound snd(str);
    rb->curSound = new QSound(str);
    rb->curSound->play();
    soundTimer->start();
}

void Menu::Description() {
    rb->show();
    descr->show();
    this->hide();
    QString str = QFileInfo("Euclase").absolutePath();
    str += "/Materials/BtnSounds/Description.wav";
    rb->curSound = new QSound(str);
    rb->curSound->play();
    soundTimer->start();
}

void Menu::Timetable() {
    rb->show();
    tmtbl->show();
    this->hide();
    QString str = QFileInfo("Euclase").absolutePath();
    str += "/Materials/BtnSounds/Timetable.wav";
    rb->curSound = new QSound(str);
    rb->curSound->play();
    soundTimer->start();
}

void Menu::Hide() {
    rb->show();
    this->hide();
}

void Menu::Register() {
    rb->show();

    void *was;
    Wow64DisableWow64FsRedirection(&was);
    ShellExecuteA(nullptr, "open", "osk.exe", nullptr, nullptr, SW_SHOWNORMAL);
    Wow64RevertWow64FsRedirection(was);

    reg->showFullScreen();
    this->hide();
    QString str = QFileInfo("Euclase").absolutePath();
    str += "/Materials/BtnSounds/Register.wav";
    rb->curSound = new QSound(str);
    rb->curSound->play();
    soundTimer->start();
}

void Menu::Instruct() {
    instr->show();
    rb->show();
    this->hide();
    QString str = QFileInfo("Euclase").absolutePath();
    str += "/Materials/BtnSounds/Instruct.wav";
    rb->curSound = new QSound(str);
    rb->curSound->play();
    soundTimer->start();
}

void Menu::PlayRet() {
    // If sound finished, play return sound
    if (rb->curSound->isFinished()) {
        soundTimer->stop();
        rb->retSound->play();
    }
}

Menu::~Menu() {
    // Deleting menu UI
    delete ui;

    // Deleting navigation temporary save
    QFile Tfile("TempMapSave.Etnm");
    Tfile.remove();

    // Deleting navigation UI
    delete nav->Navig::ui;
}
