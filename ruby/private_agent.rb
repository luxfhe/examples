#!/usr/bin/env ruby
# Lux FHE - Private Agents (Ruby)
#
# AI agents that operate on encrypted data.

require 'luxfhe'
require 'luxfhe/agents'

puts "\n=== Private AI Assistant ==="

client = Luxfhe::Client.new
server = Luxfhe::Server.new(client.evaluation_key)

# Sensitive context
sensitive_context = {
  user_id: 'user_12345',
  account_balance: 150_000,
  credit_score: 780,
}

# Encrypt context
puts "Encrypting sensitive user context..."
encrypted_context = client.encrypt_json(sensitive_context)

# Create private agent
agent = Luxfhe::Agents::PrivateAgent.new(
  model: 'gpt-4-turbo',
  fhe_server: server,
  system_prompt: 'You are a financial advisor.'
)

# Query
query = 'Should I invest more in stocks?'
puts "Agent processing encrypted context..."

encrypted_response = agent.run(
  query: query,
  encrypted_context: encrypted_context
)

# Decrypt
response = client.decrypt_json(encrypted_response)
puts "\nQuery: #{query}"
puts "Response: #{response['answer']}"
puts "\nAgent NEVER saw actual financial data!"
