#include "mpushbutton.h"


MPushButton::MPushButton(const BtnType btnType,const QString &text, QWidget *parent) : QPushButton(text,parent)
{
    this->btnType_ = btnType;
    setSheet();
}
MPushButton::MPushButton(const BtnType btnType,const QString &text,const QString size,const QString bg_color,QWidget *parent) : QPushButton(text,parent)
{
    this->btnType_ = btnType;
    this->height_ = sizes.contains(size) ? sizes[size] : 30;
    this->bg_color_ = getColorOrDefault(bg_color,bg_colors,main_color_);
    this->fill_hover_bg_color_ = getColorOrDefault(bg_color, fill_hover_bg_colors, main_fill_hover_color_);
    this->text_hover_bg_color_ = getColorOrDefault(bg_color, text_hover_bg_colors, main_text_hover_color_);
    this->pressed_bg_color_ = getColorOrDefault(bg_color,pressed_bg_colors,main_pressed_color_);
    setSheet();
}

// 设置样式
void MPushButton::setSheet()
{
    QFontMetrics fmwelcome(this->font());
    int wid = fmwelcome.boundingRect(this->text()).width();
    this->setFixedHeight(height_);
    this->setFixedWidth(wid*2.5 + height_ * 0.4);
    QString buttonStyle;

    switch (btnType_)
    {
    case BtnType::text:
        // 创建边框颜色渐变动画
        qDebug()<< "BtnType::text";
        this->setStyleSheet("");
        buttonStyle = QString(
                "MPushButton {"
                "    background-color: #ffffff;"
                "    color: %1;"
                "    border: 1px solid #ffffff;"
                "    border-radius: %2px;"
                "    padding-left: %3px;"
                "    padding-right: %3px;"
                "}"
                "MPushButton::hover{"
                "   background-color: %4;"
                "}"
                "MPushButton::pressed {"
                "    background-color: %5;"
                "}"
            )
            .arg(bg_color_)
            .arg(height_*0.1)
            .arg(height_*0.2)
            .arg(text_hover_bg_color_)
            .arg(pressed_bg_color_);
        break;
    case BtnType::fill:
        buttonStyle = QString(
                "MPushButton {"
                "    background-color: %1;"
                "    color: %2;"
                "    border-radius: %3px;"
                "    padding-left: %4px;"
                "    padding-right: %4px;"
                "}"
                "MPushButton::hover{"
                "   background-color: %5;"
                "}"
                "MPushButton::pressed {"
                "    background-color: %6;"
                "}"
            )
            .arg(bg_color_)
            .arg(text_color_)
            .arg(height_*0.1)
            .arg(height_*0.2)
            .arg(fill_hover_bg_color_)
            .arg(pressed_bg_color_);
        break;
    case BtnType::hollow:
        qDebug()<< "BtnType::hollow";
        buttonStyle = QString(
                "MPushButton {"
                "    background-color: #ffffff;"
                "    color: %1;"
                "    border: 1px solid %1;"
                "    border-radius: %2px;"
                "    padding-left: %3px;"
                "    padding-right: %3px;"
                "}"
                "MPushButton::hover{"
                "    border: 1px solid %4;"
                "    background-color: %5;"
                "}"
                "MPushButton::pressed {"
                "    background-color: %6;"
                "}"
            )
            .arg(bg_color_)
            .arg(height_*0.1)
            .arg(height_*0.2)
            .arg(fill_hover_bg_color_)
            .arg(text_hover_bg_color_)
            .arg(pressed_bg_color_);
        break;
    };
    this->setStyleSheet(buttonStyle);
    this->readFontFamily();
}

// 读取文字样式
void MPushButton::readFontFamily()
{
    int fontId = QFontDatabase::addApplicationFont(":/font/font/Roboto-Medium-12.ttf");
    QStringList fontFamilies = QFontDatabase::applicationFontFamilies(fontId);
    QFont font(fontFamilies.at(0), height_*0.5);
    this->setFont(font);
}

void MPushButton::setColor(const QString &bg_color, const QString &fill_hover_bg_color,const QString &text_hover_bg_color,const QString &pressed_bg_color)
{
    this->bg_color_ = bg_color.startsWith("#") ? bg_color : getColorOrDefault(bg_color,bg_colors,main_color_);
    this->fill_hover_bg_color_ = fill_hover_bg_color.startsWith("#") ? fill_hover_bg_color : getColorOrDefault(fill_hover_bg_color,fill_hover_bg_colors,main_fill_hover_color_);
    this->text_hover_bg_color_ = text_hover_bg_color.startsWith("#") ? text_hover_bg_color : getColorOrDefault(text_hover_bg_color,text_hover_bg_colors,main_text_hover_color_);
    this->pressed_bg_color_ = pressed_bg_color.startsWith("#") ? pressed_bg_color : getColorOrDefault(bg_color,pressed_bg_colors,main_pressed_color_);
    this->setSheet();
}

void MPushButton::setColor(const QString &color)
{
    if(color.startsWith('#'))
        return;
    this->bg_color_ = getColorOrDefault(color,bg_colors,main_color_);
    this->fill_hover_bg_color_ = getColorOrDefault(color,fill_hover_bg_colors,main_fill_hover_color_);
    this->text_hover_bg_color_ = getColorOrDefault(color,text_hover_bg_colors,main_text_hover_color_);
    this->pressed_bg_color_ = getColorOrDefault(color,pressed_bg_colors,main_pressed_color_);
    this->setSheet();
}

QString MPushButton::getColorOrDefault(const QString &color, const QMap<QString, QString> &colorMap, const QString &defaultColor) const
{
    if (colorMap.contains(color)) {
        return colorMap[color];
    } else {
        return defaultColor;
    }
}
