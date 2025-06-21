#!/bin/bash

# Arrows Express Line Embarkation System Test Script
# This script automatically tests your existing arrows_express.c program
# by providing inputs and observing outputs

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

PROGRAM_NAME="arrows_express"

echo -e "${BLUE}========================================${NC}"
echo -e "${BLUE}Arrows Express Line System Test Script${NC}"
echo -e "${BLUE}========================================${NC}"

# Function to print test status
print_status() {
    if [ $1 -eq 0 ]; then
        echo -e "${GREEN}[PASS]${NC} $2"
    else
        echo -e "${RED}[FAIL]${NC} $2"
    fi
}

# Function to print section header
print_section() {
    echo -e "\n${YELLOW}=== $1 ===${NC}"
}

# Check if program exists
if [ ! -f "./${PROGRAM_NAME}" ]; then
    echo -e "${RED}Error: ${PROGRAM_NAME} not found!${NC}"
    echo "Please compile your arrows_express.c first:"
    echo "  gcc -Wall -std=c99 -o arrows_express arrows_express.c"
    echo "Or run: make"
    exit 1
fi

# Clean up previous test outputs
print_section "Cleanup"
rm -f test*_output.txt Trip-*.txt
echo "Cleaned up previous test outputs"

# Test 1: Load passenger data from file
print_section "Test 1: Loading Passenger Data from File"
echo "This test will:"
echo "- Go to Personnel menu (option 2)"
echo "- Select Load Passenger (option 4)"
echo "- Load test_passengers.txt"
echo "- Return to main menu and exit"
echo ""

cat > test1_input.txt << 'EOF'
2
4
test_passengers.txt
7
3
EOF

echo -e "${BLUE}Running Test 1...${NC}"
./${PROGRAM_NAME} < test1_input.txt > test1_output.txt 2>&1

if [ $? -eq 0 ]; then
    print_status 0 "Test 1 completed"
    echo "Check test1_output.txt for results"
    if grep -q "loaded successfully\|successfully" test1_output.txt; then
        echo -e "${GREEN}✓ Data loading appears successful${NC}"
    fi
else
    print_status 1 "Test 1 failed"
fi

# Test 2: Add new passenger manually
print_section "Test 2: Adding New Passenger Manually"
echo "This test will:"
echo "- Go to Passenger menu (option 1)"
echo "- Add passenger: Maria Rodriguez, ID: 98765432, Priority: 2"
echo "- Trip: AE104, Drop-off: option 1"
echo ""

cat > test2_input.txt << 'EOF'
1
1
AE104
Maria Rodriguez
98765432
2
1
2
3
EOF

echo -e "${BLUE}Running Test 2...${NC}"
timeout 15 ./${PROGRAM_NAME} < test2_input.txt > test2_output.txt 2>&1

if [ $? -eq 0 ]; then
    print_status 0 "Test 2 completed"
    if grep -q "successfully added\|successfully" test2_output.txt; then
        echo -e "${GREEN}✓ Passenger addition appears successful${NC}"
    fi
elif [ $? -eq 124 ]; then
    print_status 1 "Test 2 timed out (program may be waiting for input)"
    echo "Check test2_output.txt for partial results"
else
    print_status 1 "Test 2 failed"
fi

# Test 3: View passenger count and seating chart
print_section "Test 3: Viewing Passenger Count"
echo "This test will:"
echo "- Go to Personnel menu"
echo "- View passenger count for trip AE101"
echo "- Display seating chart"
echo ""

cat > test3_input.txt << 'EOF'
2
1
AE101
7
3
EOF

echo -e "${BLUE}Running Test 3...${NC}"
./${PROGRAM_NAME} < test3_input.txt > test3_output.txt 2>&1

if [ $? -eq 0 ]; then
    print_status 0 "Test 3 completed"
    if grep -q "Passenger Count\|Seating Chart" test3_output.txt; then
        echo -e "${GREEN}✓ Seating chart display appears successful${NC}"
    fi
else
    print_status 1 "Test 3 failed"
fi

# Test 4: View drop-off count
print_section "Test 4: Viewing Drop-off Count"
echo "This test will:"
echo "- Go to Personnel menu"
echo "- View drop-off count for trip AE151"
echo ""

cat > test4_input.txt << 'EOF'
2
2
AE151
7
3
EOF

echo -e "${BLUE}Running Test 4...${NC}"
./${PROGRAM_NAME} < test4_input.txt > test4_output.txt 2>&1

if [ $? -eq 0 ]; then
    print_status 0 "Test 4 completed"
    if grep -q "Drop-off Count\|passengers" test4_output.txt; then
        echo -e "${GREEN}✓ Drop-off count display appears successful${NC}"
    fi
else
    print_status 1 "Test 4 failed"
fi

# Test 5: View passenger information
print_section "Test 5: Viewing Passenger Information"
echo "This test will:"
echo "- Go to Personnel menu"
echo "- View passenger info for trip AE101 (should show sorted by priority)"
echo ""

