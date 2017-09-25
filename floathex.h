#ifndef FLOATHEX_H
#define FLOATHEX_H

#include <QWidget>
#include <QLineEdit>
#include <QString>
#include <QPushButton>
#include <QRadioButton>
#include <QButtonGroup>
#include <QRegExpValidator>
#include <QLabel>

class floathex : public QWidget
{
    Q_OBJECT

  public:
    floathex(QWidget *parent = 0);
    ~floathex();

  private:
    // 初始化该界面
    bool InitUi(void);
    // 初始化该界面功能
    void InitUiFeature();
    // 初始化该界面参数
    void InitUiParam();

    /* 模式的设置，是为了在相应的状态下，防止用户输入不合理的数据 */
    // 设置浮点数模式
    void SetFloatMode( void );
    // 设置16进制模式
    void SetHexMode( void );


  private slots:
    // 槽 转化功能的函数
    void FuncConvertion();
    // 槽 改变进制时变化
    void radioChange();

  public:
    // 转化的功能函数
    bool Convertion(char *szLineBuf, int szDataType);

  public:
    float m_fVal;  // 存储浮点数值的全局变量
    char m_szHexBuf[256];  // 存储16进制字符串的全局变量

  private:
    QButtonGroup *m_HexSelButtonGroup;  // 选择16进制组

    QRadioButton *m_dataFloatButton;  // 选择浮点数为输入

    QRadioButton *m_dataHexButton;    // 选择16进制输入
    QRadioButton *m_dataHexAButton;   // 选择16进制正序输入
    QRadioButton *m_dataHexBButton;   // 选择16进制正序倒序输入


    QLabel *m_dataFloatLabel;  // 显示浮点值框
    QLabel *m_dataHexLabel;    // 16进制框

    QLineEdit  *m_dataWriteEdit;  // 允许用户输入的框
    QLineEdit  *m_dataFloatEdit;  // 显示浮点数的文本
    QLineEdit  *m_dataHexEdit;    // 显示16进制数的文本

    QRegExpValidator *m_pRegExp;  //  正则全局变量，用来限定相应输入模式下的正则规则

    QPushButton *m_converButton;  // 转化按钮
    // QPushButton *m_clearWriteButton;



    int m_iRadioId;

  private:
    QWidget * m_mainWidget;
};

#endif // FLOATHEX_H

// This file is set to c + + mode when you set the following content to the bottom and reopen the file
// Local Variables:
// mode: c++
// End:
