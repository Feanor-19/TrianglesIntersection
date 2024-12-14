#!/bin/bash

DATA_REF="ref_test_data/data_ref.out"
DATA_FACT="ref_test_data/data_fact.out"
DATA_IN="ref_test_data/data.in"

NUM_OF_TRIANGLES=100
CENTER_BOUND=50
TR_SIZE_BOUND=100

iteration=0

cd build/Release && \
cmake ../.. -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Release && \
cmake --build .
cd ../..

# Loop until a difference is found
while true; do
    iteration=$((iteration + 1))
    echo "Iteration: $iteration"

    python3 scripts/gen_set_trs.py "$NUM_OF_TRIANGLES" "$CENTER_BOUND" "$TR_SIZE_BOUND" "$DATA_IN" > /dev/null

    python3 scripts/ref_triangle_intsc.py "$DATA_IN" > "$DATA_REF"

    ./build/Release/Driver < "$DATA_IN" > "$DATA_FACT"

    if cmp -s "$DATA_REF" "$DATA_FACT"; then
        echo "Good, no difference!"
    else
        echo ":("
        echo "Differences between $DATA_REF and $DATA_FACT:"
        
        # Lines starting with - indicate lines present in data_ref.out but not in data_fact.out.
        # Lines starting with + indicate lines present in data_fact.out but not in data_ref.out.
        diff -u "$DATA_REF" "$DATA_FACT" | grep -E '^@@|^-|^\+'
        break
    fi

done