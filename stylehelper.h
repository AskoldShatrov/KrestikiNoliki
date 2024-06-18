#ifndef STYLEHELPER_H
#define STYLEHELPER_H


#include<QString>

class StyleHelper
{
public:
    static QString getComputerVictoryStyle();
    static QString getTab1Tab2Style();
    static QString getCrossComputerVictoryStyle();
    static QString getZeroComputerVictoryStyle();
    static QString getMainWidgetStyle();
    static QString getStartButtonsStyle();
    static QString getLeftButtonStyle();
    static QString  getRightButtonStyle();
    static QString getLeftButtonActiveStyle();
    static QString  getRightButtonActiveStyle();
    static QString getTabWidgetStyle();
    static QString getTabStyle();
    static QString getTab2Style();
    static QString getBlankButtonStyle();
    static QString getCrossNormalStyle();
    static QString getCrossVictoryStyle();
    static QString getCrossLostStyle();
    static QString getZeroVictoryStyle();
    static QString getZeroLostStyle();
    static QString getKrestikiLabelStyle();
    static QString getZeroNormalStyle();
    static QString getNormalMessegeStyle();
    static QString getVictoryMessegeStyle();
    static QString getLostMessegeStyle();
    static QString getAboutTextStyle();
    static QString getDrawMessegeStyle();
    static QStringList getRandomBackgroundImages();
};

#endif // STYLEHELPER_H
