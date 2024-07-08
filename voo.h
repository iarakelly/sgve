#ifndef VOO_H 
#define VOO_H

#include <vector>
#include "astronauta.h" 
#include <iterator>
#include <iostream>
#include <algorithm>



using namespace std;

class Voo
{
    private:
    int codigo;
    vector<Astronauta*> passageiros;


    public:
    enum Status {PLANEJADO, EM_CURSO, FINALIZADO};
    Status status;

   Voo(int codigo);
    ~Voo();
    int getCodigo() const;
    Status getStatus() const;
    const std::vector<Astronauta*>& getPassageiros() const;
    void adicionarPassageiro(Astronauta* astronauta);
    void removerPassageiro(const std::string& cpf);
};

#endif