/*******************************************************************************
 * 文件名:check.cpp
 * 文件描述:转化和计算一些校检
 * 作者:mengqp
 * 创建日期:2017/09/25 11:44:22
 * 公司：
 * 版本：Ver1.0
 *
 * 历史版本：
 * 修改人                修改时间                修改版本        修改内容
 *
 *
 ******************************************************************************/

#include <QRegExp>
#include <QRegExpValidator>
#include <QTextCursor>
#include <QStringList>
#include "check.h"
#include "widget.h"


const unsigned int RADIO_SEP_SPACE = 0x01;  // 空格分隔符
const unsigned int RADIO_SEP_NULL = 0x02;  // 无分隔符
const unsigned int RADIO_SEP_COMMA = 0x03;  // 逗号分隔符

const unsigned int RADIO_MODE_MSG = 0x01;  // 带报文显示
const unsigned int RADIO_MODE_ONLYCHECK = 0x02;  // 仅显示校验

const unsigned int RADIO_CHECK_MODBUSCRC = 0x01;  // Modbus crc
const unsigned int RADIO_CHECK_SUM = 0x02;  // 累加和
const unsigned int RADIO_CHECK_SUMNEGATE = 0x03;  // 累加和取反


/*******************************************************************************
 * 功能描述:构造函数
 ******************************************************************************/
CCheck::CCheck ( QWidget *parent )
        :QWidget( parent )
{
    m_widgetMain = (Widget *)parent;

    if ( !InitUi( ))
    {
        m_widgetMain->MsgBox( "CCheck::InitUi error!!\n" );
        return;
    }

    // if ( !InitData( ) )
    // {
    //     m_widgetMain->MsgBox( "CCheck::InitData error!!\n" );
    // }

}   /*-------- end 构造函数 -------- */

/*******************************************************************************
 * 功能描述:析构函数
 ******************************************************************************/
CCheck::~CCheck (void)
{
    DeleteUi( );
}   /*-------- end 析构函数 -------- */

/*******************************************************************************
 * 类:CCheck
 * 函数名:InitUi
 * 功能描述:初始化界面
 * 参数:void
 * 被调用:构造函数
 * 返回值:bool
 ******************************************************************************/
bool CCheck::InitUi(void)
{
    m_editBefore = NULL;
    if ( !InitUiSeparator( ) )
    {
        m_widgetMain->MsgBox( "CCheck::InitUiSeparator error!\n");
        return false;
    }

    if ( !InitUiMode( ) )
    {
        m_widgetMain->MsgBox( "CCheck::InitUiMode error!\n");
        return false;
    }

    if ( !InitUiCheck( ) )
    {
        m_widgetMain->MsgBox( "CCheck::InitUiCheck error!\n");
        return false;
    }

    if ( !InitUiDisplay( ) )
    {
        m_widgetMain->MsgBox( "CCheck::InitUiDisplay error!\n");
        return false;
    }

    return true;
}   /*-------- end class CCheck method InitUi -------- */

/*******************************************************************************
 * 类:CCheck
 * 函数名:DeleteUi
 * 功能描述:删除初始化界面
 * 参数:void
 * 被调用:析构
 * 返回值:void
 ******************************************************************************/
void CCheck::DeleteUi(void)
{
    DeleteUiDisplay( );
    DeleteUiCheck( );
    DeleteUiMode( );
    DeleteUiSeparator( );
}   /*-------- end class CCheck method DeleteUi -------- */

/*******************************************************************************
 * 类:CCheck
 * 函数名:InitUiSeparator
 * 功能描述:初始化分隔符界面
 * 参数:void
 * 被调用:InitUi
 * 返回值:bool
 ******************************************************************************/
