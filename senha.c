#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <inttypes.h>

/*
FERNANDO COSTA RODRIGUES
TRABALHO 3 - SEGURANCA DA INFORMACAO 2017.2
*/

uint64_t valida(unsigned char *senha){ //funcao que retorna a hash de 64 bits de acordo com a senha dada
    uint64_t hash = 5381, char_atual = *(senha); //inicializa H0 e o primeiro char da senha
    while(char_atual){ //enquanto houver char valido na senha
        hash = ((hash << 5) + hash) + char_atual; //usando bitshift pra multiplicar por 2^5(32) e somando com ele mesmo, mesmo que multiplicar por 33. e somando o asc do char atual
        char_atual = *(++senha); //incrementa o endereco do char referente a senha e atualizando o atual
    }
    return hash; //retorna hash de 64 bits
}

int main(){
    int n, m, i, j, achou = 0; //inicializa variaveis usadas em loops e etc
    scanf("%d", &n); //le o n

    char usuario[n][20]; //matriz de n usuarios com 20 characteres no maximo
    uint64_t hash[n]; //vetor guardando a hash de cada usuario

    for(i = 0; i < n; i++){
        scanf("%s", (char*)&usuario[i]); //le o nome de usuario e guarda
        scanf("%"SCNu64, &hash[i]); //le a hash referente
    }

    scanf("%d", &m); //le o m para o numero de testes
    unsigned char nome_teste[20], senha_teste[6]; //vetores guardam temporariamente cada teste

    for(j = 0; j < m; j++){
        scanf("%s %s", nome_teste, senha_teste); //le usuario e tentativa de senha pra cada teste
        for(i = 0; i < n; i++){
            if(!(strcmp(nome_teste, usuario[i]))){ //procura se existe o usuario no vetor de usuarios
                achou++; //marca que encontrou caso exista
                if(hash[i] == valida(senha_teste)) //compara a hash guardada no inicio com a hash gerada a partir da senha em caracteres
                    printf("Login aceito\n");
                else
                    printf("Senha incorreta\n");
                break; //para a busca caso tenha encontrado
            }
        }
        if(!achou) printf("Usuario nao encontrado\n"); //se nao encontrou e chegou ate aqui é porque nao existe usuario
        achou = 0; //zera para o novo teste
    }
    return 0;
}