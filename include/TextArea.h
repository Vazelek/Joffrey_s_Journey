#ifndef TEXTAREA_H
#define TEXTAREA_H

#include <QWidget>
#include <QLabel>
#include <QGraphicsProxyWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QImage>
#include <QDebug>
#include <QAbstractScrollArea>
#include <QFontDatabase>
#include <QVector>

class TextArea : public QGraphicsProxyWidget{
    Q_OBJECT

private:

public:
    TextArea(int x, int y, int max_width, QString text, QGraphicsItem* parent = nullptr);
    ~TextArea();
};

#endif