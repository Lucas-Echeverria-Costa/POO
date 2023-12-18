#include <iostream>
#include <vector>

// Definição da classe Lista
class Lista {
private:
    std::vector<int> lista;

public:
    Lista() {}

    void insere(int v) {
        lista.insert(lista.begin(), v); // Insere no início da lista
    }

    void remove() {
        if (!lista.empty()) {
            lista.erase(lista.begin());
        }
    }

    int tamanho() const {
        return lista.size();
    }

    int primeiro() const {
        if (!lista.empty()) {
            return lista.front();
        } else {
            return -1; // Valor padrão para indicar lista vazia
        }
    }
};

// Definição da classe Fila (FIFO)
class Fila {
private:
    Lista lista;

public:
    Fila() {}

    void insere(int v) {
        lista.insere(v);
    }

    void remove() {
        lista.remove();
    }

    int tamanho() const {
        return lista.tamanho();
    }

    int primeiro() const {
        return lista.primeiro();
    }
};

// Definição da classe Pilha (LIFO)
class Pilha {
private:
    Lista lista;

public:
    Pilha() {}

    void push(int v) {
        lista.insere(v);
    }

    void pop() {
        lista.remove();
    }

    int tamanho() const {
        return lista.tamanho();
    }

    int primeiro() const {
        return lista.primeiro();
    }
};

// Função principal
int main() {
    // Uso da Fila
    Fila minhaFila;

    minhaFila.insere(10);
    minhaFila.insere(20);
    minhaFila.insere(30);

    std::cout << "Fila após inserção:" << std::endl;
    std::cout << "Primeiro elemento: " << minhaFila.primeiro() << std::endl;
    std::cout << "Tamanho da fila: " << minhaFila.tamanho() << std::endl;

    minhaFila.remove();

    std::cout << "\nFila após remoção:" << std::endl;
    std::cout << "Primeiro elemento: " << minhaFila.primeiro() << std::endl;
    std::cout << "Tamanho da fila: " << minhaFila.tamanho() << std::endl;

    // Uso da Pilha
    Pilha minhaPilha;

    minhaPilha.push(10);
    minhaPilha.push(20);
    minhaPilha.push(30);

    std::cout << "\nPilha após inserção:" << std::endl;
    std::cout << "Primeiro elemento: " << minhaPilha.primeiro() << std::endl;
    std::cout << "Tamanho da pilha: " << minhaPilha.tamanho() << std::endl;

    minhaPilha.pop();

    std::cout << "\nPilha após pop:" << std::endl;
    std::cout << "Primeiro elemento: " << minhaPilha.primeiro() << std::endl;
    std::cout << "Tamanho da pilha: " << minhaPilha.tamanho() << std::endl;

    return 0;
}
