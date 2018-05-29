#!/usr/bin/env python2
# -*- coding: utf-8 -*-
"""
Created on Sat May 19 18:35:10 2018

@author: jorge
"""

import matplotlib.pyplot as plt
import matplotlib.animation as animation
import serial
import threading
import serial.tools.list_ports

#Volumen
h_v = []
#Presión
h_p = []
#Temperatura
t = 0

temp_p, temp_v, temp_t = [], [], 0

M = 50
N = 100000

comlist = serial.tools.list_ports.comports()
connected = []

for element in comlist:
    connected.append(element.device)

arduino = serial.Serial(connected[0], 115200, timeout=0.005)

def init():
    global h_v, h_p, t,temp_p, temp_v, temp_t
    
    h_v = [0] * M
    h_p = [0] * M
    t = 0
    temp_p = [0] * M
    temp_v = [0] * M
    temp_t = 0
    
    line.set_data(h_v, h_p)
    return line,

def animate(index, val,  line):
    global h_p, h_v, t, temp_p, temp_v, temp_t

    h_p, h_v, t = temp_p, temp_v, temp_t
    
    plt.title("T = " + str(t) + r"$^\circ C$")                
    line.set_data([h_v, h_p])
    return line,

def read_data():
    global temp_p, temp_v, temp_t
    while True:
        data = arduino.readline()[:-2]
        if data:
            try:
                sp, sv, st = data.split(":")
                if sp and sv and st:
                    temp_p.append(float(sp))
                    temp_v.append(float(sv) / 1023.0 * 45.2)
                    temp_p.pop(0)
                    temp_v.pop(0)
                    temp_t = float(st)
            except ValueError:
                pass

# Read data
t_read_data = threading.Thread(target=read_data)
t_read_data.start()

# Plot
fig = plt.figure()
line,  = plt.plot([], [], '-')
#plt.axis("scaled")
#plt.axis("off")
plt.suptitle(u"Diagrama PV de maquina térmica")
#plt.xticks([i for i in range(-TAM,TAM)])
#plt.yticks([i for i in range(-TAM,TAM)])
plt.grid()
plt.xlim(18, 28)
plt.ylim(600, 920)
plt.xlabel(r"$V\, / \,[cm^3]$")
plt.ylabel(r"$P\, / \,[hPa]$")

# Creando animaciones
# La funcion init se ejecuta solo al inicio de la animacion
# La funcion animate se ejecuta en cada iteracion
# La animacion se ejecuta N + 1 veces con el orden de indices dado por range(N + 1), como 0, 1, 2, 3, 4... N
# interval define el intervalo de tiempo entra cada animacion en milisegundos
# la opcion blit permite optimizar la animcacion, pero no sirve en todos los casos
# range(N + 1) y fargs, representan los argumentos obligatorios para la funcion animate
# retornando en "anim" es posible guardar la animacion posteriormente
anim = animation.FuncAnimation(fig, animate, range(N + 1),  fargs=(0,  line), interval = 100,  init_func=init,  repeat = False,  blit=False)

#anim.save('maquina_termica.mp4', fps=100, extra_args=['-vcodec', 'libx264'])

plt.show()
