// Lux FHE - Go Example
//
// Demonstrates basic FHE operations in Go.
//
// Build: go build -o fhe_demo
// Run: ./fhe_demo

package main

import (
	"fmt"

	"github.com/luxfi/fhe"
)

func main() {
	fmt.Println("Lux FHE - Go Example")
	fmt.Println("====================")

	// Create client (manages private key)
	client, err := fhe.NewClient()
	if err != nil {
		panic(err)
	}
	defer client.Close()

	// Create server (only evaluation key)
	server, err := fhe.NewServer(client.EvaluationKey())
	if err != nil {
		panic(err)
	}
	defer server.Close()

	// Encrypt values
	a, b := uint64(42), uint64(8)
	fmt.Printf("\nEncrypting: a=%d, b=%d\n", a, b)

	ctA, _ := client.EncryptU64(a)
	ctB, _ := client.EncryptU64(b)

	// Homomorphic operations
	fmt.Println("\nServer performing homomorphic operations...")

	ctSum, _ := server.Add(ctA, ctB)
	ctProd, _ := server.Mul(ctA, ctB)
	ctGt, _ := server.Gt(ctA, ctB)

	// Decrypt results
	fmt.Println("\nDecrypting results:")
	sum, _ := client.DecryptU64(ctSum)
	prod, _ := client.DecryptU64(ctProd)
	gt, _ := client.DecryptBool(ctGt)

	fmt.Printf("  a + b = %d (expected: 50)\n", sum)
	fmt.Printf("  a * b = %d (expected: 336)\n", prod)
	fmt.Printf("  a > b = %t (expected: true)\n", gt)

	fmt.Println("\n✓ FHE operations completed successfully")
}
