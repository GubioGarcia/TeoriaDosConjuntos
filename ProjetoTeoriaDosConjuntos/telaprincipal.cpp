#include "telaprincipal.h"
#include "ui_telaprincipal.h"

TelaPrincipal::TelaPrincipal(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::TelaPrincipal),
      CA(0),
      CB(0)
{
    ui->setupUi(this);
    ui->lineEditIncluirConjuntoA->setEnabled(false);
    ui->lineEditIncluirConjuntoB->setEnabled(false);
    ui->pushButtonIncluirConjuntoA->setEnabled(false);
    ui->pushButtonIncluirConjuntoB->setEnabled(false);
    ui->lineEditSaidaConjuntoA->setEnabled(false);
    ui->lineEditSaidaConjuntoB->setEnabled(false);
    ui->pushButtonUniao->setEnabled(false);
    ui->pushButtonIntersecao->setEnabled(false);
    ui->pushButtonCADiferencaCB->setEnabled(false);
    ui->pushButtonCBDiferencaCA->setEnabled(false);
    ui->lineEditResultado->setEnabled(false);
    ui->pushButtonUniaoOrdenada->setEnabled(false);
    ui->pushButtonSubCadeiaCA->setEnabled(false);
    ui->pushButtonSubCadeiaCB->setEnabled(false);
}

TelaPrincipal::~TelaPrincipal()
{
    delete ui;
    if(CA) delete CA;//delete condicionado, não foi criado valor inicial==0 então if(false)
    if(CB) delete CB;
}


void TelaPrincipal::on_pushButtonCriarConjuntoA_clicked()
{
    try {
        int tamanho = ui->lineEditTamanhoConjuntoA->text().toInt();
        CA = new ggs::Conjunto(tamanho);
        ui->lineEditIncluirConjuntoA->setEnabled(true);
        ui->pushButtonIncluirConjuntoA->setEnabled(true);
    } catch (QString &erro) {
        QMessageBox::information(this, "ERRO DO SISTEMA", erro);
    } catch (std::bad_alloc &erro){
        QMessageBox::information(this, "ERRO DO SISTEMA", "Conjunto não foi criado");
    }
}


void TelaPrincipal::on_pushButtonCriarConjuntoB_clicked()
{
    try {
        int tamanho = ui->lineEditTamanhoConjuntoB->text().toInt();
        CB = new ggs::Conjunto(tamanho);
        ui->lineEditIncluirConjuntoB->setEnabled(true);
        ui->pushButtonIncluirConjuntoB->setEnabled(true);
    } catch (QString &erro) {
        QMessageBox::information(this, "ERRO DO SISTEMA", erro);
    } catch (std::bad_alloc &erro){
        QMessageBox::information(this, "ERRO DO SISTEMA", "Conjunto não foi criado");
    }
}


void TelaPrincipal::on_pushButtonIncluirConjuntoA_clicked()
{
    try {
        int elemento = ui->lineEditIncluirConjuntoA->text().toInt();
        CA->ggs::Conjunto::incluirElemento(elemento);
        ui->lineEditIncluirConjuntoA->setText("");
        ui->lineEditSaidaConjuntoA->setText(QString("CA=") += CA->getConjunto());
        if(CA->getIndiceOcupacao()==CA->getTamanho()-1) ui->pushButtonSubCadeiaCA->setEnabled(true);
    } catch (QString &erro) {
        QMessageBox::information(this, "ERRO DO SISTEMA", erro);
    }
}


void TelaPrincipal::on_pushButtonIncluirConjuntoB_clicked()
{
    try {
        int elemento = ui->lineEditIncluirConjuntoB->text().toInt();
        CB->ggs::Conjunto::incluirElemento(elemento);
        ui->lineEditIncluirConjuntoB->setText("");
        ui->lineEditSaidaConjuntoB->setText(QString("CB=") += CB->getConjunto());
        if(CB->getIndiceOcupacao()==CB->getTamanho()-1) ui->pushButtonUniao->setEnabled(true);
        if(CB->getIndiceOcupacao()==CB->getTamanho()-1) ui->pushButtonIntersecao->setEnabled(true);
        if(CB->getIndiceOcupacao()==CB->getTamanho()-1) ui->pushButtonCADiferencaCB->setEnabled(true);
        if(CB->getIndiceOcupacao()==CB->getTamanho()-1) ui->pushButtonCBDiferencaCA->setEnabled(true);
        if(CB->getIndiceOcupacao()==CB->getTamanho()-1) ui->pushButtonUniaoOrdenada->setEnabled(true);
        if(CB->getIndiceOcupacao()==CB->getTamanho()-1) ui->pushButtonSubCadeiaCB->setEnabled(true);
    } catch (QString &erro) {
        QMessageBox::information(this, "ERRO DO SISTEMA", erro);
    }
}


