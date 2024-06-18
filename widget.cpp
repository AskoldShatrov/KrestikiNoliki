#include "widget.h"
#include "ui_widget.h"
#include <QTabBar>
#include "stylehelper.h"
#include <QStyleOption>
#include <QFontDatabase>
#include <QGridLayout>

#include <QRandomGenerator>
#include <QDir>
#include <QPalette>

#include "time.h"
#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    setMainWidgetBackground();
    configurationTabWidget();
    addFonts();
    setInterfaceStyle();
    player = 'X';
    changeButtonStatus(0);
    configurationGameAreaButtons();
    timer = new QTimer(this);
    connect (timer,&QTimer::timeout,this,&Widget::onComputerSlot);

    startBackgroundTimer();


}


void Widget::setMainWidgetBackground()
{
    QString style = "QWidget { background-image: url(:/resourses/images/backimages/back.png); background-repeat: no-repeat; background-size: cover; }";
    this->setStyleSheet(style);
}


Widget::~Widget()
{
    delete ui;
}

void Widget::setTabWidgetTransparent()
{
    ui->tabWidget->setStyleSheet("background: transparent;");
}

QStringList getImageFiles() {
    QString folderPath = ":/resourses/images/backimages";
    QDir folder(folderPath);
    QStringList filters;
    filters << "*.jpg" << "*.png" << "*.jpeg";
    return folder.entryList(filters, QDir::Files);
}

void Widget::setRandomBackground()
{
    QString folderPath = ":/resourses/images/backimages";
    QDir folder(folderPath);
    QStringList filters;
    filters << "*.jpg" << "*.png" << "*.jpeg";
    QStringList imageFiles = folder.entryList(filters, QDir::Files);
    if (!imageFiles.isEmpty()) {
        QString randomImagePath = folderPath + "/" + imageFiles.at(QRandomGenerator::global()->bounded(imageFiles.size()));
        QString style = QString("QWidget { background-image: url(%1); background-repeat: no-repeat; background-size: cover; }").arg(randomImagePath);
        this->setStyleSheet(style);
        ui->messageLabel->setStyleSheet(StyleHelper::getNormalMessegeStyle());
    }
}
void Widget::startBackgroundTimer() {
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Widget::setRandomBackground);
    timer->start(6000);


