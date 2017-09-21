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
    bool InitUi(void);
    void InitUiFeature();
    void InitUiParam();

    void SetFloatMode( void );
    void SetHexMode( void );


private slots:
    void FuncConvertion();
    void radioChange();

public:
    bool Convertion(char *szLineBuf, int szDataType);

public:
    float m_fVal;
    char m_szHexBuf[256];

private:
    QButtonGroup *m_HexSelButtonGroup;
    QButtonGroup *m_ByteSelButtonGroup;


    QRadioButton *m_ByteButton;
    QRadioButton *m_WordButton;
    QRadioButton *m_DwordButton;

    QRadioButton *m_dataFlaotButton;
    QRadioButton *m_dataHexButton;


    QRadioButton *m_dataHexAButton;
    QRadioButton *m_dataHexBButton;


    QLabel *m_dataFloatLabel;
    QLabel *m_dataHexLabel;

    QLineEdit  *m_dataWriteEdit;
    QLineEdit  *m_dataFloatEdit;
    QLineEdit  *m_dataHexEdit;

    QRegExpValidator *m_pRegExp;

    QPushButton *m_converButton;
   // QPushButton *m_clearWriteButton;



    int m_iRadioId;

private:
    QWidget * m_mainWidget;
};

#endif // FLOATHEX_H