void TelaPrincipal::on_pushButtonUniao_clicked()
{
    try {
        //Conjunto *uniao(Conjunto const*const objeto);
        ggs::Conjunto *CUniao = CA->uniao(CB);
        QString saida = "CAuniaoCB=";
        ui->lineEditResultado->setText(saida += CUniao->getConjunto());
        delete CUniao;
    } catch (std::bad_alloc) {
        QMessageBox::information(this, "ERRO DO SISTEMA", "Conjunto União não foi criado");
    }
}

void TelaPrincipal::on_pushButtonUniaoOrdenada_clicked()
{
    try {
        ggs::Conjunto *CUniaoOrdenada = CA->uniaoOrdenada(CB);
        QString saida = "CA Uniao Ordenada CB=";
        ui->lineEditResultado->setText(saida += CUniaoOrdenada->getConjunto());
        delete CUniaoOrdenada;
    } catch (std::bad_alloc) {
        QMessageBox::information(this, "ERRO DO SISTEMA", "Conjunto União não foi criado");
    }
}


void TelaPrincipal::on_pushButtonIntersecao_clicked()
{
    try {
        //Conjunto *intersecao(Conjunto const*const objeto);
        ggs::Conjunto *CIntersecao = CA->intersecao(CB);
        QString saida = "CAintersecaoCB=";
        ui->lineEditResultado->setText(saida += CIntersecao->getConjunto());
        delete CIntersecao;
    } catch (std::bad_alloc) {
        QMessageBox::information(this, "ERRO DO SISTEMA", "Conjunto Interseção não foi criado");
    }
}


void TelaPrincipal::on_pushButtonCADiferencaCB_clicked()
{
    try {
        ggs::Conjunto *CAdiferencaCB = CA->diferenca(CB);
        QString saida = "CA-CB=";
        ui->lineEditResultado->setText(saida += CAdiferencaCB->getConjunto());
        delete CAdiferencaCB;
    } catch (std::bad_alloc) {
        QMessageBox::information(this, "ERRO DO SISTEMA", "Conjunto Interseção não foi criado");
    }
}


void TelaPrincipal::on_pushButtonCBDiferencaCA_clicked()
{
    try {
        ggs::Conjunto *CBdiferencaCA = CB->diferenca(CA);
        QString saida = "CB-CA=";
        ui->lineEditResultado->setText(saida += CBdiferencaCA->getConjunto());
        delete CBdiferencaCA;
    } catch (std::bad_alloc) {
        QMessageBox::information(this, "ERRO DO SISTEMA", "Conjunto Interseção não foi criado");
    }
}

void TelaPrincipal::on_pushButtonSubCadeiaCA_clicked()
{
    try {
           ggs::Conjunto *subCadeiaCA = CA->subCadeiaCA();
           QString saida = "Maior Sub-Cadeia crescente em CA = ";
           ui->lineEditResultado->setText(saida += subCadeiaCA->getConjunto());
           delete subCadeiaCA;
    } catch (std::bad_alloc) {
        QMessageBox::information(this, "ERRO DO SISTEMA", "Conjunto Interseção não foi criado");
    }
}


void TelaPrincipal::on_pushButtonSubCadeiaCB_clicked()
{
    try {
        ggs::Conjunto *subCadeiaCB = CB->subCadeiaCB();
        QString saida = "Maior Sub-Cadeia decrescente em CB = ";
        ui->lineEditResultado->setText(saida += subCadeiaCB->getConjunto());
        delete subCadeiaCB;
    } catch (std::bad_alloc) {
        QMessageBox::information(this, "ERRO DO SISTEMA", "Conjunto Interseção não foi criado");
    }
}