bool CCheck::InitUiSeparator(void)
{
    // 文字
    m_labelSep = new QLabel(this);
    m_labelSep->setGeometry( 50, 20, 60, 20);
    m_labelSep->setText( FROMLOCAL("分隔符:"));

    // 选项
    m_radioSpace = new QRadioButton(this);
    m_radioSpace->setGeometry( 110, 20, 50, 20);
    m_radioSpace->setText( FROMLOCAL( "空格") );
    connect(m_radioSpace, SIGNAL(clicked()),
            this, SLOT(RadioChangeSlot()));
    m_radioSpace->click();

    m_radioNull = new QRadioButton(this);
    m_radioNull->setGeometry( 160, 20, 40, 20);
    m_radioNull->setText( FROMLOCAL( "无") );
    connect(m_radioNull, SIGNAL(clicked()),
            this, SLOT(RadioChangeSlot()));

    m_radioComma = new QRadioButton(this);
    m_radioComma->setGeometry( 200, 20, 50, 20);
    m_radioComma->setText( FROMLOCAL( "逗号") );
    connect(m_radioComma, SIGNAL(clicked()),
            this, SLOT(RadioChangeSlot()));

    // 组
    m_groupSep = new QButtonGroup( this );
    m_groupSep->addButton( m_radioSpace );
    m_groupSep->addButton( m_radioNull );
    m_groupSep->addButton( m_radioComma );

    return true;

}   /*-------- end class CCheck method InitUiSeparator -------- */

/*******************************************************************************
 * 类:CCheck
 * 函数名:DeleteUiSeparator
 * 功能描述:删除分隔符ui
 * 参数:void
 * 被调用:DeleteUi
 * 返回值:void
 ******************************************************************************/
void CCheck::DeleteUiSeparator(void)
{
    if( NULL !=  m_groupSep )
    {
        delete  m_groupSep;
        m_groupSep = NULL;
    }

    if( NULL != m_radioComma )
    {
        delete m_radioComma;
        m_radioComma = NULL;
    }

    if( NULL != m_radioNull )
    {
        delete m_radioNull;
        m_radioNull = NULL;
    }

    if( NULL != m_radioSpace )
    {
        delete m_radioSpace;
        m_radioSpace = NULL;
    }

    if( NULL != m_labelSep )
    {
        delete m_labelSep;
        m_labelSep = NULL;
    }
}   /*-------- end class CCheck method DeleteUiSeparator -------- */

/*******************************************************************************
 * 类:CCheck
 * 函数名:InitUiMode
 * 功能描述:初始化转化模式
 * 参数:void
 * 被调用:InitUi
 * 返回值:bool
 ******************************************************************************/
bool CCheck::InitUiMode(void)
{
    // 描述
    m_labelMode = new QLabel(this);
    m_labelMode->setGeometry( 40, 50, 80, 20);
    m_labelMode->setText( FROMLOCAL( "转化方式:"));

    // 选项
    m_radioMsg = new QRadioButton(this);
    m_radioMsg->setGeometry( 110, 50, 60, 20);
    m_radioMsg->setText( FROMLOCAL("报文"));
    connect(m_radioMsg, SIGNAL(clicked()),
            this, SLOT(RadioChangeSlot()));
    m_radioMsg->click();

    m_radioOnlyCheck = new QRadioButton(this);
    m_radioOnlyCheck->setGeometry( 170, 50, 60, 20);
    m_radioOnlyCheck->setText( FROMLOCAL("仅校验"));
    connect(m_radioOnlyCheck, SIGNAL(clicked()),
            this, SLOT(RadioChangeSlot()));

    // 组
    m_groupMode = new QButtonGroup( this );
    m_groupMode->addButton( m_radioMsg );
    m_groupMode->addButton( m_radioOnlyCheck );

    return true;
}   /*-------- end class CCheck method InitUiMode -------- */

/*******************************************************************************
 * 类:CCheck
 * 函数名:DeleteUiMode
 * 功能描述:删除转化模式ui
 * 参数:void
 * 被调用:DeleteUi
 * 返回值:void
 ******************************************************************************/
