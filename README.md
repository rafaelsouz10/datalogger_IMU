# Estação Meteorológica Interativa EmbarcaTech

---

## 🎯 Descrição do Projeto
Projeto desenvolvido no contexto do EmbarcaTech, utilizando a placa BitDogLab com a Raspberry Pi Pico W para criar um datalogger portátil de sensores inerciais (IMU). O sistema realiza a captura de dados do acelerômetro e giroscópio (MPU6050) em tempo real e os armazena em um cartão microSD em formato .csv. Também fornece sinalização visual e sonora dos estados do sistema, além de um script Python externo para análise dos dados capturados.

---

## ⚙️ Requisitos

- **Microcontrolador**: Raspberry Pi Pico W
- **Editor de Código**: Visual Studio Code (VS Code)
- **SDK do Raspberry Pi Pico** devidamente configurado
- **Ferramentas de build**: CMake e Ninja

---

## Instruções de Uso

### 1. Clone o Repositório
```bash
git clone https://github.com/rafaelsouz10/datalogger_IMU.git
cd datalogger_IMU
code .
```

---

### 2. Instale as Dependências

### 2.1 Certifique-se de que o SDK do Raspberry Pi Pico está configurado corretamente no VS Code. As extensões recomendadas são:

- **C/C++** (Microsoft).
- **CMake Tools**.
- **Raspberry Pi Pico**.


### 3. Configure o VS Code

Abra o projeto no Visual Studio Code e siga as etapas abaixo:

1. Certifique-se de que as extensões mencionadas anteriormente estão instaladas.
2. No terminal do VS Code, compile o código clicando em "Compile Project" na interface da extensão do Raspberry Pi Pico.
3. O processo gerará o arquivo `.uf2` necessário para a execução no hardware real.

---

### 4. Teste no Hardware Real

#### Utilizando a Placa de Desenvolvimento BitDogLab com Raspberry Pi Pico W:

1. Conecte a placa ao computador no modo BOTSEEL:
   - Pressione o botão **BOOTSEL** (localizado na parte de trás da placa de desenvolvimento) e, em seguida, o botão **RESET** (localizado na frente da placa).
   - Após alguns segundos, solte o botão **RESET** e, logo depois, solte o botão **BOOTSEL**.
   - A placa entrará no modo de programação.

2. Compile o projeto no VS Code utilizando a extensão do [Raspberry Pi Pico W](https://marketplace.visualstudio.com/items?itemName=raspberry-pi.raspberry-pi-pico):
   - Clique em **Compile Project**.

3. Execute o projeto clicando em **Run Project USB**, localizado abaixo do botão **Compile Project**.

---

### 🔌 5. Conexões e Esquemático
Abaixo está o mapeamento de conexões entre os componentes e a Raspberry Pi Pico W:

| **Componentes**        | **Pino Conectado (GPIO)** |
|------------------------|---------------------------|
| Display SSD1306 (SDA1) | GPIO 14                   |
| Display SSD1306 (SCL1) | GPIO 15                   |
| LED_VERDE              | GPIO 12                   |
| LED VERMELHO           | GPIO 13                   |
| LED AZUL               | GPIO 11                   |
| Buzzer                 | GPIO 21                   |
| Botão A                | GPIO 5                    |
| Botão B                | GPIO 6                    |
| MPU6050 (SDA0)         | GPIO 0                    |
| MPU6050 (SCL0)         | GPIO 1                    |
| Cartão SD (SPI)        | GPIO padrão SPI           |

---

---

## 📌 Funcionamento do Sistema

### 🧠 Lógica de Operação

O sistema realiza a captura de dados da IMU (aceleração e giroscópio) e salva em um cartão SD em tempo real. O usuário pode controlar a operação por meio de dois botões físicos, com feedback visual (LEDs) e sonoro (buzzer).

### 🔄 Estados e Comportamentos

| **Estado**         | **Descrição**                                 |
|--------------------|-----------------------------------------------|
| **Inicializando**  | Sistema ligado, aguardando montagem do SD     | 
| **Pronto**         | SD montado, pronto para iniciar gravação      |
| **Gravando**       | Dados sendo capturados e salvos               | 
| **Pausa**          | Gravação encerrada, aguardando nova ação      |
| **Erro SD**        | Falha na montagem ou na gravação do cartão    |

### 🔘 Botões

- **Botão A (GPIO 4)**: Inicia ou pausa a gravação de dados.
- **Botão B (GPIO 5)**: Monta ou desmonta o cartão microSD.

### 💾 Arquivo Gerado

- Nome: `dados_imu.csv`
- Formato: delimitado por ponto e vírgula `;`
- Colunas: `numero_amostra;accel_x;accel_y;accel_z;gyro_x;gyro_y;gyro_z`

### 🔔 Alertas

- **1 beep curto** ao iniciar gravação.
- **2 beeps curtos** ao parar a gravação.
- **Som contínuo + LED piscando** em caso de erro.

---

## 📌 Funcionamento do Sistema

### 🧠 Lógica de Operação

O sistema realiza a captura de dados da IMU (aceleração e giroscópio) e salva em um cartão SD em tempo real. O usuário pode controlar a operação por meio de dois botões físicos, com feedback visual (LEDs) e sonoro (buzzer).

### 🔄 Estados e Comportamentos

| **Estado**         | **Descrição**                                  | **Indicação Visual/Sonora**                         |
|--------------------|-----------------------------------------------|-----------------------------------------------------|
| **Inicializando**  | Sistema ligado, aguardando montagem do SD     | 🔴 Ambos os LEDs desligados                         |
| **Pronto**         | SD montado, pronto para iniciar gravação      | 🟢 LED Verde aceso                                  |
| **Gravando**       | Dados sendo capturados e salvos               | 🔴 LED Vermelho aceso + 1 beep curto (início)       |
| **Pausa**          | Gravação encerrada, aguardando nova ação      | 🟢 LED Verde aceso + 2 beeps curtos (parada)        |
| **Erro SD**        | Falha na montagem ou na gravação do cartão    | 🔴 LED Vermelho piscando + buzzer contínuo          |

### 🔘 Botões

- **Botão A (GPIO 4)**: Inicia ou pausa a gravação de dados.
- **Botão B (GPIO 5)**: Monta ou desmonta o cartão microSD.

### 💾 Arquivo Gerado

- Nome: `dados_imu.csv`
- Formato: delimitado por ponto e vírgula `;`
- Colunas: `numero_amostra;accel_x;accel_y;accel_z;gyro_x;gyro_y;gyro_z`

### 🔔 Alertas

- **1 beep curto** ao iniciar gravação.
- **2 beeps curtos** ao parar a gravação.
- **Som contínuo + LED piscando** em caso de erro.

---

### 8. Vídeos Demonstrativo

**Click [AQUI](https://drive.google.com/file/d/1bT5r8TBGB5UhzXl5Hbcd9m8Xn3FEGAQv/view?usp=sharing) para acessar o link do Vídeo Ensaio**
