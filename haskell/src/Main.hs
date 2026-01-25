{-# LANGUAGE OverloadedStrings #-}
{-|
Lux FHE - Haskell Example

Demonstrates basic FHE operations in Haskell.

Build: stack build
Run: stack exec luxfhe-example
-}

module Main where

import Luxfhe (Client, Server, Ciphertext)
import qualified Luxfhe as FHE
import Control.Monad.IO.Class (liftIO)

main :: IO ()
main = do
    putStrLn "Lux FHE - Haskell Example"
    putStrLn "========================="
    
    -- Create client (manages private key)
    client <- FHE.newClient
    
    -- Create server (only evaluation key)
    server <- FHE.newServer (FHE.evaluationKey client)
    
    -- Encrypt values
    let a = 42 :: Word64
        b = 8  :: Word64
    putStrLn $ "\nEncrypting: a=" ++ show a ++ ", b=" ++ show b
    
    ctA <- FHE.encryptU64 client a
    ctB <- FHE.encryptU64 client b
    
    -- Homomorphic operations
    putStrLn "\nServer performing homomorphic operations..."
    
    ctSum  <- FHE.add server ctA ctB
    ctProd <- FHE.mul server ctA ctB
    ctGt   <- FHE.gt  server ctA ctB
    
    -- Decrypt results
    putStrLn "\nDecrypting results:"
    sumResult <- FHE.decryptU64 client ctSum
    putStrLn $ "  a + b = " ++ show sumResult ++ " (expected: 50)"
    
    prodResult <- FHE.decryptU64 client ctProd
    putStrLn $ "  a * b = " ++ show prodResult ++ " (expected: 336)"
    
    gtResult <- FHE.decryptBool client ctGt
    putStrLn $ "  a > b = " ++ show gtResult ++ " (expected: True)"
    
    putStrLn "\n✓ FHE operations completed successfully"
