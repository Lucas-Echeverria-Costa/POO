#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <random>

struct Evento {
    int tipo; // 0: chegada de processo, 1: término de IO
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

int main(int argc, char* argv[]) {
    if (argc != 6) {
        std::cerr << "Uso: " << argv[0] << " arquivo_csv num_cpus velocidade_cpu memoria_total quantum\n";
        return 1;
    }

    std::string arquivo_csv = argv[1];
    int num_cpus = std::stoi(argv[2]);
    int velocidade_cpu = std::stoi(argv[3]);
    int memoria_total = std::stoi(argv[4]);
    int quantum = std::stoi(argv[5]);
    int memoria_swap = memoria_total / 2; // Tamanho do swap

    std::vector<Processo> processos;
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

    int tempo_total = 0;
    int tempo_ocupado_total = 0;
    std::vector<CPU> cpus(num_cpus);
    std::vector<Evento> eventos_futuros;
    std::default_random_engine gerador;
    std::uniform_real_distribution<double> distribuicao(0.0, 1.0);

    // Adiciona eventos de chegada de processos
    for (const auto& processo : processos) {
        Evento evento;
        evento.tipo = 0; // Chegada de processo
        evento.tempo = processo.chegada;
        evento.processo_id = processo.id;
        eventos_futuros.push_back(evento);
    }

    std::sort(eventos_futuros.begin(), eventos_futuros.end(), [](const Evento& e1, const Evento& e2) {
        return e1.tempo < e2.tempo;
    });

    while (!eventos_futuros.empty()) {
        // Avança o relógio global para o próximo evento
        tempo_total = eventos_futuros.front().tempo;
        // Processa o próximo evento
        const Evento& evento_atual = eventos_futuros.front();
        if (evento_atual.tipo == 0) {
            // Chegada de processo
            // Implemente aqui a lógica de escalonamento
            // e adicione os eventos futuros necessários
        } else if (evento_atual.tipo == 1) {
            // Término de IO
            for (auto& processo : processos) {
                if (processo.id == evento_atual.processo_id) {
                    processo.io_ocorrendo = false;
                    // Implemente aqui a lógica de término de IO
                    // e adicione os eventos futuros necessários
                    break;
                }
            }
        }
        // Remove o evento processado da lista de eventos futuros
        eventos_futuros.erase(eventos_futuros.begin());
    }

    return 0;
}
