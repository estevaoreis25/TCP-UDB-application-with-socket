#include <stdio.h>
#include <string.h> // funcoes para lidar com strings
#include <sys/socket.h> // criacao e utilizacao do socket
#include <arpa/inet.h> // define a sctruct sockaddr_in
#include <netinet/in.h> // para utilizar a funcao htons
#include <sys/types.h> // para utilizar a funcao recvfrom
#include <unistd.h>
#include <stdlib.h>

//#define PORTA 1234
#define TAMANHODADOS 1024

int main(int argc, char *argv[]){
	if(argc<3)  {
    printf("Digite corretamente ao iniciar o programa: <ip_do_servidor> <porta_do_servidor>\n");
    return -1;  
	}
	/* Criação do socket UDP */
	// AF_INET = ARPA INTERNET PROTOCOLS -- IPv4
	// SOCK_DGRAM = orientado a datagramas
	// 0 = protocolo padrao para o tipo escolhido -- UDP
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    if(sock < 0){
        perror("Houve um problema ao criar o socket:");
        return -1;
    }

    struct sockaddr_in addr_servidor; // Struct para lidar com o endereço de rede do servidor
	struct sockaddr_in addr_cliente; // Struct para lidar com o endereço de rede do cliente

	memset((char *) &addr_servidor, 0, sizeof(addr_servidor));

	// Preenchendo informações sobre o servidor
	addr_servidor.sin_family = AF_INET; // definindo a familia
	addr_servidor.sin_addr.s_addr = inet_addr(argv[1]); // definindo o endereco IP
	addr_servidor.sin_port = htons(atoi(argv[2])); // definindo a porta que vai ser utilizada para a conexão

	// ligando o socket ao endereco IP e porta
    int verifica_associacao = bind(sock, (struct sockaddr *)&addr_servidor, sizeof(addr_servidor));
    if (verifica_associacao < 0){
		printf("Erro ao associar o nome ao socket na porta:%s\n", argv[2]);
		return -1;
	}
    printf("Associacao do nome ao socket efetuado com sucesso.Porta: %s\n", argv[2]);

    char dados[TAMANHODADOS];
	int tam_recebido;
	socklen_t tamanho_cliente = sizeof(addr_cliente); // Salva o tamanho da struct addr_cliente

    // Recebendo dados
    while(1){
		printf("Aguardando por dados no endereco IP: %s, porta UDP de numero: %s\n", argv[1], argv[2]);
		tam_recebido = recvfrom(sock, dados, TAMANHODADOS, 0, (struct sockaddr *)&addr_cliente, &tamanho_cliente);
		// processando o pacote recebido
		if ( tam_recebido < 0){
			printf("Não pode receber os dados");
		}
		if ( tam_recebido > 0){
			dados[tam_recebido]='\0';
			printf("O pacote foi recebido de: %s:[%d]\nDados: %s\n\n", 
				inet_ntoa(addr_cliente.sin_addr), ntohs(addr_cliente.sin_port), dados); // Faz as conversoes necessarias de endereco e porta e mostra os dados recebidos.
				
			// respondendo ao addr_cliente
			if ((sendto(sock, dados, strlen(dados), 0, (struct sockaddr *)&addr_cliente, tamanho_cliente)) <0){
				perror("Erro ao enviar a resposta:");
			}
		}
	}
	return 0;
}
