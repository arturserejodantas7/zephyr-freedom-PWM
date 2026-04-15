<<<<<<< HEAD
# zephyr-freedom-PWM
Descrição do Projeto

O projeto está disponível em:
🔗 https://drive.google.com/drive/folders/1zfYbLzi3AJMG4G_-0UxW7b4h-hFiz7U9?usp=sharing

Os arquivos estão organizados por atividades (1 a 4) e, dentro de cada uma, há subpastas para cada teste (ex: 1.1 LED Verde (1s), 1.2 LED Verde (2s)).

Cada subpasta contém as evidências (fotos e GIFs) correspondentes.

O trabalho contempla:

1. Testes básicos com GPIO (LED)
2. Integração de Biblioteca PWM (pwm_z42)
3. Validação de Hardware: Ponte H
4. Integração Final (Controle Digital)

5. # zephyr-freedom-PWM
Controle de LED e motor usando PWM na placa Freedom com VSCode, Zephyr, MCUXpresso e PlatformIO.

**IMPORTANTE**:

- SUBA OS CÓDIGOS A CADA TESTE REALIZADO COM SUCESSO, DE FORMA **INCREMENTAL**.

- DESCREVA OS RESULTADOS OBTIDOS, INCLUINDO TAMBÉM SUAS **EVIDÊNCIAS**.

# 🏎️ Roteiro de Desenvolvimento e Testes

Este repositório contém os passos de validação técnica para o controle de motores utilizando a placa **Freedom KL25Z** com o sistema operacional **Zephyr**.

## 🛠️ Configuração Inicial (Setup)
Antes de iniciar, certifique-se de ter configurado o ambiente seguindo os guias abaixo:
* [Instalação: VSCode + Zephyr para Freedom](https://cliff-collision-333.notion.site/Instala-o-1f1a7f4c2a2b81aca6e4ce96cf7171b3)
* [Atualização para Zephyr 4.2](https://cliff-collision-333.notion.site/Atualiza-o-para-o-Zephyr-4-2-27aa7f4c2a2b802a9a3efac5c8691a84)

---

## 🟢 1. Hello World Zephyr (GPIO Básico)
**Objetivo:** Validar a instalação do Toolchain e a comunicação básica com a placa.
*Referência: [Exemplo Pisca LED RTOS](https://cliff-collision-333.notion.site/Exemplo-Pisca-LED-RTOS-1f1a7f4c2a2b8142bf66ddc7dbf306f2)*

| ID | Teste | Resultado Esperado |
|:---:|:---|:---|
| 1.1 | LED Verde (1s) | O LED onboard verde deve piscar com intervalo de 1000ms. |
| 1.2 | LED Verde (2s) | O LED onboard verde deve piscar com intervalo de 2000ms. |

**Descrição**: Validação do blink básico no LED verde onboard.

**Resultado**: Sucesso. O RTOS gerenciou os tempos de 1s e 2s via k_msleep com precisão.

| 1.1 | LED Verde (1s) | O LED onboard verde deve piscar com intervalo de 1000ms. |

<img src="evidences/1.1 LED Verde (1s) (FOTO).jpg" width="300">
<img src="evidences/1.1 LED Verde (1s) (GIF).GIF" width="300">

| 1.2 | LED Verde (2s) | O LED onboard verde deve piscar com intervalo de 2000ms. |

<img src="evidences/1.2 LED Verde (2s) (GIF).GIF" width="300">


---

## 📚 2. Integração de Biblioteca PWM (`pwm_z42`)
**Objetivo:** Validar a biblioteca de hardware e a configuração de Timers (TPM).
*Referência: [Tutorial Biblioteca PWM](https://cliff-collision-333.notion.site/PWM-Variar-a-Intensidade-do-LED-Zephyr-4-2-1f1a7f4c2a2b8115acb8c0a408af78ce) e [Artigo Embarcados](https://embarcados.com.br/biblioteca-pwm-para-frdm-kl25z/)*

| ID | Teste | Resultado Esperado |
|:---:|:---|:---|
| 2.1 | LED Laranja Fixo | O LED RGB deve exibir cor laranja constante (mix de PWM). |
| 2.2 | LED Laranja Piscante | O sinal PWM deve ser habilitado/desabilitado a cada 1s. |

Descrição: Teste de cor composta para LED laranja.

Resultado: Sucesso. A biblioteca configurou o Duty Cycle corretamente e foi possível usar mais de um LED operando em PWM, ao mesmo tempo.

| 2.1 | LED Laranja Fixo | O LED RGB deve exibir cor laranja constante (mix de PWM). |

<img src="evidences/2.1 LED Laranja Fixo (FOTO).jpg" width="300">
<img src="evidences/2.1 LED Laranja Fixo (GIF).GIF" width="300">

| 2.2 | LED Laranja Piscante | O sinal PWM deve ser habilitado/desabilitado a cada 1s. |

<img src="evidences/2.2 LED Laranja Piscante (GIF).GIF" width="300">

---

## ⚡ 3. Validação de Hardware: Ponte H

* [Guia de Uso da Ponte H L298N](https://blog.eletrogate.com/guia-definitivo-de-uso-da-ponte-h-l298n/)

**Objetivo:** Isolar problemas elétricos e garantir que os motores/bateria estão operacionais.

> **⚠️ Configuração de Hardware:**
> 1. Jumpers inseridos em **ENA** e **ENB**.
> 2. Conectar pinos **IN1** e **IN3** diretamente ao **VCC (5V)** da placa.

| ID | Teste | Resultado Esperado |
|:---:|:---|:---|
| 3.1 | Movimento Independente | Os motores devem girar em velocidade máxima ao receber alimentação. |

**Descrição**: Motores ligados diretamente ao VCC para validar a bateria e o driver L298N de forma independente.

**Resultado**: Sucesso. Torque e rotação máximos atingidos.

| 3.1 | Movimento Independente | Os motores devem girar em velocidade máxima ao receber alimentação. |

<img src="evidences/3.1 Movimento Independente.GIF" width="300">

---

## 🏁 4. Integração Final (Controle Digital)
**Objetivo:** Controlar velocidade e direção via software Zephyr.

> **⚠️ Configuração de Hardware:**
> 1. **Remover** jumpers de ENA/ENB.
> 2. Conectar **ENA -> PINO PWM1** e **ENB -> PINO PWM2** (Pinos PWM escolhidos).
> 3. Conectar **IN1/IN2/IN3/IN4** aos pinos digitais configurados no código (também é possível deixar com a configuração utilizada no teste 3 somente para movimento de ambos motores para frente).
> 4. **IMPORTANTE:** Unir o **GND** da bateria com o **GND** da KL25Z.

| ID | Teste | Resultado Esperado |
|:---:|:---|:---:|
| 4.1 | Teste Motor Único | Apenas um motor deve variar velocidade usando um pino PWM. |
| 4.2 | Teste Bi-Motor | Ambos os motores operando em sincronia para movimento em linha reta. |

**Motor Único**: Resposta linear entre o valor de PWM no código e a rotação da roda.

**Dois Motores**: Movimento sincronizado utilizando os canais 0 e 1 do TPM2 (PTB2 e PTB3).

| 4.1 | Teste Motor Único | Apenas um motor deve variar velocidade usando um pino PWM. |

<img src="evidences/4.1 Teste Motor Único.GIF" width="300">

| 4.2 | Teste Bi-Motor | Ambos os motores operando em sincronia para movimento em linha reta. |

<img src="evidences/4.2 Teste Bi-Motor.GIF" width="300">

---

