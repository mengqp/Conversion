#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTabWidget>
#include <QMessageBox>
#include <QString>

#include "public.h"
#include "floathex.h"
#include "asc.h"
#include "scale.h"

#define FROMLOCAL(a) QString::fromUtf8(a)

class Widget : public QWidget
{
    Q_OBJECT

  public:
    Widget(QWidget *parent = 0);
    ~Widget();

  private:
    // 主界面的tabWidget
    QTabWidget *m_pTab;
    // 点击显示浮点数与16进制转化的界面
    floathex *m_pFloatHex;
    // 点击显示ASCII码与数字之间转化的界面
    ASC *m_pAsc;
    // 点击显示进制之间转化的界面
    Scale *m_pScale;

  private:
    // 初始化界面
    void InitUi();
    // 消息盒子
    void MsgBox( QString str );
};

#endif // WIDGET_H
