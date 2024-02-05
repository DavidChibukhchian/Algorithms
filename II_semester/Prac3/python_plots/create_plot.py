import matplotlib.pyplot as pyplot

#---------------------------------------------------------------------------------------------------------------
source_file1  = '../results/quick_sort_Central.txt'
source_file2  = '../results/merge_sort.txt'
source_file3  = '../results/LSD_sort.txt'
title         = 'Quick, Merge and LSD sorts'
name_of_image = 'plots/quick_merge_LSD_sorts.png'

pyplot.axis([0, 10000000, 0, 120])
#---------------------------------------------------------------------------------------------------------------

source1 = open(source_file1, 'r').read().splitlines()
source2 = open(source_file2, 'r').read().splitlines()
source3 = open(source_file3, 'r').read().splitlines()

x1 = [float (source1[i].split()[0]) for i in range(len(source1))]
y1 = [float (source1[i].split()[1]) for i in range(len(source1))]

x2 = [float (source2[i].split()[0]) for i in range(len(source2))]
y2 = [float (source2[i].split()[1]) for i in range(len(source2))]

x3 = [float (source3[i].split()[0]) for i in range(len(source3))]
y3 = [float (source3[i].split()[1]) for i in range(len(source3))]

pyplot.title(title, fontsize = 20, fontname = 'Times New Roman')
pyplot.xlabel('Size', color='black')
pyplot.ylabel('Time', color='black')
pyplot.grid(True)

pyplot.plot (x1, y1, 'ro')
pyplot.plot (x2, y2, 'go')
pyplot.plot (x3, y3, 'bo')

#---------------------------------------------------------------------------------------------------------------
pyplot.legend(['Quick sort', 'Merge sort', 'LSD sort'], loc = 2)
#---------------------------------------------------------------------------------------------------------------

pyplot.savefig(name_of_image)