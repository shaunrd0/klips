
A template project for getting started working on the Ethereum blockchain.
This project comes with basic packages for compiling and deploying Solidity contracts with Truffle.

Run `cp example.secrets.json secrets.json` and fill out the copied `secrets.json` with your information.

From this directory, run `npm install` to install required packages.

From there, we can create any contracts and deploy to development or public networks...
### Development Deploy

```asm
npx truffle develop
truffle(develop)> migrate

Compiling your contracts...
===========================
> Compiling ./contracts/Migrations.sol
> Artifacts written to /home/kapper/Code/klips/blockchain/eth/truffle-solidity/build/contracts
> Compiled successfully using:
   - solc: 0.8.0+commit.c7dfd78e.Emscripten.clang



Starting migrations...
======================
> Network name:    'develop'
> Network id:      5777
> Block gas limit: 6721975 (0x6691b7)


1_initial_migration.js
======================

   Deploying 'Migrations'
   ----------------------
   > transaction hash:    0xa82aeb7e6e3839f06321edc4b41fdb92e70f87b9a989f846fd465623deda4139
   > Blocks: 0            Seconds: 0
   > contract address:    0xD79FAf957cC8d3d6c7f8fc10875D8aF75e4eE9F1
   > block number:        1
   > block timestamp:     1620058221
   > account:             0xcFE4341F1DFEbdff039642e1A26032755F38ADA5
   > balance:             99.995114
   > gas used:            244300 (0x3ba4c)
   > gas price:           20 gwei
   > value sent:          0 ETH
   > total cost:          0.004886 ETH


   > Saving migration to chain.
   > Saving artifacts
   -------------------------------------
   > Total cost:            0.004886 ETH


Summary
=======
> Total deployments:   1
> Final cost:          0.004886 ETH


- Blocks: 0            Seconds: 0
- Saving migration to chain.

truffle(develop)> .exit
```

### Public Network Deploy

To deploy, you need ETH on a wallet connected to ropsten. Metamask is the wallet I use.
I explain how to configure metamask on ropsten on [Knoats - Solidity](https://knoats.com/books/c/page/solidity)

Give yourself test Ethereum with the [Ropsten ETH Faucet](https://faucet.ropsten.be)

To deploy to ropsten test network, and verify using `truffle-verify-plugin` - 

```asm
npx truffle migrate --network ropsten
npx truffle run verify Migrations --network ropsten
```

For a guide on how I configured this project, see [Knoats - Solidity](https://knoats.com/books/c/page/solidity)

An example ERC20 token can be found at [shaunrd0/karma](https://gitlab.com/shaunrd0/karma)
