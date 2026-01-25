/**
 * Lux FHE - C++ Header
 * 
 * Modern C++ interface for FHE operations.
 */

#pragma once

#include <memory>
#include <vector>
#include <span>
#include <concepts>
#include <cstdint>

namespace luxfhe {

// Forward declarations
class Context;
class Ciphertext;

// Concept for encryptable types
template<typename T>
concept Encryptable = std::is_integral_v<T> || std::is_same_v<T, bool>;

// Ciphertext wrapper with operator overloading
class Ciphertext {
public:
    Ciphertext(std::shared_ptr<void> impl) : impl_(std::move(impl)) {}
    
    // Arithmetic operators
    Ciphertext operator+(const Ciphertext& other) const;
    Ciphertext operator-(const Ciphertext& other) const;
    Ciphertext operator*(const Ciphertext& other) const;
    Ciphertext operator-() const;
    
    // Comparison operators
    Ciphertext operator<(const Ciphertext& other) const;
    Ciphertext operator>(const Ciphertext& other) const;
    Ciphertext operator==(const Ciphertext& other) const;
    Ciphertext operator<=(const Ciphertext& other) const;
    Ciphertext operator>=(const Ciphertext& other) const;
    
    // Bitwise operators
    Ciphertext operator&(const Ciphertext& other) const;
    Ciphertext operator|(const Ciphertext& other) const;
    Ciphertext operator^(const Ciphertext& other) const;
    Ciphertext operator~() const;
    
    // Serialization
    std::vector<uint8_t> serialize() const;
    static Ciphertext deserialize(Context& ctx, std::span<const uint8_t> data);
    
private:
    std::shared_ptr<void> impl_;
    friend class Context;
};

// FHE Context (manages keys and operations)
class Context {
public:
    static std::unique_ptr<Context> create();
    ~Context();
    
    // Key management
    void keygen();
    void save_keys(const std::string& path);
    void load_keys(const std::string& path);
    
    // Encryption
    template<Encryptable T>
    Ciphertext encrypt(T value);
    
    template<Encryptable T>
    Ciphertext encrypt(std::span<const T> values);
    
    Ciphertext encrypt(const std::vector<uint64_t>& values) {
        return encrypt(std::span<const uint64_t>(values));
    }
    
    // Decryption
    template<Encryptable T>
    T decrypt(const Ciphertext& ct);
    
    template<Encryptable T>
    std::vector<T> decrypt_vector(const Ciphertext& ct);
    
    // Vector operations
    Ciphertext reduce_add(const Ciphertext& ct);
    Ciphertext reduce_mul(const Ciphertext& ct);
    
    // Conditional
    Ciphertext select(const Ciphertext& condition, const Ciphertext& if_true, const Ciphertext& if_false);
    
private:
    Context();
    struct Impl;
    std::unique_ptr<Impl> impl_;
};

} // namespace luxfhe
