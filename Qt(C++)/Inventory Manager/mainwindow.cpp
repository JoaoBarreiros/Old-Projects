#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <fstream>
#include "acerca.h"
CListaProdutos *aux=new CListaProdutos();
CListaProdutos *alerta=new  CListaProdutos();
CListaFornecedores *auxiliar=new CListaFornecedores();
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setCentralWidget(ui->tabWidget);
    ui->treeWidget->setSortingEnabled(1);//Ordenar->True
    ui->treeWidget->setColumnWidth(0,500);
    ui->treeWidget->sortByColumn(0,Qt::AscendingOrder);//Ordena a 1º coluna por ordem alfabetica (DEFAULT)
    MainWindow::lerconfig();
    MainWindow::leRelatorio();
}
//==========================================================================
MainWindow::~MainWindow()
{
    delete ui;
}
//==========================================================================
void MainWindow::on_lineEdit_textChanged()
{
    if(ui->lineEdit->text().isEmpty())//se está vazia retornamos a lista original
    {
        ui->treeWidget->clear();//clear dos dados procurados
        CNoLista *atual = aux->cabeca;
        if (aux->cabeca == NULL)
            return;//lista original vazia
        else
        {
            while (atual != NULL)
            {
                MainWindow::Add_Root_and_child(atual); //repõe a lista original
                atual = atual->proximo;
            }
        }
    }
else
    procura(ui->lineEdit->text());//procura o item desejado
}
//==========================================================================
void MainWindow::procura(QString text)
{
    ui->treeWidget->clear();
    if (aux->procuraItemMOD2(text)==0)//verifica se existe
     {
          return;//se não encontrou
     }
     else //se encontrou
     {
        int ListaSize=aux->procuraItemMOD2(text);
        do{
         CNoLista* aux2=aux->procuraItemMOD(text,ListaSize);//procura na lista
         MainWindow::Add_Root_and_child(aux2);//mostra os elementos procurados
         ListaSize--;
        }while(ListaSize>0);//ListaSize é o número de elementos da lista que começam pelo valor da variavel text
     }                      //Desta forma podemos retornar todos os elementos que começam por essa string
}
//==========================================================================
int CListaProdutos :: procuraItemMOD2(QString text)//exclusivo para a procura no inventário
{
    int conta=0;
    CNoLista *atual = cabeca;
    if (cabeca == NULL)
        return 0;
    else {
        while (atual != NULL)
        {
            if ((QString::compare(text, atual->nome, Qt::CaseInsensitive)==0)||atual->nome.startsWith(text, Qt::CaseInsensitive)||text.toInt()==atual->codigo)
                conta++;
            atual = atual->proximo;
        }
        return conta;
    }
}
//==========================================================================
CNoLista* CListaProdutos::procuraItemMOD(QString nome,int size)//exclusivo para a procura no inventário
{
    CNoLista *atual = cabeca;
    while(atual != NULL)
    {
        if (QString::compare(nome, atual->nome, Qt::CaseInsensitive)==0||atual->nome.startsWith(nome, Qt::CaseInsensitive)||nome.toInt()==atual->codigo)
            size--;
            if(size==0)
                return atual;
        else atual = atual->proximo;
    }
}
//==========================================================================
void MainWindow::on_pushButton_clicked()//Comprar
{
    ui->label_2->setText("");//Label de Erros
    if(!(ui->lineEdit_2->text() .isEmpty()||ui->lineEdit_3->text() .isEmpty()))
    {
        if(ui->lineEdit_4->text() .isEmpty())//WARNINGS
        {
            ui->label_2->setText("[WARNING]: É necessário inserir o preço do produto");
            return;
        }
        if(ui->lineEdit_5->text() .isEmpty())//WARNINGS
        {
            ui->label_2->setText("[WARNING]: É necessário inserir a quantidade do produto");
            return;
        }
        if(ui->lineEdit_10->text() .isEmpty())//WARNINGS
        {
            ui->label_2->setText("[WARNING]: É necessário inserir o fornecedor do produto");
            return;
        }
        if(!aux->procuraItem2(ui->lineEdit_2->text()))//Procura se o nome do item já existe
        {
            //Se o produto não existir
            QString nome = ui->lineEdit_2->text();
            int codigo = ui->lineEdit_3->text().toInt();
            int preco = ui->lineEdit_4->text().toInt();
            QString fornecedor = ui->lineEdit_10->text();
            int quantidade=ui->lineEdit_5->text().toInt();
            if(aux->procuraItem2(QString::number(codigo)))//WARNINGS
            {
                ui->label_2->setText("[WARNING]: Não pode inserir 2 produtos com o mesmo codigo");
                return;
            }
            if(preco<=0)//WARNINGS
            {
                ui->label_2->setText("[WARNING]: O preço não pode ser negativo");
                return;
            }
            if(quantidade<=0)//WARNINGS
            {
                ui->label_2->setText("[WARNING]: A quantidade inserida tem que ser maior que 0");
                return;
            }
            if(!auxiliar->procuraFornecedor2(fornecedor))
            {
                ui->label_2->setText("[WARNING]: O fornecedor que inseriu não existe na lista");
                return;
            }
            MainWindow::escreveRelatorio(nome,preco,quantidade,0,0);
            aux->CListaProdutos::insereItem(nome,codigo,preco,quantidade,fornecedor,0);//insere item nas listas ligadas
            on_actionGuardar_triggered();
            Add_Root_and_child2(nome,codigo,preco,quantidade);//mostra o item na treeWidget
        }
        else//Se o item já existir
        {
            QString nome=ui->lineEdit_2->text();
            CNoLista *ptr2 = aux->procuraItem(nome);//Retorna o nó com o nome inserido
            int codigo=ui->lineEdit_3->text().toInt();
            int preco=ui->lineEdit_4->text().toInt()+ptr2->preco;
            int quantidade=ui->lineEdit_5->text().toInt();  
            QString fornecedor = ptr2->fornecedor;
            int preco_pub = ptr2->preco_pub;
            int Stock_Min = ui->lineEdit_19->text().toInt();

            if(!aux->procuraItem2(QString::number(codigo))|| ptr2->codigo!=codigo)//WARNINGS
            {
                ui->label_2->setText("[WARNING]: Não pode inserir o mesmo produto com codigos diferentes");
                return;
            }
            if(preco<=0)//WARNINGS
            {
                ui->label_2->setText("[WARNING]: O preço não pode ser negativo");
                return;
            }
            if(quantidade<=0)//WARNINGS
            {
                ui->label_2->setText("[WARNING]: A quantidade inserida tem que ser maior que 0");
                return;
            }
            quantidade += ptr2->quantidade;//Somar Quantidades
            if(quantidade<=0)//WARNINGS
            {
                ui->label_2->setText("[WARNING]: A quantidade inserida tem que ser maior que 0");
                return;
            }
            if(alerta->procuraItem2(nome))
            {
                if(quantidade>=Stock_Min)
                {
                    alerta->apagaItem(nome);
                    MainWindow::atualizaAlerta();
                }
            }
            MainWindow::escreveRelatorio(nome,preco,ui->lineEdit_5->text().toInt(),preco_pub,0);
            aux->EditaItem(ptr2,nome,codigo,preco,quantidade,fornecedor,preco_pub);
            on_actionGuardar_triggered();
            ui->treeWidget->clear();
            CNoLista *atual = aux->cabeca;
            if (aux->cabeca == NULL)
                 return;//lista original vazia
            else
            {
                while (atual != NULL)
                {
                     MainWindow::Add_Root_and_child(atual);//põe a nova lista
                     atual = atual->proximo;
                }
            }
        }
    }
    else//WARNINGS
    {
            ui->label_2->setText("[WARNING]: É necessário inserir um nome e/ou codigo do produto");
            return;
    }
}
//==========================================================================
void MainWindow::on_pushButton_2_clicked()//Vender
{
    //lineEdit 6-9
    QString nome;
    int codigo;
    int preco_pub;
    int quantidade;
    ui->label_3->setText("");//label de Erro
    if(!(ui->lineEdit_6->text() .isEmpty()&&ui->lineEdit_7->text() .isEmpty()))
    {
        if(ui->lineEdit_8->text().isEmpty())//WARNINGS
        {
            ui->label_3->setText("[WARNING]: É necessário inserir o preço do produto");
            return;
        }
        if(ui->lineEdit_9->text().isEmpty())//WARNINGS
        {
            ui->label_3->setText("[WARNING]: É necessário inserir a quantidade do produto");
            return;
        }
        if(!ui->lineEdit_7->text().isEmpty()&&!aux->procuraItem2(ui->lineEdit_7->text()))
        {
            ui->label_3->setText("[WARNING]: O codigo do produto não existe na lista");
            return;
        }
        if(ui->lineEdit_6->text() .isEmpty())//Se o nome estiver vazio
        {
            codigo = ui->lineEdit_7->text().toInt();
            if(aux->procuraItem2(QString::number(ui->lineEdit_7->text().toInt())))
            {
                CNoLista *ptr2 = aux->procuraItem(QString::number(codigo));
                nome=ptr2->nome;
            }
            else
            {
                ui->label_3->setText("[WARNING]: O codigo inserido não foi encontrado no inventário");
                return;
            }
        }
        else
        {
            nome = ui->lineEdit_6->text();
            if(ui->lineEdit_7->text().isEmpty() && aux->procuraItem2(nome))
            {
                CNoLista *ptr3 = aux->procuraItem(nome);
                codigo=ptr3->codigo;
            }
            else if(ui->lineEdit_7->text().isEmpty() && !aux->procuraItem2(nome))
            {
                ui->label_3->setText("[WARNING]: O nome inserido não foi encontrado no inventário");
                return;
            }
            else
            {
                codigo = ui->lineEdit_7->text().toInt();
                if(aux->procuraItem2(nome))
                {
                    CNoLista *ptr3 = aux->procuraItem(nome);
                    if(codigo!=ptr3->codigo)
                    {
                        ui->label_3->setText("[WARNING]: O codigo do produto não condiz com o seu nome");
                        return;
                    }
                }
            }
        }
       CNoLista *ptr = aux->procuraItem(nome);
       preco_pub = ui->lineEdit_8->text().toInt();//preço total de venda
       quantidade = ui->lineEdit_9->text().toInt();
       int q = ptr->quantidade - quantidade;
       preco_pub+=ptr->preco_pub;
       QString nome = ptr->nome;
       int preco = ptr->preco;
       int q2=ptr->quantidade;
       QString fornecedor = ptr->fornecedor;

       if(preco_pub<=0)//WARNINGS
       {
           ui->label_3->setText("[WARNING]: O preço não pode ser negativo");
           return;
       }
       if(quantidade<=0)//WARNINGS
       {
            ui->label_3->setText("[WARNING]: A quantidade inserida tem que ser maior que 0");
            return;
       }
       if(q<=0)
       {
           ui->label_3->setText("[WARNING]: A quantidade resultante não pode ser negativa");
           return;
       }
       aux->CListaProdutos::apagaItem(nome);
       //Alerta Automatico
       if(ui->checkBox->isChecked()&&q<ui->lineEdit_19->text().toInt())//se alerta automatico for true e a quantidade resultante < stock_min
       {
           int stock_max=ui->lineEdit_20->text().toInt();
           int x=preco*(stock_max-q)/q2;
           MainWindow::escreveRelatorio(nome,preco,quantidade,ui->lineEdit_8->text().toInt(),1);
           MainWindow::escreveRelatorio(nome,x,stock_max-q,0,0);
           aux->CListaProdutos::insereItem(nome,codigo,x,stock_max,fornecedor,preco_pub);//reinsere item com novos dados,com preço de compra proporcional à ultima compra realizada
       }
       else if(!ui->checkBox->isChecked()&&q<ui->lineEdit_19->text().toInt())//alerta a pedido
       {
           int stock_max=ui->lineEdit_20->text().toInt();
           int x=preco*(stock_max-q)/q2;
           QTreeWidgetItem *itm = new QTreeWidgetItem(ui->treeWidget_4);
           itm->setText(0,nome);
           itm->setText(1,QString::number(q));
           itm->setText(2,QString::number(stock_max-q));
           ui->treeWidget_4->addTopLevelItem(itm);
           MainWindow::escreveRelatorio(nome,preco,quantidade,ui->lineEdit_8->text().toInt(),1);
           if (!alerta->procuraItem2(nome))
               alerta->insereItem(nome,codigo,x,q,fornecedor,preco_pub);
           else
           {
               CNoLista *ptr5 =alerta->procuraItem(nome);
               alerta->EditaItem(ptr5,nome,codigo,x,q,fornecedor,preco_pub);
               MainWindow::atualizaAlerta();
           }
           aux->insereItem(nome,codigo,preco,q,fornecedor,preco_pub);
       }
       else
       {
           MainWindow::escreveRelatorio(nome,preco,quantidade,ui->lineEdit_8->text().toInt(),1);
           aux->CListaProdutos::insereItem(nome,codigo,preco,q,fornecedor,preco_pub);//reinsere item com novos valores
           MainWindow::atualizaAlerta();
       }
       MainWindow::on_actionGuardar_triggered();//guarda automaticamente
       ui->treeWidget->clear();//Atualiza items na TreeWidget
       CNoLista *atual = aux->cabeca;
       while (atual != NULL)
       {
            MainWindow::Add_Root_and_child(atual);//põe a nova lista
            atual = atual->proximo;
       }

    }
    else//WARNINGS
    {
            ui->label_3->setText("[WARNING]: É necessário inserir um nome ou codigo do produto");
            return;
    }
}
//==========================================================================
void MainWindow::on_pushButton_5_clicked()//Editar Produtos
{
    //lineEdit 11 nome
    //lineEdit 15-18
    //lineEdit 21 preço de venda
    ui->label_12->setText("");
    if(ui->lineEdit_11->text().isEmpty())//WARNINGS
    {
        ui->label_12->setText("[WARNING]: É necessário inserir o nome do produto");
        return;
    }
    else
    {
        QString nome = ui->lineEdit_11->text();
        if(!aux->procuraItem2(nome))//WARNINGS
        {
           ui->label_12->setText("[WARNING]: O nome do produto que inseriu não se encontra no inventário");
           return;
        }
        else
        {
            int codigo;
            int preco;
            int quantidade;
            int preco_pub;
            QString fornecedor;
            CNoLista *ptr = aux->procuraItem(nome);
            if(!ui->lineEdit_15->text().isEmpty())
            {
                codigo = ui->lineEdit_15->text().toInt();
            }
            else
            {
                codigo = ptr->codigo;
            }
            if(!ui->lineEdit_16->text().isEmpty())
            {
                preco = ui->lineEdit_16->text().toInt();
            }
            else
            {
                preco = ptr->preco;
            }
            if(!ui->lineEdit_17->text().isEmpty())
            {
                quantidade = ui->lineEdit_17->text().toInt();
            }
            else
            {
                quantidade = ptr->quantidade;
            }
            if(!ui->lineEdit_18->text().isEmpty())
            {
                fornecedor = ui->lineEdit_18->text();
            }
            else
            {
                fornecedor = ptr->fornecedor;
            }
            if(!ui->lineEdit_21->text().isEmpty())
            {
                preco_pub = ui->lineEdit_21->text().toInt();
            }
            else
            {
                preco_pub = ptr->preco_pub;
            }

            if(aux->procuraItem2(QString::number(codigo))&&ptr->codigo!=codigo)//WARNINGS
            {
                ui->label_12->setText("[WARNING]: O código inserido já se encontra num produto do inventário");
                return;
            }
            if(preco < 0)//WARNINGS
            {
                ui->label_12->setText("[WARNING]: O preco não pode ser negativo");
                return;
            }
            if(quantidade <= 0)//WARNINGS
            {
                ui->label_12->setText("[WARNING]: A quantidade inserida tem que ser maior que 0 ");
                return;
            }
            MainWindow::escreveRelatorio(nome,preco,quantidade,preco_pub,3);
            aux->EditaItem(ptr,nome,codigo,preco,quantidade,fornecedor,preco_pub);
            ui->treeWidget->clear();
            CNoLista *atual = aux->cabeca;
            if (aux->cabeca == NULL)
                 return;//lista original vazia
            else
            {
                while (atual != NULL)
                {
                     MainWindow::Add_Root_and_child(atual);//põe a nova lista
                     atual = atual->proximo;
                }
            }
        }
    }
}
//==========================================================================
void MainWindow::on_pushButton_6_clicked()//Apagar
{
    ui->label_12->setText("");
    if(ui->lineEdit_11->text().isEmpty())//WARNINGS
    {
        ui->label_12->setText("[WARNING]: É necessário inserir o nome do produto");
        return;
    }
    else
    {
        if(aux->procuraItem2(ui->lineEdit_11->text()))
        {
            aux->apagaItem(ui->lineEdit_11->text());
        }
        if(alerta->procuraItem2(ui->lineEdit_11->text()))
        {
            alerta->apagaItem(ui->lineEdit_11->text());
            MainWindow::atualizaAlerta();
        }
        else//WARNINGS
        {
            ui->label_12->setText("[WARNING]: O nome que inseriu não existe no inventário");
            return;
            //ERRO NOME NÃO ENCONTRADO
        }
        ui->treeWidget->clear();
        CNoLista *atual = aux->cabeca;
        if (aux->cabeca == NULL)
             return;//lista original vazia
        else
        {
            while (atual != NULL)
            {
                 MainWindow::Add_Root_and_child(atual);//põe a nova lista
                 atual = atual->proximo;
            }
        }
    }
}
//==========================================================================
void MainWindow::on_pushButton_4_clicked()//Inserir Fornecedor
{
    ui->label_11->setText("");
    //lineEdit 12-14
    if(ui->lineEdit_12->text().isEmpty())//WARNINGS
    {
         ui->label_11->setText("[WARNING]: É necessário inserir o nome do fornecedor");
         return;
    }
    else
    {
        QString fornecedor = ui->lineEdit_12->text();
        QString morada = ui->lineEdit_13->text();
        int telefone = ui->lineEdit_14->text().toInt();
        if(ui->lineEdit_13->text().isEmpty()||ui->lineEdit_14->text().isEmpty())//WARNINGS
        {
            ui->label_11->setText("[WARNING]: É necessário inserir a morada e/ou o telefone do fornecedor");
            return;
        }
        if((ui->lineEdit_14->text()).length() != 9)//WARNINGS
        {
            ui->label_11->setText("[WARNING]: O número de telefone tem de ter 9 dígitos");
            return;
        }
        if(auxiliar->procuraFornecedor2(fornecedor))
        {
            ui->label_11->setText("[WARNING]: O nome do fornecedor que introduziu já se econtra na lista");
            return;
        }
        else
        {
            auxiliar->inserefornecedor(fornecedor,morada,telefone);
            ui->listWidget->addItem(fornecedor);
        }
    }
}
//==========================================================================
void MainWindow::on_listWidget_itemClicked(QListWidgetItem *item)//estatisticas por fornecedor
{
    ui->treeWidget_2->clear();
    int ListaSize = aux->procuraItemsporFornecedor2(item->text());
    if(ListaSize==0)
        return;
    else
    {
        while(ListaSize>0)
        {
            CNoLista *ptr = aux->procuraItemsporFornecedor(item->text(),ListaSize);
            ListaSize--;
            QTreeWidgetItem *itm = new QTreeWidgetItem(ui->treeWidget_2);
            itm->setText(0,ptr->nome);
            itm->setText(1,QString::number(ptr->preco)+"€");
            itm->setText(2,QString::number(ptr->preco_pub)+"€");
            itm->setText(3,QString::number(ptr->preco_pub-ptr->preco)+"€");
            ui->treeWidget_2->addTopLevelItem(itm);
        }
    }

}
//==========================================================================
CListaProdutos::CListaProdutos()
{
    cabeca = NULL;
}
//==========================================================================
CListaProdutos :: ~CListaProdutos()
{
    CNoLista *atual, *proximo;
    atual = cabeca;
    while (atual != NULL)
    {
        proximo = atual->proximo;
        delete atual;
        atual = proximo;
    }
}
//==========================================================================
CListaFornecedores::CListaFornecedores()
{
    cabeca = NULL;
}
//==========================================================================
CListaFornecedores :: ~CListaFornecedores()
{
    CNoListafornecedores *atual, *proximo;
    atual = cabeca;
    while (atual != NULL)
    {
        proximo = atual->proximo;
        delete atual;
        atual = proximo;
    }
}
//==========================================================================
void CListaProdutos :: insereItem(QString nome,int codigo,int preco,int quantidade, QString fornecedor,int preco_pub)
{
    CNoLista *novo=new CNoLista;
    CNoLista *atual;
    novo->nome = nome;
    novo->codigo = codigo;
    novo->preco = preco;
    novo->quantidade = quantidade;

    novo->fornecedor = fornecedor;
    novo->preco_pub = preco_pub;
    //DATA
    novo->dia = QDate::currentDate().daysInMonth();
    novo->mes = QDate::currentDate().month();
    novo->ano = QDate::currentDate().year();

    novo->proximo = NULL;
    if (cabeca == NULL)
        cabeca = novo;
    else
    {
        atual = cabeca;
        while (atual->proximo != NULL)
            atual = atual->proximo;
        atual->proximo = novo;
    }
}
//==========================================================================
CNoLista* CListaProdutos::procuraItem(QString text)
{
    CNoLista *atual = cabeca;
    bool nao_encontrado = true;
    while(atual != NULL && nao_encontrado)
    {
        if (QString::compare(text, atual->nome, Qt::CaseInsensitive)==0||text.toInt()==atual->codigo)
            nao_encontrado = false;
        else atual = atual->proximo;
    }
    return(atual);
}
//==========================================================================
bool CListaProdutos :: procuraItem2(QString text)
{
    CNoLista *atual = cabeca;
    if (cabeca == NULL)
        return false;
    else {
        while (atual != NULL)
        {
            if ((QString::compare(text, atual->nome, Qt::CaseInsensitive)==0)||text.toInt()==atual->codigo)
                return true;
            atual = atual->proximo;
        }
        return false;
    }
}
//==========================================================================
void CListaProdutos :: apagaItem(QString nome)
{
    CNoLista *atual = cabeca;
    CNoLista *anterior;
    if (cabeca == NULL)
        return;
    anterior = NULL;
    while (atual != NULL)
    {
        if (QString::compare(nome, atual->nome, Qt::CaseInsensitive)==0)
        {
            if (anterior == NULL)
                cabeca = atual->proximo;
            else
                anterior->proximo = atual->proximo;
            delete atual;
            return;
        }
        anterior = atual;
        atual = atual->proximo;
    }
}
//==========================================================================
void MainWindow::Add_Root_and_child(CNoLista *ptr)//Mostra o elemento na TreeWidget do Inventário
{
    QTreeWidgetItem *itm = new QTreeWidgetItem(ui->treeWidget);
    itm->setText(0,ptr->nome);
    itm->setText(1,QString::number(ptr->codigo));
    ui->treeWidget->addTopLevelItem(itm);
    QTreeWidgetItem *child_itm = new QTreeWidgetItem();
    child_itm->setText(0,QString::number(ptr->preco)+"€ | "+QString::number(ptr->preco_pub)+"€");
    child_itm->setText(1,QString::number(ptr->quantidade));
    itm->addChild(child_itm);
}
//==========================================================================
void MainWindow::Add_Root_and_child2(QString nome, int codigo,int Preco, int Quantidade)
{
    QTreeWidgetItem *itm = new QTreeWidgetItem(ui->treeWidget);
    itm->setText(0,nome);
    itm->setText(1,QString::number(codigo));
    ui->treeWidget->addTopLevelItem(itm);
    QTreeWidgetItem *child_itm = new QTreeWidgetItem();
    child_itm->setText(0,QString::number(Preco)+"€ | 0€");
    child_itm->setText(1,QString::number(Quantidade));
    itm->addChild(child_itm);
}
//==========================================================================
void CListaProdutos :: EditaItem(CNoLista *ptr,QString nome,int codigo,int preco,int quantidade,QString fornecedor,int preco_pub)
{
    ptr->nome =nome;
    ptr->codigo =codigo;
    ptr->preco = preco;
    ptr->quantidade = quantidade;
    ptr->fornecedor = fornecedor;
    ptr->preco_pub = preco_pub;
    ptr->mes = QDate::currentDate().month();
    ptr->ano = QDate::currentDate().year();
    ptr->dia = QDate::currentDate().day();
}
//==========================================================================
void CListaFornecedores::inserefornecedor(QString fornecedor,QString morada,int telefone)
{
    CNoListafornecedores *novo=new CNoListafornecedores;
    CNoListafornecedores *atual;
    novo->fornecedor = fornecedor;
    novo->morada = morada;
    novo->telefone = telefone;
    novo->proximo = NULL;
    if (cabeca == NULL)
        cabeca = novo;
    else
    {
        atual = cabeca;
        while (atual->proximo != NULL)
            atual = atual->proximo;
        atual->proximo = novo;
    }
}
//==========================================================================
CNoListafornecedores* CListaFornecedores ::procuraFornecedor(QString fornecedor)
{
    CNoListafornecedores *atual = cabeca;
    bool nao_encontrado = true;
    while(atual != NULL && nao_encontrado)
    {
        if (QString::compare(fornecedor, atual->fornecedor, Qt::CaseInsensitive)==0||atual->fornecedor.startsWith(fornecedor, Qt::CaseInsensitive) )
            nao_encontrado = false;
        else atual = atual->proximo;
    }
    return(atual);
}
//==========================================================================
bool CListaFornecedores :: procuraFornecedor2(QString fornecedor)
{
    CNoListafornecedores *atual = cabeca;
    if (cabeca == NULL)
        return false;
    else {
        while (atual != NULL)
        {
            if ((QString::compare(fornecedor, atual->fornecedor, Qt::CaseInsensitive)==0))
                return true;
            atual = atual->proximo;
        }
        return false;
    }
}
//==========================================================================
int CListaProdutos :: procuraItemsporFornecedor2(QString fornecedor)
{
    int conta=0;
    CNoLista *atual = cabeca;
    if (cabeca == NULL)
        return 0;
    else {
        while (atual != NULL)
        {
            if ((QString::compare(fornecedor, atual->fornecedor, Qt::CaseInsensitive)==0))
                conta++;
            atual = atual->proximo;
        }
        return conta;
    }
}
//==========================================================================
CNoLista* CListaProdutos::procuraItemsporFornecedor(QString fornecedor,int tamanho)
{
    CNoLista *atual = cabeca;
    while(atual != NULL)
    {
        if (atual->fornecedor== fornecedor)
            tamanho--;
            if(tamanho==0)
                return atual;
        else atual = atual->proximo;
    }
}//Retorna porque verificámos o nº de produtos de cada fornecedor
//==========================================================================
void MainWindow::on_actionNovo_triggered()//novo
{
    auxiliar->~CListaFornecedores();
    aux->~CListaProdutos();
    alerta->~CListaProdutos();
    ui->treeWidget_4->clear();
    ui->treeWidget->clear();
    ui->treeWidget_2->clear();
    ui->listWidget->clear();
    aux=new CListaProdutos();
    auxiliar= new CListaFornecedores();
    alerta= new CListaProdutos();
}

