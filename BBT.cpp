/* ==========================================================================================
INFORMAÇÕES
Codigo desenvolvido por: Lislaila Tarsila Pereira
Turma: Ciencia da Computação
Ideia: Criar um programa para gerenciamento de estoque de uma biblioteca, 
    onde voce pode adicionar um registro com os campos: livro, autor, genero do livro, 
    preco e quantidade disponivel em estoque. No programa voce pode adicionar livros, 
    pesquisar algun titulo, ver uma lista de todos os registros adicionados,
    editar e apagar algum registro.
===============================================================================================
*/

#include <iostream>
#include <fstream>
#include <cstring>
#include <stdio.h>
using namespace std;

struct bbt
{
    char livro[30], autor[30];
    char genero[30];
    float preco;
    int quant_estoque;
};

int menu();
void add_livros();
void visualizar_livros();
void procurar_livros();
void editar_livros();
void apagar_registro();

int main(){
    int controle = 1;
    int opcao;
    while (controle > 0)
    {
        opcao = menu();
        switch (opcao)
        {
            case 1:
                add_livros();    
                break;
            
            case 2:
                visualizar_livros();
                break;

            case 3:
                procurar_livros();
                break;

            case 4:
                editar_livros();
                break;

            case 5:
                apagar_registro();
                break;

            default:
                controle = 0;
                break;
        }
    }
    return 0;
}

int menu(){
    int menu_resposta;
    cout<<"\n=============BBT-APP================\n";
    cout<<"|                                   |\n";
    cout<<"|      1 - Adicionar livro          |\n";     
    cout<<"|      2 - Visualizar livros        |\n";
    cout<<"|      3 - Procurar livro           |\n";
    cout<<"|      4 - Editar Livros            |\n";
    cout<<"|      5 - Excluir                  |\n";
    cout<<"|      6 - Sair do programa         |\n";
    cout<<"|                                   |\n";
    cout<<"=====================================\n";
    cout<<"Digite o numero de sua opcao: ";
    cin>>menu_resposta;
    while (menu_resposta <= 0 or menu_resposta > 6)
    {
        cout<<"Opcao invalida: ";
        cin>>menu_resposta;
    }
    return menu_resposta;
}

void add_livros(){
    bbt livros;
    ofstream escrita("BBT-APP.bin", ios::binary | ios::app);
    if (escrita)
    {
        char escolha = 's';
        while (escolha == 's')
        {
            cout<<"\nNome: ";
            cin.ignore();
            cin.getline(livros.livro, 30);
            cout<<"\nAutor: ";
            cin.getline(livros.autor, 30);
            cout<<"\nGenero: ";
            cin.getline(livros.genero, 30);
            cout<<"\nPreco: ";
            cin>>livros.preco;
            cout<<"\nQuantidade disponivel no estoque: ";
            cin>>livros.quant_estoque;
            //--------------------------------------------
            escrita.write((char *) (&livros), sizeof(bbt));
            cout<<"Quer adicionar mais registros (s/n) ? ";
            cin.ignore();
            cin>>escolha;
        }
        escrita.close(); 
    }
    else
    {
        cout<<"ERROR NOT FOUND";
    }
}

void visualizar_livros(){
    bbt livros;
    ifstream leitura("BBT-APP.bin", ios::in | ios::binary);
    int quant = 0;
    if (leitura)
    {
        while (leitura.read((char *) (&livros), sizeof(bbt)))
        {
            cout<<"\nLivro: "<<livros.livro<<"\n";
            cout<<"Autor: "<<livros.autor<<"\n";
            cout<<"Genero: "<<livros.genero<<"\n";
            cout<<"Preco: "<<livros.preco<<"\n";
            cout<<"Quantidade disponivel: "<<livros.quant_estoque<<"\n";
            cout<<"=======================================";
            quant++;
        }
        leitura.close();
        if (quant == 0) cout<<"Nenhum livro foi adicionado.\n\n";
    }       
    else
    {
        cout<<"ERROR NOT FOUND!";
    }
}

