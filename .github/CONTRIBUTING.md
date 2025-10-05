# Contributing to SciFi Data Screen

## Development Setup

### Prerequisites
- Qt6 with QML support
- CMake 3.20+
- C++17 compatible compiler
- libmodbus for network communication

### Getting Started
1. Clone the repository
2. Open in VS Code with Dev Container
3. Build with `cmake --build build/`
4. Run tests with `ctest --test-dir build/`

## Code Style

### C++ Guidelines
- Follow Qt coding conventions
- Use `camelCase` for variables and functions
- Use `PascalCase` for classes
- Include comprehensive documentation

### QML Guidelines
- Use 4-space indentation
- Group properties logically
- Add comments for complex bindings
- Follow Qt Quick best practices

## Pull Request Process

1. Create a feature branch from `main`
2. Make your changes with clear commit messages
3. Add tests for new functionality
4. Update documentation as needed
5. Submit PR with detailed description

## Issue Guidelines

- Use issue templates
- Provide clear reproduction steps
- Include environment details
- Add relevant labels

## Testing

- Write unit tests for C++ components
- Add integration tests for critical workflows
- Test on multiple platforms when possible
- Verify performance requirements are met