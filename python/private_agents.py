"""
Lux FHE - Private Agents

AI agents that operate on encrypted data.
Context is never exposed to the agent server.

Install: pip install luxfhe[agents]
"""

from luxfhe import Client, Server
from luxfhe.agents import PrivateAgent, EncryptedContext

def private_assistant():
    """Private assistant that processes encrypted user context."""
    print("\n=== Private AI Assistant ===\n")
    
    client = Client()
    server = Server(client.evaluation_key)
    
    # User's sensitive context (financial data, health info, etc.)
    sensitive_context = {
        "user_id": "user_12345",
        "account_balance": 150000,
        "credit_score": 780,
        "health_conditions": ["none"],
        "portfolio": {
            "stocks": 50000,
            "bonds": 30000,
            "crypto": 20000
        }
    }
    
    # Encrypt the entire context
    print("Encrypting sensitive user context...")
    encrypted_context = client.encrypt_json(sensitive_context)
    
    # Create private agent
    agent = PrivateAgent(
        model="gpt-4-turbo",
        fhe_server=server,
        system_prompt="You are a financial advisor. Analyze the user's encrypted data."
    )
    
    # User's query
    query = "Should I rebalance my portfolio?"
    
    # Agent processes encrypted context
    print("Agent processing encrypted context...")
    encrypted_response = agent.run(
        query=query,
        encrypted_context=encrypted_context
    )
    
    # Client decrypts response
    response = client.decrypt_json(encrypted_response)
    print(f"\nUser Query: {query}")
    print(f"Agent Response: {response['answer']}")
    print("\nAgent NEVER saw actual financial data!")


def private_rag():
    """Private RAG (Retrieval Augmented Generation) on encrypted documents."""
    print("\n=== Private RAG Agent ===\n")
    
    client = Client()
    server = Server(client.evaluation_key)
    
    # Sensitive documents (legal, medical, financial)
    documents = [
        {"id": 1, "content": "Patient diagnosed with diabetes in 2023."},
        {"id": 2, "content": "Prescription: Metformin 500mg twice daily."},
        {"id": 3, "content": "Insurance claim submitted for $5,000."},
    ]
    
    # Encrypt documents
    print("Encrypting sensitive documents...")
    encrypted_docs = [client.encrypt_json(doc) for doc in documents]
    
    # Create encrypted vector store
    from luxfhe.agents import EncryptedVectorStore
    vector_store = EncryptedVectorStore(server)
    vector_store.add_documents(encrypted_docs)
    
    # RAG agent
    agent = PrivateAgent(
        model="gpt-4-turbo",
        fhe_server=server,
        tools=[vector_store],
        system_prompt="You are a medical assistant. Answer based on encrypted patient records."
    )
    
    # Query
    query = "What medication is the patient taking?"
    
    print("Agent searching encrypted documents...")
    encrypted_response = agent.run(query=query)
    
    response = client.decrypt_json(encrypted_response)
    print(f"\nQuery: {query}")
    print(f"Response: {response['answer']}")
    print("\nAgent NEVER saw medical records!")


def private_multi_agent():
    """Multiple agents collaborating on encrypted data."""
    print("\n=== Private Multi-Agent System ===\n")
    
    client = Client()
    server = Server(client.evaluation_key)
    
    # Create specialized agents
    analyst = PrivateAgent(
        model="gpt-4-turbo",
        fhe_server=server,
        name="Analyst",
        system_prompt="Analyze encrypted market data."
    )
    
    trader = PrivateAgent(
        model="gpt-4-turbo",
        fhe_server=server,
        name="Trader",
        system_prompt="Execute trades based on analysis."
    )
    
    risk_manager = PrivateAgent(
        model="gpt-4-turbo",
        fhe_server=server,
        name="RiskManager",
        system_prompt="Assess risk of proposed trades."
    )
    
    # Encrypted market data
    market_data = {
        "positions": [
            {"symbol": "AAPL", "quantity": 100, "avg_price": 150},
            {"symbol": "GOOGL", "quantity": 50, "avg_price": 2800},
        ],
        "cash": 50000,
    }
    
    encrypted_data = client.encrypt_json(market_data)
    
    # Multi-agent workflow
    print("Analyst analyzing encrypted market data...")
    analysis = analyst.run("Analyze portfolio risk", encrypted_context=encrypted_data)
    
    print("Trader proposing encrypted trades...")
    trades = trader.run("Propose rebalancing trades", encrypted_context=analysis)
    
    print("Risk manager reviewing encrypted trades...")
    approval = risk_manager.run("Assess trade risk", encrypted_context=trades)
    
    # Decrypt final decision
    decision = client.decrypt_json(approval)
    print(f"\nFinal Decision: {decision['verdict']}")
    print("All agents operated on encrypted data!")


if __name__ == "__main__":
    private_assistant()
    private_rag()
    private_multi_agent()
