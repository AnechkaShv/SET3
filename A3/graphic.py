import matplotlib.pyplot as plt
import numpy as np

# Путь к файлу с координатами
file_path = 'randomTests.txt'
file_path2 = 'randomTests5.txt'

# Чтение файла
with open(file_path, 'r', encoding = 'utf-8') as file:
    y_coords = list(map(float, file.readline().strip().split()))

with open(file_path2, 'r', encoding = 'utf-8') as file:
    y_coords2 = list(map(float, file.readline().strip().split()))

# Генерация X-координат
x_coords = np.arange(500, 10000 + 1, 100)


# Построение графика
plt.figure(figsize=(20, 12))
plt.plot(x_coords, y_coords, marker='o', linestyle='-', label='Merge sort', color='r')
plt.plot(x_coords, y_coords2, marker='o', linestyle='-', label='Merge + insertion sort', color='b')

plt.title("Сравнение на почти отсортированных массивах")
plt.xlabel('Размер массива')
plt.ylabel('Время в микросекундах')
plt.grid(True)
plt.legend()
plt.show()