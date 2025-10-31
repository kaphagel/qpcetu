#pragma once

#include <QString>
#include <QList>
#include "../utils/result.h"

/**
 * @brief Interface for data persistence repositories
 * 
 * This interface defines the contract for storing and retrieving data.
 * Implementations can be in-memory, SQLite, CSV files, circular buffers, etc.
 * 
 * Pattern: Repository Pattern (RULE-202)
 * Location: src/interfaces/ (RULE-305)
 * 
 * @tparam T The entity type being stored (e.g., DataPoint, Controller, Alarm)
 */
template<typename T>
class IRepository {
public:
    virtual ~IRepository() = default;
    
    /**
     * @brief Save an entity to the repository
     * @param entity The entity to save
     * @return Result indicating success or failure
     */
    virtual Result<void> save(const T& entity) = 0;
    
    /**
     * @brief Find an entity by its unique identifier
     * @param id The unique identifier
     * @return Result containing the entity or error message
     */
    virtual Result<T> findById(const QString& id) = 0;
    
    /**
     * @brief Retrieve all entities
     * @return Result containing list of all entities or error message
     */
    virtual Result<QList<T>> findAll() = 0;
    
    /**
     * @brief Delete an entity by its unique identifier
     * @param id The unique identifier
     * @return Result indicating success or failure
     */
    virtual Result<void> deleteById(const QString& id) = 0;
    
    /**
     * @brief Get the count of entities in the repository
     * @return Number of entities
     */
    virtual int count() const = 0;
    
    /**
     * @brief Clear all entities from the repository
     * @return Result indicating success or failure
     */
    virtual Result<void> clear() = 0;
};
