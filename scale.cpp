#include "scale.h"
#include "widget.h"
#include <stdlib.h>

Scale::Scale(QWidget *parent) : QWidget(parent)
{
    m_mainWidget = parent;
    InitUi();
    InitUiFeature();
    InitUiParam();
}

Scale::~Scale()
{
    if( NULL != m_pRegExp )
    {
        delete m_pRegExp;
        m_pRegExp = NULL;
    }

    if( NULL != m_convertFromBox )
    {
        delete m_convertFromBox;
        m_convertFromBox = NULL;
    }
    if( NULL != m_convertToBox )
    {
        delete m_convertToBox;
        m_convertToBox = NULL;
    }
    if( NULL != m_dataFromLabel  )
    {
        delete m_dataFromLabel ;
        m_dataFromLabel  = NULL;
    }
    delete m_dataOtherLabel;
    delete m_dataBinaryLabel;
    if( NULL != m_dataOctalLabel )
    {
        delete m_dataOctalLabel;
        m_dataOctalLabel = NULL;
    }
    if( NULL != m_dataDecimalLabel )
    {
        delete m_dataDecimalLabel;
        m_dataDecimalLabel = NULL;
    }
    if( NULL != m_dataHexLabel )
    {
        delete m_dataHexLabel;
        m_dataHexLabel = NULL;
    }
    delete m_dataOtherButton;

    delete m_dataDecimalButton;
    if( NULL != m_dataHexButton )
    {
        delete m_dataHexButton;
        m_dataHexButton = NULL;
    }

    delete  m_dataWriteEdit;
    delete  m_dataOtherEdit;
    delete  m_dataBinaryEdit;
    if( NULL != m_dataOctalEdit )
    {
        delete m_dataOctalEdit;
        m_dataOctalEdit = NULL;
    }
    if( NULL != m_dataDecimalEdit )
    {
        delete m_dataDecimalEdit;
        m_dataDecimalEdit = NULL;
    }
    if( NULL != m_dataHexEdit )
    {
        delete m_dataHexEdit;
        m_dataHexEdit = NULL;
    }


    delete m_converButton;




    //delete m_clearWriteButton;
}


bool Scale::InitUi()
{
    //创建控件 Label
    m_dataBinaryLabel = new QLabel(this);
    m_dataBinaryLabel->setGeometry(50,100,150,20);
    m_dataBinaryLabel->setText(FROMLOCAL("二进制"));

    m_dataOctalLabel = new QLabel(this);
    m_dataOctalLabel->setGeometry(50,150,150,20);
    m_dataOctalLabel->setText(FROMLOCAL("八进制"));

    m_dataDecimalLabel = new QLabel(this);
    m_dataDecimalLabel->setGeometry(50,200,150,20);
    m_dataDecimalLabel->setText(FROMLOCAL("十进制"));

    m_dataHexLabel = new QLabel(this);
    m_dataHexLabel->setGeometry(50,250,250,20);
    m_dataHexLabel->setText(FROMLOCAL("十六进制"));

    m_dataOtherLabel = new QLabel(this);
    m_dataOtherLabel->setGeometry(70,300,200,20);
    m_dataOtherLabel->setText(FROMLOCAL("进制"));
    m_dataOtherLabel->show();

    m_dataFromLabel = new QLabel(this);
    m_dataFromLabel->setGeometry( 540, 20, 50, 20);
    m_dataFromLabel->setText( FROMLOCAL("进制"));
    m_dataFromLabel->show();

    m_dataBinaryButton = new QRadioButton(this);
    m_dataBinaryButton->setGeometry(50,20,100,20);
    m_dataBinaryButton->setText(FROMLOCAL("二进制"));
    m_dataBinaryButton->click();

    m_dataOctalButton = new QRadioButton(this);
    m_dataOctalButton->setGeometry(150,20,100,20);
    m_dataOctalButton->setText(FROMLOCAL("八进制"));

    m_dataDecimalButton = new QRadioButton(this);
    m_dataDecimalButton->setGeometry(250,20,100,20);
    m_dataDecimalButton->setText(FROMLOCAL("十进制"));

    m_dataHexButton = new QRadioButton(this);
    m_dataHexButton->setGeometry(350,20,100,20);
    m_dataHexButton->setText(FROMLOCAL("十六进制"));

    m_dataOtherButton = new QRadioButton(this);
    m_dataOtherButton->setGeometry(450,20,100,20);
    m_dataOtherButton->setText(FROMLOCAL("其它"));




    //创建控件 QlineEdit
    m_dataWriteEdit = new QLineEdit(this);
    m_dataWriteEdit->setGeometry(100,50,150,20);

    m_dataBinaryEdit = new QLineEdit(this);
    m_dataBinaryEdit->setGeometry(100,100,150,20);

    m_dataOctalEdit = new QLineEdit(this);
    m_dataOctalEdit->setGeometry(100,150,150,20);

    m_dataDecimalEdit = new QLineEdit(this);
    m_dataDecimalEdit->setGeometry(100,200,150,20);

    m_dataHexEdit = new QLineEdit(this);
    m_dataHexEdit->setGeometry(100,250,150,20);

    m_dataOtherEdit = new QLineEdit(this);
    m_dataOtherEdit->setGeometry(100,300,150,20);

    // combobox
    m_convertFromBox=new QComboBox(this);
    m_convertFromBox->setGeometry(500, 20, 40, 20);
    for ( int i=2; i <= 32; i++)
    {
        m_convertFromBox->addItem( QString::number( i, 10) );
    }

    m_convertToBox = new QComboBox(this);
    m_convertToBox->setGeometry(30, 300, 40, 20 );
    for ( int i=2; i <= 32; i++)
    {
        m_convertToBox->addItem( QString::number( i, 10) );
    }

    //创建控件 QPushButton
    m_converButton = new QPushButton(this);
    m_converButton->setGeometry(270,50,50,20);
    m_converButton->setText(FROMLOCAL("转换"));

  //  m_clearWriteButton = new QPushButton(this);
   // m_clearWriteButton->setGeometry(250,50,50,20);
  //  m_clearWriteButton->setText(FROMLOCAL("清空"));

    return true;
}

