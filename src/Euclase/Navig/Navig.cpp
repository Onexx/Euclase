#include "Navig.h"

#include "data.h"

Navig::Navig(QWidget* parent) : QWidget(parent), ui(new Ui::Navig) {
    setWindowState(Qt::WindowMaximized);
    ui->setupUi(this);
    this->setWindowFlag(Qt::FramelessWindowHint);

    // Connecting all buttons
    connect(ui->PbBlock, &QPushButton::clicked, this, &Navig::Block);
    connect(ui->PbOpen, &QPushButton::clicked, this, &Navig::Open);
    connect(ui->PbOpenMap, &QPushButton::clicked, this, &Navig::OpenMap);
    connect(ui->PbSaveMap, &QPushButton::clicked, this, &Navig::SaveMap);

    // Setting names to buttons from language file
    ui->PbBlock->setText(Data::navBtns::lock);
    ui->PbOpen->setText(Data::navBtns::loadBgnd);
    ui->PbOpenMap->setText(Data::navBtns::loadMap);
    ui->PbSaveMap->setText(Data::navBtns::saveMap);

    // Creating map scene
    scene = new DropScene();
    ui->graphicsView->setAcceptDrops(true);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setAttribute(Qt::WA_AcceptTouchEvents);
    ui->graphicsView_2->setAttribute(Qt::WA_AcceptTouchEvents);

    // Creating bar with rectangles and circles
    auto scene2 = new QGraphicsScene();
    ui->graphicsView_2->setScene(scene2);
    auto c = new DragCircle(0, 0, 100, 100);
    auto r = new DragRect(0, 150, 100, 100);
    scene2->addItem(c);
    scene2->addItem(r);

    // Creating statistics
    StatisticsCreate();

    // Creating temporary save of map
    QFile Tfile("TempMapSave.Etnm");
    Tfile.open(QIODevice::WriteOnly);
    Tfile.close();
}

/**
 * Opens background image of floor plan
 */
void Navig::Open() {
    QString str = QFileDialog::getOpenFileName(nullptr, "Open Dialog", "",
                                               "*.png *.jpg *.jpeg *.bmp");
    scene->clear();
    // Add opened image as a background
    QPixmap Map(str);
    QSize MapSize = ui->graphicsView->size();
    Map = Map.scaled(MapSize, Qt::KeepAspectRatio);
    scene->addPixmap(Map);
    Map = Map.scaled(MapSize, Qt::KeepAspectRatio);

    // Saving image to temporary save
    QFile file("TempMapSave.Etnm");
    if (!(file.open(QIODevice::WriteOnly))) {
        return;
    }
    QDataStream out(&file);
    out.setVersion(QDataStream::Qt_4_2);
    out << Map;
    file.close();
}

/**
 * Saves current map to file
 */
void Navig::SaveMap() {
    QFile Tfile("TempMapSave.Etnm");
    if (!(Tfile.open(QIODevice::ReadOnly))) {
        return;
    }
    QDataStream in(&Tfile);
    in.setVersion(QDataStream::Qt_4_2);
    QPixmap Map;
    in >> Map;
    Tfile.close();
    QString SaveName = QFileDialog::getSaveFileName(
        this, tr("Save File"), "", tr("Euclase Navigation Map(*.Enm)"));
    QSize MapSize = ui->graphicsView->size();
    Map = Map.scaled(MapSize, Qt::KeepAspectRatio);
    QFile file(SaveName);
    if (!(file.open(QIODevice::WriteOnly))) {
        return;
    }
    QDataStream out(&file);
    out.setVersion(QDataStream::Qt_4_2);
    int cnt = 0;

    // counting amount of objects on map
    foreach (QGraphicsItem* item, ui->graphicsView->scene()->items()) {
        if (item->type() == QGraphicsEllipseItem::Type ||
            item->type() == QGraphicsRectItem::Type) {
            cnt++;
        }
    }

    // Writing BG image to save
    out << Map;
    qDebug() << "cnt = " << cnt;

    // Writing amount of objects on map
    out << cnt;
    // Writing data about objects on map
    foreach (QGraphicsItem* item, ui->graphicsView->scene()->items()) {
        if (item->type() == QGraphicsEllipseItem::Type) {
            QString Type = "ellipse";
            out << Type;
            int idx = item->data(Qt::UserRole).toInt(),
                w = item->boundingRect().width(),
                h = item->boundingRect().height();
            QPointF pos = item->pos();
            ObservableCircle* ellipse =
                qgraphicsitem_cast<ObservableCircle*>(item);
            int dir = ellipse->CurrentDirection;
            out << w << h;
            out << pos;
            out << idx;
            out << dir;
            qDebug() << w << ' ' << h << ' ' << pos << ' ' << idx << ' ' << dir
                     << endl;
        }
        if (item->type() == QGraphicsRectItem::Type) {
            QString Type = "rect";
            out << Type;
            int idx = item->data(Qt::UserRole).toInt(),
                w = item->boundingRect().width() - 2,
                h = item->boundingRect().height() - 2;
            QPointF pos = item->pos();
            ObservableRect* rect = qgraphicsitem_cast<ObservableRect*>(item);
            w *= rect->kw;
            h *= rect->kh;
            out << w << h;
            out << pos;
            out << idx;
            qDebug() << w << ' ' << h << ' ' << pos << ' ' << idx << endl;
        }
    }
    file.close();
}