cat > test5_input.txt << 'EOF'
2
3
AE101
7
3
EOF

echo -e "${BLUE}Running Test 5...${NC}"
./${PROGRAM_NAME} < test5_input.txt > test5_output.txt 2>&1

if [ $? -eq 0 ]; then
    print_status 0 "Test 5 completed"
    if grep -q "Passenger Information\|Priority\|Name" test5_output.txt; then
        echo -e "${GREEN}✓ Passenger info display appears successful${NC}"
    fi
else
    print_status 1 "Test 5 failed"
fi

# Test 6: Search passenger by last name
print_section "Test 6: Searching Passenger"
echo "This test will:"
echo "- Go to Personnel menu"
echo "- Search for passengers with last name 'Doe'"
echo ""

cat > test6_input.txt << 'EOF'
2
5
Doe
7
3
EOF

echo -e "${BLUE}Running Test 6...${NC}"
./${PROGRAM_NAME} < test6_input.txt > test6_output.txt 2>&1

if [ $? -eq 0 ]; then
    print_status 0 "Test 6 completed"
    if grep -q "Search Results\|found\|Doe" test6_output.txt; then
        echo -e "${GREEN}✓ Passenger search appears successful${NC}"
    fi
else
    print_status 1 "Test 6 failed"
fi

# Test 7: Test invalid trip number
print_section "Test 7: Invalid Trip Number Handling"
echo "This test will:"
echo "- Try to add passenger to invalid trip AE999"
echo "- Should show error message"
echo ""

cat > test7_input.txt << 'EOF'
1
1
AE999
2
3
EOF

echo -e "${BLUE}Running Test 7...${NC}"
timeout 10 ./${PROGRAM_NAME} < test7_input.txt > test7_output.txt 2>&1

if [ $? -eq 0 ]; then
    print_status 0 "Test 7 completed"
    if grep -q -i "invalid\|not found" test7_output.txt; then
        echo -e "${GREEN}✓ Invalid input handling appears successful${NC}"
    fi
elif [ $? -eq 124 ]; then
    print_status 1 "Test 7 timed out (program may be waiting for input)"
    echo "Check test7_output.txt for partial results"
else
    print_status 1 "Test 7 failed"
fi

# Test 8: Generate save file and load it
print_section "Test 8: File Generation and Loading"
echo "This test will:"
echo "- Exit program to generate Trip-DD-MM-YYYY.txt file"
echo "- Then load and view the generated file"
echo ""

echo "3" | ./${PROGRAM_NAME} > test8a_output.txt 2>&1

# Check if trip file was generated
if ls Trip-*.txt 1> /dev/null 2>&1; then
    TRIP_FILE=$(ls Trip-*.txt | head -1)
    echo -e "${GREEN}✓ Trip file generated: $TRIP_FILE${NC}"
    
    # Now test loading the file
    cat > test8b_input.txt << EOF
2
6
$TRIP_FILE
7
3
EOF
    
    echo -e "${BLUE}Testing file loading...${NC}"
    ./${PROGRAM_NAME} < test8b_input.txt > test8b_output.txt 2>&1
    
    if [ $? -eq 0 ]; then
        print_status 0 "File loading test completed"
        if grep -q "Trip File Contents\|AE" test8b_output.txt; then
            echo -e "${GREEN}✓ File loading appears successful${NC}"
        fi
    else
        print_status 1 "File loading test failed"
    fi
else
    print_status 1 "No trip file generated"
fi

# Summary
print_section "Test Summary"
echo "All tests completed!"
echo ""
echo "Output files generated:"
echo "- test1_output.txt - File loading test"
echo "- test2_output.txt - Manual passenger addition"
echo "- test3_output.txt - Passenger count/seating chart"
echo "- test4_output.txt - Drop-off count"
echo "- test5_output.txt - Passenger information"
echo "- test6_output.txt - Passenger search"
echo "- test7_output.txt - Invalid input handling"
echo "- test8a_output.txt, test8b_output.txt - File generation/loading"
echo "- Trip-*.txt - Generated trip data files"
echo ""
echo -e "${YELLOW}Review the output files to see detailed results${NC}"
echo -e "${BLUE}========================================${NC}"

# Show a quick preview of key results
echo -e "\n${YELLOW}Quick Results Preview:${NC}"
echo "Test 1 (File Loading):"
grep -i "loaded\|error\|success" test1_output.txt | head -2 || echo "Check test1_output.txt"

echo "Test 2 (Add Passenger):"
grep -i "successfully\|added\|invalid" test2_output.txt | head -2 || echo "Check test2_output.txt"

echo "Test 3 (Seating Chart):"
grep -i "passenger count\|seating" test3_output.txt | head -2 || echo "Check test3_output.txt"

# Cleanup input files
rm -f test*_input.txt

echo -e "\n${GREEN}Test script completed!${NC}"