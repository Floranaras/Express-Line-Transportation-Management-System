# Express Line Transportation Management System

A comprehensive C-based transportation booking and management system designed for inter-campus shuttle services.

## Overview

This system manages passenger reservations for a fleet of shuttles operating between two campus locations. It features priority-based seating, route management, and comprehensive passenger tracking capabilities.

## Features

### Core Functionality
- **20 Daily Routes** - Scheduled trips between Campus A and Campus B
- **Priority-Based Seating** - 6-tier passenger priority system (1 = highest priority)
- **Dynamic Capacity Management** - Regular (13 passengers) and high-demand (16 passengers) configurations
- **Route-Specific Drop-offs** - Different drop-off points based on route selection
- **Real-time Seat Assignment** - Visual seating charts with availability tracking

### Passenger Features
- Passenger information encoding with trip selection
- Priority-based automatic seat assignment
- Route-specific drop-off point selection
- Trip availability checking

### Administrative Features
- Passenger count visualization with seating charts
- Drop-off point passenger distribution
- Passenger information management (sorted by priority)
- Passenger search by name
- File-based data import/export
- Trip data persistence

## Getting Started

### Prerequisites
- GCC compiler with C99 standard support
- Linux/Unix environment (recommended)
- Make utility

### Compilation
```bash
# Using Make (recommended)
make

# Manual compilation
gcc -Wall -std=c99 -o express_system express_system.c
```

### Running the System
```bash
# Interactive mode
./express_system

# Run automated tests
chmod +x test_system.sh
./test_system.sh
```

## System Architecture

### Data Structures
- **Passenger Records** - Name, ID, priority level, trip details
- **Trip Management** - Route information, passenger lists, capacity tracking
- **Priority Queue** - Automatic passenger sorting and seat assignment

### Route Configuration
- **Campus A to Campus B Routes** (TR101-TR109)
  - Via Highway Exit: Odd-numbered routes
  - Via Boulevard Exit: Even-numbered routes
- **Campus B to Campus A Routes** (TR150-TR160)
  - Via Main Road: Odd-numbered routes  
  - Via Express Route: Even-numbered routes

### Priority Levels
1. **Level 1** - Faculty with inter-campus assignments
2. **Level 2** - Students with inter-campus courses
3. **Level 3** - Researchers
4. **Level 4** - Administrative staff
5. **Level 5** - University fellows
6. **Level 6** - General users with official business

## File Structure
```
express-transportation-system/
├── express_system.c          # Main source code
├── test_passengers.txt       # Sample passenger data
├── test_system.sh           # Automated test suite
├── Makefile                 # Build configuration
└── README.md               # This file
```

## Testing

The system includes a comprehensive test suite covering:
- File I/O operations
- Passenger booking workflows  
- Data validation and error handling
- Seating chart generation
- Search functionality
- Priority-based sorting

Run tests with:
```bash
./test_system.sh
```

## Sample Data Format

### Passenger Data File Format
```
TR101
Main Campus - Transport Hub
John Smith
12345678
1
Highway Exit - Stop 1

TR102
Main Campus - Transport Hub
Jane Doe
87654321
2
Boulevard Guard Station
```

### Generated Trip Files
Files are automatically saved as `Trip-DD-MM-YYYY.txt` with passenger details.

## Technical Specifications

### Programming Standards
- **Language**: C99 standard compliant
- **Coding Style**: Linux kernel coding standards
- **Memory Management**: Stack-based allocation (no dynamic memory)
- **Error Handling**: Comprehensive input validation and error recovery
- **Documentation**: Function-level documentation with pre/post conditions

### Constraints and Design Decisions
- No global variables
- No early returns from void functions
- Hungarian notation for local variables
- Modular function design
- Robust input buffer management

## Performance Characteristics

- **Capacity**: Up to 500 total passengers across all routes
- **Scalability**: 20 concurrent routes with 16 passengers each
- **Memory Usage**: Fixed allocation, no memory leaks
- **File I/O**: Efficient text-based persistence

## Development

### Code Organization
- **Main Loop**: User interface and menu navigation
- **Data Management**: Passenger and trip record handling
- **I/O Operations**: File reading/writing and user input
- **Business Logic**: Priority sorting and seat assignment
- **Utilities**: Input validation and error handling

### Key Algorithms
- **Selection Sort**: For priority-based passenger ordering
- **Linear Search**: For passenger and trip lookups
- **Dynamic Capacity**: Automatic switching between 13/16 seat configurations

## Known Limitations

- Text-based interface only
- Fixed route schedules (no dynamic scheduling)
- Single-day operation (no multi-day booking)
- ASCII-only passenger names

## License

This project is provided as-is for educational and demonstration purposes. Feel free to modify and adapt for your own transportation management needs.

## Contributing

This is a learning project demonstrating C programming concepts including:
- Structured programming with multiple data types
- File I/O and data persistence
- Input validation and error handling
- Algorithm implementation (sorting, searching)
- Memory management in C
- Comprehensive testing strategies

## Support

For technical questions about the implementation or to report issues, please review the source code comments and test cases for guidance.

---

**Note**: This system was developed as an academic exercise in C programming and software engineering principles.