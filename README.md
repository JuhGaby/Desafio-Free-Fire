# Desafio-Free-Fire
Sistema em C que simula o inventário de um jogo de sobrevivência, mostrando três níveis de evolução. Demonstra na prática como diferentes estruturas de dados e algoritmos afetam o desempenho em situações de jogo, ajudando a escolher a melhor abordagem para cada cenário.
Sistema de Inventário e Torre de Resgate - Estruturas de Dados

🎮 Descrição do Projeto

Sistema completo de gerenciamento de inventário e montagem de torre de resgate desenvolvido em C, implementando múltiplas estruturas de dados e algoritmos para um cenário de jogo de sobrevivência. O projeto demonstra a evolução desde estruturas básicas até algoritmos avançados de ordenação e busca.

🚀 Funcionalidades Principais

Nível 1: Sistema Básico de Inventário

· Structs e Listas Sequenciais: Implementação de mochila com vetores
· Operações CRUD: Cadastro, remoção, listagem e busca de itens
· Busca Sequencial: Localização de itens por nome

Nível 2: Comparação de Estruturas

· Vetor vs Lista Encadeada: Implementação paralela das duas estruturas
· Análise de Desempenho: Comparação empírica de operações
· Busca Binária: Implementada no vetor ordenado
· Ordenação: Algoritmo Bubble Sort para vetores

Nível 3: Sistema Avançado de Torre de Resgate

· Múltiplos Algoritmos: Bubble Sort, Insertion Sort e Selection Sort
· Critérios de Ordenação: Nome, tipo e prioridade
· Análise de Complexidade: Medição de tempo e comparações
· Busca Binária Otimizada: Para componentes críticos

🛠️ Tecnologias e Conceitos

· Linguagem: C
· Estruturas de Dados: Arrays, Structs, Listas Encadeadas
· Algoritmos:
  · Ordenação: Bubble Sort, Insertion Sort, Selection Sort
  · Busca: Sequencial, Binária
· Análise: Complexidade de algoritmos, Big O notation

📁 Estrutura do Projeto

```
projeto-estruturas-dados/
│
├── nivel1-inventario-basico/     # Sistema básico com vetores
├── nivel2-comparacao-estruturas/ # Vetor vs Lista Encadeada  
├── nivel3-torre-resgate/         # Algoritmos avançados
├── docs/                         # Documentação
└── README.md                     # Este arquivo
```

🎯 Contexto do Jogo

O projeto simula um cenário de jogo de sobrevivência onde o jogador deve:

1. Coletar recursos essenciais na fase inicial
2. Organizar o inventário de forma eficiente
3. Montar uma torre de resgate com componentes na ordem correta
4. Escapar da ilha antes que a zona segura se feche

📊 Métricas de Desempenho

O sistema inclui medições para:

· Tempo de execução dos algoritmos
· Número de comparações realizadas
· Número de trocas/operações
· Eficiência por elemento processado

🎓 Objetivos Educacionais

· Compreender diferenças entre estruturas de dados estáticas e dinâmicas
· Implementar e comparar algoritmos clássicos de ordenação
· Analisar complexidade algorítmica na prática
· Desenvolver pensamento crítico sobre escolhas de estruturas

🔧 Como Compilar e Executar

```bash
# Compilar
gcc -o sistema_principal main.c

# Executar
./sistema_principal
```

👨‍💻 Autor

Desenvolvido como parte do estudo de estruturas de dados e algoritmos.

📄 Licença

Este projeto é para fins educacionais.

---

Tags: C Estruturas de Dados Algoritmos Ordenação Busca Complexidade Jogos Educação
