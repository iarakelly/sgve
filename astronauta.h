#ifndef ASTRONAUTA_H
#define ASTRONAUTA_H
#include <string>

using namespace std;

class Astronauta 
{
    private:
    string cpf;
    string nome;
    bool disponivel;
    bool vivo;
    int idade;

    public:
    Astronauta(string cpf, string nome, int idade);
    
        string getCPF() const;
        string getNome() const;
        int getIdade() const;
        bool isDisponivel() const;
        bool isVivo() const;
        void setVivo(bool vivo);
        void setDisponivel(bool disponivel);
    
};

#endif