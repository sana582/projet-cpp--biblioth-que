# Bibliothèque Management System

A comprehensive C++ library management system that handles book lending, member management, and inter-library operations with object-oriented design principles.

## Project Overview

This project implements a complete library management system in C++ featuring:
- **Multi-type book catalog** (Novels, Comics, Poetry, Theater, Albums)
- **Member management** with borrowing limits
- **Inter-library lending** and ISBN-based requests
- **Comprehensive error handling** and validation
- **Object-oriented architecture** with inheritance and polymorphism

## Architecture

### Core Classes

- **`Bibliotheque`** - Main library management class
- **`Livre`** (Abstract) - Base class for all book types
- **`Adherent`** - Library member management
- **Book Types**: `Roman`, `BandeDessinee`, `RecueilPoesie`, `PieceTheatre`, `Album`

### Key Features

- **Member Registration** - Inscription/désinscription with validation
- **Book Management** - Add, remove, search by code/ISBN
- **Lending System** - Borrow/return with limit enforcement
- **Inter-library Operations** - Lend between libraries, ISBN requests
- **Categorized Display** - View books by type
- **State Management** - Track book availability (Libre/Emprunté/Prêté)

## Project Structure

```
project_cpp/
├── src/
│   ├── main.cpp                 # Main demonstration program
│   ├── test.cpp                 # Unit tests
│   ├── test_adherent.cpp        # Member-specific tests
│   ├── Bibliotheque.h/.cpp      # Library management
│   ├── Livre.h                  # Abstract book base class
│   ├── Adherent.h/.cpp          # Member management
│   ├── Book Types/
│   │   ├── Roman.h/.cpp
│   │   ├── BandeDessinee.h/.cpp
│   │   ├── RecueilPoesie.h/.cpp
│   │   ├── PieceTheatre.h/.cpp
│   │   └── Album.h/.cpp
│   ├── Enums.h                  # Enumerations and utilities
│   └── Exceptions.h             # Custom exception classes
├── diagrams/
│   └── uml_Diargams.md         # UML class diagrams
└── .vscode/                    # Development configuration
```

## Getting Started

### Prerequisites

- C++17 compatible compiler (g++, clang++, MSVC)
- Make or build system of choice

### Building

```bash
# Compile the main demo
g++ -std=c++17 src/*.cpp -o bibliotheque_demo

# Compile tests
g++ -std=c++17 src/test.cpp src/*.cpp -o bibliotheque_tests

# Run the demo
./bibliotheque_demo

# Run tests
./bibliotheque_tests
```

### Quick Demo

The `main.cpp` provides a comprehensive demonstration covering:
- Library and member creation
- Book addition of various types
- Borrowing/returning operations
- Inter-library lending
- Error handling scenarios

## Usage Examples

### Creating a Library

```cpp
Bibliotheque b1("Biblio Centrale", "Marseille", "B001");
```

### Adding Members

```cpp
Adherent a1("Naimi", "Salima", "Marseille", "A001", 2);
b1.inscrire(&a1);
```

### Adding Books

```cpp
b1.acheterLivre(new Roman("R001", "Victor Hugo", "Les Misérables", 
                         "Editeur1", "ISBN-111", PublicCible::Adulte, 
                         GenreRoman::Litterature));

b1.acheterLivre(new BandeDessinee("BD01", "Goscinny", "Astérix", 
                                  "Editeur2", "ISBN-222", PublicCible::ToutPublic, 
                                  "Uderzo"));
```

### Borrowing Books

```cpp
bool success = b1.emprunterLivre("A001", "R001");
```

### Inter-library Lending

```cpp
Bibliotheque b2("Biblio Nord", "Aix-en-Provence", "B002");
bool lent = b1.preterLivreVers(b2, "T001");
```

## Testing

The project includes comprehensive unit tests covering:

- **Borrowing Limits** - Member borrowing restrictions
- **Inter-library Operations** - Lending and ISBN requests
- **Book Management** - Addition, removal, and state changes
- **Error Handling** - Invalid operations and edge cases

Run tests with:
```bash
./bibliotheque_tests
```

## Book Types & Categories

### Supported Book Types

| Type | Class | Specific Properties |
|------|-------|---------------------|
| Novel | `Roman` | `GenreRoman` (Literature, Crime, Romance, etc.) |
| Comic | `BandeDessinee` | `dessinateur` (Illustrator) |
| Poetry | `RecueilPoesie` | `TypePoesie` (Verse, Prose, Mixed) |
| Theater | `PieceTheatre` | `siecle` (Century) |
| Album | `Album` | `TypeIllustration` (Photos, Drawings, Mixed) |

### Target Audiences

- `Adulte` - Adult content
- `Ados` - Teen content  
- `Jeunesse` - Children's content
- `ToutPublic` - All ages

## Technical Details

### Design Patterns

- **Inheritance** - Abstract `Livre` base class with specialized implementations
- **Composition** - Libraries contain members and books
- **State Management** - Book states tracked through enums
- **Association** - Bidirectional relationships between classes

### Memory Management

- Smart pointers recommended for production use
- Manual memory management in current implementation
- RAII principles followed where possible

### Error Handling

- Return value validation for operations
- Custom exception classes for error conditions
- Graceful handling of invalid states

## UML Diagram

See `diagrams/uml_Diargams.md` for complete class diagrams showing:
- Class relationships and inheritance
- Method signatures and attributes
- Enumerations and data types

## Contributing

1. Fork the repository
2. Create a feature branch (`git checkout -b feature/AmazingFeature`)
3. Commit your changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

## License

This project is part of an academic assignment for Centrale Méditerranée.

## Academic Context

This project was developed as part of a C++ programming course at Centrale Méditerranée, demonstrating:
- Object-oriented programming principles
- Software architecture design
- Memory management in C++
- Testing and validation methodologies

## Support

For questions or issues regarding this project, please refer to the course documentation or contact the teaching staff.

---