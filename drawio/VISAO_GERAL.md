# 📘 Visão Geral do Projeto Push_swap

## 🎯 Objetivo do Projeto

**Push_swap** é um projeto da 42 que desafia você a ordenar uma pilha de inteiros usando um conjunto limitado de operações, gerando a sequência mais curta possível de instruções.

### Requisitos principais:
- ✅ Ordenar pilha `a` em ordem crescente
- ✅ Usar apenas 11 operações permitidas
- ✅ Minimizar o número de operações
- ✅ Detectar e rejeitar entradas inválidas (não-numéricos, duplicatas, overflow)

---

## 🏗️ Arquitetura do Projeto

```
┌─────────────────────────────────────────────────────┐
│                    INPUT (argv)                     │
│              "3 2 1 5 4" ou 3 2 1 5 4              │
└────────────────────┬────────────────────────────────┘
                     │
                     ▼
┌─────────────────────────────────────────────────────┐
│              1. PARSING & VALIDAÇÃO                 │
│  • Validar formato (is_valid_input)                │
│  • Converter strings para int (safe_atoi)          │
│  • Detectar duplicatas                             │
│  • Criar pilha A                                   │
└────────────────────┬────────────────────────────────┘
                     │
                     ▼
┌─────────────────────────────────────────────────────┐
│              2. NORMALIZAÇÃO                        │
│  • Atribuir índices 0..N-1 baseado em valores      │
│  • Exemplo: [-5, 100, 2] → [0, 2, 1]              │
└────────────────────┬────────────────────────────────┘
                     │
                     ▼
┌─────────────────────────────────────────────────────┐
│         3. ESCOLHA DO ALGORITMO                     │
│  • N = 2: 1 swap                                   │
│  • N = 3: hardcoded (max 2 ops)                    │
│  • N ≤ 5: sort_five                                │
│  • N > 5: Radix Sort                               │
└────────────────────┬────────────────────────────────┘
                     │
                     ▼
┌─────────────────────────────────────────────────────┐
│            4. EXECUÇÃO DAS OPERAÇÕES                │
│  • Aplicar operações (sa, pb, ra, etc.)            │
│  • Imprimir cada instrução no stdout               │
└────────────────────┬────────────────────────────────┘
                     │
                     ▼
┌─────────────────────────────────────────────────────┐
│                 OUTPUT (stdout)                     │
│                    sa                               │
│                    pb                               │
│                    ra                               │
│                    ...                              │
└─────────────────────────────────────────────────────┘
```

---

## 📦 Componentes do Sistema

### **1. Estrutura de Dados - Pilhas (Stacks)**

```c
typedef struct s_stack
{
    int             value;      // valor original
    int             index;      // índice normalizado (0..N-1)
    struct s_stack  *next;      // próximo nó (lista ligada)
}   t_stack;
```

**Características**:
- Lista ligada simples (singly linked list)
- `stack_a`: pilha inicial (contém todos os números)
- `stack_b`: pilha auxiliar (começa vazia)
- O primeiro nó é o "topo" da pilha

---

### **2. As 11 Operações Permitidas**

#### **Swap (troca os 2 primeiros elementos)**
- `sa`: swap a
- `sb`: swap b
- `ss`: sa + sb simultaneamente

#### **Push (move o topo de uma pilha para outra)**
- `pa`: push a (topo de b → topo de a)
- `pb`: push b (topo de a → topo de b)

#### **Rotate (desloca todos para cima, primeiro vira último)**
- `ra`: rotate a
- `rb`: rotate b
- `rr`: ra + rb simultaneamente

#### **Reverse Rotate (desloca todos para baixo, último vira primeiro)**
- `rra`: reverse rotate a
- `rrb`: reverse rotate b
- `rrr`: rra + rrb simultaneamente

**Exemplo visual**:
```
Pilha inicial: [3, 2, 1]  (3 no topo)

sa  → [2, 3, 1]  (troca 3 e 2)
ra  → [3, 1, 2]  (3 vai para baixo)
rra → [2, 3, 1]  (2 vem para cima)
```

---

### **3. Módulos do Código**

#### **📄 Parsing e Validação**
```
is_valid_input.c
├── is_valid_input()      - valida formato de token
├── safe_atoi()           - conversão string→int segura
├── ft_isspace()          - detecta whitespace
└── helpers auxiliares    - skip_whitespace, parse_sign, etc.

parse_input.c
├── parse_arguments()     - processa argc/argv
├── has_duplicates()      - detecta números repetidos
├── normalize_values()    - atribui índices
└── error_exit()          - libera memória e sai com erro
```

