#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QtCore>
#include <QtGui>
#include <QMainWindow>
#include <QTreeWidgetItem>
#include <QListWidgetItem>
#include "acerca.h"
namespace Ui {
class MainWindow;
}

using namespace std;
class CListaProdutos;
class CListaTipos;
class CListaEncomendas;
class CListaFornecedores;

class CNoLista
{
public:
   CNoLista *proximo;
   QString nome;
   int quantidade;
   int codigo;
   int preco;//Preço de aquisição
   int preco_pub;//Preço de venda
   int dia;
   int mes;
   int ano;
   QString fornecedor;
};
class CNoListafornecedores
{
public:
   CNoListafornecedores *proximo;
   QString fornecedor;
   QString morada;
   int telefone;
};
class CListaProdutos
{
    friend class CNoLista;
public:
   CNoLista *cabeca;
   CListaProdutos(void);
   ~CListaProdutos(void);
   CNoLista* procuraItem(QString text);
   CNoLista* procuraItemMOD(QString nome,int size);
   void insereItem(QString nome,int codigo,int preco,int quantidade,QString fornecedor,int preco_pub);
   void apagaItem(QString nome);
   bool procuraItem2(QString text);
   int procuraItemMOD2(QString text);
   CNoLista* procuraItemPorMes(int mesp,int size);
   int procuraItemPorMes2(int mesp);
   CNoLista* procuraItemsporFornecedor(QString fornecedor,int tamanho);
   int procuraItemsporFornecedor2(QString fornecedor);
   void EditaItem(CNoLista *ptr,QString nome,int codigo,int preco,int quantidade,QString fornecedor,int preco_pub);
};

class CListaFornecedores
{
public:
  CNoListafornecedores *cabeca;
  void inserefornecedor(QString fornecedor,QString morada,int telefone);
  CNoListafornecedores* procuraFornecedor(QString fornecedor);
  bool procuraFornecedor2(QString fornecedor);
  CListaFornecedores(void);
  ~CListaFornecedores(void);
};

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void procura(QString text);
    void Add_Root_and_child(CNoLista *ptr);
    void on_lineEdit_textChanged();
    void on_pushButton_2_clicked();
    void on_pushButton_5_clicked();
    void on_pushButton_6_clicked();
    void on_pushButton_4_clicked();
    void on_listWidget_itemClicked(QListWidgetItem *item);
    void on_actionNovo_triggered();
    void on_actionSair_triggered();
    void Add_Root_and_child2(QString nome, int codigo,int Preco, int Quantidade);
    void on_actionGuardar_triggered();
    void on_actionAbrir_triggered();
    void on_actionAcerca_triggered();
    void on_horizontalSlider_sliderMoved(int position);
    void on_pushButton_3_clicked();
    void lerconfig();
    void on_pushButton_7_clicked();
    void conversor(QString &str,bool guardar);
    void escreveRelatorio(QString nome, int preco, int quantidade, int preco_pub, int op);
    void atualizaAlerta();
    void leRelatorio();

private:
    Ui::MainWindow *ui;
    Acerca *acerca;
};
#endif // MAINWINDOW_H