void Scale::InitUiFeature()
{
    //设置windows
    this->setWindowTitle(FROMLOCAL("转化工具"));
   // this->resize(500,300);
    this->setFixedSize(800,600);

    connect(m_dataWriteEdit, SIGNAL(textChanged(QString)), this, SLOT(FuncConvertion()) );
    //设置 QRadioButton
    connect(m_dataOtherButton,SIGNAL(clicked(bool)),
            this,SLOT(radioChange()));
    connect(m_dataDecimalButton,SIGNAL(clicked(bool)),
            this,SLOT(radioChange()));
    connect(m_dataHexButton,SIGNAL(clicked(bool)),
            this,SLOT(radioChange()));
    connect(m_dataBinaryButton,SIGNAL(clicked(bool)),
            this,SLOT(radioChange()));
    connect(m_dataOctalButton,SIGNAL(clicked(bool)),
            this,SLOT(radioChange()));

    //设置 QlineEdit
    m_dataOtherEdit->setReadOnly(true);
    m_dataBinaryEdit->setReadOnly(true);
    m_dataDecimalEdit->setReadOnly(true);
    m_dataOctalEdit->setReadOnly(true);
    m_dataHexEdit->setReadOnly(true);

    //设置 QPushButton
    connect(m_converButton,SIGNAL(released()),
            this,SLOT(FuncConvertion()));

}

void Scale::InitUiParam()
{
    m_iRadioId = 0;
    m_pRegExp = new QRegExpValidator(this);
    SetBinaryMode();
}


void Scale::FuncConvertion()
{
    QString  str = m_dataWriteEdit->text();
    if( str.isEmpty())
    {
        m_dataOtherEdit->clear();
        m_dataBinaryEdit->clear();
        m_dataOctalEdit->clear();
        m_dataDecimalEdit->clear();
        m_dataHexEdit->clear();
        return;
    }

    char* ch;
    QByteArray ba = str.toLatin1();
    ch=ba.data();

    Convertion(ch, m_iRadioId);



    m_dataOtherEdit->setText((m_Other));
    m_dataHexEdit->setText((m_hex));
    m_dataBinaryEdit->setText((m_Binary));
    m_dataOctalEdit->setText((m_Octal));
    m_dataDecimalEdit->setText((m_Decimal));
}

void Scale::radioChange()
{
    m_dataWriteEdit->clear();
    if(sender() == m_dataBinaryButton)
    {
        m_iRadioId = 0;
        SetBinaryMode();
    }
    else if(sender() == m_dataOctalButton)
    {
        m_iRadioId = 1;
        SetOctalMode();
    }
    else if(sender() == m_dataDecimalButton)
    {
        m_iRadioId = 2;
        SetDecimalMode();
    }
    else if(sender() == m_dataHexButton)
    {
        m_iRadioId = 3;
        SetHexMode();
    }
    if(sender() == m_dataOtherButton)
    {
        m_iRadioId = 4;
        SetOtherMode();
    }


}


