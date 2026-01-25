/**
 * Lux FHE - C++ Example
 * 
 * Modern C++ interface for FHE operations.
 * 
 * Build: g++ -std=c++20 -o fhe_demo main.cpp -lluxfhe
 * Run: ./fhe_demo
 */

#include <iostream>
#include <memory>
#include <vector>
#include "luxfhe.hpp"

int main() {
    std::cout << "Lux FHE - C++ Example\n";
    std::cout << "=====================\n\n";
    
    // Initialize FHE context with RAII
    auto ctx = luxfhe::Context::create();
    
    // Generate keys
    std::cout << "Generating keys...\n";
    ctx->keygen();
    
    // Encrypt values
    uint64_t a = 42, b = 8;
    std::cout << "Encrypting: a=" << a << ", b=" << b << "\n";
    
    auto ct_a = ctx->encrypt(a);
    auto ct_b = ctx->encrypt(b);
    
    // Homomorphic operations
    std::cout << "\nPerforming homomorphic operations...\n";
    
    auto ct_sum = ct_a + ct_b;
    auto ct_prod = ct_a * ct_b;
    auto ct_gt = ct_a > ct_b;
    
    // Decrypt results
    std::cout << "\nDecrypting results...\n";
    std::cout << "  a + b = " << ctx->decrypt<uint64_t>(ct_sum) << " (expected: 50)\n";
    std::cout << "  a * b = " << ctx->decrypt<uint64_t>(ct_prod) << " (expected: 336)\n";
    std::cout << "  a > b = " << std::boolalpha << ctx->decrypt<bool>(ct_gt) << " (expected: true)\n";
    
    // Vector operations
    std::cout << "\n--- Vector Operations ---\n";
    std::vector<uint64_t> vec = {1, 2, 3, 4, 5};
    auto ct_vec = ctx->encrypt(vec);
    
    // Sum all elements homomorphically
    auto ct_total = ctx->reduce_add(ct_vec);
    std::cout << "Vector sum: " << ctx->decrypt<uint64_t>(ct_total) << " (expected: 15)\n";
    
    std::cout << "\n✓ FHE operations completed successfully\n";
    return 0;
}
