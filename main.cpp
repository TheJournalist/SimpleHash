#include <stdlib.h>
#include <iostream>
#include <cstdlib>
#include <locale.h>
#include <limits>
#include <math.h>
#include <string.h>

using namespace std;


typedef struct
{
    int quantidade;
    char* str[10];
} HashTable;


//imprime o menu podendo ou não imprimir as opções
void imprimeMenu(bool tudo, bool atual, HashTable* table)
{
    system("cls");
    cout << "   ________  ___  _____ ______   ________  ___       _______              ___    ___           " << endl;
    cout << "  |\\   ____\\|\\  \\|\\   _ \\  _   \\|\\   __  \\|\\  \\     |\\  ___ \\            |\\  \\  |\\  \\          " << endl;
    cout << "  \\ \\  \\___|\\ \\  \\ \\  \\\\\\__\\ \\  \\ \\  \\|\\  \\ \\  \\    \\ \\   __/|         __\\_\\  \\_\\_\\  \\_____    " << endl;
    cout << "   \\ \\_____  \\ \\  \\ \\  \\\\|__| \\  \\ \\   ____\\ \\  \\    \\ \\  \\_|/__      |\\____    ___    ____\\   " << endl;
    cout << "    \\|____|\\  \\ \\  \\ \\  \\    \\ \\  \\ \\  \\___|\\ \\  \\____\\ \\  \\_|\\ \\     \\|___| \\  \\__|\\  \\___|   " << endl;
    cout << "      ____\\_\\  \\ \\__\\ \\__\\    \\ \\__\\ \\__\\    \\ \\_______\\ \\_______\\        __\\_\\  \\_\\_\\  \\_____ " << endl;
    cout << "     |\\_________\\|__|\\|__|     \\|__|\\|__|     \\|_______|\\|_______|       |\\____    ____   ____\\" << endl;
    cout << "     \\|_________|                                                        \\|___| \\  \\__|\\  \\___|" << endl;
    cout << "                                                                               \\ \\__\\ \\ \\__\\   " << endl;
    cout << "                                                                                \\|__|  \\|__|   " << endl;
    cout << "================================================================================================" << endl;
    if(atual)
    {
        cout << "index: | ";
        for(int i = 0; i<10; i++)
        {
            cout << i;
            if(table->str[i] != nullptr)
                for(unsigned int j=0; j<strlen(table->str[i]); j++)
                    cout << " ";
            cout << " | ";
        }
        cout << endl << "valor: | ";
        for(int i = 0; i<10; i++)
        {
            if(table->str[i] != nullptr)
                cout << table->str[i];
            cout << "  | ";
        }
        cout << endl << "================================================================================================" << endl;
    }
    if(tudo)
    {
        cout << " Selecione uma opcao:" << endl;
        cout << "   1. Inserir" << endl;
        cout << "   2. Busca" << endl;
        cout << "   3. Remocao" << endl;
        cout << "   0. Sair" << endl;
        cout << "================================================================================================" << endl;
        cout << ">>";
    }
}

int lerEntrada(const char* print)
{
    int input = -1;
    bool valid= false;
    do
    {
        cout << print;
        cin >> input;
        if (cin.good())
        {
            valid = true;
        }
        else
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            cout << " Entrada inválida!" << endl;
        }
    }
    while (!valid);
    return (input);
}

unsigned int hash1(const char *str)
{
    unsigned int value = 1;
    unsigned int a = 5;

    for (; *str; str++)
    {
        value = value * a + (unsigned char)(*str);
        a++;
    }
    return value%10;
}

unsigned int hash2(const char *str)
{
    return 1;
}

int inserir(const char *strg, HashTable* table)
{
    int h1 = hash1(&strg[0u]);
    int h2 = hash2(&strg[0u]);

    if(table->quantidade == 10)
        return -1;

    while(table->str[h1] != nullptr)
    {
        if(!strcmp(table->str[h1], strg)) //Valor já existe!
            return -2;
        h1 = (h1 + h2) % 10; //Tabela circular
    }

    table->str[h1] = (char*)malloc(strlen(strg) * sizeof(char));
    strcpy(table->str[h1], strg);
    table->quantidade++;
    return h1;
}

//busca elemento e retorna sua posicao, retorna -1 para nao encontrado
int busca(const char *strg, HashTable* table)
{
    int h1 = hash1(&strg[0u]);
    int h2 = hash2(&strg[0u]);
    int initial = h1;
    //hash vazia
    if(table->quantidade == 0)
        return -1;

    while(table->str[h1] != nullptr)
    {
        if(!strcmp(table->str[h1], strg)) //Achou o valor!
            return h1;
        h1 = (h1 + h2) % 10; //Tabela circular
        if(h1==initial)//viu todos
            break;
    }
    return -1;
}

//remove elemento e retorna sua posicao, retorna -1 para nao encontrado
int remover(const char *strg, HashTable* table)
{
    int pos;
    pos = busca(strg,table);
    //elemento nao existe
    if(pos == -1)
        return -1;
    //removendo
    free(table->str[pos]);
    table->str[pos]=nullptr;
    table->quantidade--;

    return pos;
}

int main()
{
    char ent;
    int ret;
    string entrada;
    HashTable table;

    table.quantidade = 0;
    for(int i=0; i<10; i++)
        for(int j=0; j<20; j++)
            table.str[i] = nullptr;

    while(1)
    {
        system("cls");

        imprimeMenu(true, false, &table);

        getline(cin, entrada);
        ent = entrada[0];

        switch(ent)
        {
        case '0':
            return 0;
            break;
        /// Inserir
        case '1':
            ret = -3;
            while(1)
            {
                imprimeMenu(false, true, &table);
                cout << " 1. Inserir" << endl;
                if(ret == -2)
                    cout << "   Valor ja existe na tabela!" << endl;
                else if(ret == -1)
                    cout << "   Tabela cheia!" << endl;
                else if(ret > -1)
                    cout << "   Valor adicionado na posicao " << ret << endl;

                cout << "   Inserir (pressione apenas ENTER para sair): ";
                getline(cin, entrada);
                if(entrada == "")
                    break;
                ret = inserir(&entrada[0u], &table);
                system("cls");
            }
            break;
        /// Busca
        case '2':
            while(1){
                imprimeMenu(false, true, &table);
                cout << " 2. Busca" << endl;
                cout << "   Buscar (pressione apenas ENTER para sair): ";
                getline(cin, entrada);
                if(entrada == "")
                    break;
                ret = busca(&entrada[0u], &table);
                if(ret == -1)
                    cout << "   String nao se encontra na tabela!" << endl;
                else
                    cout << "   String encontrada, posicao: " << ret << endl;
                system("pause");
            }
            break;
        /// Remoção
        case '3':
            while(1){
                imprimeMenu(false, true, &table);
                cout << " 2. Remocao" << endl;
                cout << "   Remover (pressione apenas ENTER para sair): ";
                getline(cin, entrada);
                if(entrada == "")
                    break;
                ret = remover(&entrada[0u], &table);
                if(ret == -1)
                    cout << "   String nao se encontra na tabela!" << endl;
                else
                    cout << "   String removida da posicao: " << ret << endl;
                system("pause");
            }
            break;
        /// Entrada inválida
        default:
            break;
        }
    }

    return 0;
}
