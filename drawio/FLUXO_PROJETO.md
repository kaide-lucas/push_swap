# 📚 FLUXO COMPLETO DO PROJETO PUSH_SWAP

## 🎯 Visão Geral

O Push Swap é um programa que recebe números como argumentos e imprime uma sequência de operações para ordená-los usando duas pilhas (A e B).

---

## 🔄 FLUXO DE EXECUÇÃO DETALHADO

```
┌─────────────────────────────────────────────────────────────┐
│                     ./push_swap 3 2 5 1 4                   │
│                           (ENTRADA)                          │
└─────────────────────────────────────────────────────────────┘
                              │
                              ▼
┌─────────────────────────────────────────────────────────────┐
│                    1. MAIN (main.c)                          │
├─────────────────────────────────────────────────────────────┤
│  • Verifica se argc >= 2                                     │
│  • Se não: retorna 0 (sem fazer nada)                       │
│  • Se sim: continua...                                       │
└─────────────────────────────────────────────────────────────┘
                              │
                              ▼
┌─────────────────────────────────────────────────────────────┐
│           2. PARSE & VALIDAÇÃO (parse_input.c)              │
├─────────────────────────────────────────────────────────────┤
│  parse_arguments(argc, argv):                               │
│    │                                                          │
│    ├─► Para cada argumento (argv[1]...argv[n]):            │
│    │   ├─► safe_atoi() → converte string para int          │
│    │   │   └─► is_valid_input() → valida formato           │
│    │   ├─► stack_new() → cria novo nó                      │
│    │   └─► stack_add_back() → adiciona na pilha            │
│    │                                                          │
│    ├─► has_duplicates() → verifica duplicatas              │
│    └─► normalize_values() → atribui índices (0,1,2...)    │
│                                                              │
│  RESULTADO: Stack A preenchida e validada                   │
│             Stack B inicializada como NULL                   │
└─────────────────────────────────────────────────────────────┘
                              │
                              ▼
┌─────────────────────────────────────────────────────────────┐
│         3. ALGORITMO DE ORDENAÇÃO (push_swap.c)             │
├─────────────────────────────────────────────────────────────┤
│  push_swap(&stack_a, &stack_b):                             │
│    │                                                          │
│    ├─► is_sorted() → Já está ordenado?                     │
│    │   └─► Se SIM: retorna (não faz nada)                  │
│    │   └─► Se NÃO: continua...                             │
│    │                                                          │
│    └─► radix_sort():                                        │
│        │                                                      │
│        ├─► get_max_bits() → Calcula bits necessários       │
│        │   Ex: 5 números = índices 0-4 = 3 bits            │
│        │                                                      │
│        └─► Para cada bit (0 até max_bits):                 │
│            │                                                  │
│            ├─► Para cada número na stack_a:                │
│            │   │                                             │
│            │   ├─► Bit atual é 0?                          │
│            │   │   └─► SIM: pb (move para stack_b)        │
│            │   │   └─► NÃO: ra (rotaciona stack_a)        │
│            │   │                                             │
│            │   └─► (imprime operação na stdout)            │
│            │                                                  │
│            └─► Devolve tudo de B para A: pa...             │
│                                                              │
│  RESULTADO: Stack A ordenada, operações impressas           │
└─────────────────────────────────────────────────────────────┘
                              │
                              ▼
┌─────────────────────────────────────────────────────────────┐
│              4. OPERAÇÕES (swap.c, push.c, etc)             │
├─────────────────────────────────────────────────────────────┤
│  Cada operação:                                              │
│    1. Manipula as pilhas (troca, move, rotaciona)          │
│    2. Imprime o comando (sa, pb, ra, etc)                   │
│                                                              │
│  SWAP (swap.c):      PUSH (push.c):      ROTATE (rotate.c):│
│  • sa: troca A       • pa: B→A           • ra: A[0]→fim    │
│  • sb: troca B       • pb: A→B           • rb: B[0]→fim    │
│  • ss: troca ambas                       • rr: ambas        │
│                                                              │
│  REVERSE ROTATE (reverse.c):                                │
│  • rra: A[fim]→topo                                         │
│  • rrb: B[fim]→topo                                         │
│  • rrr: ambas                                                │
└─────────────────────────────────────────────────────────────┘
                              │
                              ▼
┌─────────────────────────────────────────────────────────────┐
│                   5. LIMPEZA E SAÍDA                         │
├─────────────────────────────────────────────────────────────┤
│  • stack_clear(&stack_a) → libera memória de A             │
│  • stack_clear(&stack_b) → libera memória de B             │
│  • return (0) → sucesso                                     │
└─────────────────────────────────────────────────────────────┘
                              │
                              ▼
                          (STDOUT)
                    pb
                    ra
                    pb
                    pa
                    pa
```

