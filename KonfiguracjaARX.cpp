#include "KonfiguracjaARX.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QMessageBox>

KonfiguracjaARX::KonfiguracjaARX(ModelARX* model, QWidget* parent)
    : QDialog(parent), modelArx(model) {
    setWindowTitle("Konfiguracja Modelu ARX");
    setModal(false);
    resize(300, 250);

    QVBoxLayout* layout = new QVBoxLayout(this);

    layout->addWidget(new QLabel("Współczynniki A (po przecinku):"));
    edycjaA = new QLineEdit(wektorNaTekst(modelArx->getA()));
    layout->addWidget(edycjaA);

    layout->addWidget(new QLabel("Współczynniki B (po przecinku):"));
    edycjaB = new QLineEdit(wektorNaTekst(modelArx->getB()));
    layout->addWidget(edycjaB);

    layout->addWidget(new QLabel("Opóźnienie transportowe (k):"));
    spinOpoznienie = new QSpinBox();
    spinOpoznienie->setRange(1, 1000);
    spinOpoznienie->setValue(modelArx->getOpoznienie());
    layout->addWidget(spinOpoznienie);

    layout->addWidget(new QLabel("Odchylenie std. szumu:"));
    spinSzum = new QDoubleSpinBox();
    spinSzum->setRange(0.0, 100.0);
    spinSzum->setSingleStep(0.01);
    spinSzum->setValue(modelArx->getSzum());
    layout->addWidget(spinSzum);

    QPushButton* btnZamknij = new QPushButton("Zastosuj i Zamknij");
    connect(btnZamknij, &QPushButton::clicked, this, &KonfiguracjaARX::close);
    layout->addWidget(btnZamknij);
}

void KonfiguracjaARX::closeEvent(QCloseEvent* event) {
    zapiszZmiany();
    QDialog::closeEvent(event);
}

void KonfiguracjaARX::zapiszZmiany() {
    std::vector<double> noweA = parsujWektor(edycjaA->text());
    std::vector<double> noweB = parsujWektor(edycjaB->text());

    if (noweA.size() < 3 || noweB.size() < 3) {
        QMessageBox::warning(this, "Błąd", "Wektory A i B muszą mieć minimum 3 współczynniki!");
        edycjaA->setText(wektorNaTekst(modelArx->getA()));
        edycjaB->setText(wektorNaTekst(modelArx->getB()));
        return;
    }

    modelArx->setA(noweA);
    modelArx->setB(noweB);
    modelArx->setOpoznienie(spinOpoznienie->value());
    modelArx->setSzum(spinSzum->value());
}

std::vector<double> KonfiguracjaARX::parsujWektor(const QString& tekst) {
    std::vector<double> wek;
    QStringList lista = tekst.split(',');
    for (const QString& elem : lista) {
        bool ok;
        double val = elem.toDouble(&ok);
        if (ok) wek.push_back(val);
    }
    return wek;
}

QString KonfiguracjaARX::wektorNaTekst(const std::vector<double>& wektor) {
    QStringList lista;
    for (double v : wektor) lista << QString::number(v);
    return lista.join(", ");
}
