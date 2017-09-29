/*******************************************************************************
 * 文件名:check.h
 * 文件描述:见cpp
 * 作者:mengqp
 * 创建日期:2017/09/25 11:45:53
 * 公司：
 * 版本：Ver1.0
 *
 * 历史版本：
 * 修改人                修改时间                修改版本        修改内容
 *
 *
 ******************************************************************************/

#ifndef CHECK_H
#define CHECK_H

#include <QWidget>
#include <QLabel>
#include <QRadioButton>
#include <QButtonGroup>
#include <QPushButton>
#include <QTextEdit>

class Widget;

/*******************************************************************************
 *功能描述:
 *******************************************************************************/
class CCheck : public QWidget
{
    Q_OBJECT

  public:
    /* constructor */
    explicit CCheck( QWidget *parent = 0);
    /* distructor */
    virtual ~CCheck(void);

  private:
    // 初始化界面
    bool InitUi( void );
    // 删除界面初始化
    void DeleteUi( void );
    // 初始化数据
    bool InitData( void );
    // 删除数据
    void DeleteData( void );

  private:
    // 初始化分隔符 是逗号，空格，还是无
    bool InitUiSeparator( void );
    // 删除分隔符
    void DeleteUiSeparator( void );
    // 初始化转化模式 是公校验还是增加原报文
    bool InitUiMode( void );
    // 删除报文模式
    void DeleteUiMode( void );
    // 初始化校验类型 是CRC 0x68其它?
    bool InitUiCheck( void );
    // 删除校验类型
    void DeleteUiCheck( void );
    // 初始校验框
    bool InitUiDisplay( void );
    // 删除校验框
    void DeleteUiDisplay( void );

  private:
    Widget *m_widgetMain;

  private slots:
    // 槽 转化选项变化
    void RadioChangeSlot( );
    // 槽 转化
    void ConvertionSlot();

  private:  // 转化功能函数
    // 获取校验方式处理报文
    QString GetCheckString( void );
    // 获取分隔符
    QString GetSepString( void );
    // 获取模式报文
    QString GetModeString( void );
    // 转化功能函数
    QString GetConvertString( void );

  private:
    // 获取校验后的str
    QString GetConvertCheckString( unsigned char *pBuf, unsigned int iBufLen );
    // 获取校验后的modbus str
    QString GetModbusCrcString( unsigned char *pBuf, unsigned int iBufLen );
    // 获取校验后的累加和 str
    QString GetSumString( unsigned char *pBuf, unsigned int iBufLen );
    // 获取校验后的累加和取反 str
    QString GetSumNeGateString( unsigned char *pBuf, unsigned int iBufLen );

  private:  // ui
    // 分隔符
    QLabel *m_labelSep;  // 分隔符文字
    // 分隔符选项
    QRadioButton *m_radioSpace;  // 空格 ' '
    QRadioButton *m_radioNull;  // 无 ''
    QRadioButton *m_radioComma;  // ， ','
    // 分隔符组
    QButtonGroup *m_groupSep;  //

    // 转化方式
    QLabel *m_labelMode;  // 转化方式文字
    // 转化选项
    QRadioButton *m_radioMsg;  // 原报文:在转化区带着原来的报文
    QRadioButton *m_radioOnlyCheck;  // 仅校验:仅显示校验位
    // 组
    QButtonGroup *m_groupMode;

    // 校验方式
    QLabel *m_lableCheck;  // 文字
    // 选项
    QRadioButton *m_radioModbusCrc;  // Modbus CRC
    QRadioButton *m_radioSum;        // 校验和
    QRadioButton *m_radioSumNegate;        // 校验和取反
    // 组
    QButtonGroup *m_groupCheck;

    // 显示区
    QPushButton *m_buttonConvert;  // 转化按钮
    QTextEdit *m_editBefore;  // 校验前输入框
    QTextEdit *m_editAfter;  // 校验后显示框

  private:  // data
    unsigned int m_sep;  // 分隔符
    unsigned int m_mode; // 显示模式
    unsigned int m_check;  // 校验方式



};


#endif /* CHECK_H */

// This file is set to c + + mode when you set the following content to the bottom and reopen the file
// Local Variables:
// mode: c++
// End:
