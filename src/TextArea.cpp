#include "TextArea.h"

TextArea::TextArea(int x, int y, int max_width, QString text, QGraphicsItem* parent) : QGraphicsProxyWidget(parent){

    QWidget* widget = new QWidget;
    widget->setAttribute(Qt::WA_TranslucentBackground, true);

    setWidget(widget);
    setMaximumWidth(max_width + 5);
    setMaximumHeight(200);
    widget->setFixedHeight(200);
    setPos(x, y);

    QHBoxLayout* layout = new QHBoxLayout();
    widget->setLayout(layout);
    layout->setAlignment(Qt::AlignCenter);

    int id = QFontDatabase::addApplicationFont("../fonts/RobotoSlab-VariableFont_wght.ttf");
    QString family = QFontDatabase::applicationFontFamilies(id).at(0);
    QFont roboto(family);

    QString line_break_text = "";
    while(text.indexOf("<br>") != -1){
        line_break_text += text.left(text.indexOf("<br>"));
        text = text.right(text.length() - text.indexOf("<br>") - 4);
        line_break_text += "\n";
    }
    line_break_text += text;

    QLabel* label = new QLabel;
    label->setText(line_break_text);
    label->setWordWrap(true);
    label->setStyleSheet("font-size: 6px;"
                         "background-color: rgba(255, 255, 255, 0.3);"
                         "border: 1px solid black;"
                         "border-radius: 5px;");
    label->setFont(roboto);
    label->setAlignment(Qt::AlignCenter);
    label->setMargin(3);
    label->setFixedWidth(max_width);
    layout->setSizeConstraint(QLayout::SetMinimumSize);

    layout->addWidget(label);
}

TextArea::~TextArea(){
    qDebug() << this;
}