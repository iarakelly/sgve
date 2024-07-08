#include "voo.h"

    Voo::Voo(int codigo)
    {
        this->codigo = codigo;
        status = PLANEJADO;
        passageiros = {};
    }
    Voo:: ~Voo() 
    {
        for (auto* astronauta : passageiros) 
        {
            delete astronauta;
        }
    }
    int Voo::getCodigo()const
    {
        return codigo;
    }
    Voo::Status Voo::getStatus()const
    {
        return status;
    }
    const vector<Astronauta*>& Voo::getPassageiros()const
    {
        return passageiros;
    }
    void Voo::adicionarPassageiro(Astronauta* astronauta)
    {
        passageiros.push_back(astronauta);
    }
    void Voo::removerPassageiro(const string& cpf)
    {
        auto it = find_if(passageiros.begin(), passageiros.end(), [&](const Astronauta* astronauta){return astronauta->getCPF() == cpf;});
        if (it != passageiros.end())
        {
            passageiros.erase(it);
            cout << "Astronauta removido do voo com sucesso." << endl;
        }
        else
        {
            cout << "Astronauta não encontrado neste voo." << endl;
        }
    }
