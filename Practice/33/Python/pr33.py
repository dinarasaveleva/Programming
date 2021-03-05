def create(size, nach = 0, shag = 0):
    a = []
    temp = nach
    for i in range(size):
        a.append(temp)
        temp += shag
    return a
def printA(arr):
    print(arr)
    return arr
def sort(array):
    dlina = len(array) 
    for i in range(1, dlina):
        k = array[i]
        j = i
        while (j - 1 >= 0) and (array[j - 1] > k):
            array[j - 1], array[j] = array[j], array[j - 1]
            j = j - 1
        array[j] = k

print("Введите размер: ", end = '')
sizepol = int(input())
print("Введите первый элемент: ", end = '')
nach = int(input())
print("Введите шаг: ", end = '')
shag = int(input())

if (1<sizepol and sizepol < 10000 and -10000<nach and nach <10000 and -10000 < shag and shag < 10000):
    a = create(sizepol, nach, shag)
    sort(a)
    printA(a)
else:
    print("Error")