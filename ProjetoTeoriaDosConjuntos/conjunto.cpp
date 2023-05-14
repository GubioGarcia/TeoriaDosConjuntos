#include "conjunto.h"

namespace ggs {
    Conjunto::~Conjunto(){
        if(array) delete[] array;//delete sem [] deleta apenas a primeira casa do vetor
    }

    Conjunto::Conjunto(int tamanho):
        tamanho(0),
        indiceOcupacao(-1),
        array(0)
    {
        if(tamanho<=0) throw QString("Tamanho do Conjunto não pode ser <= 0");
       try {
           array = new int[tamanho];
           this->tamanho = tamanho;//atributo recebe parametro
       } catch (std::bad_alloc &erro) {
                throw QString("Conjunto não foi criado = faltou espaço");
       }
     }

    int Conjunto::getTamanho() const
    {
        return tamanho;
    }

    QString Conjunto::getConjunto() const{
        QString saida = "{";
        for(int pos=0; pos<=indiceOcupacao; pos++){
            saida = saida += QString::number(*(array+pos));
            if(pos<indiceOcupacao) saida = saida += ",";
        }
        saida = saida += "}";
        return saida;
    }

    bool Conjunto::verificarOcupacao()const{
        return (indiceOcupacao==tamanho-1);
    }

    void Conjunto::incluirElemento(int elemento){
        if(verificarOcupacao()) throw QString("Não há espaço no conjunto para alocação do elemento");
        if(buscar(elemento)) throw QString("Elemento já existe no Conjunto");
        indiceOcupacao++;
        *(array+indiceOcupacao)=elemento;
    }

    int Conjunto::getIndiceOcupacao() const
    {
        return indiceOcupacao;
    }

    bool Conjunto::estaVazio()const{
        if(indiceOcupacao == -1) return true;
        else return false;
    }

    bool Conjunto::buscar(int elemento)const{
        for(int pos=0; pos<=indiceOcupacao; pos++){
            if(*(array+pos)==elemento) return true;
        }
        return false;
    }

    Conjunto *Conjunto::uniao(Conjunto const*const objeto)const{
        try {
            int tamanho = this->indiceOcupacao+objeto->indiceOcupacao;
            Conjunto *AuxUniao = new Conjunto(tamanho);
            for(int pos=0; pos<=this->indiceOcupacao; pos++){
                *(AuxUniao->array+pos) = *(this->array+pos);
            }//inclui os elementos do this no uniao
            AuxUniao->indiceOcupacao=this->indiceOcupacao;
            for(int i=0; i<=objeto->indiceOcupacao; i++){
                //if(!AuxUniao->buscar(*(objeto->array+pos))) - metodo para negação da condição sem uso de variavel auxiliar
                int elemento = *(objeto->array+i);
                if(AuxUniao->buscar(elemento)==false){
                   AuxUniao->indiceOcupacao++;
                   *(AuxUniao->array+AuxUniao->indiceOcupacao)=elemento;
                }
            }//inclui os elementos do parametro objeto se estes não exitirem no this
            return AuxUniao;
        } catch (std::bad_alloc) {
            throw QString ("Conjunto União não foi criado");
        }
    }

    Conjunto *Conjunto::intersecao(Conjunto const*const objeto)const{
        try {
            int tamanho = this->getIndiceOcupacao();
            if(this->indiceOcupacao > objeto->indiceOcupacao) tamanho = objeto->indiceOcupacao;
            Conjunto *AuxIntersecao = new Conjunto(tamanho);
            for (int pos=0; pos<=this->indiceOcupacao; pos++){
                if (objeto->buscar(*(this->array+pos))){
                    AuxIntersecao->indiceOcupacao++;
                    *(AuxIntersecao->array+AuxIntersecao->indiceOcupacao) = *(this->array+pos);
                }
            }
            return AuxIntersecao;
        } catch (std::bad_alloc) {
            throw QString ("Conjunto Interseção não foi criado");
        }
    }

