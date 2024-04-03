a = input("Enter the colors: ").split() 
print(a)
converted_a = []

for color in a:
    if color == 'red':
        converted_a.append(0)
    elif color == 'white':
        converted_a.append(1)
    elif color == 'blue':
        converted_a.append(2)
print(converted_a)

for i in range(0, len(converted_a)):
    min_index = i
    for j in range(i+1,len(converted_a)):
        if converted_a[j] < converted_a[min_index]:
            min_index = j
    (converted_a[min_index], converted_a[i]) = (converted_a[i], converted_a[min_index])

print(converted_a)
           
