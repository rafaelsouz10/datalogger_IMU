import pandas as pd
import matplotlib.pyplot as plt

# Lê o arquivo CSV
df = pd.read_csv("dados_imu.csv", sep=';')

# Gera vetor de tempo com base no número de amostra
tempo = df['numero_amostra']

# Plot acelerômetro
plt.figure("Acelerômetro")
plt.plot(tempo, df['accel_x'], label='Ax')
plt.plot(tempo, df['accel_y'], label='Ay')
plt.plot(tempo, df['accel_z'], label='Az')
plt.title("Dados do Acelerômetro")
plt.xlabel("Tempo (amostras)")
plt.ylabel("Aceleração")
plt.legend()
plt.grid(True)

# Plot giroscópio
plt.figure("Giroscópio")
plt.plot(tempo, df['gyro_x'], label='Gx')
plt.plot(tempo, df['gyro_y'], label='Gy')
plt.plot(tempo, df['gyro_z'], label='Gz')
plt.title("Dados do Giroscópio")
plt.xlabel("Tempo (amostras)")
plt.ylabel("Velocidade Angular")
plt.legend()
plt.grid(True)

plt.show()
