#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <stdlib.h>

#define TAMDADO 1024
#define PORTA 1234

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
	if (sock<0){
		perror("Houve um problema ao criar o socket:");
        return -1;
    }

	//Preenchendo informações sobre o servidor e Ligando o socket a todos IPs locais e escolhendo qualquer porta
    struct sockaddr_in addr_cliente;
	struct sockaddr_in addr_servidor;

	/* Preenchendo as informacoes de identificacao do remoto */
  	addr_servidor.sin_family 	   = AF_INET;
  	addr_servidor.sin_addr.s_addr = inet_addr(argv[1]);
  	addr_servidor.sin_port 	   = htons(atoi(argv[2]));

  	addr_cliente.sin_family 	 = AF_INET;
  	addr_cliente.sin_addr.s_addr= htonl(INADDR_ANY);  
  	addr_cliente.sin_port 	     = htons(0); /* usa porta livre entre (1024-5000)*/

	int associacao = bind(sock, (struct sockaddr *)&addr_cliente, sizeof(addr_cliente));
	if (associacao < 0) {
		printf("Erro ao associar o nome ao socket na porta:%s\n", argv[2]);
		return -1;
	}
	printf("Associacao do nome ao socket efetuado com sucesso.Porta: %s\n", argv[2]);

	// Definindo addr_servidor como o endereco que deve ser conectado
	// Convertendo a string 127.0.0.1 para binario com inet_aton

   /*  char *servidor = "127.0.0.1";

	if (inet_aton(servidor, &addr_servidor.sin_addr)==0) {
		printf("Não foi possivel fazer a conversao de string para binario\n");
		return -1;
	}
 */
	// Enviando mensagem para o servidor
    socklen_t tamanho_servidor = sizeof(addr_servidor);
    char dado[TAMDADO];
	printf("Enviando mensagem para o servidor: %s [%s]\n", argv[1], argv[2]);
	sprintf(dado, "Ola, tudo bem?");
	if (sendto(sock, dado, strlen(dado), 0, (struct sockaddr *)&addr_servidor, tamanho_servidor)==-1) {
		perror("Erro ao enviar o pacote:");
		return -1;
	}

	// Recebendo resposta do servidor
    int tam_recebido;	
	if ((tam_recebido = recvfrom(sock, dado, TAMDADO, 0, (struct sockaddr *)&addr_servidor, &tamanho_servidor)) >=0 ){
		dado[tam_recebido] = '\0';
		printf("Mensagem recebida: %s \n", dado);
	}
	close(sock);
	return 0;
}