#### **📄 Estrutura e Utilidades da Pilha**
```
stack_utils.c
├── stack_new()           - cria novo nó
├── stack_add_front()     - adiciona no topo
├── stack_add_back()      - adiciona no fim
├── stack_size()          - conta elementos
├── stack_last()          - retorna último nó
└── stack_clear()         - libera toda a pilha

stack_checks.c
├── is_sorted()           - verifica se está ordenada
├── stack_min()           - retorna menor valor
├── stack_max()           - retorna maior valor
└── get_position()        - posição de um valor
```

#### **📄 Operações das Pilhas**
```
operations_swap.c         - sa, sb, ss
operations_push.c         - pa, pb
operations_rotate.c       - ra, rb, rr
operations_reverse.c      - rra, rrb, rrr
```

#### **📄 Algoritmos de Ordenação**
```
sort_small.c
├── sort_two()            - ordena 2 elementos
├── sort_three()          - ordena 3 elementos (hardcoded)
└── sort_five()           - ordena ≤5 elementos

sort_radix.c
└── radix_sort()          - Radix Sort em base 2 (para N>5)
```

#### **📄 Main e Coordenação**
```
main.c
└── main()                - orquestra todo o fluxo
```

---

## 🔄 Fluxo de Execução Completo

### **Entrada**: `./push_swap 3 2 1 5 4`

```c
main(argc=6, argv=["./push_swap", "3", "2", "1", "5", "4"])
│
├─▶ 1. PARSING
│   ├─ Validar cada argumento com is_valid_input()
│   ├─ Converter com safe_atoi() → [3, 2, 1, 5, 4]
│   ├─ Checar duplicatas → OK
│   └─ Criar pilha A: 3→2→1→5→4→NULL
│
├─▶ 2. NORMALIZAÇÃO
│   ├─ Ordenar valores: [1, 2, 3, 4, 5]
│   ├─ Atribuir índices:
│   │   1→0, 2→1, 3→2, 4→3, 5→4
│   └─ Pilha A normalizada: 2→1→0→4→3→NULL
│
├─▶ 3. CHECAGEM RÁPIDA
│   └─ is_sorted()? → Não, continuar
│
├─▶ 4. ESCOLHER ALGORITMO
│   ├─ stack_size() = 5
│   └─ Usar sort_five()
│
├─▶ 5. EXECUTAR ORDENAÇÃO
│   ├─ sort_five() aplica operações:
│   │   pb → imprime "pb"
│   │   pb → imprime "pb"
│   │   sa → imprime "sa"
│   │   pa → imprime "pa"
│   │   pa → imprime "pa"
│   └─ Pilha A final: 0→1→2→3→4→NULL (ordenada!)
│
└─▶ 6. LIMPEZA
    ├─ stack_clear(&stack_a)
    ├─ stack_clear(&stack_b)
    └─ return 0
```

### **Saída** (stdout):
```
pb
pb
sa
pa
pa
```

---

## 🎯 Critérios de Avaliação

### **Performance (número de operações)**

| Tamanho | Operações máximas | Nota |
|---------|-------------------|------|
| 3 números | ≤ 3 | ✅ |
| 5 números | ≤ 12 | ✅ |
| 100 números | ≤ 700 | ✅ 5/5 pontos |
| 100 números | ≤ 900 | 4/5 pontos |
| 100 números | ≤ 1100 | 3/5 pontos |
| 500 números | ≤ 5500 | ✅ 5/5 pontos |
| 500 números | ≤ 7000 | 4/5 pontos |

### **Comportamento com erros**

Deve imprimir `"Error\n"` no stderr e sair se:
- ❌ Argumento não é inteiro
- ❌ Argumento está fora do intervalo de `int`
- ❌ Há números duplicados
- ❌ Argumento vazio ou inválido

---

## 🧠 Estratégias de Ordenação

### **1. Para N ≤ 3 (Hardcoded)**
```
Todos os casos possíveis resolvidos com no máximo 2 operações.
Exemplo: [3,2,1] → sa + rra → [1,2,3]
```

