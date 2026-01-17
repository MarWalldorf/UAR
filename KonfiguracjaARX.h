#ifndef KONFIGURACJAARX_H
#define KONFIGURACJAARX_H

#include <QDialog>
#include <QLineEdit>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <vector>
#include "ModelARX.h"

class KonfiguracjaARX : public QDialog {
    Q_OBJECT
public:
    explicit KonfiguracjaARX(ModelARX* model, QWidget* parent = nullptr);

protected:
    void closeEvent(QCloseEvent* event) override;

private:
    ModelARX* modelArx;
    QLineEdit* edycjaA;
    QLineEdit* edycjaB;
    QSpinBox* spinOpoznienie;
    QDoubleSpinBox* spinSzum;

    void zapiszZmiany();
    std::vector<double> parsujWektor(const QString& tekst);
    QString wektorNaTekst(const std::vector<double>& wektor);
};

#endif