void procurar_livros(){
    bbt livros;
    ifstream procurar("BBT-APP.bin", ios::binary | ios::in);
    if (procurar)
    {
        cout<<"Pesquisar por: 1-Titulo, 2-Autor, 3-Genero ? ";
        int resposta;
        cin>>resposta;
        while (resposta < 1 or resposta > 3)
        {
            cout<<"Opcao invalida: ";
            cin>>resposta;
        }
        char *variavel1 = new char;
        char variavel2[30];
        if (resposta == 1)
        {
            cout<<"Digite o nome do livro: ";
            cin.ignore();
            cin.getline(variavel2, 30);
            variavel1 = livros.livro;
        }
        else if (resposta == 2)
        {
            cout<<"Digite o nome do autor: ";
            cin.ignore();
            cin.getline(variavel2, 30);
            variavel1 = livros.autor;
        }
        else
        {
            cout<<"Digite o genero: ";
            cin.ignore();
            cin.getline(variavel2, 30);
            variavel1 = livros.genero;
        }
        bool achou = false;
        while (procurar.read((char *) (&livros), sizeof(bbt)))
        {
            if (strcmp(variavel1, variavel2) == 0)
            {
                cout<<"\nLivro: "<<livros.livro<<"\n";
                cout<<"Autor: "<<livros.autor<<"\n";
                cout<<"Genero: "<<livros.genero<<"\n";
                cout<<"Preco: "<<livros.preco<<"\n";
                cout<<"Quantidade disponivel: "<<livros.quant_estoque<<"\n";
                cout<<"=======================================";
                achou = true;
            }    
        }
        procurar.close();
        delete[]variavel1;
        if (achou == false)
        {
            cout<<"Nao encontrado! ";
        }
        char escolha = 'n';
        cout<<"\nDeseja pesquisar outro titulo (s/n) ? ";
        cin>>escolha;
        if (escolha == 's' or escolha == 'S')
        {
            procurar_livros();
        }
     
    }
    else
    {
        cout<<"ERROR NOT FOUND";
    }
}

void editar_livros(){
    bbt livros;
    fstream editar("BBT-APP.bin", ios::binary | ios::in | ios::out);
    if (editar)
    {
        editar.seekg (0, editar.end);	
        int tamanho = editar.tellg();
        int quant_reg = (int)tamanho / sizeof(bbt);	
        char livroprocurar[30];
        cout<<"Digite o nome de um livro para procurar e editar: ";
        cin.ignore();
        cin.getline(livroprocurar, 30);
        bool achou = false;
        int i = 0;
        while ((i < quant_reg) and (achou == false))
        {
            editar.seekp(i*sizeof(livros));
            editar.read((char *) (&livros), sizeof(bbt));
            if (strcmp(livros.livro, livroprocurar) == 0)
            {
                cout<<"\nLivro: "<<livros.livro<<"\n";
                cout<<"Autor: "<<livros.autor<<"\n";
                cout<<"Genero: "<<livros.genero<<"\n";
                cout<<"Preco: "<<livros.preco<<"\n";
                cout<<"Quantidade disponivel: "<<livros.quant_estoque<<"\n";
                cout<<"=======================================";
                achou = true;
                    
                cout<<"\nDigite novas informacoes:\n";
                cout<<"\nNome: ";
                cin.getline(livros.livro, 30);
                cout<<"\nAutor: ";
                cin.getline(livros.autor, 30);
                cout<<"\nGenero: ";
                cin.getline(livros.genero, 30);
                cout<<"\nPreco: ";
                cin>>livros.preco;
                cout<<"\nQuantidade disponivel no estoque: ";
                cin>>livros.quant_estoque;
                editar.seekp((i)*sizeof(bbt));
                editar.write((char *) (&livros), sizeof(bbt)); 
                editar.clear();
                editar.close();
            }
            i++;
        }        
        if (achou == false)
        {
            cout<<"Nao encontrado!\n";
        }
        char escolha = 'n';
        cout<<"Deseja editar outro titulo (s/n) ?";
        cin>>escolha;
        if (escolha == 's' or escolha == 'S')
        {
            editar_livros();
        }
        
    }
    else
    {
        cout<<"ERROR NOT FOUND\n";
    }
}

void apagar_registro(){
    bbt livros;
    fstream deletar("BBT-APP.bin", ios::binary | ios::in);
    fstream deletar_aux("BBT-APP-AUX.bin", ios::binary | ios::out);
    deletar.seekg(0);
    if (deletar or deletar_aux)
    {
        cout<<" Dejesa apagar: 1-Um registro, 2-Todos os registros ";
        int opcao;
        cin>>opcao;
        while (opcao < 1 or opcao > 2)
        {
            cout<<"Opcao invalida: ";
            cin>>opcao;
        }
        
        if (opcao == 1)
        {    
            char livro_procurar[30];
            cout<<"Digite o nome de um livro para procurar e apagar: ";
            cin.ignore();
            cin.getline(livro_procurar, 30);
            while (deletar.read((char *) (&livros), sizeof(bbt)))
            {
                if (strcmp(livros.livro, livro_procurar) != 0)
                {
                    deletar_aux.write((char *) (&livros), sizeof(bbt));
                }    
            }
        }
        deletar.close();
        deletar_aux.close();
        remove("BBT-APP.bin");
        rename("BBT-APP-AUX.bin", "BBT-APP.bin");
        cout<<"Registro apagado com sucesso!\n";      
    }
    else
    {
        cout<<"ERROR NOT FOUND!";
    }
}