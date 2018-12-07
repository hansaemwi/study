def bubble_sort(alist):
    for i in range(len(alist)-1, 0, -1):
        for j in range(i):
            if alist[j] > alist[j+1]:
                temp = alist[j]
                alist[j] = alist[j+1]
                alist[j+1] = temp
    return alist

print(bubble_sort([7, 18, 20, 16, 3, 4, 5, 87]))