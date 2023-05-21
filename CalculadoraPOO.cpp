
#include <iostream>
#include <cmath>
#include <stack>
#include <map>
#include <functional>

typedef struct valores{
    std::string operacao;
    double inserido[2];
    double resultado;
} VALORES;

class Historico {
    public:
    std::stack<valores> data;
    
    void Adicionar(double valor1, std::string operacao, double valor2, double resultado) {
        VALORES* novo = new VALORES;
        novo->inserido[0] = valor1;
        novo->inserido[1] = valor2;
        novo->resultado = resultado;
        novo->operacao = operacao;
        this->data.push(*novo);
    };
    
    void MostrarResultado() {

        if(data.top().inserido[1] == NULL) {
                    std::cout << data.top().inserido[0] << data.top().operacao << " = " <<  data.top().resultado << "\n";
                } else {
                    std::cout << data.top().inserido[0]
                    << data.top().operacao
                    << data.top().inserido[1] << " = " 
                    << data.top().resultado << "\n";
                }
    };

    void Mostrar(){
        std::cout << "*****************************\n";
        std::cout << "**********HISTÓRICO**********\n";
        std::cout << "*****************************\n";
            while (!data.empty()) {
                std::stack<valores> imprimir;
                imprimir = this->data;
                if(data.top().inserido[1] == NULL) {
                    std::cout << imprimir.top().inserido[0] << imprimir.top().operacao << "=" <<  imprimir.top().resultado << "\n";
                } else {
                    std::cout << imprimir.top().inserido[0]
                    << imprimir.top().operacao
                    << imprimir.top().inserido[1] << " = " 
                    << imprimir.top().resultado << "\n";
                }
                
                data.pop();
            }
        std::cout << "\n";
    };
};


class Calculadora {
    public:
    Historico historico;   

    void soma(double valor1, double valor2){
            
        historico.Adicionar(valor1, " + ", valor2, valor1 + valor2);
        historico.MostrarResultado();
    };
    void subtracao(double valor1, double valor2){
        
        historico.Adicionar(valor1, " - ", valor2, valor1 - valor2);
        historico.MostrarResultado();
    };
    void multiplicacao(double valor1, double valor2){
        historico.Adicionar(valor1, " * ", valor2, valor1*valor2);
        historico.MostrarResultado();
    };
    void divisao(double valor1, double valor2){
        if(valor2 != 0) {
            historico.Adicionar(valor1, " ÷ ", valor2, valor1/valor2);
            historico.MostrarResultado();
        }
        else {std::cout << "Divisão por 0!\n";}
        
    };
    void quadrado(double valor){
        historico.Adicionar(valor, "²", NULL, valor*valor);
        historico.MostrarResultado();
    };
    void cubo(double valor){
        historico.Adicionar(valor, "³", NULL, valor*valor*valor);
        historico.MostrarResultado();
    };
    void raizquadrada(double valor){
        historico.Adicionar(valor, "√", NULL, sqrt(valor));
        historico.MostrarResultado();
    };
    void raizcubica(double valor){
        historico.Adicionar(valor, "∛", NULL, pow(valor, 1.0/3.0));
        historico.MostrarResultado();
    };

  
};


class Menu {

    Calculadora calculadora;
    int opcao;
    int subopcao;
    double valor1;
    double valor2;
    std::map<int, std::function<void()>> mapaFuncoes;

    public:
    Menu() {
        
        mapaFuncoes[1] = [this]() { calculadora.soma(valor1, valor2); };
        mapaFuncoes[2] = [this]() { calculadora.subtracao(valor1, valor2); };
        mapaFuncoes[3] = [this]() { calculadora.multiplicacao(valor1, valor2); };
        mapaFuncoes[4] = [this]() { calculadora.divisao(valor1, valor2); };
        mapaFuncoes[5] = [this]() { calculadora.quadrado(valor1); };
        mapaFuncoes[6] = [this]() { calculadora.cubo(valor1); };
        mapaFuncoes[7] = [this]() { calculadora.raizquadrada(valor1); };
        mapaFuncoes[8] = [this]() { calculadora.raizcubica(valor1); };
        mapaFuncoes[9] = [this]() { calculadora.historico.Mostrar(); };

    }
    
    void principal() {
        
        std::cout << "*****************************\n";
        std::cout << "*********CALCULADORA*********\n";
        std::cout << "*****************************\n";
        std::cout << "1 - SOMA\n";
        std::cout << "2 - SUBTRAÇÃO\n";
        std::cout << "3 - MULTIPLICAÇÃO\n";
        std::cout << "4 - DIVISÃO\n";
        std::cout << "5 - ELEVAR NÚMERO AO QUADRADO\n";
        std::cout << "6 - ELEVAR NÚMERO AO CUBO\n";
        std::cout << "7 - RAIZ QUADRADA\n";
        std::cout << "8 - RAIZ CÚBICA\n";
        std::cout << "9 - HISTÓRICO\n";
        std::cout << "10 - SAIR\n";
        std::cout << "Escolha uma das funções digitando o seu valor correspondente:";
        std::cin >> opcao;
        
    };

    void submenu1() {
        std::cout << "*********VALOR 1*********\n";
        std::cout << "1 - USAR RESULTADO ANTERIOR\n";
        std::cout << "2 - DIGITAR\n";
        std::cin >> subopcao;
        if(subopcao == 2 && opcao <= 4) {
            std::cout << "Digite o valor 1: ";
            std::cin >> valor1;
            std::cout << "Digite o valor 2: ";
            std::cin >> valor2;
        } else if(subopcao == 1 && opcao <= 4 && !calculadora.historico.data.empty()) {
            valor1 = calculadora.historico.data.top().resultado;
            std::cout << "Digite o valor 2:";
            std::cin >> valor2;
        } else if(subopcao == 1 && opcao > 4 && !calculadora.historico.data.empty()) {
            valor1 = calculadora.historico.data.top().resultado;
            
        } else if(subopcao == 2 && opcao > 4) {
            std::cout << "Digite o valor:";
            std::cin >> valor1;
        }

        else {
            std::cout << "Valor inválido";
        }
    };

    void submenu2() {
        
        std::cout << "1 - VOLTAR AO MENU\n";
        std::cout << "2 - FECHAR CALCULADORA\n";
        std::cin >> subopcao;

    }

    void Run() {
        
        do {
            std::cin.clear();
            principal();

            if(opcao >= 1 && opcao <= 9) {
                
                if(opcao != 9)
                submenu1();
                //std::cout << "\x1b[2J";
                //windows
                std::system("cls");
                //linux
                //std::system("clear");
                mapaFuncoes[opcao]();
                                
                submenu2();
                if(subopcao == 2) {
                    std::cout << "Calculadora finalizada!\n";
                    break;
                }
            }
            else if(opcao == 10)
            std::cout << "Calculadora finalizada!\n";
            else{std::cout << "Valor inválido\n";}
        } while(opcao != 10);
    }
};

int main() {
    Menu menu;
    
    menu.Run();
    
    return 0;
}
