#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <locale.h>

#include "astronauta.h"
#include "voo.h"

class Sistema 
{
private:
    vector<Astronauta*> astronautas;
    vector<Voo*> voos;

public:
    ~Sistema() {
        for (auto& astronauta : astronautas)
        {
            delete astronauta;
        }

        for (auto& voo : voos)
        {
            delete voo;
        }
    }
    void cadastrarAstronauta(string cpf, string nome, int idade) 
    {
        astronautas.push_back(new Astronauta(cpf, nome, idade));
    }
    void listarAstronautas() 
    {
        cout << "Astronautas cadastrados:" << endl;
        cout << "------------------------" << endl;

        for (auto i = astronautas.begin(); i != astronautas.end(); i++) 
        {
        Astronauta* astronauta = *i;
        cout << "CPF: " << astronauta->getCPF() << ", Nome: " << astronauta->getNome() << ", Idade: " << astronauta->getIdade() << endl;
        }
    }
    void cadastrarVoo(int codigo)
    {
        auto it = find_if(voos.begin(), voos.end(), [&](const Voo* voo){return voo->getCodigo() == codigo;});
        if (it == voos.end())
        {
            voos.push_back(new Voo(codigo));
            cout << "Voo Cadastrado com sucesso!" << endl;


        }
        else
        {
            cout << "O voo informado já está cadastrado." << endl;
        }
    }
    void listarVoos() const
    {
        cout << "Lista de Voos" << endl;
        cout << "--------------------------------------------" << endl;
        for(const Voo* voo : voos)
        {
            cout <<"Código: "<< voo->getCodigo()<< endl;
            cout << "Status:";
            switch(voo->getStatus())
            {
                case Voo::PLANEJADO: cout <<"Planejado"<<endl; break;
                case Voo::EM_CURSO: cout <<"Em curso"<<endl; break;
                case Voo::FINALIZADO: cout <<"Finalizado"<<endl; break;

            }
            cout << "Lista de passageiros: "<< endl;
            const vector<Astronauta*>& passageiros = voo->getPassageiros();
            if (passageiros.empty())
            {
                cout << " Nenhum passageiro" << endl;
            }
            else
            {
                for(const Astronauta* astronauta : passageiros)
                {
                    cout << "CPF:" << astronauta ->getCPF() <<
                    ", Nome: " << astronauta-> getNome()<< endl;
                }
            }
            cout << "-------------------------------------" << endl;

        }
    }
    void adicionarPassageiro(const string& cpf, int codigo)
    {
     auto it = find_if(voos.begin(), voos.end(), [&](const Voo* voo){return voo->getCodigo() == codigo;});
     if (it != voos.end())
        {  
            if(  (*it)->getStatus()== Voo::PLANEJADO)
            {
                auto itA = find_if(astronautas.begin(), astronautas.end(), [&](const Astronauta* a){return a->getCPF() == cpf;});

                if(itA != astronautas.end())
                {
                        (*it)->adicionarPassageiro(*itA);
                        cout << "Astronauta adicionado em voo com sucesso." << endl;
                }
                
                else
                {
                     cout << "Astronauta não encontrado." << endl;
                }
            
            }
            else
            {
                cout << "Não é possível adicionar passageiros a um voo que não está em planejamento." << endl;
            }
        }
    else
        {
            cout <<"Voo não encontrado" << endl;
        }
    }
    void lancarVoo(int codigo) 
    {
      auto it = find_if(voos.begin(), voos.end(), [&](const Voo* voo){return voo->getCodigo() == codigo;});
     if (it != voos.end())
        {  
            if((*it)->getStatus()== Voo::PLANEJADO)
            {
               if (!(*it)->getPassageiros().empty()) 
               { 
                bool todosDisponiveis = all_of((*it)->getPassageiros().begin(), (*it)->getPassageiros().end(), [](const Astronauta* astronauta) {return astronauta->isDisponivel();});
                
               if (todosDisponiveis) 
                    {
                    (*it)->status = Voo::EM_CURSO;
                    
                    for (Astronauta* astronauta : (*it)->getPassageiros()) 
                    {
                        astronauta->setDisponivel(false);
                    }
                    cout << "Voo " << codigo << " lançado com sucesso!" << endl;
                    }
                else 
                    {
                        cout << "Nem todos os astronautas associados ao voo estão disponíveis." << endl;
                    }
                }
                else
                {
                cout << "Não é possível lançar um voo sem passageiros." << endl;                    
                }
                    
            }
            else
            {
                cout << "Voo não está em estado de planejamento." << endl;                    
            }
        }
    else
        {
            cout <<"Voo não encontrado" << endl;
        }
    }
    void finalizar_voo_sucesso(int codigo) 
    {
    auto it = find_if(voos.begin(), voos.end(), [&](const Voo* voo) { return voo->getCodigo() == codigo; });
    
    if (it != voos.end()) 
    {
        if ((*it)->getStatus() == Voo::EM_CURSO) 
        { 
            (*it)->status = Voo::FINALIZADO;
            
            for (Astronauta* astronauta : (*it)->getPassageiros()) 
            {
                astronauta->setDisponivel(true);
            }
            
            cout << "Voo " << codigo << " finalizado com sucesso!" << endl;
        }
        else 
        {
            cout << "Erro: O voo não está em estado 'em curso', portanto não pode ser finalizado com sucesso." << endl;
        }
    } 
    else 
    {
        cout << "Erro: Voo não encontrado." << endl;
    }
    }
    void remover_astronauta( string& CPF, int codigo)
    {
        auto it = find_if(voos.begin(), voos.end(), [&](const Voo* voo) { return voo->getCodigo() == codigo; });
        if (it != voos.end())
        {
            if((*it)->getStatus()== Voo::PLANEJADO)
            {
                (*it)->removerPassageiro(CPF);
            }
            else
            {
                cout << "Voo não está sendo planejado." << endl;
            }
        }
        else 
        {
            cout << "Voo não encontrado."<< endl;
        }
        
    }
    void explodir_voo(int codigo)
    {
        auto it = find_if(voos.begin(), voos.end(), [&](const Voo* voo) { return voo->getCodigo() == codigo; });
        if (it != voos.end())
        {
            if((*it)->getStatus()== Voo::EM_CURSO)
            {
                (*it)->status = Voo::FINALIZADO;

                for (Astronauta* astronauta: (*it)->getPassageiros())
                {
                    astronauta->setDisponivel(false);
                    astronauta->setVivo(false);

                    cout << "O voo explodiu." << endl;

                }

            }
            else 
            {
                cout << "O voo não está em curso!" << endl;
            }

        }
        else
        {
            cout << "Voo não encontrado" << endl;
        }

    }
     void listar_mortos() 
    {
        cout << "Astronautas mortos:" << endl;
        for (auto i = astronautas.begin(); i != astronautas.end(); i++) 
        {
            Astronauta* astronauta = *i;
            if (!astronauta->isVivo()) 
            {
                cout << "CPF: " << astronauta->getCPF() << ", Nome: " << astronauta->getNome() << ", Idade: " << astronauta->getIdade() << endl;
            }
            else
            {
                continue;
            }
        }
    }
};

