/**
 * Lux FHE - C Header
 * 
 * Core FHE operations for the Lux ecosystem.
 */

#ifndef LUXFHE_H
#define LUXFHE_H

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

// Opaque types
typedef struct luxfhe_context luxfhe_context_t;
typedef struct luxfhe_ciphertext luxfhe_ciphertext_t;

// Initialization
luxfhe_context_t* luxfhe_init(void);
void luxfhe_destroy(luxfhe_context_t* ctx);

// Key generation
int luxfhe_keygen(luxfhe_context_t* ctx);
int luxfhe_save_keys(luxfhe_context_t* ctx, const char* path);
int luxfhe_load_keys(luxfhe_context_t* ctx, const char* path);

// Encryption
luxfhe_ciphertext_t* luxfhe_encrypt_u64(luxfhe_context_t* ctx, uint64_t value);
luxfhe_ciphertext_t* luxfhe_encrypt_bool(luxfhe_context_t* ctx, bool value);
luxfhe_ciphertext_t* luxfhe_encrypt_bytes(luxfhe_context_t* ctx, const uint8_t* data, size_t len);

// Decryption
uint64_t luxfhe_decrypt_u64(luxfhe_context_t* ctx, luxfhe_ciphertext_t* ct);
bool luxfhe_decrypt_bool(luxfhe_context_t* ctx, luxfhe_ciphertext_t* ct);
size_t luxfhe_decrypt_bytes(luxfhe_context_t* ctx, luxfhe_ciphertext_t* ct, uint8_t* out, size_t out_len);

// Arithmetic operations
luxfhe_ciphertext_t* luxfhe_add(luxfhe_context_t* ctx, luxfhe_ciphertext_t* a, luxfhe_ciphertext_t* b);
luxfhe_ciphertext_t* luxfhe_sub(luxfhe_context_t* ctx, luxfhe_ciphertext_t* a, luxfhe_ciphertext_t* b);
luxfhe_ciphertext_t* luxfhe_mul(luxfhe_context_t* ctx, luxfhe_ciphertext_t* a, luxfhe_ciphertext_t* b);
luxfhe_ciphertext_t* luxfhe_neg(luxfhe_context_t* ctx, luxfhe_ciphertext_t* a);

// Comparison operations
luxfhe_ciphertext_t* luxfhe_lt(luxfhe_context_t* ctx, luxfhe_ciphertext_t* a, luxfhe_ciphertext_t* b);
luxfhe_ciphertext_t* luxfhe_gt(luxfhe_context_t* ctx, luxfhe_ciphertext_t* a, luxfhe_ciphertext_t* b);
luxfhe_ciphertext_t* luxfhe_eq(luxfhe_context_t* ctx, luxfhe_ciphertext_t* a, luxfhe_ciphertext_t* b);
luxfhe_ciphertext_t* luxfhe_lte(luxfhe_context_t* ctx, luxfhe_ciphertext_t* a, luxfhe_ciphertext_t* b);
luxfhe_ciphertext_t* luxfhe_gte(luxfhe_context_t* ctx, luxfhe_ciphertext_t* a, luxfhe_ciphertext_t* b);

// Bitwise operations
luxfhe_ciphertext_t* luxfhe_and(luxfhe_context_t* ctx, luxfhe_ciphertext_t* a, luxfhe_ciphertext_t* b);
luxfhe_ciphertext_t* luxfhe_or(luxfhe_context_t* ctx, luxfhe_ciphertext_t* a, luxfhe_ciphertext_t* b);
luxfhe_ciphertext_t* luxfhe_xor(luxfhe_context_t* ctx, luxfhe_ciphertext_t* a, luxfhe_ciphertext_t* b);
luxfhe_ciphertext_t* luxfhe_not(luxfhe_context_t* ctx, luxfhe_ciphertext_t* a);

// Memory management
void luxfhe_free_ciphertext(luxfhe_ciphertext_t* ct);
luxfhe_ciphertext_t* luxfhe_clone_ciphertext(luxfhe_ciphertext_t* ct);

// Serialization
size_t luxfhe_serialize_ciphertext(luxfhe_ciphertext_t* ct, uint8_t* out, size_t out_len);
luxfhe_ciphertext_t* luxfhe_deserialize_ciphertext(luxfhe_context_t* ctx, const uint8_t* data, size_t len);

#ifdef __cplusplus
}
#endif

#endif // LUXFHE_H