    Conjunto *Conjunto::diferenca(Conjunto const*const objeto)const{
        try {
            int tamanho = this->getIndiceOcupacao();
            if(this->indiceOcupacao > objeto->indiceOcupacao) tamanho = objeto->indiceOcupacao;
            Conjunto *AuxDiferenca = new Conjunto(tamanho);
            for (int pos=0; pos<=this->indiceOcupacao; pos++){
                if (!objeto->buscar(*(this->array+pos))){
                    AuxDiferenca->indiceOcupacao++;
                    *(AuxDiferenca->array+AuxDiferenca->indiceOcupacao) = *(this->array+pos);
                }
            }
            return AuxDiferenca;
        } catch (std::bad_alloc) {
            throw QString ("Conjunto Diferença não foi criado");
        }
    }

    bool Conjunto::eSubconjunto(Conjunto const*const objeto)const{
        for (int pos=0; pos<=this->indiceOcupacao; pos++){
            if (!objeto->buscar(*(this->array+pos))) return false;
        }
        return true;
    }

    bool Conjunto::eIdentico(Conjunto const*const objeto)const{
        if(this->indiceOcupacao!=objeto->indiceOcupacao) return false;
        for (int pos=0; pos<=this->indiceOcupacao; pos++){
            if (!objeto->buscar(*(this->array+pos))) return false;
        }
        return true;
    }

    bool Conjunto::eDisjunto(Conjunto const*const objeto)const{
        for (int pos=0; pos<=this->indiceOcupacao; pos++){
            if (objeto->buscar(*(this->array+pos))) return false;
        }
        return true;
    }

    float Conjunto::mediaAritmetica()const{
        if(this->estaVazio()) return 0;
        float media = 0;
        for(int pos=0; pos<=this->indiceOcupacao; pos++){
            media = media + *(this->array+pos);
        }
        return media/(indiceOcupacao+1);
    }

    int Conjunto::amplitude()const{
        if(this->estaVazio()) throw QString("Não há amplitude em conjunto vazio");
        int menorElemento=*(this->array+0), maiorElemento=*(this->array+0);
        for(int pos=0; pos<=this->indiceOcupacao; pos++){
            if(*(this->array+pos) < menorElemento) menorElemento = *(this->array+pos);
            if(*(this->array+pos) > maiorElemento) maiorElemento = *(this->array+pos);
        }
        return maiorElemento-menorElemento;
    }

    int Conjunto::produtoEscalar(Conjunto const*const objeto)const{
        if(this->indiceOcupacao!=objeto->indiceOcupacao) throw QString("Não é possível PRODUTO ESCALAR em conjuntos com Indice de Ocupação diferentes");
        int auxProdutoEscalar=0;
        for(int pos=0; pos<=this->indiceOcupacao; pos++){
            auxProdutoEscalar=auxProdutoEscalar+(*(this->array+pos)*(*(objeto->array+pos)));
        }
        return auxProdutoEscalar;
    }

    Conjunto *Conjunto::uniaoOrdenada(Conjunto const*const objeto)const{
        try {
            Conjunto *CAuxUniaoOrdenada = this->uniao(objeto);
            for(int i=0; i<=CAuxUniaoOrdenada->indiceOcupacao; i++){
                for(int j=i+1; j<=CAuxUniaoOrdenada->indiceOcupacao; j++){
                    if(*(CAuxUniaoOrdenada->array+i)>*(CAuxUniaoOrdenada->array+j)){
                        int aux = *(CAuxUniaoOrdenada->array+i);
                        *(CAuxUniaoOrdenada->array+i) = *(CAuxUniaoOrdenada->array+j);
                        *(CAuxUniaoOrdenada->array+j) = aux;
                    }
                }
            }
            return CAuxUniaoOrdenada;
        } catch (std::bad_alloc) {
            throw QString ("Conjunto União Ordenada não foi criado");
        }
    }

