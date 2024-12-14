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

def main():
    # Check if the filename is provided as a command line argument
    if len(sys.argv) != 2:
        print(f"Usage: python3 {sys.argv[0]} <filename>")
        return

    filename = sys.argv[1]

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

    intersecting_triangles = set()

    # Check for intersections between each pair of triangles
    for i in range(num_triangles):
        for j in range(i + 1, num_triangles):
            triangle1 = triangles[i]
            triangle2 = triangles[j]
            if intersects(triangle1, triangle2):
                intersecting_triangles.add(i)
                intersecting_triangles.add(j)

    # Print the indices of triangles that intersect
    if len(intersecting_triangles) > 0:
        print("\n".join(list(map(str, sorted(intersecting_triangles)))))

if __name__ == "__main__":
    main()
