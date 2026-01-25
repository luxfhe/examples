# Lux FHE Examples

Multi-language examples for the Lux FHE (Fully Homomorphic Encryption) ecosystem.

## 🌍 Language Support

| Language | Directory | Status | Use Case |
|----------|-----------|--------|----------|
| **C** | [c/](./c) | ✅ Full | Embedded systems, native libs |
| **C++** | [cpp/](./cpp) | ✅ Full | High-performance apps |
| **Python** | [python/](./python) | ✅ Full | ML, data science, agents |
| **Go** | [go/](./go) | ✅ Full | Backend services, MPC |
| **Rust** | [rust/](./rust) | ✅ Full | Crypto, WASM, performance |
| **Ruby** | [ruby/](./ruby) | 🚧 Beta | Web apps, scripts |
| **Elixir** | [elixir/](./elixir) | 🚧 Beta | Distributed systems |
| **Haskell** | [haskell/](./haskell) | 🚧 Beta | Formal verification |
| **Node.js** | [node/](./node) | ✅ Full | Web, serverless, agents |

## 🚀 Quick Start

### Python
```bash
pip install luxfhe
python python/basic.py
```

### Go
```bash
cd go
go run main.go
```

### Rust
```bash
cd rust
cargo run
```

### Node.js
```bash
cd node
npm install
npx tsx basic.ts
```

### C/C++
```bash
cd c
make
./fhe_demo
```

## 📚 Example Categories

### Basic FHE Operations
Every language includes a `basic` example demonstrating:
- Key generation
- Encryption/decryption
- Homomorphic arithmetic (+, -, ×)
- Comparisons (<, >, ==)
- Bitwise operations

### Private Machine Learning
See `python/private_ml.py`:
- Linear regression on encrypted data
- Classification on encrypted patient records
- Server never sees plaintext data

### Private Agents
See `python/private_agents.py` and `node/private_agents.ts`:
- AI assistants operating on encrypted context
- RAG with encrypted document search
- Multi-agent systems on encrypted data

## 🏗️ Architecture

```
┌─────────────────────────────────────────────────────────────────┐
│                      Your Application                           │
├─────────────────────────────────────────────────────────────────┤
│  ┌────────────────────────────────────────────────────────┐     │
│  │    Language Bindings (Python, Go, Rust, Node, etc.)    │     │
│  └────────────────────────────────────────────────────────┘     │
│                              │                                   │
│  ┌────────────────────────────────────────────────────────┐     │
│  │              Lux FHE Compiler (LLVM)                   │     │
│  │    github.com/luxfi/fhe-compiler                        │     │
│  └────────────────────────────────────────────────────────┘     │
│                              │                                   │
│  ┌─────────────┬─────────────┬─────────────┬──────────────┐     │
│  │   Torus     │  Torus-ML   │  Torus-NTT  │  Torus-FFT   │     │
│  │  (Runtime)  │    (ML)     │  (Accel)    │   (Accel)    │     │
│  └─────────────┴─────────────┴─────────────┴──────────────┘     │
│                              │                                   │
│  ┌────────────────────────────────────────────────────────┐     │
│  │         Core: github.com/luxfi/fhe + lattice           │     │
│  └────────────────────────────────────────────────────────┘     │
└─────────────────────────────────────────────────────────────────┘
```

## 🔗 Related Repositories

### Core Libraries (github.com/luxfi)
- [luxfi/fhe](https://github.com/luxfi/fhe) - Core FHE library (Go)
- [luxfi/lattice](https://github.com/luxfi/lattice) - Lattice crypto (Go)
- [luxfi/torus](https://github.com/luxfi/torus) - FHE compiler & runtime
- [luxfi/torus-ml](https://github.com/luxfi/torus-ml) - ML on encrypted data
- [luxfi/fhe-compiler](https://github.com/luxfi/fhe-compiler) - LLVM compiler

### Documentation (github.com/luxfhe)
- [luxfhe/docs](https://github.com/luxfhe/docs) - Full documentation
- [luxfhe/handbook](https://github.com/luxfhe/handbook) - Deep dive guide
- [luxfhe/workshop](https://github.com/luxfhe/workshop) - Interactive tutorials

## 📄 License

Apache 2.0 - See [LICENSE](./LICENSE).

---

**Built by [Lux Network](https://lux.network) & [Hanzo AI](https://hanzo.ai)**