---

## 📊 ESTRUTURA DE DADOS

```c
typedef struct s_stack
{
    int value;              // Valor original (ex: 42, 21, 84)
    int index;              // Índice normalizado (0, 1, 2...)
    struct s_stack *next;   // Próximo nó da lista
} t_stack;
```

### Exemplo de Normalização:
```
Input:     [42, 21, 84, 63]
           ↓
Values:    [42, 21, 84, 63]
Indices:   [ 1,  0,  3,  2]  ← Usado no Radix Sort
```

---

## 🔢 EXEMPLO PRÁTICO: `./push_swap 3 2 1`

### FASE 1: Parsing
```
Stack A: [3] → [2] → [1] → NULL
         val  val  val
         idx  idx  idx
```

### FASE 2: Normalização
```
Stack A: [3] → [2] → [1]
         ↓     ↓     ↓
      idx=2  idx=1  idx=0

Valores ordenados: 1 < 2 < 3
Índices:          0   1   2
```

### FASE 3: Radix Sort (3 números = 2 bits)

**Bit 0 (menos significativo):**
```
Índices em binário:
2 = 10  → bit[0] = 0  → pb
1 = 01  → bit[0] = 1  → ra
0 = 00  → bit[0] = 0  → pb

Stack A: [3(2)] → [2(1)] → [1(0)]
         
Processo bit 0:
  [3(2=10)] bit 0 = 0 → pb → Stack B: [3]
  [2(1=01)] bit 0 = 1 → ra → Stack A: [2]
  [1(0=00)] bit 0 = 0 → pb → Stack B: [1,3]
  
  Devolve tudo: pa, pa
  Stack A: [1,3,2]
```

**Bit 1 (mais significativo):**
```
  [1(0=00)] bit 1 = 0 → pb → Stack B: [1]
  [3(2=10)] bit 1 = 1 → ra → Stack A: [3]
  [2(1=01)] bit 1 = 0 → pb → Stack B: [2,1]
  
  Devolve tudo: pa, pa
  Stack A: [2,1,3] ... continua até ordenar
```

---

## 📁 ARQUIVOS E RESPONSABILIDADES

| Arquivo | Funções | Propósito |
|---------|---------|-----------|
| **main.c** | `main()` | Orquestra o fluxo geral |
| **parse_input.c** | `parse_arguments()` | Processa argv e valida |
| **is_valid_input.c** | `is_valid_input()`, `safe_atoi()` | Valida strings e converte |
| **cheker.c** | `has_duplicates()`, `normalize_values()` | Verifica duplicatas e normaliza |
| **stack_utilis.c** | `stack_new()`, `stack_add_back()`, `stack_clear()` | Gerencia estrutura da pilha |
| **push_swap.c** | `push_swap()`, `radix_sort()`, funções auxiliares | Algoritmo de ordenação |
| **push.c** | `push()`, `pa()`, `pb()` | Operações de transferência |
| **swap.c** | `swap()`, `sa()`, `sb()`, `ss()` | Operações de troca |
| **rotate.c** | `rotate()`, `ra()`, `rb()`, `rr()` | Operações de rotação |
| **reverse.c** | `reverse_rotate()`, `rra()`, `rrb()`, `rrr()` | Operações de rotação reversa |

---

## 🎯 CASOS DE ERRO

```c
// 1. Sem argumentos
./push_swap
→ return (0) // Não faz nada

// 2. Argumento inválido
./push_swap abc
→ write(2, "Error\n", 6) + return (1)

// 3. Número fora do range (int overflow)
./push_swap 2147483648
→ write(2, "Error\n", 6) + return (1)

// 4. Duplicatas
./push_swap 1 2 1
→ write(2, "Error\n", 6) + return (1)

// 5. Já ordenado
./push_swap 1 2 3
→ return (0) // Não imprime nada
```

---

## 🚀 OTIMIZAÇÕES FUTURAS

1. **Casos pequenos**: Para 2-3 elementos, usar casos específicos em vez de Radix
2. **Pré-ordenação**: Detectar sequências já ordenadas
3. **Chunk sorting**: Para grandes volumes, dividir em chunks

---

## 💡 PONTOS-CHAVE

✅ **Separação de responsabilidades**: Cada arquivo tem uma função específica
✅ **Validação robusta**: Múltiplas camadas de verificação
✅ **Normalização**: Simplifica o algoritmo usando índices
✅ **Radix Sort**: Eficiente O(n*k) onde k = número de bits
✅ **Memória limpa**: Sempre libera recursos alocados

---

**Resumo**: Input → Parse → Valida → Normaliza → Ordena → Imprime → Limpa → Sai
