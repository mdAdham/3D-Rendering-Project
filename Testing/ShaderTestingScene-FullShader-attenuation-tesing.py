constant = 1.0
linear = 0.7
quadratic = 1.8

distance = 2.0

while distance != -1:
    distance = float(input("Enter the distance: "))
    attenuation = 1.0 / (constant + (linear * distance) + (quadratic * distance * distance))
    print(attenuation)
