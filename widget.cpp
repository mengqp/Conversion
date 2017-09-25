#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    InitUi();
}

Widget::~Widget()
{
    if( NULL != m_pScale )
    {
        delete m_pScale;
        m_pScale = NULL;
    }

    if( NULL != m_pAsc )
    {
        delete m_pAsc;
        m_pAsc = NULL;
    }

    if( NULL != m_pFloatHex )
    {
        delete m_pFloatHex;
        m_pFloatHex = NULL;
    }


    if( NULL != m_pTab )
    {
        delete m_pTab;
        m_pTab = NULL;
    }

}

/*******************************************************************************
 * 类:Widget
 * 函数名:MsgBox
 * 功能描述: 打印消息，起警告作用
 * 参数: QString str
 * 返回值:void
 ******************************************************************************/
void Widget::MsgBox( QString str)
{
    QMessageBox msgBox;
    msgBox.setText(str);
    msgBox.exec();
}   /*-------- end class Widget method MsgBox -------- */


/*******************************************************************************
 * 类:Widget
 * 函数名:InitUi
 * 功能描述:初始化界面
 * 参数:void
 * 返回值:void
 ******************************************************************************/
void Widget::InitUi(void)
{
    this->setFixedSize(800,600);

    m_pTab = new QTabWidget(this);
    if ( NULL == m_pTab )
    {
        MsgBox( "tabwiget new error" );
    }
    m_pTab->setGeometry(0,0,800,600);

    // 创建浮点数与16进制转化的界面
    m_pFloatHex = new floathex( this );
    if ( NULL == m_pFloatHex )
    {
        MsgBox( "floathex new error" );
    }
    m_pFloatHex->setGeometry(0,0,350,200);
    m_pTab->addTab( m_pFloatHex, FROMLOCAL("浮点数16进制"));

    // 创建ASC码与数字转化的界面
    m_pAsc = new ASC(this);
    if ( NULL == m_pAsc )
    {
        MsgBox( "Asc new error" );
    }
    m_pAsc->setGeometry(0,0,350,200);
    m_pTab->addTab( m_pAsc, FROMLOCAL("ASCII"));

    // 创建进制之间转化的界面
    m_pScale = new Scale(this);
    if ( NULL == m_pScale )
    {
        MsgBox( "Scale new error ");
    }
    m_pScale->setGeometry(0, 0, 350, 200);
    m_pTab->addTab( m_pScale, FROMLOCAL("进制"));

}   /*-------- end class Widget method InitUi -------- */
