def main():
    # Read a line of input from standard input
    input_numbers = input("Enter nine float numbers separated by spaces: ")
    
    # Split the input string into a list of strings and convert them to floats
    numbers = list(map(float, input_numbers.split()))
    
    # Check if we have exactly nine numbers
    if len(numbers) != 9:
        print("Error: Please enter exactly nine float numbers.")
        return
    
    # Unpack the numbers into three tuples
    a1, a2, a3 = numbers[0:3]
    a4, a5, a6 = numbers[3:6]
    a7, a8, a9 = numbers[6:9]
    
    # Format and print the output
    output = f"triangle(({a1}, {a2}, {a3}), ({a4}, {a5}, {a6}), ({a7}, {a8}, {a9}))"
    print(output)

if __name__ == "__main__":
    main()