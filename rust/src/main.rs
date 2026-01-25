//! Lux FHE - Rust Example
//!
//! Demonstrates basic FHE operations in Rust.

use luxfhe::{Client, Server, Result};

fn main() -> Result<()> {
    println!("Lux FHE - Rust Example");
    println!("======================\n");
    
    let client = Client::new()?;
    let server = Server::new(client.evaluation_key())?;
    
    let (a, b) = (42u64, 8u64);
    println!("Encrypting: a={a}, b={b}");
    
    let ct_a = client.encrypt(a)?;
    let ct_b = client.encrypt(b)?;
    
    println!("\nServer performing homomorphic operations...");
    let ct_sum = server.add(&ct_a, &ct_b)?;
    let ct_prod = server.mul(&ct_a, &ct_b)?;
    let ct_gt = server.gt(&ct_a, &ct_b)?;
    
    println!("\nDecrypting results:");
    println!("  a + b = {} (expected: 50)", client.decrypt::<u64>(&ct_sum)?);
    println!("  a * b = {} (expected: 336)", client.decrypt::<u64>(&ct_prod)?);
    println!("  a > b = {} (expected: true)", client.decrypt::<bool>(&ct_gt)?);
    
    println!("\n✓ FHE operations completed successfully");
    Ok(())
}
