#include "floathex.h"
#include "widget.h"

floathex::floathex(QWidget *parent)
    : QWidget(parent)
{
    m_mainWidget = parent;
    InitUi();
    InitUiFeature();
    InitUiParam();
}

floathex::~floathex()
{
    if( NULL != m_dataFloatLabel )
    {
        delete m_dataFloatLabel;
        m_dataFloatLabel = NULL;
    }

    if( NULL != m_dataHexLabel )
    {
        delete m_dataHexLabel;
        m_dataHexLabel = NULL;
    }

    if( NULL != m_HexSelButtonGroup )
    {
        delete m_HexSelButtonGroup;
        m_HexSelButtonGroup = NULL;
    }

    if( NULL != m_dataFloatButton )
    {
        delete m_dataFloatButton;
        m_dataFloatButton = NULL;
    }

    if( NULL != m_dataHexButton )
    {
        delete m_dataHexButton;
        m_dataHexButton = NULL;
    }

    if( NULL != m_dataHexBButton )
    {
        delete m_dataHexBButton;
        m_dataHexBButton = NULL;
    }

    if( NULL !=  m_dataHexAButton )
    {
        delete  m_dataHexAButton;
        m_dataHexAButton = NULL;
    }

    if( NULL != m_dataWriteEdit )
    {
        delete m_dataWriteEdit;
        m_dataWriteEdit = NULL;
    }

    if( NULL != m_dataFloatEdit )
    {
        delete m_dataFloatEdit;
        m_dataFloatEdit = NULL;
    }

    if( NULL != m_dataHexEdit )
    {
        delete m_dataHexEdit;
        m_dataHexEdit = NULL;
    }

    if( NULL != m_converButton )
    {
        delete m_converButton;
        m_converButton = NULL;
    }

    if( NULL != m_pRegExp )
    {
        delete m_pRegExp;
        m_pRegExp = NULL;
    }
    delete m_pRegExp;
}


bool floathex::InitUi()
{
    //创建控件 Label
    m_dataFloatLabel = new QLabel(this);
    m_dataFloatLabel->setGeometry(50,100,200,20);
    m_dataFloatLabel->setText(FROMLOCAL("浮点"));
    m_dataFloatLabel->show();

    m_dataHexLabel = new QLabel(this);
    m_dataHexLabel->setGeometry(50,150,150,20);
    m_dataHexLabel->setText(FROMLOCAL("十六进制"));

    //创建 QRadioButton
    m_HexSelButtonGroup = new QButtonGroup(this);

    m_dataFloatButton = new QRadioButton(this);
    m_dataFloatButton->setGeometry(50,20,50,20);
    m_dataFloatButton->setText(FROMLOCAL("浮点"));
    m_dataFloatButton->click();


    m_dataHexButton = new QRadioButton(this);
    m_dataHexButton->setGeometry(100,20,100,20);
    m_dataHexButton->setText(FROMLOCAL("十六进制"));


    m_dataHexAButton = new QRadioButton(this);
    m_dataHexAButton->setGeometry(250,20,100,20);
    m_dataHexAButton->setText(FROMLOCAL("正序"));
    m_dataHexAButton->hide();


    m_dataHexBButton = new QRadioButton(this);
    m_dataHexBButton->setGeometry(300,20,100,20);
    m_dataHexBButton->setText(FROMLOCAL("倒序"));
    m_dataHexBButton->hide();


    //创建控件 QlineEdit
    m_dataWriteEdit = new QLineEdit(this);
    m_dataWriteEdit->setGeometry(100,50,150,20);
    connect(m_dataWriteEdit, SIGNAL(textChanged(QString)), this, SLOT(FuncConvertion()) );

    m_dataFloatEdit = new QLineEdit(this);
    m_dataFloatEdit->setGeometry(100,100,150,20);

    m_dataHexEdit = new QLineEdit(this);
    m_dataHexEdit->setGeometry(100,150,150,20);

    //创建控件 QPushButton
    m_converButton = new QPushButton(this);
    m_converButton->setGeometry(270,50,50,20);
    m_converButton->setText(FROMLOCAL("转换"));

  //  m_clearWriteButton = new QPushButton(this);
   // m_clearWriteButton->setGeometry(250,50,50,20);
  //  m_clearWriteButton->setText(FROMLOCAL("清空"));

    m_fVal = 0;
    memset( m_szHexBuf, 0, sizeof(m_szHexBuf));

    return true;
}

