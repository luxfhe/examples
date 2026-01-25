"""
Lux FHE - Private Machine Learning

Train and run ML models on encrypted data.
The server never sees the plaintext data.

Install: pip install luxfhe[ml]
"""

import numpy as np
from luxfhe import Client, Server
from luxfhe.ml import EncryptedLinearRegression, EncryptedLogisticRegression

def private_linear_regression():
    """Linear regression on encrypted data."""
    print("\n=== Private Linear Regression ===\n")
    
    client = Client()
    server = Server(client.evaluation_key)
    
    # Client has private training data
    X_train = np.array([[1], [2], [3], [4], [5]])
    y_train = np.array([2, 4, 6, 8, 10])
    
    # Client encrypts training data
    print("Client encrypting training data...")
    X_enc = client.encrypt_array(X_train)
    y_enc = client.encrypt_array(y_train)
    
    # Server trains on encrypted data
    print("Server training on encrypted data...")
    model = EncryptedLinearRegression()
    model.fit(server, X_enc, y_enc)
    
    # Client encrypts test input
    X_test = np.array([[6]])
    X_test_enc = client.encrypt_array(X_test)
    
    # Server makes encrypted prediction
    print("Server making encrypted prediction...")
    y_pred_enc = model.predict(server, X_test_enc)
    
    # Client decrypts prediction
    y_pred = client.decrypt_array(y_pred_enc)
    print(f"\nPrediction for X=6: {y_pred[0]:.2f} (expected: ~12)")
    print("Server NEVER saw the actual data!")


def private_classification():
    """Logistic regression classifier on encrypted data."""
    print("\n=== Private Classification ===\n")
    
    client = Client()
    server = Server(client.evaluation_key)
    
    # Client has private patient data (sensitive!)
    # Features: [age, blood_pressure, cholesterol]
    X_train = np.array([
        [25, 120, 180], [30, 125, 190], [35, 130, 200],  # Healthy
        [55, 150, 250], [60, 155, 260], [65, 160, 270],  # At risk
    ])
    y_train = np.array([0, 0, 0, 1, 1, 1])  # 0=healthy, 1=at risk
    
    # Client encrypts data
    print("Client encrypting sensitive patient data...")
    X_enc = client.encrypt_array(X_train)
    y_enc = client.encrypt_array(y_train)
    
    # Server trains classifier
    print("Server training on encrypted data...")
    model = EncryptedLogisticRegression()
    model.fit(server, X_enc, y_enc)
    
    # New patient data (also encrypted)
    X_test = np.array([[50, 145, 240]])
    X_test_enc = client.encrypt_array(X_test)
    
    # Server predicts
    print("Server classifying encrypted patient...")
    y_pred_enc = model.predict(server, X_test_enc)
    
    # Client decrypts
    risk = "At Risk" if client.decrypt_array(y_pred_enc)[0] > 0.5 else "Healthy"
    print(f"\nPatient classification: {risk}")
    print("Server NEVER saw patient data!")


if __name__ == "__main__":
    private_linear_regression()
    private_classification()
