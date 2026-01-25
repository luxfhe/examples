#!/usr/bin/env ruby
# Lux FHE - Ruby Example
#
# Demonstrates basic FHE operations in Ruby.
#
# Install: gem install luxfhe
# Run: ruby basic.rb

require 'luxfhe'

puts "Lux FHE - Ruby Example"
puts "======================"

# Create client (manages private key)
client = Luxfhe::Client.new

# Create server (only evaluation key)
server = Luxfhe::Server.new(client.evaluation_key)

# Encrypt values
a, b = 42, 8
puts "\nEncrypting: a=#{a}, b=#{b}"

ct_a = client.encrypt(a)
ct_b = client.encrypt(b)

# Homomorphic operations
puts "\nServer performing homomorphic operations..."

ct_sum = server.add(ct_a, ct_b)
ct_prod = server.mul(ct_a, ct_b)
ct_gt = server.gt(ct_a, ct_b)

# Decrypt results
puts "\nDecrypting results:"
puts "  a + b = #{client.decrypt(ct_sum)} (expected: 50)"
puts "  a * b = #{client.decrypt(ct_prod)} (expected: 336)"
puts "  a > b = #{client.decrypt(ct_gt)} (expected: true)"

puts "\n✓ FHE operations completed successfully"