void CCheck::DeleteUiMode(void)
{
    if( NULL !=  m_groupMode )
    {
        delete  m_groupMode;
        m_groupMode = NULL;
    }

    if( NULL != m_radioOnlyCheck )
    {
        delete m_radioOnlyCheck;
        m_radioOnlyCheck = NULL;
    }

    if( NULL != m_radioMsg )
    {
        delete m_radioMsg;
        m_radioMsg = NULL;
    }

    if( NULL != m_labelMode )
    {
        delete m_labelMode;
        m_labelMode = NULL;
    }
}   /*-------- end class CCheck method DeleteUiMode -------- */

/*******************************************************************************
 * 类:CCheck
 * 函数名:InitUiCheck
 * 功能描述:初始化校验
 * 参数:void
 * 被调用:InitUi
 * 返回值:bool
 ******************************************************************************/
bool CCheck::InitUiCheck(void)
{
    // 文字
    m_lableCheck = new QLabel(this);
    m_lableCheck->setGeometry( 40, 80, 60, 20);
    m_lableCheck->setText( FROMLOCAL("校检方式:"));

    // 选项
    m_radioModbusCrc = new QRadioButton(this);
    m_radioModbusCrc->setGeometry( 110, 80, 90, 20);
    m_radioModbusCrc->setText( FROMLOCAL( "ModbusCRC"));
    connect(m_radioModbusCrc, SIGNAL(clicked()),
            this, SLOT(RadioChangeSlot()));
    m_radioModbusCrc->click();

    m_radioSum = new QRadioButton(this);
    m_radioSum->setGeometry( 200, 80, 60, 20);
    m_radioSum->setText( FROMLOCAL( "累加和"));
    connect(m_radioSum, SIGNAL(clicked()),
            this, SLOT(RadioChangeSlot()));

    m_radioSumNegate = new QRadioButton(this);
    m_radioSumNegate->setGeometry( 260, 80, 100, 20);
    m_radioSumNegate->setText( FROMLOCAL( "累加和取反"));
    connect(m_radioSumNegate, SIGNAL(clicked()),
            this, SLOT(RadioChangeSlot()));

    // 组
    m_groupCheck = new QButtonGroup(this);
    m_groupCheck->addButton( m_radioModbusCrc );
    m_groupCheck->addButton( m_radioSum );
    m_groupCheck->addButton( m_radioSumNegate );

    return true;
}   /*-------- end class CCheck method InitUiCheck -------- */

/*******************************************************************************
 * 类:CCheck
 * 函数名:DeleteUiCheck
 * 功能描述:删除校验方式ui
 * 参数:void
 * 被调用:DeleteUi
 * 返回值:void
 ******************************************************************************/
void CCheck::DeleteUiCheck(void)
{
    if( NULL != m_groupCheck )
    {
        delete m_groupCheck;
        m_groupCheck = NULL;
    }

    if( NULL != m_radioSumNegate )
    {
        delete m_radioSumNegate;
        m_radioSumNegate = NULL;
    }
    if( NULL != m_radioSum )
    {
        delete m_radioSum;
        m_radioSum = NULL;
    }
    if( NULL != m_radioModbusCrc )
    {
        delete m_radioModbusCrc;
        m_radioModbusCrc = NULL;
    }

    if( NULL != m_lableCheck )
    {
        delete m_lableCheck;
        m_lableCheck = NULL;
    }
}   /*-------- end class CCheck method DeleteUiCheck -------- */

/*******************************************************************************
 * 类:CCheck
 * 函数名:InitUiDisplay
 * 功能描述:初始化校验窗口
 * 参数:void
 * 被调用:InitUi
 * 返回值:bool
 ******************************************************************************/
bool CCheck::InitUiDisplay(void)
{
    // 转化按钮
    m_buttonConvert = new QPushButton(this);
    m_buttonConvert->setGeometry(385, 370, 30, 20 );
    m_buttonConvert->setText( FROMLOCAL("转化"));
    connect( m_buttonConvert, SIGNAL(clicked()),
             this,SLOT( ConvertionSlot()));

    // 校验前
    m_editBefore = new QTextEdit(this);
    m_editBefore->setGeometry( 20, 140, 360, 400);
    m_editBefore->setReadOnly( false );
    connect( m_editBefore, SIGNAL(textChanged() ),
             this,SLOT( ConvertionSlot()));

    // 校验后
    m_editAfter = new QTextEdit(this);
    m_editAfter->setGeometry( 420, 140, 360, 400);
    m_editAfter->setReadOnly( true );

    return true;
}   /*-------- end class CCheck method InitUiDisplay -------- */

