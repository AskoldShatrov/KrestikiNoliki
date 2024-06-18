#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPainter>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();


protected:
   void paintEvent(QPaintEvent* event);

private slots:
    void on_leftButton_clicked();
    void setTabWidgetTransparent();
    void setTab2Background();
    void setMainWidgetBackground();
    void on_rightButton_clicked();
    void on_startButton_clicked();
    void on_aboutButton_clicked();
    //запись on_ использует метаобъектный компилятор
    void onGameAreaButtonClicked();
    void onComputerSlot();



private:
    Ui::Widget *ui;
    void setInterfaceStyle();
    void changeButtonStatus(int num);
    void configurationTabWidget();
     void setTabWidgetStyle();
    void addFonts();
    void changeButtonStyle(int row, int column, const QString& style);
    void configurationGameAreaButtons();
    void setGameAreaButtons();
    void start();
    void lockPlayer();
    void computerInGame();
    void checkGameStop();
    void endGame();
    void getVictoryStyle();
    void applyVictoryStyle();
    QStringList getImageFiles();
    void setRandomBackground();
    void startBackgroundTimer();



    char gameArea[3][3] = {
        {'-', '-', '-'}, {'-', '-', '-'}, {'-', '-', '-'}
    };
    char player = 'X'; // X или O
    int progress = 0;
    bool gameStart = false;
    bool playerLocked = true;
    QTimer *timer;
    bool stop;
    char winner;

};





#endif // WIDGET_H
