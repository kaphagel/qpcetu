#pragma once

#include <QString>
#include <variant>

/**
 * @brief Result type for operations that can fail without using exceptions
 * 
 * This provides a type-safe way to return either a success value or an error message.
 * Use this for synchronous operations that can fail.
 * 
 * Usage:
 *   Result<int> readValue() {
 *       if (success) return Result<int>::success(42);
 *       return Result<int>::failure("Connection failed");
 *   }
 *   
 *   auto result = readValue();
 *   if (result.isSuccess()) {
 *       int value = result.value();
 *   } else {
 *       QString error = result.error();
 *   }
 * 
 * @tparam T The type of the success value
 */
template<typename T>
class Result {
public:
    /**
     * @brief Create a successful result
     */
    static Result<T> success(const T& value) {
        return Result<T>(value);
    }
    
    /**
     * @brief Create a failure result
     */
    static Result<T> failure(const QString& errorMessage) {
        return Result<T>(errorMessage);
    }
    
    /**
     * @brief Check if the result is successful
     */
    bool isSuccess() const {
        return std::holds_alternative<T>(m_data);
    }
    
    /**
     * @brief Check if the result is a failure
     */
    bool isFailure() const {
        return std::holds_alternative<QString>(m_data);
    }
    
    /**
     * @brief Get the success value (only valid if isSuccess() is true)
     */
    T value() const {
        return std::get<T>(m_data);
    }
    
    /**
     * @brief Get the error message (only valid if isFailure() is true)
     */
    QString error() const {
        return std::get<QString>(m_data);
    }
    
    /**
     * @brief Get the value or a default value if failure
     */
    T valueOr(const T& defaultValue) const {
        return isSuccess() ? value() : defaultValue;
    }

private:
    // Private constructors - use static factory methods
    explicit Result(const T& value) : m_data(value) {}
    explicit Result(const QString& error) : m_data(error) {}
    
    std::variant<T, QString> m_data;
};

/**
 * @brief Specialized Result<void> for operations that don't return a value
 * 
 * Usage:
 *   Result<void> doOperation() {
 *       if (success) return Result<void>::success();
 *       return Result<void>::failure("Operation failed");
 *   }
 */
template<>
class Result<void> {
public:
    static Result<void> success() {
        return Result<void>(true);
    }
    
    static Result<void> failure(const QString& errorMessage) {
        return Result<void>(errorMessage);
    }
    
    bool isSuccess() const {
        return m_success;
    }
    
    bool isFailure() const {
        return !m_success;
    }
    
    QString error() const {
        return m_errorMessage;
    }

private:
    explicit Result(bool success) : m_success(success), m_errorMessage("") {}
    explicit Result(const QString& error) : m_success(false), m_errorMessage(error) {}
    
    bool m_success;
    QString m_errorMessage;
};
