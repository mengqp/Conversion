#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTabWidget>
#include <QMessageBox>
#include <QString>

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
    QTabWidget *m_pTab;

    floathex *m_pFloatHex;

    ASC *m_pAsc;

    Scale *m_pScale;

  private:
    // 初始化界面
    void InitUi();
    // 消息盒子
    void MsgBox( QString str );
};

#endif // WIDGET_H
