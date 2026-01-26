# Lux FHE Examples

**Real, working examples** for Fully Homomorphic Encryption development.

## ML Examples (`ml/`)

Production-ready machine learning on encrypted data:

| Example | Description | Data |
|---------|-------------|------|
| [credit_scoring/](./ml/credit_scoring/) | Credit risk prediction | HMEQ dataset |
| [disease_prediction/](./ml/disease_prediction/) | Healthcare predictions | Medical records |
| [cifar/](./ml/cifar/) | Image classification | CIFAR-10 |
| [federated_learning/](./ml/federated_learning/) | Distributed training | - |
| [hybrid_model/](./ml/hybrid_model/) | Mixed FHE/plaintext | - |

### Quick Start

```bash
cd ml/credit_scoring
python -m venv .venv && source .venv/bin/activate
pip install -r requirements.txt
jupyter lab CreditScoring.ipynb
```

## Deployment Examples (`deployment/`)

Production deployment patterns:

| Example | Description |
|---------|-------------|
| [breast_cancer/](./deployment/breast_cancer/) | Cancer detection API |
| [sentiment_analysis/](./deployment/sentiment_analysis/) | NLP on encrypted text |
| [server/](./deployment/server/) | FHE inference server |

## Blockchain Examples (`blockchain/`)

FHE for smart contracts:

| Example | Description |
|---------|-------------|
| [hardhat-template/](./blockchain/hardhat-template/) | Solidity + FHE |
| [react-template/](./blockchain/react-template/) | React dApp + FHE |

## Requirements

- Python 3.10+
- For ML: `pip install torus-ml`
- For blockchain: Node.js 18+

## Related

- [luxfhe/docs](https://github.com/luxfhe/docs) - Documentation
- [luxfhe/handbook](https://github.com/luxfhe/handbook) - Deep dive
- [luxfhe/workshop](https://github.com/luxfhe/workshop) - Tutorials

## License

Apache 2.0