void floathex::InitUiFeature()
{
    //设置windows
    this->setWindowTitle(FROMLOCAL("转化工具"));
   // this->resize(500,300);
    this->setFixedSize(350,200);

    //设置 QRadioButton
    connect(m_dataFloatButton,SIGNAL(clicked(bool)),
            this,SLOT(radioChange()));
    connect(m_dataHexButton,SIGNAL(clicked(bool)),
            this,SLOT(radioChange()));
    connect(m_dataHexAButton,SIGNAL(clicked(bool)),
            this,SLOT(radioChange()));
    connect(m_dataHexBButton,SIGNAL(clicked(bool)),
            this,SLOT(radioChange()));
    m_HexSelButtonGroup->addButton(m_dataHexAButton);
    m_HexSelButtonGroup->addButton(m_dataHexBButton);
   // m_ByteSelButtonGroup->addButton(m_DwordButton);
   // m_ByteSelButtonGroup->addButton(m_WordButton);
   // m_ByteSelButtonGroup->addButton(m_ByteButton);

   // m_DwordButton->click();


    //设置 QlineEdit
    m_dataFloatEdit->setReadOnly(true);
    m_dataHexEdit->setReadOnly(true);

    //设置 QPushButton
    connect(m_converButton,SIGNAL(released()),
            this,SLOT(FuncConvertion()));
}

void floathex::InitUiParam()
{
    m_iRadioId = 0;
    //m_pConversion = new CConverTion();
    m_pRegExp = new QRegExpValidator(this);
    SetFloatMode();
}


void floathex::FuncConvertion()
{
    QString  str = m_dataWriteEdit->text();
    if( str.isEmpty())
    {
        m_dataFloatEdit->clear();
        m_dataHexEdit->clear();
        return;
    }
    char* ch;
    QByteArray ba = str.toLatin1();
    ch=ba.data();

    Convertion(ch, m_iRadioId);

    //double d = 11111.12345;
    m_dataFloatEdit->setText(QString::number(m_fVal));
    //m_dataFloatEdit->setText(QString("%1").arg(d,0,'f',3));
    m_dataHexEdit->setText(QString(m_szHexBuf));
}

void floathex::radioChange()
{
    if(sender() == m_dataFloatButton)
    {
        m_iRadioId = 0;
        m_dataHexAButton->hide();
        m_dataHexBButton->hide();
        m_dataWriteEdit->clear();
        SetFloatMode();

    }
    else if(sender() == m_dataHexButton)
    {
        m_iRadioId = 1;
        m_dataHexAButton->click();
        m_dataHexAButton->show();
        m_dataHexBButton->show();
        m_dataWriteEdit->clear();
        SetHexMode();
    }
    else if(sender() == m_dataHexAButton)
    {
        m_iRadioId = 2;
    }
    else if(sender() == m_dataHexBButton)
    {
        m_iRadioId = 3;
    }

}

void floathex::SetFloatMode()
{
    QRegExp rx("^-?[0-9]+\\.?\\d*$()|(^[+-]?([0-9]*\\.?[0-9]+|[0-9]+\\.?[0-9]*)([eE][+-]?[0-9]+)?$)");
    m_pRegExp->setRegExp(rx);
    m_dataWriteEdit->setValidator(m_pRegExp);

}

void floathex::SetHexMode()
{
    QRegExp rx("^([0-9a-fA-F]{1,2}\\ ?){4}$");
    m_pRegExp->setRegExp(rx);
    m_dataWriteEdit->setValidator(m_pRegExp);
}

bool floathex::Convertion(char *szLineBuf, int szDataType)
{
#ifdef  DebugMod
qDebug() << "Convertion"<<szDataType;
#endif

    unsigned char szTmpBuf[4];
    unsigned char szTmpBuf1[4];
    unsigned char *p;

    m_fVal = 0.0;
    memset(m_szHexBuf, 0, sizeof(m_szHexBuf));

    switch(szDataType)
    {
    case 0://float
        sscanf( szLineBuf, "%f",  &m_fVal );
        p = (unsigned char *)&m_fVal;

        sprintf(m_szHexBuf, "%02x %02x %02x %02x",
                *p, *(p+1), *(p+2), *(p+3));
        break;
    case 1://byte
    case 2://byte ->
        sscanf( szLineBuf, "%2x %2x %2x %2x",
                (unsigned int *)&szTmpBuf[0], (unsigned int *)&szTmpBuf[1], (unsigned int *)&szTmpBuf[2], (unsigned int *)&szTmpBuf[3]);
        memcpy( &m_fVal, szTmpBuf, 4 );
        sprintf(m_szHexBuf, "%02x %02x %02x %02x",
                szTmpBuf[0], szTmpBuf[1], szTmpBuf[2], szTmpBuf[3]);
        break;
    case 3://byte <-
        sscanf( szLineBuf, "%2x %2x %2x %2x",
                (unsigned int *)&szTmpBuf1[0], (unsigned int *)&szTmpBuf1[1], (unsigned int *)&szTmpBuf1[2], (unsigned int *)&szTmpBuf1[3]);

                szTmpBuf[3]  = szTmpBuf1[0];
                szTmpBuf[2]  = szTmpBuf1[1];
                szTmpBuf[1]  = szTmpBuf1[2];
                szTmpBuf[0]  = szTmpBuf1[3];

        memcpy( &m_fVal, szTmpBuf, 4 );
        sprintf(m_szHexBuf, "%02x %02x %02x %02x",
                szTmpBuf[0], szTmpBuf[1], szTmpBuf[2], szTmpBuf[3]);
        break;
    default:

        break;
    }

#ifdef  DebugMod
  qDebug() << m_fVal << m_szHexBuf << endl;
#endif



    return true;
}