    Conjunto *Conjunto::subCadeiaCA()const{
        try {
            Conjunto *Aux = new Conjunto(this->indiceOcupacao);
            Conjunto *ConjuntoSubCadeiaCA = new Conjunto(this->indiceOcupacao);

            for(int pos=0; pos<=this->indiceOcupacao; pos++){
                if(pos<this->indiceOcupacao){
                    if(*(this->array+pos) < *(this->array+pos+1)){
                        *(Aux->array+Aux->indiceOcupacao+1) = *(this->array+pos);
                        Aux->indiceOcupacao++;
                    }
                    else{
                        if(*(this->array+pos+1) < *(this->array+pos+2)){
                            *(Aux->array+Aux->indiceOcupacao+1) = *(this->array+pos);
                            Aux->indiceOcupacao++;
                        }
                        if(Aux->indiceOcupacao > ConjuntoSubCadeiaCA->indiceOcupacao){
                            delete ConjuntoSubCadeiaCA;
                            ConjuntoSubCadeiaCA = Aux;
                            Aux = new Conjunto(this->indiceOcupacao);
                        }
                        else{
                            delete Aux;
                            Aux = new Conjunto(this->indiceOcupacao);
                        }
                    }
                }
                else{
                    if(*(this->array+pos-1) < *(this->array+pos)){
                        *(Aux->array+Aux->indiceOcupacao+1) = *(this->array+pos);
                        Aux->indiceOcupacao++;
                        if(Aux->indiceOcupacao > ConjuntoSubCadeiaCA->indiceOcupacao){
                            delete ConjuntoSubCadeiaCA;
                            ConjuntoSubCadeiaCA = Aux;
                            Aux = new Conjunto(this->indiceOcupacao);
                        }
                    }
                    else{
                        if(Aux->indiceOcupacao > ConjuntoSubCadeiaCA->indiceOcupacao){
                            delete ConjuntoSubCadeiaCA;
                            ConjuntoSubCadeiaCA = Aux;
                            Aux = new Conjunto(this->indiceOcupacao);
                        }
                    }
                }
            }
            delete Aux;
            return ConjuntoSubCadeiaCA;
        } catch (std::bad_alloc) {
            throw QString ("Conjunto Sub Cadeia não foi criado");
        }
    }

    Conjunto *Conjunto::subCadeiaCB()const{
        try {
            Conjunto *Aux = new Conjunto(this->indiceOcupacao);
            Conjunto *ConjuntoSubCadeiaCB = new Conjunto(this->indiceOcupacao);

            for(int pos=0; pos<this->indiceOcupacao; pos++){
                if(pos<this->indiceOcupacao){
                    if(*(this->array+pos) > *(this->array+pos+1)){
                        *(Aux->array+Aux->indiceOcupacao+1) = *(this->array+pos);
                        Aux->indiceOcupacao++;
                    }
                    else{
                        if(*(this->array+pos+1) > *(this->array+pos+2)){
                            *(Aux->array+Aux->indiceOcupacao+1) = *(this->array+pos);
                            Aux->indiceOcupacao++;
                        }
                        if(Aux->indiceOcupacao > ConjuntoSubCadeiaCB->indiceOcupacao){
                            delete ConjuntoSubCadeiaCB;
                            ConjuntoSubCadeiaCB = Aux;
                            Aux = new Conjunto(this->indiceOcupacao);
                        }
                        else{
                            delete Aux;
                            Aux = new Conjunto(this->indiceOcupacao);
                        }
                    }
                }
                else{
                    if(*(this->array+pos-1) > *(this->array+pos)){
                        *(Aux->array+Aux->indiceOcupacao+1) = *(this->array+pos);
                        Aux->indiceOcupacao++;
                        if(Aux->indiceOcupacao > ConjuntoSubCadeiaCB->indiceOcupacao){
                            delete ConjuntoSubCadeiaCB;
                            ConjuntoSubCadeiaCB = Aux;
                            Aux = new Conjunto(this->indiceOcupacao);
                        }
                    }
                    else{
                        if(Aux->indiceOcupacao > ConjuntoSubCadeiaCB->indiceOcupacao){
                            delete ConjuntoSubCadeiaCB;
                            ConjuntoSubCadeiaCB = Aux;
                            Aux = new Conjunto(this->indiceOcupacao);
                        }
                    }
                }
            }
            delete Aux;
            return ConjuntoSubCadeiaCB;
        } catch (std::bad_alloc) {
            throw QString ("Conjunto Sub Cadeia não foi criado");
        }
    }
}
