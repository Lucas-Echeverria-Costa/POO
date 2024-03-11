#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <random>

class Simulador {
private:
    struct Evento {
        int tipo; // 0: chegada de processo, 1: término de quantum, 2: término de IO
        int tempo; // Tempo do evento
        int processo_id; // ID do processo associado ao evento
    };

    struct Processo {
        int id;
        int chegada;
        int prioridade;
        int prioridade_dinamica;
        int quantuns_alocados;
        int instrucoes_restantes;
        int instrucoes_total;
        int memoria;
        int io_rate;
        bool io_ocorrendo;
        int tempo_io_restante;
    };

    struct CPU {
        bool ocupada = false;
        int tempo_ocupada = 0;
    };

    std::string arquivo_csv;
    int num_cpus;
    int velocidade_cpu;
    int memoria_total;
    int quantum;
    int memoria_swap;
    std::vector<Processo> processos;
    std::vector<CPU> cpus;
    std::vector<Evento> eventos_futuros;
    int tempo_global;

public:
    Simulador() {}

    void lerEntrada() {
        // Solicitar ao usuário os valores necessários
        std::cout << "Informe o nome do arquivo CSV: ";
        std::cin >> arquivo_csv;
        std::cout << "Informe o número de CPUs: ";
        std::cin >> num_cpus;
        std::cout << "Informe a velocidade da CPU (MIPS): ";
        std::cin >> velocidade_cpu;
        std::cout << "Informe a quantidade total de memória (Gb): ";
        std::cin >> memoria_total;
        std::cout << "Informe o quantum (ms): ";
        std::cin >> quantum;

        memoria_swap = memoria_total / 2; // Tamanho do swap
    }

    void lerArquivo() {
        std::ifstream arquivo(arquivo_csv);
        std::string linha;

        while (std::getline(arquivo, linha)) {
            std::istringstream iss(linha);
            std::string valor;
            Processo processo;
            std::getline(iss, valor, ',');
            processo.id = std::stoi(valor);
            std::getline(iss, valor, ',');
            processo.chegada = std::stoi(valor);
            std::getline(iss, valor, ',');
            processo.prioridade = std::stoi(valor);
            processo.prioridade_dinamica = processo.prioridade;
            processo.quantuns_alocados = 0;
            std::getline(iss, valor, ',');
            processo.instrucoes_total = std::stoi(valor);
            processo.instrucoes_restantes = processo.instrucoes_total;
            std::getline(iss, valor, ',');
            processo.memoria = std::stoi(valor);
            std::getline(iss, valor, ',');
            processo.io_rate = std::stoi(valor);
            processo.io_ocorrendo = false;
            processo.tempo_io_restante = 0;
            processos.push_back(processo);
        }

        std::sort(processos.begin(), processos.end(), [](const Processo& p1, const Processo& p2) {
            return p1.chegada < p2.chegada;
        });
    }

    void simular() {
        tempo_global = 0;
        while (!eventos_futuros.empty()) {
            tempo_global = eventos_futuros.front().tempo;
            const Evento& evento_atual = eventos_futuros.front();
            if (evento_atual.tipo == 0) {
                escalonarProcesso(evento_atual.processo_id);
            } else if (evento_atual.tipo == 1) {
                finalizarQuantum(evento_atual.processo_id);
            } else if (evento_atual.tipo == 2) {
                finalizarIO(evento_atual.processo_id);
            }
            eventos_futuros.erase(eventos_futuros.begin());
        }
    }

    void escalonarProcesso(int processo_id) {
        for (auto& processo : processos) {
            if (processo.id == processo_id) {
                std::cout << "Escalonando processo " << processo_id << " em uma CPU." << std::endl;
                // Lógica de escalonamento aqui
                // Por exemplo, alocar o processo em uma CPU disponível
                for (auto& cpu : cpus) {
                    if (!cpu.ocupada) {
                        cpu.ocupada = true;
                        cpu.tempo_ocupada = 0;
                        processo.quantuns_alocados++;
                        // Adicionar evento de término do quantum
                        adicionarEvento(1, tempo_global + quantum, processo_id);
                        break;
                    }
                }
                break;
            }
        }
    }

    void finalizarQuantum(int processo_id) {
        for (auto& processo : processos) {
            if (processo.id == processo_id) {
                std::cout << "Processo " << processo_id << " finalizou quantum." << std::endl;
                processo.instrucoes_restantes -= quantum;
                if (processo.instrucoes_restantes <= 0) {
                    // Processo terminou
                    // Implemente a remoção do processo do sistema se necessário
                } else {
                    // Adicionar evento de término do quantum seguinte
                    adicionarEvento(1, tempo_global + quantum, processo_id);
                }
                break;
            }
        }
    }

    void finalizarIO(int processo_id) {
        for (auto& processo : processos) {
            if (processo.id == processo_id) {
                std::cout << "Processo " << processo_id << " finalizou operação de IO." << std::endl;
                processo.io_ocorrendo = false;
                processo.tempo_io_restante = 0;
                // Adicionar processo desbloqueado à lista de prontos
                adicionarEvento(0, tempo_global, processo_id);
                break;
            }
        }
    }

    void adicionarEvento(int tipo, int tempo, int processo_id) {
        eventos_futuros.push_back({tipo, tempo, processo_id});
        std::sort(eventos_futuros.begin(), eventos_futuros.end(), [](const Evento& e1, const Evento& e2) {
            return e1.tempo < e2.tempo;
        });
    }

    void executar() {
        lerEntrada();
        lerArquivo();
        simular();
    }
};

int main() {
    Simulador simulador;
    simulador.executar();

    return 0;
}
