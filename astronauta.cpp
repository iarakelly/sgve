#include "astronauta.h"


Astronauta::Astronauta(std::string cpf, std::string nome, int idade) 
{
    this->cpf = cpf;
    this->nome = nome;
    this->idade = idade;
    disponivel = true;
    vivo = true;

}

    string Astronauta::getCPF() const {
        return cpf;
    }

    string Astronauta::getNome() const {
        return nome;
    }

    int Astronauta::getIdade() const {
        return idade;
    }

    bool Astronauta::isDisponivel() const {
        return disponivel;
    }

    void Astronauta::setDisponivel(bool disponivel) {
        this->disponivel = disponivel;
    }
    bool Astronauta::isVivo () const {
        return vivo;
    }
    void Astronauta::setVivo(bool vivo){
        this->vivo = vivo;

    }
