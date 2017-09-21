#ifndef SCALE_H
#define SCALE_H

#include <QWidget>
#include <QLineEdit>
#include <QString>
#include <QPushButton>
#include <QRadioButton>
#include <QButtonGroup>
#include <QRegExpValidator>
#include <QLabel>
#include <QString>
#include <QComboBox>

class Scale : public QWidget
{
    Q_OBJECT
public:
    explicit Scale(QWidget *parent = 0);
    ~Scale();

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
    void SetBinaryMode( void );
    void SetOctalMode(void );
    void SetOtherMode(void);

    // void StrToAsc( );
    // void AscToStr( );
    // int HexToStr();

public:
    QString m_hex;
    QString m_Decimal;
    QString m_Octal;
    QString m_Binary;
    QString m_Other;
    // char m_SeparatorBuf[3];

private:
    QRadioButton *m_dataDecimalButton;
    QRadioButton *m_dataBinaryButton;
    QRadioButton *m_dataOctalButton;
    QRadioButton *m_dataHexButton;
    QRadioButton *m_dataOtherButton;


    QLabel *m_dataOtherLabel;
    QLabel *m_dataBinaryLabel;
    QLabel *m_dataOctalLabel;
    QLabel *m_dataDecimalLabel;
    QLabel *m_dataHexLabel;
    QLabel *m_dataFromLabel;


    QLineEdit  *m_dataWriteEdit;
    QLineEdit  *m_dataOtherEdit;
    QLineEdit  *m_dataBinaryEdit;
    QLineEdit  *m_dataOctalEdit;
    QLineEdit  *m_dataDecimalEdit;
    QLineEdit  *m_dataHexEdit;

    QRegExpValidator *m_pRegExp;

    QPushButton *m_converButton;

    QComboBox *m_convertFromBox;
    QComboBox *m_convertToBox;
   // QPushButton *m_clearWriteButton;



    int m_iRadioId;

private:
    QWidget * m_mainWidget;
signals:

public slots:
};

#endif // SCALE_H
