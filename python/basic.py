"""
Lux FHE - Python Example

Demonstrates basic FHE operations in Python.

Install: pip install luxfhe
Run: python basic.py
"""

from luxfhe import Client, Server, EncryptedUint64

def main():
    print("Lux FHE - Python Example")
    print("=" * 30)
    
    # Initialize client (has private key)
    client = Client()
    
    # Initialize server (only has evaluation key)
    server = Server(client.evaluation_key)
    
    # Client encrypts values
    a, b = 42, 8
    print(f"\nEncrypting: a={a}, b={b}")
    
    ct_a = client.encrypt(a)
    ct_b = client.encrypt(b)
    
    # Server performs operations on encrypted data
    print("\nServer performing homomorphic operations...")
    
    ct_sum = server.add(ct_a, ct_b)
    ct_prod = server.mul(ct_a, ct_b)
    ct_gt = server.gt(ct_a, ct_b)
    
    # Client decrypts results
    print("\nDecrypting results:")
    print(f"  a + b = {client.decrypt(ct_sum)} (expected: 50)")
    print(f"  a * b = {client.decrypt(ct_prod)} (expected: 336)")
    print(f"  a > b = {client.decrypt(ct_gt)} (expected: True)")
    
    print("\n✓ FHE operations completed successfully")


if __name__ == "__main__":
    main()
