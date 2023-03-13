#include <stdio.h>
#include <stdlib.h>

#define MEMORY_SIZE 30000

int main() {
    // abre o arquivo de entrada para leitura
    FILE* input_file = fopen("ArquivoBF.txt", "r");

    // aloca a memória do BrainFuck
    char memory[MEMORY_SIZE] = {0};
    char* ptr = memory;

    // lê o código do arquivo
    char code[10000] = {0};
    int code_size = 0;
    char c;
    while ((c = fgetc(input_file)) != EOF) {
        // adiciona ao vetor de código apenas os caracteres válidos do Brainfuck
        if (c == '+' || c == '-' || c == '<' || c == '>' || c == ',' || c == '.' || c == '[' || c == ']') {
            code[code_size++] = c;
        }
    }
    fclose(input_file);

    // executa o código
    int code_pos = 0; // posição atual no código
    int loop_stack[1000] = {0}; // pilha de loops
    int loop_pos = 0; // posição atual na pilha
    while (code_pos < code_size) {
        char op = code[code_pos++]; // pega o próximo comando
        switch (op) {
            case '+': ++*ptr; break;
            case '-': --*ptr; break;
            case '<': --ptr; break;
            case '>': ++ptr; break;
            case ',': *ptr = getchar(); break;
            case '.': putchar(*ptr); break;
            case '[':
                if (*ptr == 0) { // se o valor atual é zero, pula para o próximo ']'
                    int depth = 1;
                    while (depth > 0) {
                        char c = code[code_pos++];
                        if (c == '[') ++depth;
                        else if (c == ']') --depth;
                    }
                } else { // senão, adiciona a posição atual na pilha de loops
                    loop_stack[loop_pos++] = code_pos - 1;
                }
                break;
            case ']':
                if (*ptr != 0) { // se o valor atual é diferente de zero, volta para o início do loop
                    code_pos = loop_stack[loop_pos - 1];
                } else { // senão, remove a posição atual da pilha de loops
                    --loop_pos;
                }
                break;
        }
    }

    return 0;
}

