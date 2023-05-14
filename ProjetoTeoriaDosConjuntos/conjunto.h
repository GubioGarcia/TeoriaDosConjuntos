#ifndef CONJUNTO_H
#define CONJUNTO_H

#include <QString>
#include <QMessageBox>

namespace ggs{
    class Conjunto
    {
    private:
        int tamanho;//não terá set pois não pode mudar o tamanho através do set, apenas usando new
        int indiceOcupacao;
        int *array;//não terá get e nem set pois é o endereço do vetor
    public:
        Conjunto(int tamanho);
        ~Conjunto();
        int getTamanho() const;
        int getIndiceOcupacao() const;

        QString getConjunto() const;
        bool buscar(int elemento)const;
        bool verificarOcupacao()const;
        void incluirElemento(int elemento);
        QString obterConjunto()const;
        bool estaVazio()const;

        Conjunto *uniao(Conjunto const*const objeto)const;
        Conjunto *intersecao(Conjunto const*const objeto)const;
        Conjunto *diferenca(Conjunto const*const objeto)const;
        Conjunto *uniaoOrdenada(Conjunto const*const objeto)const;
        Conjunto *subCadeiaCA()const;
        Conjunto *subCadeiaCB()const;

        bool eSubconjunto(Conjunto const*const objeto)const;
        bool eIdentico(Conjunto const*const objeto)const;
        bool eDisjunto(Conjunto const*const objeto)const;
        int amplitude()const;
        float mediaAritmetica()const;
        int produtoEscalar(Conjunto const*const objeto)const;
    };
}
#endif // CONJUNTO_H
