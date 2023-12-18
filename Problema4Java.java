import java.util.ArrayList;

// Definição da classe Lista
class Lista {
    private ArrayList<Integer> lista;

    public Lista() {
        this.lista = new ArrayList<>();
    }

    public void insere(int v) {
        this.lista.add(0, v); // Insere no início da lista
    }

    public void remove() {
        if (!this.lista.isEmpty()) {
            this.lista.remove(0);
        }
    }

    public int tamanho() {
        return this.lista.size();
    }

    public Integer primeiro() {
        if (!this.lista.isEmpty()) {
            return this.lista.get(0);
        } else {
            return null;
        }
    }
}

// Definição da classe Fila (FIFO)
class Fila {
    private Lista lista;

    public Fila() {
        this.lista = new Lista();
    }

    public void insere(int v) {
        this.lista.insere(v);
    }

    public void remove() {
        this.lista.remove();
    }

    public int tamanho() {
        return this.lista.tamanho();
    }

    public Integer primeiro() {
        return this.lista.primeiro();
    }
}

// Definição da classe Pilha (LIFO)
class Pilha {
    private Lista lista;

    public Pilha() {
        this.lista = new Lista();
    }

    public void push(int v) {
        this.lista.insere(v);
    }

    public void pop() {
        this.lista.remove();
    }

    public int tamanho() {
        return this.lista.tamanho();
    }

    public Integer primeiro() {
        return this.lista.primeiro();
    }
}

// Exemplo de uso
public class Main {
    public static void main(String[] args) {
        // Uso da Fila
        Fila minhaFila = new Fila();

        minhaFila.insere(10);
        minhaFila.insere(20);
        minhaFila.insere(30);

        System.out.println("Fila após inserção:");
        System.out.println("Primeiro elemento: " + minhaFila.primeiro());
        System.out.println("Tamanho da fila: " + minhaFila.tamanho());

        minhaFila.remove();

        System.out.println("\nFila após remoção:");
        System.out.println("Primeiro elemento: " + minhaFila.primeiro());
        System.out.println("Tamanho da fila: " + minhaFila.tamanho());

        // Uso da Pilha
        Pilha minhaPilha = new Pilha();

        minhaPilha.push(10);
        minhaPilha.push(20);
        minhaPilha.push(30);

        System.out.println("\nPilha após inserção:");
        System.out.println("Primeiro elemento: " + minhaPilha.primeiro());
        System.out.println("Tamanho da pilha: " + minhaPilha.tamanho());

        minhaPilha.pop();

        System.out.println("\nPilha após pop:");
        System.out.println("Primeiro elemento: " + minhaPilha.primeiro());
        System.out.println("Tamanho da pilha: " + minhaPilha.tamanho());
    }
}
