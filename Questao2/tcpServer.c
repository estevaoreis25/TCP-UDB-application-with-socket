#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>

#define QLEN 10  //fila de clientes
#define MAX_SIZE 100		//tamanho do buffer

int recebe_cliente(int descritor, struct sockaddr_in endereco_cliente)  {

	char buf_rec[MAX_SIZE]; // buffer de dados recebidos
	char buf_sen[MAX_SIZE]; // buffer de dados enviados
	int  n; // número de caracteres lidos do cliente
	while (1) {

		memset(&buf_rec, 0x0, sizeof(buf_rec));
		n = recv(descritor, &buf_rec, sizeof(buf_rec),0); // recebendo dados da função send do cliente
		if (strncmp(buf_rec, "FIM", 3) == 0) // Verifica se o cliente quer encerrar a conexão
			break;
		fprintf(stdout, "Cliente %u >> %s", ntohs(endereco_cliente.sin_port), buf_rec); // Mensagens enviadas do cliente para o servidor
		if(strcmp(buf_rec, "LIBERADO\n") == 0){ // Se a mensagem que o cliente enviou for igual a LIBERADO,
			do{									// agora o servidor pode enviar mensagens para o cliente
				printf("> ");
				scanf("%s", buf_sen);			// scaneia mensagem que será enviada para o cliente
				send(descritor, buf_sen, strlen(buf_sen), 0); // Envia dados para o cliente
			}while(strcmp(buf_sen, "LIBERADO") != 0); // Envia dados enquanto for diferente de LIBERADO
		}



   } // fim while 
   fprintf(stdout, "Encerrando conexao com: %u ...\n\n", ntohs(endereco_cliente.sin_port));
   close (descritor);
 }

int main(int argc, char *argv[]){
   
   int sd, novo_sd; // descritores 
   int pid, alen,n; 

	if (argc<3) {
		printf("Informe IP e Porta para este servidor\n");
		exit(1); 
	}

	struct sockaddr_in endereco_servidor;  // endereco do servidor      
   struct sockaddr_in endereco_cliente;   // endereco do cliente    

   memset((char *)&endereco_servidor,0,sizeof(endereco_servidor)); // limpa a variavel endereco_servidor    
   endereco_servidor.sin_family 		= AF_INET;           	// familia TCP/IP   
   endereco_servidor.sin_addr.s_addr 	= inet_addr(argv[1]); 	// endereco IP      
   endereco_servidor.sin_port 		= htons(atoi(argv[2])); // PORTA	    

   // Cria o socket 
	sd = socket(AF_INET, SOCK_STREAM, 0);
	if (sd < 0) {
		fprintf(stderr, "Falha ao criar socket!\n");
		exit(1); 
	}

   // liga o socket a porta e ao ip 
	if (bind(sd, (struct sockaddr *)&endereco_servidor, sizeof(endereco_servidor)) < 0) {
		fprintf(stderr,"Ligacao Falhou!\n");
		exit(1); 
	}

   // Ouve a porta
	if (listen(sd, QLEN) < 0) {
		fprintf(stderr,"Falhou ouvindo porta!\n");
		exit(1); 
	}

	printf("Servidor escutando no IP %s, na porta %s ...\n\n", argv[1], argv[2]);
   // Aceita conexoes 
	alen = sizeof(endereco_cliente);
	while(1){
	 // espera nova conexao do cliente	
		if ( (novo_sd=accept(sd, (struct sockaddr *)&endereco_cliente, &alen)) < 0) {
			fprintf(stdout, "Falha na conexao\n");
			exit(1); 
		}

		fprintf(stdout, "%u conectado.\n\n", ntohs(endereco_cliente.sin_port)); 
		recebe_cliente(novo_sd, endereco_cliente);
   	} // fim for 
		return 0;
} // fim do programa 


 
