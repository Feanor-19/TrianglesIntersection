import sys
import random
import numpy as np
import math
from math import cos, sin, pi

def gen_triple(lower_bound, upper_bound):
    return np.array([random.uniform(lower_bound, upper_bound),
                     random.uniform(lower_bound, upper_bound),
                     random.uniform(lower_bound, upper_bound)])

def main():
    if len(sys.argv) != 5:
        print(f"Usage: python3 {sys.argv[0]} <N_of_triangles> <center_bound> <tr_size_bound> <filename>")
        sys.exit(1)

    N = int(sys.argv[1])
    center_bound = float(sys.argv[2])
    tr_size_bound = float(sys.argv[3])
    filename = sys.argv[4]

    print(f"N:               {N}")
    print(f"center_bound:    {center_bound}")
    print(f"tr_size_bound:   {tr_size_bound}")
    print(f"Output filename: {filename}")

    # Generate 
    generated = []
    for _ in range(N):
        center = np.array(gen_triple(0, center_bound))
        phi = gen_triple(0, 2*pi)
        psi = gen_triple(-pi/2, pi/2)
        size = random.uniform(0, tr_size_bound)
        
        points_rel = [size*np.array([cos(phi[i])*cos(psi[i]), sin(phi[i])*cos(psi[i]), sin(psi[i])]) for i in range(3)]
        
        generated.append([center + points_rel[i] for i in range(3)])

    # Write the generated to a file
    with open(filename, 'w') as file:
        file.write(f"{N}\n")
        for triangle in generated:
            for point in triangle:
                file.write(' '.join(map(str, point)))
                file.write('\n')    
            file.write('\n')

if __name__ == "__main__":
    main()
