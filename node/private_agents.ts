/**
 * Lux FHE - Private Agents (TypeScript)
 *
 * AI agents that operate on encrypted data.
 */

import { Client, Server } from '@luxfhe/core';
import { PrivateAgent, EncryptedContext } from '@luxfhe/agents';

async function privateAssistant() {
    console.log('\n=== Private AI Assistant ===\n');
    
    const client = await Client.create();
    const server = await Server.create(client.evaluationKey);
    
    // Sensitive user context
    const sensitiveContext = {
        userId: 'user_12345',
        accountBalance: 150000,
        creditScore: 780,
        portfolio: {
            stocks: 50000,
            bonds: 30000,
            crypto: 20000,
        },
    };
    
    // Encrypt context
    console.log('Encrypting sensitive user context...');
    const encryptedContext = await client.encryptJson(sensitiveContext);
    
    // Create private agent
    const agent = new PrivateAgent({
        model: 'gpt-4-turbo',
        fheServer: server,
        systemPrompt: 'You are a financial advisor.',
    });
    
    // Query
    const query = 'Should I rebalance my portfolio?';
    
    console.log('Agent processing encrypted context...');
    const encryptedResponse = await agent.run({
        query,
        encryptedContext,
    });
    
    // Decrypt response
    const response = await client.decryptJson(encryptedResponse);
    console.log(`\nQuery: ${query}`);
    console.log(`Response: ${response.answer}`);
    console.log('\nAgent NEVER saw actual financial data!');
}

async function main() {
    await privateAssistant();
}

main().catch(console.error);
