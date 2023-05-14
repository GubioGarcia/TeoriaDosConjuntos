#ifndef TELAPRINCIPAL_H
#define TELAPRINCIPAL_H

#include <QMainWindow>
#include <conjunto.h>
#include <QString>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class TelaPrincipal; }
QT_END_NAMESPACE

class TelaPrincipal : public QMainWindow
{
    Q_OBJECT

public:
    TelaPrincipal(QWidget *parent = nullptr);
    ~TelaPrincipal();

private slots:
    void on_pushButtonCriarConjuntoA_clicked();

    void on_pushButtonCriarConjuntoB_clicked();

    void on_pushButtonIncluirConjuntoA_clicked();

    void on_pushButtonIncluirConjuntoB_clicked();

    void on_pushButtonUniao_clicked();

    void on_pushButtonIntersecao_clicked();

    void on_pushButtonCADiferencaCB_clicked();

    void on_pushButtonCBDiferencaCA_clicked();

    void on_pushButtonExecutar_clicked();

    void on_pushButtonUniaoOrdenada_clicked();

    void on_pushButtonSubCadeiaCA_clicked();

    void on_pushButtonSubCadeiaCB_clicked();

private:
    Ui::TelaPrincipal *ui;
    ggs::Conjunto *CA;//conjunto é atributo pois o botoes precisam usar ele fora do escopo do botao criar
    ggs::Conjunto *CB;//ponteiro pois deve ser criado com NEW, pois a tela ira iniciar e criaria o CA sem informação do tamanho
};
#endif // TELAPRINCIPAL_H