//Позволяет использовать правила QSS для основного виджета который является наследником QWIDGET
void Widget::paintEvent(QPaintEvent *event)
{
    QStyleOption opt;
    opt.initFrom(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
    QWidget::paintEvent(event);
}

void Widget::setInterfaceStyle()
{

    ui->startButton->setStyleSheet(StyleHelper::getStartButtonsStyle());
    ui->aboutButton->setStyleSheet(StyleHelper::getStartButtonsStyle());
    ui->rightButton->setStyleSheet(StyleHelper::getRightButtonActiveStyle());
    ui->leftButton->setStyleSheet(StyleHelper::getLeftButtonActiveStyle());
    ui->tabWidget->setStyleSheet(StyleHelper::getTabWidgetStyle());
    ui->tab->setStyleSheet(StyleHelper::getTabStyle());
    ui->Krestiki->setStyleSheet(StyleHelper::getKrestikiLabelStyle());

    ui->tabWidget->setStyleSheet("QTabWidget::pane { background: #1E2022; }");

    setGameAreaButtons();

    ui->messageLabel->setText("ПРИВЕТ КРАСОТКА");
    ui->messageLabel->setStyleSheet(StyleHelper::getNormalMessegeStyle());
    ui->messageLabel->setStyleSheet(StyleHelper::getNormalMessegeStyle());
    ui->tab_2->setStyleSheet(StyleHelper::getTab1Tab2Style());


}


void Widget::setTab2Background()
{
    QPalette palette = ui->tab_2->palette();
    palette.setColor(QPalette::Window, QColor("#YOUR_DESIRED_COLOR")); // Замените #YOUR_DESIRED_COLOR на нужный цвет
    ui->tab_2->setPalette(palette);
    ui->tab_2->setAutoFillBackground(true);
}

void Widget::changeButtonStatus(int num)
{

    if(num==1){

        ui->leftButton->setStyleSheet(StyleHelper::getLeftButtonActiveStyle());
        ui->rightButton->setStyleSheet(StyleHelper::getRightButtonStyle());
    }else {     ui->leftButton->setStyleSheet(StyleHelper::getLeftButtonStyle());
        ui->rightButton->setStyleSheet(StyleHelper::getRightButtonActiveStyle());}

}

void Widget::configurationTabWidget()
{
    ui->tabWidget->tabBar()->hide();
    ui->tabWidget->setMaximumHeight(320);
    ui->tabWidget->setCurrentIndex(0);
}

void Widget::addFonts()
{
    QFontDatabase::addApplicationFont(":/resourses/fonts/Roboto-Medium.ttf");
    QFontDatabase::addApplicationFont(":/resourses/fonts/Roboto-MediumItalic.ttf");

}
void Widget::changeButtonStyle(int row, int column, const QString& style)
{
    QGridLayout *grid = qobject_cast<QGridLayout*>(ui->tab->layout());
    QPushButton *btn = qobject_cast<QPushButton*>(grid->itemAtPosition(row, column)->widget());
    // Получили указатель на кнопку, которую получили из дизайнера Qt Designer
    btn->setStyleSheet(style);

}

void Widget::configurationGameAreaButtons()
{
    QGridLayout *grid = qobject_cast<QGridLayout*>(ui->tab->layout());
    for (int row = 0; row < 3; row++) {
        for (int column = 0; column < 3; column++) {
            QPushButton *btn = qobject_cast<QPushButton*>(grid->itemAtPosition(row, column)->widget());
            btn ->setProperty("row",row);
            btn ->setProperty("column", column);

            connect(btn,&QPushButton::clicked, this, &Widget::onGameAreaButtonClicked);
        }
    }
}
void Widget::setGameAreaButtons()
{
    QString style = StyleHelper::getBlankButtonStyle();
    for(int row=0; row<3; row++){
        for(int column=0; column<3; column++){
            changeButtonStyle(row, column, style);
        }
    }
}

void Widget::start()
{

    setGameAreaButtons();

    for (int r = 0; r < 3; r++) {
        for (int c = 0; c < 3; c++) {
            gameArea[r][c] = '-';
        }
    }
    progress = 0;
    gameStart = true;

    if (player != 'X')
        computerInGame();

}

void Widget::lockPlayer()
{
    if (player) {
        playerLocked = false;
    } else {
        playerLocked = true;
    }
}
void Widget::on_leftButton_clicked()
{
    changeButtonStatus(2);
    player = 'X';
}


void Widget::on_rightButton_clicked()
{
    changeButtonStatus(1);
    player = '0';
}
void Widget::on_startButton_clicked()
{
    if (player == '\0') { // Проверяем, выбран ли символ (крестик или нолик)
        ui->messageLabel->setText("Выберите крестик или нолик!");
        ui->messageLabel->setStyleSheet(StyleHelper::getNormalMessegeStyle());
        return; // Если символ не выбран, выходим из метода
    }

    ui->tabWidget->setCurrentIndex(0);
    if(gameStart)
    {
        playerLocked = 0;
        ui->startButton->setText("Играть");
        ui->startButton->setStyleSheet(StyleHelper::getStartButtonsStyle());
        ui->leftButton->setDisabled(false);
        ui->rightButton->setDisabled(false);
        gameStart = false;
        ui->messageLabel->setText("ЛОХ");
        ui->messageLabel->setStyleSheet(StyleHelper::getLostMessegeStyle());
    }
    else {
        ui->messageLabel->setText("ПОЕХАЛИ");
        ui->messageLabel->setStyleSheet(StyleHelper::getNormalMessegeStyle());
        start();
        lockPlayer();
        ui->startButton->setText("Сдаюсь :(((((");
        ui->startButton->setStyleSheet(StyleHelper::getStartButtonsStyle());
        ui->leftButton->setDisabled(true);
        ui->rightButton->setDisabled(true);

        // Разблокировка всех игровых кнопок
        QGridLayout *grid = qobject_cast<QGridLayout*>(ui->tab->layout());
        for (int row = 0; row < 3; row++) {
            for (int column = 0; column < 3; column++) {
                QPushButton *btn = qobject_cast<QPushButton*>(grid->itemAtPosition(row, column)->widget());
                btn->setEnabled(true); // Разблокировка кнопки
            }
        }
    }
}
void Widget::onGameAreaButtonClicked()
{
    if (!playerLocked) {
        QPushButton *btn = qobject_cast<QPushButton*>(sender());
        int row = btn->property("row").toInt();
        int column = btn->property("column").toInt();
        QString style;
        if (player == 'X') {
            style = StyleHelper::getCrossNormalStyle();
            gameArea[row][column] = 'X';
        } else {
            style = StyleHelper::getZeroNormalStyle();
            gameArea[row][column] = '0';
        }
        changeButtonStyle(row, column, style);
        playerLocked = true;
        progress++;
        checkGameStop();
        endGame();
        computerInGame();

        // Отключаем кнопку после нажатия
        btn->setEnabled(false);
    }
}
void Widget::computerInGame()
{
    if (stop)
        return;
    srand(time(0));
    int index = rand()%3;
    QStringList list = {"ДУМАЮ КАК ПОХОДИТЬ ", "ХМ... ", "СЕЙЧАС Я ТЕБЯ УДИВЛЮ"};
    ui->messageLabel->setText(list.at(index));
    timer ->start(2000);
}

void Widget::checkGameStop()
{
    winner = '-';
    char symbols[2] = {'X', '0'};
    for (int i = 0; i < 2; i++) {
        // Проверка строк
        for (int row = 0; row < 3; row++) {
            if ((gameArea[row][0] == symbols[i]) && (gameArea[row][1] == symbols[i]) && (gameArea[row][2] == symbols[i])) {
                stop = true;
                winner = symbols[i];
                endGame(); // Вызов endGame после определения победы по строке
                return;
            }
        }

        // Проверка столбцов
        for (int col = 0; col < 3; col++) {
            if ((gameArea[0][col] == symbols[i]) && (gameArea[1][col] == symbols[i]) && (gameArea[2][col] == symbols[i])) {
                stop = true;
                winner = symbols[i];
                endGame(); // Вызов endGame после определения победы по столбцу
                return;
            }
        }
    }

    // Проверка диагоналей
    if ((gameArea[0][0] == 'X') && (gameArea[1][1] == 'X') && (gameArea[2][2] == 'X')) {
        stop = true;
        winner = 'X';
        endGame(); // Вызов endGame после определения победы по главной диагонали
        return;
    }

    if ((gameArea[0][0] == '0') && (gameArea[1][1] == '0') && (gameArea[2][2] == '0')) {
        stop = true;
        winner = '0';
        endGame(); // Вызов endGame после определения победы по главной диагонали
        return;
    }

    if ((gameArea[0][2] == 'X') && (gameArea[1][1] == 'X') && (gameArea[2][0] == 'X')) {
        stop = true;
        winner = 'X';
        endGame(); // Вызов endGame после определения победы по побочной диагонали
        return;
    }

    if ((gameArea[0][2] == '0') && (gameArea[1][1] == '0') && (gameArea[2][0] == '0')) {
        stop = true;
        winner = '0';
        endGame(); // Вызов endGame после определения победы по побочной диагонали
        return;
    }

    // Если игра не завершена, сбрасываем флаг stop
    stop = false;

    if(progress == 9){
        stop = true;
        winner = '-'; // Устанавливаем ничью
        endGame(); // Вызов endGame после определения ничьей
    }
}

void Widget::endGame()
{
    if (stop) {
        if (winner == player) {
            // Применение стиля победы для кнопок игрока
            for (int r = 0; r < 3; r++) {
                for (int c = 0; c < 3; c++) {
                    if ((r == 0 && c == 0) || (r == 1 && c == 1) || (r == 2 && c == 2) ||
                        (r == 0 && c == 2) || (r == 2 && c == 0) ||
                        (gameArea[r][0] == player && gameArea[r][1] == player && gameArea[r][2] == player) ||
                        (gameArea[0][c] == player && gameArea[1][c] == player && gameArea[2][c] == player)) {
                        if (gameArea[r][c] == player) {
                            if (player == 'X') {
                                changeButtonStyle(r, c, StyleHelper::getCrossVictoryStyle());
                            } else {
                                changeButtonStyle(r, c, StyleHelper::getZeroVictoryStyle());
                            }
                        }
                    }
                }
            }
        } else if (winner == '-') {
            // Ничья
        } else {
            // Применение стиля поражения для кнопок компьютера
            for (int r = 0; r < 3; r++) {
                for (int c = 0; c < 3; c++) {
                    if ((r == 0 && c == 0) || (r == 1 && c == 1) || (r == 2 && c == 2) ||
                        (r == 0 && c == 2) || (r == 2 && c == 0) ||
                        (gameArea[r][0] == winner && gameArea[r][1] == winner && gameArea[r][2] == winner) ||
                        (gameArea[0][c] == winner && gameArea[1][c] == winner && gameArea[2][c] == winner)) {
                        if (gameArea[r][c] == winner) {
                            if (winner == 'X') {
                                changeButtonStyle(r, c, StyleHelper::getCrossComputerVictoryStyle());
                            } else {
                                changeButtonStyle(r, c, StyleHelper::getZeroComputerVictoryStyle());
                            }
                        }
                    }
                }
            }
        }

        // Блокировка всех игровых кнопок
        QGridLayout *grid = qobject_cast<QGridLayout*>(ui->tab->layout());
        for (int row = 0; row < 3; row++) {
            for (int column = 0; column < 3; column++) {
                QPushButton *btn = qobject_cast<QPushButton*>(grid->itemAtPosition(row, column)->widget());
                btn->setEnabled(false); // Блокировка кнопки
            }
        }

        playerLocked = true;
        ui->startButton->setText("Играть");
        ui->startButton->setStyleSheet(StyleHelper::getStartButtonsStyle());
        ui->leftButton->setDisabled(false);
        ui->rightButton->setDisabled(false);
        gameStart = false;
    }
}
void Widget::onComputerSlot()
{
    char comp;
    QString style;

    if (player == 'X') {
        comp = '0';
        style = StyleHelper::getZeroNormalStyle();
    } else {
        comp = 'X';
        style = StyleHelper::getCrossNormalStyle();
    }

    timer->stop();

    while (true) {
        int row = rand() % 3;
        int column = rand() % 3;
        if (gameArea[row][column] == '-') {
            gameArea[row][column] = comp;

            QGridLayout *grid = qobject_cast<QGridLayout*>(ui->tab->layout());
            QPushButton *btn = qobject_cast<QPushButton*>(grid->itemAtPosition(row, column)->widget());

            changeButtonStyle(row, column, style);
            ui->messageLabel->setText("ХОДИ!!!!!");
            progress++;
            checkGameStop();
            endGame();

            // Отключаем кнопку после хода компьютера
            btn->setEnabled(false);
            playerLocked = false; // Сброс переменной после хода компьютера
            break;
        }
    }
}
void Widget::on_aboutButton_clicked()
{
    ui->tabWidget->setCurrentIndex(1);
}
// ui->pushButton_10->setStyleSheet(); если хочу адрессоваться к конкретному
// ui->tabWidget->setStyleSheet("QPushButton{color:#f00;}");
// int id = QFontDatabase::addApplicationFont(":/resourses/fonts/Roboto-Medium.ttf");
// QString family =  QFontDatabase::applicationFontFamilies(id).at(0);
// qDebug() << family; //для выяснения имени шрифта с которым нужно будет работать