using namespace std;

bool validarCPF(string cpf) 
{
    return all_of(cpf.begin(), cpf.end(), ::isdigit);
}

int main()
{
    setlocale(LC_ALL, "Portuguese");

    Sistema sistema;

    string cpf; string nome;
    int idade;
    int opc = 0, cont=1;
    int codigo = 0;
     
    while(cont!=0)
    {
    //Terminal


    cout << "Qual ação deseja? " << endl;
    cout << "----------------------------------" << endl; 
    cout << "(1) Cadastrar Astronauta" << endl;  //FEITA
    cout << "(2) Adicionar Astronauta em Voo" << endl; //FEITA
    cout << "(3) Remover Astronauta em Voo" << endl; //FEITA
    cout << "(4) Listar Astronautas mortos" << endl; //FEITA
    cout << "----------------------------------" << endl; 
    cout << "(5) Cadastrar Voo" << endl; //FEITA
    cout << "(6) Lancar Voo" << endl;  //FEITA
    cout << "(7) Explodir Voo" << endl; //FEITA
    cout << "(8) Finalizar Voo" << endl;  //FEITA
    cout << "(9) Listar todos os Voos" << endl; //FEITA

    cout << "(10)Listar astronautas" << endl;
    cin >> opc;

    system("clear||cls");

    switch (opc)
    {
    case 1:
        cout << "Cadastro de Astronauta" << endl;
        cout << "Informe o CPF: ";
        cin >> cpf;
        while (!validarCPF(cpf))
            {
                cout << "CPF inválido. Digite novamente: ";
                cin >> cpf;
            }
        cout << "Informe o Nome: ";
        cin.ignore();
        getline(cin, nome);
        cout << "Idade: ";
        cin >> idade;

        sistema.cadastrarAstronauta(cpf, nome, idade);

        cout << "Astronauta Cadastrado com sucesso!" << endl;
        cout << "Deseja voltar para o menu? (1 = Sim, 0 = Nao)" << endl;
        cin >> cont;

        system("clear||cls");


        break;
    case 2:

        cout << "Informe o CPF do astronauta: ";
        cin >> cpf;
        while (!validarCPF(cpf))
            {
                cout << "CPF inválido. Digite novamente: ";
                cin >> cpf;
            }
        cout << "Informe o código do voo: ";
        cin >> codigo;

        sistema.adicionarPassageiro(cpf, codigo);

        cout << "Deseja voltar para o menu? (1 = Sim, 0 = Nao)" << endl;
        cin >> cont;

        system("clear||cls");

        break;
    case 10:
        cout << "============Lista de Astronautas============" << endl;
        cont = 0;
        sistema.listarAstronautas();
        cout << "Deseja voltar para o menu? (1 = Sim, 0 = Nao)" << endl;
        cin >> cont;
        system("clear||cls");

        break;
    case 5:

        cont =0;
        cout << "============Cadastro de Voo============" << endl;
        cout << "Código: ";
        cin >> codigo;
        sistema.cadastrarVoo(codigo);
        cout << "Deseja voltar para o menu? (1 = Sim, 0 = Nao)" << endl;
        cin >> cont;
        system("clear||cls");

        break;
    case 9:
        cout << "============Lista de Voos============" << endl;
        cont =0;
        sistema.listarVoos();
        cout << "Deseja voltar para o menu? (1 = Sim, 0 = Nao)" << endl;
        cin >> cont;
        system("clear||cls");
        
        break;
    case 6:
        cout << "============Lançador============" << endl;
        cont =0;
        cout << "Código do Voo para lancamento: ";
        cin >> codigo;
        sistema.lancarVoo(codigo);
        cout << "Deseja voltar para o menu? (1 = Sim, 0 = Nao)" << endl;
        cin >> cont;
        system("clear||cls");

        break;
    case 3:
        cout << "============Removedor de Passageiro============" << endl;
        cont =0;
        cout << "Código do Voo: ";
        cin >> codigo;
        cout << "CPF do astronauta que deseja remover: ";
        cin >> cpf;
        sistema.remover_astronauta(cpf, codigo);
        cout << "Deseja voltar para o menu? (1 = Sim, 0 = Nao)" << endl;
        cin >> cont;
        system("clear||cls");

        break;

    case 7:
        cout << "Informe o código do Voo que explodiu: ";
        cin >> codigo;
        cont =0;
        sistema.explodir_voo(codigo);
        cout << "Deseja voltar para o menu? (1 = Sim, 0 = Nao)" << endl;
        cin >> cont;
        system("clear||cls");
        
        break;

    case 4:
        cout << "============Lista de Passageiros Mortos============" << endl;
        cont =0;
        cout << "Lista de astronautas mortos:" << endl;
        sistema.listar_mortos();
        cout << "Deseja voltar para o menu? (1 = Sim, 0 = Nao)" << endl;
        cin >> cont;
        system("clear||cls");
        
        break;

    case 8:
        cont =0;
        cout << "Finalizar Voo:" << endl;
        cout << "Informe o código do Voo: ";
        cin >> codigo;
        sistema.finalizar_voo_sucesso(codigo);
        cout << "Voo finalizado com sucesso!" << endl;
        cout << "Deseja voltar para o menu? (1 = Sim, 0 = Nao)" << endl;
        cin >> cont;
        system("clear||cls");
        
        break;

    default:
        break;
    }
    }

    return 0;
}
