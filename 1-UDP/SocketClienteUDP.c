#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>

#define TAMDADO 1024
#define PORTA 1234

int main(void){
    /* Criação do socket UDP */
    // AF_INET = ARPA INTERNET PROTOCOLS -- IPv4
    // SOCK_DGRAM = orientado a datagramas
    // 0 = protocolo padrao para o tipo escolhido -- UDP

    int sock = socket(AF_INET, SOCK_DGRAM, 0);
	if (sock<0){
		perror("Houve um problema ao criar o socket:");
        return -1;
    }

	//Preenchendo informações sobre o servidor e Ligando o socket a todos IPs locais e escolhendo qualquer porta
    struct sockaddr_in addr_cliente;
	struct sockaddr_in addr_servidor;

	memset((char *)&addr_cliente, 0, sizeof(addr_cliente));
	addr_cliente.sin_family = AF_INET;
	addr_cliente.sin_addr.s_addr = htonl(INADDR_ANY);
	addr_cliente.sin_port = htons(0);

	if (bind(sock, (struct sockaddr *)&addr_cliente, sizeof(addr_cliente)) < 0) {
		perror("Erro ao associar o nome ao socket:");
		return -1;
	}

	// Definindo addr_servidor como o endereco que deve ser conectado
	// Convertendo a string 127.0.0.1 para binario com inet_aton
	memset((char *) &addr_servidor, 0, sizeof(addr_servidor));
	addr_servidor.sin_family = AF_INET;
	addr_servidor.sin_port = htons(PORTA);
    char *servidor = "127.0.0.1";

	if (inet_aton(servidor, &addr_servidor.sin_addr)==0) {
		printf(stderr, "Não foi possivel fazer a conversao de string para binario\n");
		return -1;
	}

	// Enviando mensagem para o servidor
    socklen_t slen = sizeof(addr_servidor);
    char dado[TAMDADO];
	printf("Enviando mensagem para o servidor: %s [%d]\n", servidor, PORTA);
	sprintf(dado, "Ola, tudo bem?");
	if (sendto(sock, dado, strlen(dado), 0, (struct sockaddr *)&addr_servidor, slen)==-1) {
		perror("Erro ao enviar o pacote:");
		return -1;
	}

	// Recebendo resposta do servidor
    int tam_recebido;	
	if ((tam_recebido = recvfrom(sock, dado, TAMDADO, 0, (struct sockaddr *)&addr_servidor, &slen)) >=0 ){
		dado[tam_recebido] = '\0';
		printf("Mensagem recebida: %s \n", dado);
	}
	close(sock);
	return 0;
}