bool Scale::Convertion(char *szLineBuf, int szDataType)
{
    char *e;
    int buf_len = strlen( szLineBuf);
    if ( buf_len > 1024 )
    {
        buf_len = 1024;
    }

    switch(szDataType)
    {
        case 0://字符
            {

                int num = 0;
                num=strtol(szLineBuf,&e,2);
                char buf[9] = "";
                m_Decimal = QString::number( num );
                public_itoa(num,buf,16);
                m_hex = QString( buf );
                public_itoa(num,buf,8);
                m_Octal = QString( buf );
                public_itoa(num,buf,2);
                m_Binary = QString( buf );
                bool ok;
                public_itoa(num,buf, m_convertToBox->currentText().toInt( &ok, 10));
                m_Other = QString( buf );
            }
            break;
        case 1://八进制
            {
                int num = 0;
                num=strtol(szLineBuf,&e,8);
                char buf[9] = "";
                buf[0] = num;
                m_Other = QString( buf );
                m_Decimal = QString::number( num );
                public_itoa(num,buf,16);
                m_hex = QString( buf );
                public_itoa(num,buf,8);
                m_Octal = QString( buf );
                public_itoa(num,buf,2);
                m_Binary = QString( buf );
                bool ok;
                public_itoa(num,buf, m_convertToBox->currentText().toInt( &ok, 10));
                m_Other = QString( buf );
            }
            break;
        case 2://10进制
            {
                int num = atoi( szLineBuf );
                char buf[9] = "";
                buf[0] = num;
                m_Other = QString( buf );
                m_Decimal = QString::number( num );
                public_itoa(num,buf,16);
                m_hex = QString( buf );
                public_itoa(num,buf,8);
                m_Octal = QString( buf );
                public_itoa(num,buf,2);
                m_Binary = QString( buf );
                bool ok;
                public_itoa(num,buf, m_convertToBox->currentText().toInt( &ok, 10));
                m_Other = QString( buf );

            }
            break;
        case 3://16进制 <-
            {
                int num = 0;
                num=strtol(szLineBuf,&e,16);
                char buf[9] = "";
                buf[0] = num;
                m_Other = QString( buf );
                m_Decimal = QString::number( num );
                public_itoa(num,buf,16);
                m_hex = QString( buf );
                public_itoa(num,buf,8);
                m_Octal = QString( buf );
                public_itoa(num,buf,2);
                m_Binary = QString( buf );
                bool ok;
                public_itoa(num,buf, m_convertToBox->currentText().toInt( &ok, 10));
                m_Other = QString( buf );
            }
            break;
        case 4://其它进制 <-
            {
                int num = 0;
                bool ok;
                num=strtol(szLineBuf,&e,m_convertFromBox->currentText().toInt( &ok, 10) );
                char buf[9] = "";
                buf[0] = num;
                m_Other = QString( buf );
                m_Decimal = QString::number( num );
                public_itoa(num,buf,16);
                m_hex = QString( buf );
                public_itoa(num,buf,8);
                m_Octal = QString( buf );
                public_itoa(num,buf,2);
                m_Binary = QString( buf );
                public_itoa(num,buf, m_convertToBox->currentText().toInt( &ok, 10));
                m_Other = QString( buf );
            }
            break;
        default:

            break;
    }

    return true;
}

void Scale::SetDecimalMode()
{
    QRegExp rx("^[0-9]+$");
    m_pRegExp->setRegExp(rx);
    m_dataWriteEdit->setValidator(m_pRegExp);

}

void Scale::SetHexMode()
{
    QRegExp rx("^([0-9a-fA-F])+$");
    m_pRegExp->setRegExp(rx);
    m_dataWriteEdit->setValidator(m_pRegExp);
}

/*******************************************************************************
 * 类:Scale
 * 函数名:SetBinaryMode
 * 功能描述:设置二进制模式
 * 参数:void
 * 返回值:void
 ******************************************************************************/
void Scale::SetBinaryMode(void)
{
    QRegExp rx("^[0-1]+$");
    m_pRegExp->setRegExp(rx);
    m_dataWriteEdit->setValidator(m_pRegExp);

}   /*-------- end class Scale method SetBinaryMode -------- */

/*******************************************************************************
 * 类:Scale
 * 函数名:SetOctalMode()
 * 功能描述: 设置八进制模式
 * 参数:void
 * 返回值:void
 ******************************************************************************/
void Scale::SetOctalMode(void)
{
    QRegExp rx("^[0-7]+$");
    m_pRegExp->setRegExp(rx);
    m_dataWriteEdit->setValidator(m_pRegExp);

}   /*-------- end class Scale method SetOctalMode() -------- */

/*******************************************************************************
 * 类:Scale
 * 函数名:SetOtherMode()
 * 功能描述:设置其它模式
 * 参数:void
 * 返回值:void
 ******************************************************************************/
void Scale::SetOtherMode()
{
    // if ( m_convertFromBox->currentIndex() < 10 )
    // {
    //     char buf[128];
    //     sprintf( buf, "^[0-%d]+$", m_convertFromBox->currentIndex() );
    //     QRegExp rx("^[0-7]+$");
    //     m_pRegExp->setRegExp(rx);
    //     m_dataWriteEdit->setValidator(m_pRegExp);

    // }
    // else
    {
        m_dataWriteEdit->setValidator( NULL );
    }
}   /*-------- end class Scale method SetOtherMode() -------- */
