import sys
import random

def main():
    if len(sys.argv) != 5:
        print(f"Usage: python3 {sys.argv[0]} <N_of_triangles> <lower_bound> <top_bound> <filename>")
        sys.exit(1)

    N = int(sys.argv[1])
    lower_bound = float(sys.argv[2])
    top_bound = float(sys.argv[3])
    filename = sys.argv[4]

    print(f"N:               {N}")
    print(f"lower_bound:     {lower_bound}")
    print(f"top_bound:       {top_bound}")
    print(f"Output filename: {filename}")

    # Generate 
    generated = [[random.uniform(lower_bound, top_bound) for _ in range(3)] for _ in range(N*3)]

    # Write the generated to a file
    with open(filename, 'w') as file:
        file.write(f"{N}\n")
        for triple in generated:
            file.write(' '.join(map(str, triple)))
            file.write('\n')
        file.write('\n')

if __name__ == "__main__":
    main()