/*******************************************************************************
 * 类:CCheck
 * 函数名:DeleteUiDisplay
 * 功能描述:删除窗口
 * 参数:void
 * 被调用:DeleteUi
 * 返回值:void
 ******************************************************************************/
void CCheck::DeleteUiDisplay(void)
{
    if( NULL != m_buttonConvert )
    {
        delete m_buttonConvert;
        m_buttonConvert = NULL;
    }

    if( NULL != m_editBefore )
    {
        delete m_editBefore;
        m_editBefore = NULL;
    }

    if( NULL != m_editAfter )
    {
        delete m_editAfter;
        m_editAfter = NULL;
    }
}   /*-------- end class CCheck method DeleteUiDisplay -------- */

/*******************************************************************************
 * 类:CCheck
 * 函数名:RadioChangeSlot
 * 功能描述:点击radio选项变化时，此函数启作用
 * 参数:void
 * 被调用:信号 radio->click
 * 返回值:void
 ******************************************************************************/
void CCheck::RadioChangeSlot(void)
{
    if ( NULL != m_editBefore )
    {
        m_editBefore->clear();
    }

    // 分隔符
    if ( sender() == m_radioSpace )
    {
        m_sep = RADIO_SEP_SPACE;
    }
    else if ( sender() == m_radioNull )
    {
        m_sep = RADIO_SEP_NULL;
    }
    else if ( sender() == m_radioComma )
    {
        m_sep = RADIO_SEP_COMMA;
    }

    // 转化方式
    if ( sender() == m_radioMsg )
    {
        m_mode = RADIO_MODE_MSG;
    }
    else if ( sender() == m_radioOnlyCheck )
    {
        m_mode = RADIO_MODE_ONLYCHECK;
    }

    // 校验方式
    if ( sender() == m_radioModbusCrc )
    {
        m_check = RADIO_CHECK_MODBUSCRC;
    }
    else if ( sender() == m_radioSum )
    {
        m_check = RADIO_CHECK_SUM;
    }
    else if ( sender() == m_radioSumNegate )
    {
        m_check = RADIO_CHECK_SUMNEGATE;
    }
}   /*-------- end class CCheck method RadioChangeSlot -------- */

/*******************************************************************************
 * 类:CCheck
 * 函数名:ConvertionSlot
 * 功能描述:转化功能
 * 参数:void
 * 被调用:
 * 返回值:void
 ******************************************************************************/
void CCheck::ConvertionSlot(void)
{
    // 清空
    m_editAfter->clear( );
    // 获取
    QString str = GetCheckString( );
    // 显示
    m_editAfter->setText( str );
}   /*-------- end class CCheck method ConvertionSlot -------- */

/*******************************************************************************
 * 类:CCheck
 * 函数名:GetCheckString
 * 功能描述:获取校验后的字符串
 * 参数:void
 * 被调用:ConvertionSlot
 * 返回值:QString
 ******************************************************************************/
QString CCheck::GetCheckString(void)
{
    QString str;
    str = GetModeString();

    // QString strInput = m_editBefore->toPlainText();
    str += GetConvertString();

    return str;
}   /*-------- end class CCheck method GetCheckString -------- */

/*******************************************************************************
 * 类:CCheck
 * 函数名:GetSepString
 * 功能描述:获取间隔串
 * 参数:void
 * 被调用:GetCheckString()
 * 返回值:QString
 ******************************************************************************/
