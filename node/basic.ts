/**
 * Lux FHE - Node.js/TypeScript Example
 *
 * Demonstrates basic FHE operations in TypeScript.
 *
 * Install: npm install @luxfhe/core
 * Run: npx tsx basic.ts
 */

import { Client, Server } from '@luxfhe/core';

async function main() {
    console.log('Lux FHE - Node.js Example');
    console.log('=========================\n');
    
    // Create client (manages private key)
    const client = await Client.create();
    
    // Create server (only evaluation key)
    const server = await Server.create(client.evaluationKey);
    
    // Encrypt values
    const [a, b] = [42n, 8n];
    console.log(`Encrypting: a=${a}, b=${b}`);
    
    const ctA = await client.encryptU64(a);
    const ctB = await client.encryptU64(b);
    
    // Homomorphic operations
    console.log('\nServer performing homomorphic operations...');
    
    const ctSum = await server.add(ctA, ctB);
    const ctProd = await server.mul(ctA, ctB);
    const ctGt = await server.gt(ctA, ctB);
    
    // Decrypt results
    console.log('\nDecrypting results:');
    console.log(`  a + b = ${await client.decryptU64(ctSum)} (expected: 50)`);
    console.log(`  a * b = ${await client.decryptU64(ctProd)} (expected: 336)`);
    console.log(`  a > b = ${await client.decryptBool(ctGt)} (expected: true)`);
    
    console.log('\n✓ FHE operations completed successfully');
}

main().catch(console.error);