### **2. Para N = 4-5 (Híbrido)**
```
1. Push os 2 menores para B
2. Ordenar os 3 restantes em A (sort_three)
3. Push de volta para A na ordem correta
```

### **3. Para N > 5 (Radix Sort em base 2)**
```
1. Normalizar valores para 0..N-1
2. Iterar sobre cada bit (do LSB ao MSB)
3. Para cada bit:
   - Se bit = 0: pb (manda para B)
   - Se bit = 1: ra (mantém em A)
4. Depois de processar todos os elementos: pa tudo de volta
5. Repetir para o próximo bit

Complexidade: O(N * log N)
```

**Exemplo visual (3 números: [2,0,1]):**
```
Bit 0 (LSB):
[2,0,1] → 2=10b (bit0=0) → pb
[0,1]   → 0=00b (bit0=0) → pb
[1]     → 1=01b (bit0=1) → ra
Depois: pa pa → [0,2,1]

Bit 1:
[0,2,1] → 0=00b (bit1=0) → pb
[2,1]   → 2=10b (bit1=1) → ra
[1]     → 1=01b (bit1=0) → pb
Depois: pa pa pa → [0,1,2] ✅ ordenado
```

---

## 📂 Estrutura Final de Arquivos

```
push_swap/
├── Makefile              # compilação
├── push_swap.h           # header com structs e protótipos
├── README.md             # documentação do projeto
├── VISAO_GERAL.md        # este arquivo
│
├── main.c                # ponto de entrada
├── is_valid_input.c      # validação de tokens ✅
├── parse_input.c         # parsing de argumentos
├── error.c               # tratamento de erros
│
├── stack_utils.c         # funções básicas da pilha
├── stack_checks.c        # is_sorted, min, max, etc.
│
├── operations_swap.c     # sa, sb, ss
├── operations_push.c     # pa, pb
├── operations_rotate.c   # ra, rb, rr
├── operations_reverse.c  # rra, rrb, rrr
│
├── sort_small.c          # algoritmos para N≤5
├── sort_radix.c          # Radix Sort para N>5
│
└── libft/                # biblioteca padrão da 42
    ├── libft.h
    ├── ft_isdigit.c
    ├── ft_putstr_fd.c
    └── ...
```

---

## 🚀 Ordem de Implementação Recomendada

1. ✅ **Validação de input** (is_valid_input.c) — COMPLETO
2. ⬜ **Estrutura das pilhas** (stack_utils.c)
3. ⬜ **Operações básicas** (operations_*.c)
4. ⬜ **Parsing completo** (parse_input.c)
5. ⬜ **Algoritmos pequenos** (sort_small.c)
6. ⬜ **Radix Sort** (sort_radix.c)
7. ⬜ **Main funcional** (main.c)
8. ⬜ **Testes e otimização**

---

## 🧪 Como Testar

### **Teste manual**
```bash
make
./push_swap 3 2 1
# Saída esperada: lista de operações
```

### **Teste com checker (se disponível)**
```bash
ARG="4 67 3 87 23"
./push_swap $ARG | ./checker $ARG
# Esperado: OK
```

### **Contar operações**
```bash
ARG=$(seq 1 100 | shuf)
./push_swap $ARG | wc -l
# Esperado: ≤ 700 para 100 números
```

### **Teste de erros**
```bash
./push_swap "abc"          # Error
./push_swap 1 2 2          # Error (duplicata)
./push_swap 2147483648     # Error (overflow)
```

---

## 📚 Recursos Adicionais

### **Conceitos importantes**:
- Lista ligada (singly linked list)
- Normalização de valores
- Radix Sort
- Complexidade algorítmica
- Gerenciamento de memória (malloc/free)

### **Ferramentas úteis**:
- `valgrind` para detectar memory leaks
- `norminette` para verificar norma da 42
- Visualizadores online de push_swap

---

## ✅ Checklist de Entrega

- [ ] Código compila sem warnings (`-Wall -Wextra -Werror`)
- [ ] Makefile com regras: all, clean, fclean, re
- [ ] Sem memory leaks (valgrind)
- [ ] Tratamento de erros completo
- [ ] Funciona com 3, 5, 100, 500 números
- [ ] Número de operações dentro dos limites
- [ ] Norminette OK
- [ ] README.md documentado

---

**Última atualização**: 01/11/2025  
**Status do projeto**: 🟡 Em desenvolvimento (parsing completo, faltam operações e algoritmos)