QString CCheck::GetSepString(void)
{
    QString str;

    QRegExp rx;
    switch ( m_sep )
    {
        case RADIO_SEP_SPACE: // 空格
            {
                str = " ";
                rx.setPattern("^([0-9a-fA-f]{1,2}\\x20)*[0-9a-fA-f]?");
            }
            break;

        case RADIO_SEP_NULL: // 无
            {
                str = "";
                rx.setPattern("^([0-9a-fA-f])*$");
            }
            break;

        case RADIO_SEP_COMMA: // 逗号
            {
                str = ",";
                rx.setPattern("^([0-9a-fA-f]{1,2}\\,)*[0-9a-fA-f]?$");
            }
            break;

        default:
            str.clear();
            break;
    }
    QRegExpValidator v(rx,0);
    int pos = 0;

    QString s = m_editBefore->toPlainText();
    int iRtn = v.validate( s, pos );
    if (0 == iRtn )
    {
        m_widgetMain->MsgBox( FROMLOCAL("您输入的内容不符合规则"));
        // //获取当前文本光标
        // QTextCursor cursor = m_editBefore->textCursor();
        // //将光标移动到文本结尾，便于删除字符测试，实际上并不需要该步骤
        // cursor.movePosition(QTextCursor::End);
        // //判断当前是否选中了文本，如果选中了文本则取消选中的文本，再删除前一个字符
        // if(cursor.hasSelection())
        //     cursor.clearSelection();
        // //删除前一个字符
        // cursor.deletePreviousChar();
        // //设置当前的光标为更改后的光标
        // m_editBefore->setTextCursor(cursor);
    }

    return str;
}   /*-------- end class CCheck method GetSepString -------- */

/*******************************************************************************
 * 类:CCheck
 * 函数名:GetModeString
 * 功能描述:获取前缀报文
 * 参数:void
 * 被调用:GetCheckString
 * 返回值:QString
 ******************************************************************************/
QString CCheck::GetModeString(void)
{
    QString str;
    switch ( m_mode )
    {
        case RADIO_MODE_MSG: // 带报文
            {
                str = m_editBefore->toPlainText();
            }
            break;
        case RADIO_MODE_ONLYCHECK: // 只显示校验
            {
                str = "";
            }
            break;
        default:
            str.clear();
            break;
    }

    return str;
}   /*-------- end class CCheck method GetModeString -------- */

/*******************************************************************************
 * 类:CCheck
 * 函数名:GetConvertString
 * 功能描述:获取转化后的报文
 * 参数:void
 * 被调用:GetCheckString
 * 返回值:QString
 ******************************************************************************/
QString CCheck::GetConvertString(void)
{
    QString str;
    QString strSep = GetSepString( );
    str = m_editBefore->toPlainText();
    if ( str.isEmpty() )
    {
        return str;
    }

    unsigned char *pBuf = new unsigned char[ str.count() + 20 ];
    unsigned int iBufLen = 0;
    // unsigned char buf[2048] = "";
    if ( "" != strSep)
    {
        QStringList list = str.split( QRegExp(strSep) );
        for (int i=0; i < list.count(); i++)
        {
            bool ok;
            QString s = list.at(i );
            unsigned char tmp = s.toInt(&ok,16);
            if ( ok )
            {
                pBuf[iBufLen++] = tmp;
                // printf("%2x \n", pBuf[i]);
            }
        }
    }
    else
    {
        int len = str.count();
        if ( 1 == len % 2)
        {
            len = len + 1;
        }
        int max = len / 2;

        for ( int i=0; i < max; i++)
        {
            bool ok;
            int mid = 2 * i;
            QString s = "";
            if ( ( i == max - 1 ) & ( 1 == len % 2 ))
            {
                s = str.mid( mid, 1);
            }
            else
            {
                s = str.mid( mid, 2);
            }

            unsigned char tmp = s.toInt(&ok,16);
            if ( ok )
            {
                pBuf[iBufLen++] = tmp;
                // printf("%2x \n", pBuf[i]);
            }
        }

    }

    str = GetConvertCheckString( pBuf, iBufLen );
    if( NULL != pBuf )
    {
        delete pBuf;
        pBuf = NULL;
    }

    return str;
}   /*-------- end class CCheck method GetConvertString -------- */

