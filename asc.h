#ifndef ASC_H
#define ASC_H

#include <QWidget>
#include <QLineEdit>
#include <QString>
#include <QPushButton>
#include <QRadioButton>
#include <QButtonGroup>
#include <QRegExpValidator>
#include <QLabel>
#include <QString>

class ASC : public QWidget
{
    Q_OBJECT
public:
    explicit ASC(QWidget *parent = 0);
    ~ASC();

    bool InitUi(void);
    void InitUiFeature();
    void InitUiParam();



private slots:
    void FuncConvertion();
    void radioChange();

public:
    bool Convertion(char *szLineBuf, int szDataType);
    void SetDecimalMode( void );
    void SetHexMode( void );
    // void StrToAsc( );
    // void AscToStr( );
    // int HexToStr();

public:
    QString m_str;
    QString m_hex;
    QString m_Decimal;
    QString m_Octal;
    QString m_Binary;
    char m_SeparatorBuf[3];

private:
    QButtonGroup *m_DigitalSelButtonGroup;
    QButtonGroup *m_ByteSelButtonGroup;


    QRadioButton *m_dataCharButton;
    QRadioButton *m_dataDigitalButton;


    QRadioButton *m_dataDecimalButton;
    QRadioButton *m_dataBinaryButton;
    QRadioButton *m_dataOctalButton;
    QRadioButton *m_dataHexButton;


    QLabel *m_dataCharLabel;
    QLabel *m_dataBinaryLabel;
    QLabel *m_dataOctalLabel;
    QLabel *m_dataDecimalLabel;
    QLabel *m_dataHexLabel;
    QLabel *m_dataSeparatorLabel;


    QLineEdit  *m_dataWriteEdit;
    QLineEdit  *m_dataCharEdit;
    QLineEdit  *m_dataBinaryEdit;
    QLineEdit  *m_dataOctalEdit;
    QLineEdit  *m_dataDecimalEdit;
    QLineEdit  *m_dataHexEdit;
    QLineEdit  *m_dataSeparatorEdit;

    QRegExpValidator *m_pRegExp;

    QPushButton *m_converButton;
   // QPushButton *m_clearWriteButton;



    int m_iRadioId;

private:
    QWidget * m_mainWidget;
};

#endif // ASC_H
