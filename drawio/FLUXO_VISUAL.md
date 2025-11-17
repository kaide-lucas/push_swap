# 🎨 FLUXO VISUAL SIMPLIFICADO - PUSH_SWAP

## 📌 Entrada → Saída

```
ENTRADA:  ./push_swap 5 2 1 3 4
           ↓
SAÍDA:    pb
          pb
          ra
          pa
          pa
          ...
```

---

## 🔄 CICLO DE VIDA DO PROGRAMA

```
START
  ↓
┌─────────────────┐
│  1. VALIDAÇÃO   │  ← Argumentos válidos? Duplicatas?
└─────────────────┘
  ↓
┌─────────────────┐
│  2. CONSTRUÇÃO  │  ← Criar Stack A com os números
└─────────────────┘
  ↓
┌─────────────────┐
│  3. NORMALIZAÇÃO│  ← Converter para índices (0,1,2...)
└─────────────────┘
  ↓
┌─────────────────┐
│  4. ORDENAÇÃO   │  ← Radix Sort bit por bit
└─────────────────┘
  ↓
┌─────────────────┐
│  5. IMPRESSÃO   │  ← Cada operação vai para stdout
└─────────────────┘
  ↓
┌─────────────────┐
│  6. LIMPEZA     │  ← Liberar memória
└─────────────────┘
  ↓
END
```

---

## 🏗️ ANATOMIA DAS ESTRUTURAS

### Stack (Lista Encadeada)
```
Stack A:  [TOP] → [MID] → [BOT] → NULL
           ┌──────┐  ┌──────┐  ┌──────┐
           │val: 5│  │val: 2│  │val: 1│
           │idx: 4│  │idx: 1│  │idx: 0│
           │next ─┼─→│next ─┼─→│next ─┼─→ NULL
           └──────┘  └──────┘  └──────┘
```

---

## ⚙️ RADIX SORT - COMO FUNCIONA

### Exemplo: [3, 2, 1] → índices [2, 1, 0]

```
PASSO 1: Normalizar valores
─────────────────────────────
Valores:  3    2    1
          ↓    ↓    ↓
Ordem:    3º   2º   1º
          ↓    ↓    ↓
Índices:  2    1    0


PASSO 2: Converter para binário
─────────────────────────────────
Índice    Binário
  2    →    10
  1    →    01
  0    →    00

Precisamos de 2 bits (max = 2)


PASSO 3: Separar por BIT 0 (direita)
──────────────────────────────────────
Stack A: [3(10)] [2(01)] [1(00)]
                   ↑        ↑
         bit0=0 ──┘        └── bit0=0
         bit0=1 ───────────────┘

Se bit 0 = 0 → pb (vai para B)
Se bit 0 = 1 → ra (rotaciona A)

Resultado:
  Stack B: [3, 1]  ← números com bit 0 = 0
  Stack A: [2]     ← números com bit 0 = 1

Devolver tudo: pa, pa
  Stack A: [1, 3, 2]


PASSO 4: Separar por BIT 1 (esquerda)
───────────────────────────────────────
Repete o processo com bit 1...
Ao final: Stack A ordenada [1, 2, 3]
```

---

## 📊 OPERAÇÕES DISPONÍVEIS

### SWAP (s)
```
sa: Stack A          sb: Stack B          ss: ambas
[2] [1] [3]    →    [1] [2] [3]
 ↕                   ↕
```

### PUSH (p)
```
pa: B → A            pb: A → B
A:[1][2]  B:[3]  →  A:[3][1][2]  B:[]
   ←────
```

### ROTATE (r)
```
ra: primeiro→último  rb: idem em B       rr: ambas
[1][2][3]  →  [2][3][1]
 └─────────────→┘
```

### REVERSE ROTATE (rr)
```
rra: último→primeiro  rrb: idem em B    rrr: ambas
[1][2][3]  →  [3][1][2]
 ┌─────────────┘
```

---

## 🎯 DECISÕES DO ALGORITMO

```
┌─────────────────────────────┐
│  Stack já ordenada?         │
│  └─ SIM → PARA (nada)      │
│  └─ NÃO → continua         │
└─────────────────────────────┘
         │
         ▼
┌─────────────────────────────┐
│  Para cada BIT:             │
│   Para cada NÚMERO:         │
│     ┌─ Bit = 0? → pb       │
│     └─ Bit = 1? → ra       │
│   Devolve todos: pa...      │
└─────────────────────────────┘
         │
         ▼
    Stack ordenada!
```

---

## 🧪 TESTE MENTAL: [5, 2, 1]

```
1. Parse:         [5] → [2] → [1]
2. Normaliza:     [2] → [1] → [0]  (índices)
3. Bits:          10  → 01  → 00
4. Ordena por bit 0, depois bit 1
5. Resultado:     [0] → [1] → [2]  = [1, 2, 5] ✅
```

---

## 📝 CHECKLIST DE VALIDAÇÃO

```
✅ É número inteiro?
✅ Está no range INT_MIN..INT_MAX?
✅ Não tem duplicatas?
✅ Formato correto (não tem letras)?
   └─ Passa? → Continua
   └─ Falha? → "Error\n" e sai
```

---

## 🎓 CONCEITOS-CHAVE

| Conceito | Explicação |
|----------|------------|
| **Stack** | Pilha (LIFO - Last In First Out) |
| **Index** | Posição relativa ordenada (0 = menor) |
| **Radix** | Ordena dígito por dígito (aqui: bit por bit) |
| **Bit shifting** | `>>` move bits para direita |
| **Bit masking** | `& 1` pega o último bit |

---

## 🚀 EXECUÇÃO EM TEMPO REAL

```bash
# Terminal 1: Ver operações
./push_swap 3 2 1

# Terminal 2: Contar operações
./push_swap 3 2 1 | wc -l

# Terminal 3: Validar (futuro)
./push_swap 3 2 1 | ./checker 3 2 1
```

---

**TL;DR**: 
1. Recebe números
2. Valida e normaliza
3. Ordena com Radix Sort bit-a-bit
4. Imprime cada operação
5. Limpa e sai

✨ **Simples, eficiente e elegante!** ✨
