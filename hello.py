# importando função para ler string mais facilmente
from cs50 import get_string

# receber nome do usuário
name = get_string("What is your name?\n")

# imprimir nome
print(f"hello, {name}")