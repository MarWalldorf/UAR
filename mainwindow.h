#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QtCharts>
#include <QLineEdit>
#include <QComboBox>
#include <QSpinBox>
#include <QPushButton>
#include <QDoubleSpinBox>
#include "ModelARX.h"
#include "RegulatorPID.h"
#include "Generator.h"
#include "Petla_Sprzezenia.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

private slots:
    void krokSymulacji();
    void przelaczSymulacje();
    void zresetujSymulacje();
    void otworzKonfiguracjeARX();

    void aktualizujPID();
    void aktualizujGenerator();
    void aktualizujInterwal();
    void zresetujCalkePID();

    void zapiszKonfiguracje();
    void wczytajKonfiguracje();

private:
    ModelARX arx;
    RegulatorPID pid;
    Generator gen;
    Petla_Sprzezenia petla;

    QTimer* timerSymulacji;
    double aktualnyCzas;
    bool czyDziala;
    int interwalMs;

    // GUI - Kontrolki
    QLineEdit *edycjaKp, *edycjaTi, *edycjaTd;
    QComboBox *comboMetodaCalk;

    QComboBox *comboGenTyp;
    QDoubleSpinBox *spinGenOffset, *spinGenAmp, *spinGenOkres;
    QDoubleSpinBox *spinGenWypelnienie;
    QDoubleSpinBox *spinGenCzasAkt;

    QSpinBox *spinInterwal;
    QPushButton *btnStartStop;

    // Wykresy i serie danych
    QLineSeries *seriaZadana, *seriaWyjscie, *seriaUchyb, *seriaSterowanie;
    QLineSeries *seriaP, *seriaI, *seriaD;
    QChart *wykresGlowny, *wykresUchyb, *wykresSterowanie, *wykresPID;
    QValueAxis *osXGlowny, *osYGlowny, *osXUchyb, *osYUchyb;
    QValueAxis *osXSterowanie, *osYSterowanie, *osXPID, *osYPID;

    // Metody pomocnicze
    void konfigurujGUI();
    void konfigurujWykresy();
    void aktualizujDaneWykresow(double t, double w, double y, double e, double u);
};

#endif // MAINWINDOW_H
