# Desafio - Modelo Moto Elétrica

O desafio consiste em desenvolver um modelo em linguagem C++ para representar:

  - Moto elétrica;
  - Bateria;
  - Estação de Troca de Bateria (ETB);
  - Ponto de Carga (CP).

O modelo considera as equações de carga de bateria, em um ponto de carga, descarga enquanto acoplada à moto, ambas por unidade de tempo, sendo que a descarga realizada na moto depende da velocidade. Além disso considera um sistema de equações simples para o movimento da moto, levando em conta velocidade e aceleração.


## Documentação

A aplicação foi dividida em 4 classes principais, que serão detalhadas a seguir:


### [`class Battery`](https://github.com/l-pires/modelo-moto-eletrica-cpp/blob/main/src/Battery.hpp)

Representa uma bateria física, que possui uma carga e deve estar atrelada a um hospedeiro.

#### Atributos:

  - `uid | long long int` - Identificador único;
  - `soc | float` - (_state of charge_) denota a porcentagem de carga;
  - `host | (void *)` - referência para o hospedeiro.

#### Métodos:

  - `setUid(uid | long long int) | void` - Atualiza o `uid` da bateria, utilizado apenas para o caso em que a bateria foi instanciada com o construtor padrão;
  - `attach(host | void *)` - Associa a bateria à um hospedeiro;
  - `detach() | void` - Desassocia a bateria do hospedeiro atual;
  - `charge(percent | float) | float` - atualiza a carga da bateria, incrementando a porcentagem recebida e retornando a carga atual.


### [`class CP`](https://github.com/l-pires/modelo-moto-eletrica-cpp/blob/main/src/CP.hpp)

Representa um ponto de carga, que pode armazenar uma bateria e carregá-la.

#### Atributos:

  - `charging | bool` - determina se a bateria acoplada está sendo carregada;
  - `battery | (Battery *)` - referência para a bateria acoplada.

#### Métodos:

  - `attach(battery | Battery *) | void` - associa o ponto de carga a uma bateria;
  - `detach() | (Battery *)` - desassocia e retorna a referência para a bateria atual;
  - `timeToCharged() | int` - retorna o tempo restante até a carga total da bateria.


### [`class ETB`](https://github.com/l-pires/modelo-moto-eletrica-cpp/blob/main/src/ETB.hpp)

Representa uma estação de troca de bateria, que pode armazenar e carregar várias baterias, com pontos de cargas.

#### Atributos:

  - `uid | long int` - Identificador único;
  - `cps | CP[]` - Lista de pontos de carga;

#### Métodos:

  - `getNofStored() | int` - retorna o número de baterias armazenadas;
  - `getNofCharging() | int` - retorna o número de baterias que estão carregando;
  - `getBattery(index | int) | (Battery *)` - retorna a referência para a bateria armazenada no ponto de carga de índice especificado;
  - `attach(index | int, battery | Battery *) | void` - associa uma bateria a um ponto de carga especificado pelo índice;
  - `detach(index | int) | (Battery *)` - desassocia e retorna a referência para uma bateria associada ao ponto de carga referenciado pelo índice;
  - `startCharging(index | int) | void` - inicia o carregamento de um ponto de carga referenciado pelo índice;
  - `stopCharging(index | int) | void` - encerra o carregamento de um ponto de carga referenciado pelo índice;
  - `timeToCharged(index | int) | int` - retorna o tempo restante até a carga total da bateria associada ao ponto de carga referenciado pelo índice;
  - `isEmpty(index | int) | bool` - determina se o ponto de carga referenciado pelo índice está vazio;
  - `isCharging(index | int) | bool` - determina se a bateria associada ao ponto de carga referenciado pelo índice está carregando;
  - `update() | void` - atualiza o estado da estação em uma unidade de tempo;


### [`class Motorcycle`](https://github.com/l-pires/modelo-moto-eletrica-cpp/blob/main/src/Motorcycle.hpp)

Representa uma moto elétrica.

#### Atributos:

  - `plate | char[]` -  uma _string_ que armazena a placa da moto (7 caracteres alfanuméricos);
  - `speed | float` - velocidade da moto;
  - `battery | (Battery *)` - referência para a bateria acoplada.

#### Métodos:
  - `turnOn() | void` - atualiza o estado da moto para ligada;
  - `turnOff() | void` - atualiza o estado da moto para desligada;
  - `attach(battery | Battery *) | void` - associa a moto a uma bateria;
  - `detach() | (Battery *)` - desassocia e retorna a referência para a bateria atual;
  - `accelerate() | void` - atualiza a aceleração da moto para um valor predeterminado;
  - `startBrake() | void` - aciona o freio, aplicando uma aceleração negativa predeterminada;
  - `stopBrake() | void` - libera o freio, zerando a aceleração se ela for negativa;
  - `update() | void` - atualiza o estado da moto em uma unidade de tempo;


### [`main.cpp`](https://github.com/l-pires/modelo-moto-eletrica-cpp/blob/main/src/main.cpp)

Além das classes, foi implementado no projeto um programa que executa uma simulação teste predeterminada. 

___

## Compilação

A compilação é feita executando o script [`compile.sh`](https://github.com/l-pires/modelo-moto-eletrica-cpp/blob/main/compile.sh), que utiliza o [`Makefile`](https://github.com/l-pires/modelo-moto-eletrica-cpp/blob/main/src/Makefile) para gerar o programa executável. Para isso, basta rodar o script com o interpretador de linha de comando da sua escolha, por exemplo: 

```bash
  sh compile.sh
```

O script irá criar uma subpasta `/build` com o programa.


## Execução

Para executar o programa também é disponibilizado um simples script `run.sh`, que pode ser executado na forma:

```bash
  sh run.sh
```

Também é possível executar diretamente o programa gerado dentro da pasta `/build`. É recomendado que a saída seja redirecionada para um arquivo de texto, uma vez que o programa gera um grande relatório da simulação:

```bash
  sh run.sh > out.txt
```


## Ambiente de Desenvolvimento

O projeto foi desenvolvido no Windows 10, utilizando o [WSL2](https://docs.microsoft.com/en-us/windows/wsl/) com a distro Ubuntu. Foi utilizado o compilador `g++` na versão 9.4.0, que suporta por padrão C++14.
