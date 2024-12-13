import sys
import numpy as np
from gpytoolbox import triangle_triangle_distance

def intersects(triangle1, triangle2):
    assert(len(triangle1) == 9 and len(triangle2) == 9)
    s0 = np.array(triangle1[0:3])
    s1 = np.array(triangle1[3:6])
    s2 = np.array(triangle1[6:9])
    t0 = np.array(triangle2[0:3])
    t1 = np.array(triangle2[3:6])
    t2 = np.array(triangle2[6:9])
    dist = triangle_triangle_distance(s0,s1,s2,t0,t1,t2)
    return dist == 0

def nice_format(triangle_vertices):
    a1, a2, a3 = triangle_vertices[0:3]
    a4, a5, a6 = triangle_vertices[3:6]
    a7, a8, a9 = triangle_vertices[6:9]
    
    return f"triangle(({a1}, {a2}, {a3}), ({a4}, {a5}, {a6}), ({a7}, {a8}, {a9}))"

def main():
    # Check if the filename and the chosen triangle number are provided as a command line argument
    if len(sys.argv) != 3:
        print(f"Usage: python3 {sys.argv[0]} <data.in> <chosen triangle number>")
        return

    filename = sys.argv[1]
    the_chosen = int(sys.argv[2])

    try:
        with open(filename, 'r') as file:
            # Read all lines from the file and split them into tokens
            content = file.read().splitlines()
            numbers = []

            # Extract float values from the content, ignoring empty lines
            for line in content:
                # Split by whitespace and filter out empty strings
                numbers.extend([float(num) for num in line.split() if num.strip()])

            # The first number is the count of triangles
            num_triangles = int(numbers[0])
            triangles = []
            index = 1

            # Read the triangle vertices
            for i in range(num_triangles):
                triangle = []
                for j in range(9):
                    triangle.append(numbers[index])
                    index += 1
                triangles.append(triangle)

    except FileNotFoundError:
        print(f"Error: The file '{filename}' was not found.")
        return
    except ValueError:
        print("Error: Invalid data format in the file.")
        return

    for i in range(num_triangles):
        if i != the_chosen:
            if intersects(triangles[the_chosen], triangles[i]):
                print(f"The chosen intersects (at least) with triangle {i}:")
                print(nice_format(triangles[i]))
                print("The chosen one:")
                print(nice_format(triangles[the_chosen]))
                break

if __name__ == "__main__":
    main()
