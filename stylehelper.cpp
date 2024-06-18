#include "stylehelper.h"
#include <QStringList>
#include <QRandomGenerator>
#include <QDir>

QString StyleHelper::getCrossComputerVictoryStyle()
{
    return "QPushButton {"
           "background:none;"
           "border: none;"
           "background-color: red;"
           "background-image: url(:/resourses/images/cross_large.png);"
           "background-repeat: no-repeat;"
           "background-position: center center;"
           "}";
}

QString StyleHelper::getZeroComputerVictoryStyle()
{
    return "QPushButton {"
           "background:none;"
           "border: none;"
           "background-color: red;"
           "background-image: url(:/resourses/images/zero_large.png);"
           "background-repeat: no-repeat;"
           "background-position: center center;"
           "}";
}


QString StyleHelper::getTab1Tab2Style()
{
    return
           "QWidget#tab_2 {"
           "background:none;"
           "background-image: none;"
           "background-color: #F0F0F0;"
           "color: #333333;"
           "font-family: 'Roboto Medium';"
           "font-size: 14px;"
           "border: 1px solid #CCCCCC;"
           "border-radius: 5px;"
           "padding: 10px;"
           "}";
}


    QStringList StyleHelper::getRandomBackgroundImages() {
        QString folderPath = ":/resourses/images/back";
        QDir folder(folderPath);
        QStringList filters;
        filters << "*.jpg" << "*.png" << "*.jpeg";
        QStringList imageFiles = folder.entryList(filters, QDir::Files);
        return imageFiles;
    }
    QString StyleHelper::getKrestikiLabelStyle()
    {
        return "QLabel#Krestiki {"
               "background: #5C2634;"
               "border-radius: 6px;"
               "background-color: rgba(92, 38, 52, 0.95); "
               "}";
    }
    QString StyleHelper::getStartButtonsStyle()
    {
        return "QPushButton{"
               "color: #fff;"
               "background: none;"
               "border: none;"
               "border-radius: 19px;"
               "background-color: #847277;"
               "font-size: 16px;"
               "font-family: 'Roboto Medium';"
               "}"
               "QPushButton::hover{"
               "background-color: #5C2634;"
               "}"
               "QPushButton::pressed{"
               "background-color: #461B27;"

               "}";
    }

    QString StyleHelper::getComputerVictoryStyle()
    {
        return "QPushButton {"
               "background:none;"
               " background-color: red;"
               "border: none;"
               "background-color: #8B0000;"
               "}";
    }

    QString StyleHelper::getLeftButtonStyle()
    {
        return "QPushButton{"
               "background-image: url(:/resourses/images/cross_small.png);"
               "background-color: #C8A1A9;"
               "background-repeat: no-repeat;"
               "background-position: center center;"
               "border: 1px solid #333;"
               "border-top-left-radius: 5px;"
               "border-bottom-left-radius: 5px;"

               "}";
    }

    QString StyleHelper::getRightButtonStyle()
    {
        return "QPushButton{"
               "background-image: url(:/resourses/images/zero_small.png);"
               "background-color: #C8A1A9;"
               "background-repeat: no-repeat;"
               "background-position: center center;"
               "border: 1px solid #333;"
               "border-top-right-radius: 5px;"
               "border-bottom-right-radius: 5px;"

               "}";
    }
    QString StyleHelper::getLeftButtonActiveStyle()
    {
        return "QPushButton{"
               "background-image: url(:/resourses/images/cross_small.png);"

               "background-repeat: no-repeat;"
               "background-position: center center;"
               "border: 1px solid #333;"
               "border-top-left-radius: 5px;"
               "border-bottom-left-radius: 5px;"
               "}";
    }

    QString StyleHelper::getRightButtonActiveStyle()
    {
        return "QPushButton{"
               "background-image: url(:/resourses/images/zero_small.png);"
               "background-repeat: no-repeat;"
               "background-position: center center;"
               "border: 1px solid #333;"
               "border-top-right-radius: 5px;"
               "border-bottom-right-radius: 5px;"
               "}";
    }

    QString StyleHelper::getTabWidgetStyle()
    {
        return "QTabWidget{"
               "border: none;"
               "}"
               "QTabWidget::pane{"
               "border: 1px solid #222;"
               "border-radius: 3px;"
               "}";
    }

    QString StyleHelper::getTabStyle()
    {
        return "QWidget#tab{"
               "background: rgb(33, 40, 45);"
               "}";
    }


    QString StyleHelper::getBlankButtonStyle()
    {
        return "QPushButton {"
               "border: none;"


               "background: #F5F5F5;"
               "}"
               "QPushButton:hover {"
               "background:#B0B0B0;"
               "}";
    }
    QString StyleHelper::getCrossNormalStyle() {
        static QStringList availableImages = StyleHelper::getRandomBackgroundImages();
        if (availableImages.isEmpty()) {
            availableImages = StyleHelper::getRandomBackgroundImages();
        }
        int randomIndex = QRandomGenerator::global()->bounded(availableImages.size());
        QString randomImagePath = availableImages.takeAt(randomIndex);
        QString folderPath = ":/resourses/images/back";

        return "QPushButton {"
               "border: none;"
               "background: url(" + folderPath + "/" + randomImagePath + ") no-repeat center center, qlineargradient(spread:pad, x1:0.216, y1:0.216, x2:0.784, y2:0.784, stop:0 rgba(0, 0, 0, 255), stop:1 rgba(255, 255, 255, 255));"

                                                      "background-blend-mode: multiply;"
                                                      "background-size: cover;"
                                                      "background-position: center;"
                                                      "image: url(:/resourses/images/cross_large.png);"
                                                      "image-position: center center;"
                                                      "}";
    }

    QString StyleHelper::getCrossVictoryStyle()
    {
        return "QPushButton {"

               "background:none;"
               "border: none;"
               "background-color: #20401B;"
               "background-image: url(:/resourses/images/cross_large.png);"
               "background-repeat: no-repeat;"
               "background-position: center center;"
               "}";
    }

    QString StyleHelper::getCrossLostStyle()
    {
        return "QPushButton {"
               "background:none;"
               "border: none;"
               "background-color: #00301F;"
               "background-image: url(:/resourses/images/cross_large.png);"
               "background-repeat: no-repeat;"
               "background-position: center center;"
               "}";
    }

    QString StyleHelper::getZeroNormalStyle() {
        static QStringList availableImages = StyleHelper::getRandomBackgroundImages();
        if (availableImages.isEmpty()) {
            availableImages = StyleHelper::getRandomBackgroundImages();
        }
        int randomIndex = QRandomGenerator::global()->bounded(availableImages.size());
        QString randomImagePath = availableImages.takeAt(randomIndex);
        QString folderPath = ":/resourses/images/back";

        return "QPushButton {"
               "border: none;"
               "background: url(" + folderPath + "/" + randomImagePath + ") no-repeat center center, qlineargradient(spread:pad, x1:0.216, y1:0.216, x2:0.784, y2:0.784, stop:0 rgba(0, 0, 0, 255), stop:1 rgba(255, 255, 255, 255));"
                                                      "background-blend-mode: multiply;"
                                                      "background-size: cover;"
                                                      "background-position: center;"
                                                      "image: url(:/resourses/images/zero_large.png);"
                                                      "image-position: center center;"
                                                      "}";
    }

    QString StyleHelper::getZeroVictoryStyle()
    {
        return "QPushButton {"
               "border: none;"
               "background-color: #20401B;"
               "background-image: url(:/resourses/images/zero_large.png);"
               "background-repeat: no-repeat;"
               "background-position: center center;"
               "}";
    }

    QString StyleHelper::getZeroLostStyle()
    {
        return "QPushButton {"
               "border: none;"
               "background-color: #00301F;"
               "background-image: url(:/resourses/images/zero_large.png);"
               "background-repeat: no-repeat;"
               "background-position: center center;"
               "}";
    }
    QString StyleHelper::getNormalMessegeStyle()
    {
        return "QLabel#messageLabel {"
               "background: none;"
               "font-family: 'Roboto Medium';"
               "font-size: 12px;"
               "background-color: #D7BAC2;"
               "color: ##00008B;"
               "font-weight: bold;"
               "}";
    }




    QString StyleHelper::getVictoryMessegeStyle()
    {
        return "QLabel {"
               "background:none;"
               "font-family: 'Roboto Medium';"
               "font-size: 12px;"
               "background: #228B22;"
               "border: 1px solid #000000;"
               "color: ##00008B;"
                 "font-weight: bold;"
               "}";
    }
    QString StyleHelper::getLostMessegeStyle()
    {
        return "QLabel {"
               "background:none;"
               "font-family: 'Roboto Medium';"
               "font-size: 12px;"
               "background: #8B0000;"
               "border: 1px solid #000000;"
               "color: ##00008B;"
                 "font-weight: bold;"
               "}";
    }

    QString StyleHelper::getDrawMessegeStyle()
    {
        return "QLabel {"
               "background:none;"
               "font-family: 'Roboto Medium';"
               "font-size: 12px;"
               "background: #808080;"
               "border: 1px solid #000000;"
               "color: ##00008B;"
                 "font-weight: bold;"
               "}";
    }

