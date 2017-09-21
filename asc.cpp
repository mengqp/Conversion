#include "asc.h"
#include "widget.h"
#include <stdlib.h>

ASC::ASC(QWidget *parent) : QWidget(parent)
{
    m_mainWidget = parent;
    InitUi();
    InitUiFeature();
    InitUiParam();
}

ASC::~ASC()
{
    if( NULL != m_pRegExp )
    {
        delete m_pRegExp;
        m_pRegExp = NULL;
    }
    delete m_dataCharLabel;
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
    if( NULL != m_dataSeparatorLabel )
    {
        delete m_dataSeparatorLabel;
        m_dataSeparatorLabel = NULL;
    }

    delete m_DigitalSelButtonGroup;
    delete m_dataCharButton;
    delete m_dataDigitalButton;

    delete m_dataDecimalButton;
    if( NULL != m_dataHexButton )
    {
        delete m_dataHexButton;
        m_dataHexButton = NULL;
    }

    delete  m_dataWriteEdit;
    delete  m_dataCharEdit;
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
    if( NULL != m_dataSeparatorEdit )
    {
        delete m_dataSeparatorEdit;
        m_dataSeparatorEdit = NULL;
    }


    delete m_converButton;




    //delete m_clearWriteButton;
}

bool ASC::InitUi()
{
    //创建控件 Label
    m_dataCharLabel = new QLabel(this);
    m_dataCharLabel->setGeometry(50,100,200,20);
    m_dataCharLabel->setText(FROMLOCAL("字符"));
    m_dataCharLabel->show();

    m_dataBinaryLabel = new QLabel(this);
    m_dataBinaryLabel->setGeometry(50,150,150,20);
    m_dataBinaryLabel->setText(FROMLOCAL("二进制"));

    m_dataOctalLabel = new QLabel(this);
    m_dataOctalLabel->setGeometry(50,200,150,20);
    m_dataOctalLabel->setText(FROMLOCAL("八进制"));

    m_dataDecimalLabel = new QLabel(this);
    m_dataDecimalLabel->setGeometry(50,250,150,20);
    m_dataDecimalLabel->setText(FROMLOCAL("十进制"));

    m_dataHexLabel = new QLabel(this);
    m_dataHexLabel->setGeometry(50,300,150,20);
    m_dataHexLabel->setText(FROMLOCAL("十六进制"));

    m_dataSeparatorLabel = new QLabel(this);
    m_dataSeparatorLabel->setGeometry(50,350,150,20);
    m_dataSeparatorLabel->setText(FROMLOCAL("分隔符"));

    //创建 QRadioButton
    m_DigitalSelButtonGroup = new QButtonGroup(this);
   // m_ByteSelButtonGroup = new QButtonGroup(this);

    m_dataCharButton = new QRadioButton(this);
    m_dataCharButton->setGeometry(50,20,50,20);
    m_dataCharButton->setText(FROMLOCAL("字符"));
    m_dataCharButton->click();


    m_dataDigitalButton = new QRadioButton(this);
    m_dataDigitalButton->setGeometry(100,20,100,20);
    m_dataDigitalButton->setText(FROMLOCAL("数字"));


    m_dataDecimalButton = new QRadioButton(this);
    m_dataDecimalButton->setGeometry(200,20,100,20);
    m_dataDecimalButton->setText(FROMLOCAL("十进制"));
    m_dataDecimalButton->hide();

    m_dataHexButton = new QRadioButton(this);
    m_dataHexButton->setGeometry(300,20,100,20);
    m_dataHexButton->setText(FROMLOCAL("十六进制"));
    m_dataHexButton->hide();

    //创建控件 QlineEdit
    m_dataWriteEdit = new QLineEdit(this);
    m_dataWriteEdit->setGeometry(100,50,150,20);
    connect(m_dataWriteEdit, SIGNAL(textChanged(QString)), this, SLOT(FuncConvertion()) );

    m_dataCharEdit = new QLineEdit(this);
    m_dataCharEdit->setGeometry(100,100,150,20);

    m_dataBinaryEdit = new QLineEdit(this);
    m_dataBinaryEdit->setGeometry(100,150,150,20);

    m_dataOctalEdit = new QLineEdit(this);
    m_dataOctalEdit->setGeometry(100,200,150,20);

    m_dataDecimalEdit = new QLineEdit(this);
    m_dataDecimalEdit->setGeometry(100,250,150,20);

    m_dataHexEdit = new QLineEdit(this);
    m_dataHexEdit->setGeometry(100,300,150,20);

    m_dataSeparatorEdit = new QLineEdit(this);
    m_dataSeparatorEdit->setGeometry(100,350,150,20);
    m_dataSeparatorEdit->setText(FROMLOCAL(","));

    //创建控件 QPushButton
    m_converButton = new QPushButton(this);
    m_converButton->setGeometry(270,50,50,20);
    m_converButton->setText(FROMLOCAL("转换"));

  //  m_clearWriteButton = new QPushButton(this);
   // m_clearWriteButton->setGeometry(250,50,50,20);
  //  m_clearWriteButton->setText(FROMLOCAL("清空"));

    return true;
}