void TelaPrincipal::on_pushButtonExecutar_clicked()
{
    try {
        const QString strSim = "SIM";
        const QString strNao = "NÃO";

        //VAZIO
        if(CA->estaVazio()){
            QTableWidgetItem *item1 = new QTableWidgetItem(strSim);
            ui->tableWidgetSaida->setItem(0,0,item1);
        }
        else{
            QTableWidgetItem *item2 = new QTableWidgetItem(strNao);
            ui->tableWidgetSaida->setItem(0,0,item2);
        }
        if(CB->estaVazio()){
            QTableWidgetItem *item1 = new QTableWidgetItem(strSim);
            ui->tableWidgetSaida->setItem(0,1,item1);
        }
        else{
            QTableWidgetItem *item2 = new QTableWidgetItem(strNao);
            ui->tableWidgetSaida->setItem(0,1,item2);
        }

        //SUBCONJUNTO
        if(CA->eSubconjunto(CB)){
            QTableWidgetItem *item1 = new QTableWidgetItem(strSim);
            ui->tableWidgetSaida->setItem(1,0,item1);
        }
        else{
            QTableWidgetItem *item2 = new QTableWidgetItem(strNao);
            ui->tableWidgetSaida->setItem(1,0,item2);
        }
        if(CB->eSubconjunto(CA)){
            QTableWidgetItem *item1 = new QTableWidgetItem(strSim);
            ui->tableWidgetSaida->setItem(1,1,item1);
        }
        else{
            QTableWidgetItem *item2 = new QTableWidgetItem(strNao);
            ui->tableWidgetSaida->setItem(1,1,item2);
        }

        //IDENTICOS
        if(CA->eIdentico(CB)){
            QTableWidgetItem *item1 = new QTableWidgetItem(strSim);
            ui->tableWidgetSaida->setItem(2,0,item1);
        }
        else{
            QTableWidgetItem *item2 = new QTableWidgetItem(strNao);
            ui->tableWidgetSaida->setItem(2,0,item2);
        }

        if(CB->eIdentico(CA)){
            QTableWidgetItem *item1 = new QTableWidgetItem(strSim);
            ui->tableWidgetSaida->setItem(2,1,item1);
        }
        else{
            QTableWidgetItem *item2 = new QTableWidgetItem(strNao);
            ui->tableWidgetSaida->setItem(2,1,item2);
        }

        //DISJUNTO
        if(CA->eDisjunto(CB)){
            QTableWidgetItem *item1 = new QTableWidgetItem(strSim);
            ui->tableWidgetSaida->setItem(3,0,item1);
        }
        else{
            QTableWidgetItem *item2 = new QTableWidgetItem(strNao);
            ui->tableWidgetSaida->setItem(3,0,item2);
        }

        if(CB->eDisjunto(CA)){
            QTableWidgetItem *item1 = new QTableWidgetItem(strSim);
            ui->tableWidgetSaida->setItem(3,1,item1);
        }
        else{
            QTableWidgetItem *item2 = new QTableWidgetItem(strNao);
            ui->tableWidgetSaida->setItem(3,1,item2);
        }

        //MEDIA ARITMETICA
        if(float auxMedia = CA->mediaAritmetica()){
            QTableWidgetItem *item1 = new QTableWidgetItem(QString::number(auxMedia));
            ui->tableWidgetSaida->setItem(5,0,item1);
        }
        else{
            QTableWidgetItem *item2 = new QTableWidgetItem(QString::number(auxMedia));
            ui->tableWidgetSaida->setItem(5,0,item2);
        }

        if(float auxMedia = CB->mediaAritmetica()){
            QTableWidgetItem *item1 = new QTableWidgetItem(QString::number(auxMedia));
            ui->tableWidgetSaida->setItem(5,1,item1);
        }
        else{
            QTableWidgetItem *item2 = new QTableWidgetItem(QString::number(auxMedia));
            ui->tableWidgetSaida->setItem(5,1,item2);
        }

        //AMPLITUDE
        if(int auxAmplitude = CA->amplitude()){
            QTableWidgetItem *item1 = new QTableWidgetItem(QString::number(auxAmplitude));
            ui->tableWidgetSaida->setItem(4,0,item1);
        }
        else{
            QTableWidgetItem *item2 = new QTableWidgetItem(QString::number(auxAmplitude));
            ui->tableWidgetSaida->setItem(4,0,item2);
        }

        if(int auxAmplitude = CB->amplitude()){
            QTableWidgetItem *item1 = new QTableWidgetItem(QString::number(auxAmplitude));
            ui->tableWidgetSaida->setItem(4,1,item1);
        }
        else{
            QTableWidgetItem *item2 = new QTableWidgetItem(QString::number(auxAmplitude));
            ui->tableWidgetSaida->setItem(4,1,item2);
        }

        //PRODUTO ESCALAR
        if(int auxProdutoEscalar = CA->produtoEscalar(CB)){
            QTableWidgetItem *item1 = new QTableWidgetItem(QString::number(auxProdutoEscalar));
            ui->tableWidgetSaida->setItem(6,0,item1);
        }
        else{
            QTableWidgetItem *item2 = new QTableWidgetItem(QString::number(auxProdutoEscalar));
            ui->tableWidgetSaida->setItem(6,0,item2);
        }

        if(int auxProdutoEscalar = CB->produtoEscalar(CA)){
            QTableWidgetItem *item1 = new QTableWidgetItem(QString::number(auxProdutoEscalar));
            ui->tableWidgetSaida->setItem(6,1,item1);
        }
        else{
            QTableWidgetItem *item2 = new QTableWidgetItem(QString::number(auxProdutoEscalar));
            ui->tableWidgetSaida->setItem(6,1,item2);
        }

    } catch (QString &erro) {
        QMessageBox::information(this, "ERRO DO SISTEMA", erro);
    }

}
