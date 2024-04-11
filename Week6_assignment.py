def quick_sort(arr):
    if len(arr) <= 1:
        return arr
    pivot = arr[len(arr) // 2]
    smaller, equal, larger = [], [], []
    for element in arr:
        if element < pivot:
            smaller.append(element)
        elif element == pivot:
            equal.append(element)
        else:
            larger.append(element)
    return quick_sort(smaller) + equal + quick_sort(larger)

def merge_arrays(arr1, arr2):
    merged = []
    i = j = 0
    while i < len(arr1) and j < len(arr2):
        if arr1[i] == 'Xanh' or (arr1[i] == 'Đỏ' and arr2[j] == 'Trắng'):
            merged.append(arr1[i])
            i += 1
        else:
            merged.append(arr2[j])
            j += 1
    while i < len(arr1):
        merged.append(arr1[i])
        i += 1
    while j < len(arr2):
        merged.append(arr2[j])
        j += 1
    return merged

arr = ['Đỏ', 'Xanh', 'Trắng', 'Trắng', 'Đỏ', 'Xanh', 'Xanh', 'Đỏ']
sorted_arr = quick_sort(arr)
print("Sorted array:", sorted_arr)

new_arr = ['Xanh', 'Đỏ', 'Trắng']
merged_arr = merge_arrays(sorted_arr, new_arr)
print("Merged array:", merged_arr)