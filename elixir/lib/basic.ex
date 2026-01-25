defmodule Luxfhe.Examples.Basic do
  @moduledoc """
  Lux FHE - Elixir Example
  
  Demonstrates basic FHE operations in Elixir.
  
  Run: mix run lib/basic.ex
  """

  def main do
    IO.puts("Lux FHE - Elixir Example")
    IO.puts("========================")

    # Create client (manages private key)
    {:ok, client} = Luxfhe.Client.new()

    # Create server (only evaluation key)
    {:ok, server} = Luxfhe.Server.new(Luxfhe.Client.evaluation_key(client))

    # Encrypt values
    a = 42
    b = 8
    IO.puts("\nEncrypting: a=#{a}, b=#{b}")

    {:ok, ct_a} = Luxfhe.Client.encrypt(client, a)
    {:ok, ct_b} = Luxfhe.Client.encrypt(client, b)

    # Homomorphic operations
    IO.puts("\nServer performing homomorphic operations...")

    {:ok, ct_sum} = Luxfhe.Server.add(server, ct_a, ct_b)
    {:ok, ct_prod} = Luxfhe.Server.mul(server, ct_a, ct_b)
    {:ok, ct_gt} = Luxfhe.Server.gt(server, ct_a, ct_b)

    # Decrypt results
    IO.puts("\nDecrypting results:")
    IO.puts("  a + b = #{Luxfhe.Client.decrypt(client, ct_sum)} (expected: 50)")
    IO.puts("  a * b = #{Luxfhe.Client.decrypt(client, ct_prod)} (expected: 336)")
    IO.puts("  a > b = #{Luxfhe.Client.decrypt(client, ct_gt)} (expected: true)")

    IO.puts("\n✓ FHE operations completed successfully")
  end
end

Luxfhe.Examples.Basic.main()