void ASC::InitUiFeature()
{
    //设置windows
    this->setWindowTitle(FROMLOCAL("转化工具"));
   // this->resize(500,300);
    this->setFixedSize(800,600);

    //设置 QRadioButton
    connect(m_dataCharButton,SIGNAL(clicked(bool)),
            this,SLOT(radioChange()));
    connect(m_dataDigitalButton,SIGNAL(clicked(bool)),
            this,SLOT(radioChange()));
    connect(m_dataDecimalButton,SIGNAL(clicked(bool)),
            this,SLOT(radioChange()));
    connect(m_dataHexButton,SIGNAL(clicked(bool)),
            this,SLOT(radioChange()));
    m_DigitalSelButtonGroup->addButton(m_dataDecimalButton);
    m_DigitalSelButtonGroup->addButton(m_dataHexButton);

    //设置 QlineEdit
    m_dataCharEdit->setReadOnly(true);
    m_dataBinaryEdit->setReadOnly(true);
    m_dataDecimalEdit->setReadOnly(true);
    m_dataOctalEdit->setReadOnly(true);
    m_dataHexEdit->setReadOnly(true);

    //设置 QPushButton
    connect(m_converButton,SIGNAL(released()),
            this,SLOT(FuncConvertion()));
}

void ASC::InitUiParam()
{
    m_iRadioId = 0;
    m_pRegExp = new QRegExpValidator(this);
}


void ASC::FuncConvertion()
{
    QString  str = m_dataWriteEdit->text();
    if( str.isEmpty())
    {
        m_dataCharEdit->clear();
        m_dataBinaryEdit->clear();
        m_dataOctalEdit->clear();
        m_dataDecimalEdit->clear();
        m_dataHexEdit->clear();
        return;
    }

    QString strs = m_dataSeparatorEdit->text();
    char* chs;
    QByteArray bas = strs.toLatin1();
    chs=bas.data();
    strncpy(m_SeparatorBuf, chs, 2 );

    char* ch;
    QByteArray ba = str.toLatin1();
    ch=ba.data();

    Convertion(ch, m_iRadioId);



    m_dataCharEdit->setText((m_str));
    m_dataHexEdit->setText((m_hex));
    m_dataBinaryEdit->setText((m_Binary));
    m_dataOctalEdit->setText((m_Octal));
    m_dataDecimalEdit->setText((m_Decimal));
}

void ASC::radioChange()
{
    if(sender() == m_dataCharButton)
    {
        m_iRadioId = 0;
        m_dataDecimalButton->hide();
        m_dataHexButton->hide();
        m_dataSeparatorEdit->show();
        m_dataSeparatorLabel->show();
        m_dataWriteEdit->clear();
        m_dataWriteEdit->setValidator( NULL );

    }
    else if(sender() == m_dataDigitalButton)
    {
        m_iRadioId = 1;
        m_dataDecimalButton->click();
        m_dataDecimalButton->show();
        m_dataHexButton->show();
        m_dataSeparatorEdit->hide();
        m_dataSeparatorLabel->hide();
        m_dataWriteEdit->clear();
    }
    else if(sender() == m_dataDecimalButton)
    {
        m_iRadioId = 2;
        m_dataWriteEdit->clear();
        SetDecimalMode();
    }
    else if(sender() == m_dataHexButton)
    {
        m_iRadioId = 3;
        m_dataWriteEdit->clear();
        SetHexMode();
    }

}


bool ASC::Convertion(char *szLineBuf, int szDataType)
{
    int buf_len = strlen( szLineBuf);
    if ( buf_len > 1024 )
    {
        buf_len = 1024;
    }

    switch(szDataType)
    {
    case 0://字符
        {

            char hex_str[(2+3) * 1024] = "";
            char b_str[(8+3) * 1024] = "";
            char o_str[(3+3) * 1024] = "";
            char d_str[(3+3) * 1024] = "";

            char buf[9];
            char *p = buf;
            for (int i = 0; i < buf_len; i++)
            {
                public_itoa( szLineBuf[i], p, 2);
                strcat(b_str, p );
                strcat(b_str, m_SeparatorBuf );

                public_itoa( szLineBuf[i], p, 8);
                strcat(o_str, p );
                strcat(o_str, m_SeparatorBuf );

                public_itoa( szLineBuf[i], p, 10);
                strcat(d_str, p );
                strcat(d_str, m_SeparatorBuf );

                public_itoa( szLineBuf[i], p, 16);
                strcat(hex_str, p );
                strcat(hex_str, m_SeparatorBuf );
            }
            m_str = QString( szLineBuf );
            m_Binary = QString( b_str );
            m_Octal = QString( o_str );
            m_Decimal = QString( d_str );
            m_hex = QString( hex_str );

            break;

        }
    case 1://数字
    case 2://10进制
        {
            int num = atoi( szLineBuf );
            char buf[9] = "";
            buf[0] = num;
            m_str = QString( buf );
            m_Decimal = QString::number( num );
            public_itoa(num,buf,16);
            m_hex = QString( buf );
            public_itoa(num,buf,8);
            m_Octal = QString( buf );
            public_itoa(num,buf,2);
            m_Binary = QString( buf );

        }
        break;
    case 3://16进制 <-
        {
            int num = 0;
            sscanf( szLineBuf, "%x", &num );
            char buf[9] = "";
            buf[0] = num;
            m_str = QString( buf );
            m_Decimal = QString::number( num );
            public_itoa(num,buf,16);
            m_hex = QString( buf );
            public_itoa(num,buf,8);
            m_Octal = QString( buf );
            public_itoa(num,buf,2);
            m_Binary = QString( buf );
        }
        break;
    default:

        break;
    }

    return true;
}

void ASC::SetDecimalMode()
{
    QRegExp rx("^([0-9]{1,2})$|^([1][2][0-7])$|^([1][0-1][0-9])$");
    m_pRegExp->setRegExp(rx);
    m_dataWriteEdit->setValidator(m_pRegExp);

}

void ASC::SetHexMode()
{
    QRegExp rx("^([0-9a-fA-F])$|^([0-7][0-9a-fA-F])$");
    m_pRegExp->setRegExp(rx);
    m_dataWriteEdit->setValidator(m_pRegExp);
}