/**
 * Opens from file previously saved map
 */
void Navig::OpenMap() {
    qDebug() << "Opening the map";
    QString str =
        QFileDialog::getOpenFileName(nullptr, "Open Dialog", "", "*.Enm");
    QFile file(str);
    if (!(file.open(QIODevice::ReadOnly))) {
        qDebug() << "Error while opening map";
        return;
    }
    QDataStream in(&file);
    in.setVersion(QDataStream::Qt_4_2);
    scene->clear();

    // Reading BG from save
    QPixmap Map;
    in >> Map;
    scene->addPixmap(Map);

    // Reading amount of objects on map
    int cnt;
    in >> cnt;

    // Reading current configurations for objects
    int R = 255, G = 255, B = 153;
    QFile Cfile("Settings/Conf.txt");
    if (Cfile.open(QIODevice::Text | QIODevice::ReadOnly)) {
        while (!Cfile.atEnd()) {
            bool key = true;
            QString curLine = Cfile.readLine();
            QStringList lst = curLine.split(" ");
            if (lst.at(0) == "Colour" && lst.at(1) == "=") {
                R = lst.at(2).toInt(&key);
                G = lst.at(3).toInt(&key);
                B = lst.at(4).toInt(&key);
                key = false;
            } else {
                if (lst.at(0) == "HeightOfCircle" ||
                    lst.at(0) == "WidthOfCircle" ||
                    lst.at(0) == "HeightOfRectangle" ||
                    lst.at(0) == "WidthOfRectangle" ||
                    (curLine[0] == '/' && curLine[1] == '/')) {
                    key = false;
                }
            }
            if (key) {
                break;
            }
        }
    } else {
        qDebug() << "Can't open configuratons file";
    }
    Cfile.close();

    // Reading data about objects on map
    qDebug() << "Loading objects";
    qDebug() << cnt;
    for (int i = 0; i < cnt; i++) {
        QString Type;
        in >> Type;
        qDebug() << "Type = " << Type;
        if (Type == "ellipse") {
            QPointF pos;
            int w, h, idx, dir;
            in >> w >> h;
            in >> pos;
            in >> idx;
            in >> dir;
            qDebug() << w << h << pos << idx;
            QSizeF size(w, h);
            auto item = new ObservableCircle(QRectF(QPointF(), size));
            item->setData(Qt::UserRole, idx);
            auto number = new QGraphicsTextItem(QString("%0").arg(idx), item);
            auto dirline = new QGraphicsLineItem(item);
            dirline->setPen(
                QPen(Qt::red, 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
            dirline->setData(Qt::UserRole, item->data(Qt::UserRole));
            switch (dir) {
            case (0): {
                dirline->setLine(
                    item->rect().width(), item->rect().height() / 2,
                    item->rect().width() + 7, item->rect().height() / 2);
                break;
            }
            case (1): {
                dirline->setLine(
                    item->rect().width() / 2, item->rect().height(),
                    item->rect().width() / 2, item->rect().height() + 7);
                break;
            }
            case (2): {
                dirline->setLine(0, item->rect().height() / 2, -7,
                                 item->rect().height() / 2);
                break;
            }
            case (3): {
                dirline->setLine(item->rect().width() / 2, 0,
                                 item->rect().width() / 2, -7);
                break;
            }
            }
            number->setFlag(QGraphicsItem::ItemIsSelectable, false);
            number->setFlag(QGraphicsItem::ItemIgnoresTransformations, true);
            number->setPos(
                (item->rect().width() - number->boundingRect().width()) / 2,
                (item->rect().height() - number->boundingRect().height()) / 2);
            item->setPos(pos.x(), pos.y());
            item->setFlag(QGraphicsItem::ItemIsMovable, true);
            item->setFlag(QGraphicsItem::ItemIsSelectable, true);
            item->setBrush(QBrush(QColor(R, G, B, 150)));  // colour
            scene->addItem(item);
        }
        if (Type == "rect") {
            QPointF pos;
            int w, h, idx;
            in >> w >> h;
            in >> pos;
            in >> idx;
            qDebug() << w << ' ' << h << ' ' << pos << ' ' << idx << endl;
            QSizeF size(w, h);
            auto item = new ObservableRect(QRectF(QPointF(), size));
            item->setData(Qt::UserRole, idx);
            auto number = new QGraphicsTextItem(QString("%0").arg(idx), item);
            number->setFlag(QGraphicsItem::ItemIsSelectable, false);
            number->setPos(
                (item->rect().width() - number->boundingRect().width()) / 2,
                (item->rect().height() - number->boundingRect().height()) / 2);
            item->setPos(pos.x(), pos.y());
            item->setFlag(QGraphicsItem::ItemIsMovable, true);
            item->setFlag(QGraphicsItem::ItemIsSelectable, true);
            item->setBrush(QBrush(QColor(R, G, B, 150)));
            scene->addItem(item);
        }
    }
    file.close();

    // Saving BG image to temporary save
    QSize MapSize = ui->graphicsView->size();
    Map = Map.scaled(MapSize, Qt::KeepAspectRatio);
    QFile fileS("TempMapSave.Etnm");
    if (!(fileS.open(QIODevice::WriteOnly))) {
        return;
    }
    QDataStream out(&fileS);
    out.setVersion(QDataStream::Qt_4_2);
    out << Map;

    // Counting and saving amount of objects on map to temporary save
    foreach (QGraphicsItem* item, ui->graphicsView->scene()->items()) {
        if (item->type() == QGraphicsEllipseItem::Type ||
            item->type() == QGraphicsRectItem::Type) {
            cnt++;
        }
    }
    out << cnt;

    // Saving data about objects to temporary save
    foreach (QGraphicsItem* item, ui->graphicsView->scene()->items()) {
        if (item->type() == QGraphicsEllipseItem::Type) {
            QString Type = "ellipse";
            out << Type;
            int w = item->boundingRect().width(),
                h = item->boundingRect().height();
            out << w << h;
            out << item->pos();
            out << item->data(Qt::UserRole).toInt();
        }
        if (item->type() == QGraphicsRectItem::Type) {
            QString Type = "rect";
            out << Type;
            int w = item->boundingRect().width(),
                h = item->boundingRect().height();
            out << w << h;
            out << item->pos();
            out << item->data(Qt::UserRole).toInt();
        }
    }
    fileS.close();
}

void Navig::keyPressEvent(QKeyEvent* event) {
    if (event->key() == Qt::Key_Escape && isBlocked) {
        // Unblocking the map
        isBlocked = false;
        ui->PbBlock->show();
        ui->PbOpen->show();
        ui->PbOpenMap->show();
        ui->PbSaveMap->show();
        ui->graphicsView_2->show();
        int cnt = 0;
        for (auto item : ui->graphicsView->scene()->items()) {
            if (dynamic_cast<QGraphicsEllipseItem*>(item) ||
                dynamic_cast<QGraphicsRectItem*>(item)) {
                item->setFlag(QGraphicsItem::ItemIsMovable, true);
                qDebug() << cnt++;
                item->setFlag(QGraphicsItem::ItemIsSelectable, true);
            }
        }
    } else {
        if (event->key() == Qt::Key_S) {
            if (event->modifiers() & Qt::CTRL) {
                SaveMap();
                qDebug() << "Save";
            }
        } else {
            QWidget::keyPressEvent(event);
        }
    }
}

/**
 * Disables the movement of circles and rectangles.
 * Makes navigation ready for using by guests.
 */
void Navig::Block() {
    isBlocked = true;
    QMessageBox* msgBox = new QMessageBox(
        QMessageBox::Information, Data::navBlock::head, Data::navBlock::text,
        QMessageBox::Ok | QMessageBox::Cancel);
    msgBox->setButtonText(QMessageBox::Ok, Data::navBlock::ok);
    msgBox->setButtonText(QMessageBox::Cancel, Data::navBlock::cancel);
    int n = msgBox->exec();
    delete msgBox;
    if (n == QMessageBox::Ok) {
        ui->PbBlock->hide();
        ui->PbOpen->hide();
        ui->PbOpenMap->hide();
        ui->PbSaveMap->hide();
        ui->graphicsView_2->hide();
        for (auto item : ui->graphicsView->scene()->items()) {
            item->setFlag(QGraphicsItem::ItemIsMovable, false);
            item->setFlag(QGraphicsItem::ItemIsSelectable, false);
        }
    }
}

Navig::~Navig() {}
