# Aplicação UDP Cliente Servidor Utilizando Socket

Essa solução aplica os conceitos de um servidor UDP, onde é iniciado uma aplicação servidor que o tempo inteiro espera dados de uma aplicação cliente. A aplicação cliente é incializada informando os dados de endereço de ip e porta do servidor e ai então pode enviar mensagens ao servidor. Quando o servidore recebe a mensagem, ele apresenta a mensagem recebida e reenvia para o cliente a mesma mensagem como uma forma de confirmar que recebeu aquela mensagem.

## Limitações da solução
Esta solução é limitada nas seguntes questões:
- Sempre que o cliente deseja enviar alguma mensagem para o servidor, ele precisa inicializar o programa passando sempre as informações de endereço de IP e porta para se conectar ao servidor
- O servidor sempre reenvia a mesma mensagem para o cliente, nao sendo possivel personalizar a mensagem de confirmação de recebimento dos dados enviados para o cliente.