//==========================================================================
void MainWindow::on_actionSair_triggered()//sair
{
    MainWindow ::close();
}
//==========================================================================
void MainWindow::on_actionGuardar_triggered()//guardar produtos e fornecedores
{
    ofstream guardarF("Fornecedores.dat");//Guarda Dados dos Fornecedores
    CNoListafornecedores *atual2 = auxiliar->cabeca;
    if (auxiliar->cabeca == NULL)
        return;//Se não há fornecedores, também não há produtos.
    else
    {
        while (atual2 != NULL)
        {
            MainWindow::conversor(atual2->fornecedor,1);
            MainWindow::conversor(atual2->morada,1);
            guardarF<<atual2->fornecedor.toStdString()<<" "<<atual2->morada.toStdString()<<" "<<atual2->telefone<<endl;
            atual2 = atual2->proximo;
        }
    }
    guardarF.close();

    ofstream guardarP("Produtos.dat");//Guarda Dados dos Produtos
    CNoLista *atual = aux->cabeca;
    if (aux->cabeca == NULL)
        return;
    else
    {
        while (atual != NULL)
        {
            MainWindow::conversor(atual->fornecedor,1);
            MainWindow::conversor(atual->nome,1);
            guardarP<<atual->nome.toStdString()<<" "<<atual->codigo<<" "<<atual->preco<<" "<<atual->fornecedor.toStdString()<<" "<<atual->quantidade<<" "<<atual->preco_pub<<endl;
            atual = atual->proximo;
        }
    }
    guardarP.close();
}
//==========================================================================
void MainWindow::on_actionAbrir_triggered()//abrir
{
    MainWindow::on_actionNovo_triggered();
    string fornecedor;
    string morada;
    int telefone;
    QString F;
    QString M;
     ifstream Abrir("Fornecedores.dat");
    while(Abrir>> fornecedor >> morada >> telefone)
    {
            F= QString::fromStdString(fornecedor);
            M= QString::fromStdString(morada);
            MainWindow::conversor(F,0);
            MainWindow::conversor(M,0);
            auxiliar->inserefornecedor(F,M,telefone);
            ui->listWidget->addItem(F);
    }
    string produto;
    int codigo;
    int preco;
    int quantidade;
    int preco_pub;
    QString P;

    ifstream Abrir2("Produtos.dat");
    while(Abrir2>> produto >> codigo >> preco >> fornecedor >> quantidade >> preco_pub)
    {
        P = QString::fromStdString(produto);
        F =QString::fromStdString(fornecedor);
        MainWindow::conversor(P,0);
        MainWindow::conversor(F,0);
        aux->insereItem(P,codigo,preco,quantidade,F,preco_pub);
        MainWindow::on_lineEdit_textChanged();
    }
}
//==========================================================================
void MainWindow::on_actionAcerca_triggered()//acerca
{
    acerca = new Acerca(this);
    acerca->show();
}
//==========================================================================
void MainWindow::on_horizontalSlider_sliderMoved(int position)//faturação
{
    int mes = QDate::currentDate().month();
    int ano = QDate::currentDate().year();

    int pos=position/10;
    int mesp=(pos-11)+mes;
    if(mesp<=0)
    {
       mesp+=12;
       ano--;
    }
    QString mess = QDate::currentDate().longMonthName(mesp);
    ui->label_5->setText(mess+" de "+QString::number(ano));
    ui->treeWidget_3->clear();
    int ListaSize=aux->procuraItemPorMes2(mesp);
    while(ListaSize>0)
    {
        CNoLista* aux3=aux->procuraItemPorMes(mesp,ListaSize);//procura na lista
        QTreeWidgetItem *itm = new QTreeWidgetItem(ui->treeWidget_3);
        itm->setText(0,aux3->nome);
        itm->setText(1,QString::number(aux3->preco)+"€");
        itm->setText(2,QString::number(aux3->preco_pub)+"€");
        itm->setText(3,QString::number(aux3->preco_pub-aux3->preco)+"€");
        ui->treeWidget->addTopLevelItem(itm);
        ListaSize--;
    }
}
//==========================================================================
int CListaProdutos::procuraItemPorMes2(int mesp)//faturaçao
{
    int conta=0;
    CNoLista *atual = cabeca;
    if (cabeca == NULL)
        return 0;
    else {
        while (atual != NULL)
        {
            if (mesp==atual->mes)
                conta++;
            atual = atual->proximo;
        }
        return conta;
    }
}
//==========================================================================
CNoLista* CListaProdutos::procuraItemPorMes(int mesp,int size)//faturação
{
    CNoLista *atual = cabeca;
    while(atual != NULL)
    {
        if (mesp==atual->mes)
            size--;
            if(size==0)
                return atual;
        else atual = atual->proximo;
    }
}
//==========================================================================

