/**
 * Lux FHE - C Example
 * 
 * Demonstrates basic FHE operations: encrypt, compute, decrypt
 * 
 * Build: gcc -o fhe_demo main.c -lluxfhe -lm
 * Run: ./fhe_demo
 */

#include <stdio.h>
#include <stdlib.h>
#include "luxfhe.h"

int main() {
    printf("Lux FHE - C Example\n");
    printf("===================\n\n");
    
    // Initialize FHE context
    luxfhe_context_t* ctx = luxfhe_init();
    if (!ctx) {
        fprintf(stderr, "Failed to initialize FHE context\n");
        return 1;
    }
    
    // Generate keys
    printf("Generating keys...\n");
    luxfhe_keygen(ctx);
    
    // Encrypt two values
    uint64_t a = 42, b = 8;
    printf("Encrypting: a=%lu, b=%lu\n", a, b);
    
    luxfhe_ciphertext_t* ct_a = luxfhe_encrypt_u64(ctx, a);
    luxfhe_ciphertext_t* ct_b = luxfhe_encrypt_u64(ctx, b);
    
    // Homomorphic operations (on encrypted data!)
    printf("\nPerforming homomorphic operations...\n");
    
    // Addition: a + b
    luxfhe_ciphertext_t* ct_sum = luxfhe_add(ctx, ct_a, ct_b);
    
    // Multiplication: a * b
    luxfhe_ciphertext_t* ct_prod = luxfhe_mul(ctx, ct_a, ct_b);
    
    // Comparison: a > b
    luxfhe_ciphertext_t* ct_gt = luxfhe_gt(ctx, ct_a, ct_b);
    
    // Decrypt results
    printf("\nDecrypting results...\n");
    uint64_t sum = luxfhe_decrypt_u64(ctx, ct_sum);
    uint64_t prod = luxfhe_decrypt_u64(ctx, ct_prod);
    uint64_t gt = luxfhe_decrypt_bool(ctx, ct_gt);
    
    printf("  a + b = %lu (expected: 50)\n", sum);
    printf("  a * b = %lu (expected: 336)\n", prod);
    printf("  a > b = %s (expected: true)\n", gt ? "true" : "false");
    
    // Cleanup
    luxfhe_free_ciphertext(ct_a);
    luxfhe_free_ciphertext(ct_b);
    luxfhe_free_ciphertext(ct_sum);
    luxfhe_free_ciphertext(ct_prod);
    luxfhe_free_ciphertext(ct_gt);
    luxfhe_destroy(ctx);
    
    printf("\n✓ FHE operations completed successfully\n");
    return 0;
}
