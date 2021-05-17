#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_SIZE    	80

int main(int argc,char * argv[]) {
	struct  sockaddr_in ladoServ; /* contem dados do servidor 	*/
	int     sd;          	      /* socket descriptor              */
	int     n,k;                  /* num caracteres lidos do servidor */
	char    bufout[MAX_SIZE];     /* buffer de dados enviados  */
	char    buf_in[MAX_SIZE];     /* buffer de dados recebidos  */
	
	/* confere o numero de argumentos passados para o programa */
  	if(argc<3)  {
    	   printf("uso correto: %s <ip_do_servidor> <porta_do_servidor>\n", argv[0]);
    	   exit(1);  }

	memset((char *)&ladoServ,0,sizeof(ladoServ)); /* limpa estrutura */
	memset((char *)&bufout,0,sizeof(bufout));     /* limpa buffer */
	
	ladoServ.sin_family      = AF_INET; /* config. socket p. internet*/
	ladoServ.sin_addr.s_addr = inet_addr(argv[1]); // ip adress
	ladoServ.sin_port        = htons(atoi(argv[2])); // porta

	/* Cria socket */
	sd = socket(AF_INET, SOCK_STREAM, 0);
	if (sd < 0) {
		fprintf(stderr, "Criacao do socket falhou!\n");
		exit(1); }

	/* Conecta socket ao servidor definido */
	if (connect(sd, (struct sockaddr *)&ladoServ, sizeof(ladoServ)) < 0) {
		fprintf(stderr,"Tentativa de conexao falhou!\n");
		exit(1); }
	while (1) {
		printf("> ");
		fgets(bufout, MAX_SIZE, stdin);    /* le dados do teclado */
		send(sd,&bufout,strlen(bufout),0); /* enviando dados ...  */
		if (strncmp(bufout, "FIM",3) == 0) 
			break;
		if(strcmp(bufout, "LIBERADO\n") == 0){

		do{

			if ((n = recv(sd, buf_in, 8192, 0)) > 0) { // recebendo dados da função send do servidor
	        buf_in[n] = '\0'; // define fim da string

	        fprintf(stdout, "Servidor >> %s\n", buf_in); // Printa mensagem recebida do servidor
	   		}
   		}while(strcmp (buf_in, "LIBERADO") != 0 ); // Envia dados enquanto for diferente de LIBERADO
   	}

	} /* fim while */
	printf("------- encerrando conexao com o servidor -----\n");
	close (sd);
	return (0);
} /* fim do programa */