/*******************************************************************************
 * 类:CCheck
 * 函数名:GetConvertCheckString
 * 功能描述:获取校验后的str
 * 参数:unsigned char *pBuf 16进制字符串
 * 参数:unsigned int iBufLen  长度
 * 被调用:GetConverString
 * 返回值:QString
 ******************************************************************************/
QString CCheck::GetConvertCheckString(unsigned char *pBuf, unsigned int iBufLen )
{
    switch ( m_check)
    {
        case RADIO_CHECK_MODBUSCRC: // modbus crc
            {
                return GetModbusCrcString( pBuf, iBufLen );
            }
            break;

        case RADIO_CHECK_SUM: // modbus crc
            {
                return GetSumString( pBuf, iBufLen );
            }
            break;

        case RADIO_CHECK_SUMNEGATE: // modbus crc
            {
                return GetSumNeGateString( pBuf, iBufLen );
            }
            break;
        default:
            break;
    }

    return "";
}   /*-------- end class CCheck method GetConvertCheckString -------- */

/*******************************************************************************
 * 类:CCheck
 * 函数名:GetModbusCrcString
 * 功能描述:modbus crc
 * 参数:unsigned char *pBuf
 * 参数:unsigned int iBufLen
 * 被调用:
 * 返回值:QString
 ******************************************************************************/
QString CCheck::GetModbusCrcString(unsigned char *pBuf, unsigned int iBufLen )
{
    unsigned short Genpoly=0xA001;
    unsigned short CRC=0xFFFF;
    unsigned short index;
    while(iBufLen--)
    {
        CRC=CRC^(unsigned short)*pBuf++;
        for(index=0;index<8;index++)
        {
            if((CRC & 0x0001)==1)
                CRC=(CRC>>1)^Genpoly;
            else
                CRC=CRC>>1;
        }
    }

    QString sep = GetSepString( );
    QString str = sep
                  + QString("%1").arg( ( CRC ) & 0xff, 2, 16, QChar('0'))
                  +sep
                  + QString("%1").arg( ( CRC >> 8 ) & 0xff, 2, 16, QChar('0'))
                  ;

    return str;
}   /*-------- end class CCheck method GetModbusCrcString -------- */

/*******************************************************************************
 * 类:CCheck
 * 函数名:GetSumString
 * 功能描述:校验和
 * 参数:unsigned char *pBuf
 * 参数:unsigned int iBufLen
 * 被调用:
 * 返回值:QString
 ******************************************************************************/
QString CCheck::GetSumString(unsigned char *pBuf, unsigned int iBufLen)
{
    QString str = "";
	unsigned char byRtn = 0x00;
    unsigned int i;

    if( pBuf == NULL || iBufLen <= 0 )
		return str;

	for ( i=0; i<iBufLen ; i++ )
	{
		byRtn += pBuf[i];
	}

    QString sep = GetSepString( );
    str = sep + QString("%1").arg( byRtn, 2, 16, QChar('0'));
    return str;
}   /*-------- end class CCheck method GetSumString -------- */

/*******************************************************************************
 * 类:CCheck
 * 函数名:GetSumNegateString
 * 功能描述:校验和
 * 参数:unsigned char *pBuf
 * 参数:unsigned int iBufLen
 * 被调用:
 * 返回值:QString
 ******************************************************************************/
QString CCheck::GetSumNeGateString(unsigned char *pBuf, unsigned int iBufLen)
{
    QString str = "";
	unsigned char byRtn = 0x00;
    unsigned int i;

    if( pBuf == NULL || iBufLen <= 0 )
		return str;

	for ( i=0; i<iBufLen ; i++ )
	{
		byRtn += pBuf[i];
	}

    QString sep = GetSepString( );
    unsigned char byRtnNegate = ~byRtn;
    str = sep + QString("%1").arg( byRtnNegate, 2, 16, QChar('0'));

    return str;
}   /*-------- end class CCheck method GetSumNeGateString -------- */