void MainWindow::on_pushButton_3_clicked()//guarda config
{
    ui->label_8->setText("");
    if(ui->lineEdit_19->text().isEmpty()||ui->lineEdit_20->text().isEmpty())
    {
        ui->label_8->setText("[WARNING]: O stock mínimo e/ou stock máximo não podem estar vazios ");
        return;
    }
    if(ui->lineEdit_19->text().toInt()>=ui->lineEdit_20->text().toInt())
    {
        ui->label_8->setText("[WARNING]: O Stock mínimo não pode ser maior que o stock máximo ");
        return;
    }
    ofstream guardarC("config.txt");
    guardarC<<ui->lineEdit_19->text().toStdString()<<endl;
    guardarC<<ui->lineEdit_20->text().toStdString()<<endl;
    guardarC<<ui->lineEdit_22->text().toStdString()<<endl;
    if(ui->checkBox->isChecked())
        guardarC<<1<<endl;
    else
        guardarC<<0<<endl;

    guardarC.close();
}
//==========================================================================
void MainWindow::lerconfig()
{
    int stock_min;
    int stock_max;
    double IVA;
    bool alerta;
    ifstream Abrir("config.txt");
    if(Abrir.fail())
    {
        stock_min=100;
        stock_max=1000;
        IVA=0.23;
        alerta=true;
    }
    else
    {
         Abrir>> stock_min >> stock_max >> IVA>>alerta;
    }
        ui->lineEdit_19->setText(QString::number(stock_min));
        ui->lineEdit_20->setText(QString::number(stock_max));
        ui->lineEdit_22->setText(QString::number(IVA));
        ui->checkBox->setChecked(alerta);
}
//==========================================================================
void MainWindow::on_pushButton_7_clicked()//Compra items em falta (alertas)
{
   ui->treeWidget_4->clear();
   int Stock_Max = ui->lineEdit_20->text().toInt();
   CNoLista *atual = alerta->cabeca;
   if (alerta->cabeca == NULL)
       return;
   else
   {
       while (atual != NULL)
       {
         MainWindow::escreveRelatorio(atual->nome,atual->preco,Stock_Max,0,2);
         if(!aux->procuraItem2(atual->nome))
            aux->insereItem(atual->nome,atual->codigo,atual->preco,Stock_Max,atual->fornecedor,atual->preco_pub);
         else
         {
             CNoLista *ptr=aux->procuraItem(atual->nome);
             aux->EditaItem(ptr,atual->nome,atual->codigo,atual->preco,Stock_Max,atual->fornecedor,atual->preco_pub);

         }
         MainWindow::on_lineEdit_textChanged();
         atual = atual->proximo;
       }
   }
   alerta->~CListaProdutos();
   alerta=new CListaProdutos();
}
//==========================================================================
void MainWindow::conversor(QString &str,bool guardar)//Para guardar dados
{
    if(guardar)
    {
        for(int i=0;i<str.length();i++)
        {
            if (str[i] == ' ' )
                str[i] = '_';
        }
    }
    else// o Operador << lê até encontrar um espaço, sem este conversor o programa perderia parte dos dados ao abrir
    {
        for(int i=0;i<str.length();i++)
        {
            if (str[i] == '_' )
                str[i] = ' ';
        }
    }
}
//==========================================================================
void MainWindow::escreveRelatorio(QString nome,int preco,int quantidade,int preco_pub,int op)
{
    double IVA = ui->lineEdit_22->text().toDouble();
    int mes = QDate::currentDate().month();
    int ano = QDate::currentDate().year();
    int dia = QDate::currentDate().day();
    int hora = QTime::currentTime().hour();
    int min = QTime::currentTime().minute();

    ofstream relatorio("relatorio.txt", std::ofstream::app);
    if (op == 0)
    {
        relatorio<<ano<<"-"<<mes<<"-"<<dia<<" "<<hora<<":"<<min<<" Compra: "<<quantidade<<" de "<<nome.toStdString()<<" "<<preco<<"€ ,IVA="<<IVA<<endl;
    }
    else if (op == 1)
    {
        relatorio<<ano<<"-"<<mes<<"-"<<dia<<" "<<hora<<":"<<min<<" Venda: "<<quantidade<<" de "<<nome.toStdString()<<" "<<preco_pub<<"€ ,IVA="<<IVA<<endl;
    }
    else if (op == 2)
    {
        relatorio<<ano<<"-"<<mes<<"-"<<dia<<" "<<hora<<":"<<min<<" Alerta: "<<nome.toStdString()<<", Nova quantidade:"<<quantidade<<" Preço total de Aquisição:"<<preco<<"€ ,IVA="<<IVA<<endl;
    }
    else if (op == 3)
    {
        relatorio<<ano<<"-"<<mes<<"-"<<dia<<" "<<hora<<":"<<min<<" Editar: "<<nome.toStdString()<<", Nova quantidade:"<<quantidade<<" Preço total de Aquisição:"<<preco<<"€ Preço de Venda:"<<preco_pub<<" ,IVA="<<IVA<<endl;
    }
    relatorio.close();
}
//==========================================================================
void MainWindow::atualizaAlerta()
{
    ui->treeWidget_4->clear();
    int Stock_Max = ui->lineEdit_20->text().toInt();
    CNoLista *atual = alerta->cabeca;
    if (alerta->cabeca == NULL)
        return;//lista original vazia
    else
    {
        while (atual != NULL)
        {
            QTreeWidgetItem *itm = new QTreeWidgetItem(ui->treeWidget_4);
            itm->setText(0,atual->nome);
            itm->setText(1,QString::number(atual->quantidade));
            itm->setText(2,QString::number(Stock_Max - atual->quantidade));
            ui->treeWidget_4->addTopLevelItem(itm);
            atual = atual->proximo;
        }
    }
}
//==========================================================================
void MainWindow::leRelatorio()
{
    string aux;
    string ano;
    int valor;
    bool apagar=0;
    ifstream ler("relatorio.txt");
    if(ler.fail())
        return;
    else
        ler>>aux;
    for(int i=0;i<aux.length();i++)
    {
        if(aux[i]=='-')
        {
            for(int j=0;j<i;j++)
            {
                ano+=aux[j];
            }
            valor=atoi(ano.c_str());
            if(QDate::currentDate().year()==valor+1)
            {
                apagar=1;
            }
            break;
        }
    }
    ler.close();
    if(apagar)
    {
        std::ofstream apagar;
        apagar.open("relatorio.txt", std::ofstream::out | std::ofstream::trunc);
        apagar.close();
    }
}
//==========================================================================
