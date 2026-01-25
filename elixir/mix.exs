defmodule LuxfheExamples.MixProject do
  use Mix.Project

  def project do
    [
      app: :luxfhe_examples,
      version: "0.1.0",
      elixir: "~> 1.14",
      deps: deps()
    ]
  end

  defp deps do
    [
      {:luxfhe, "~> 0.1"}
    ]
  end
end
