var config = {
    apiUrl: "https://wallet.monerov.online:1985/",
    mainnetExplorerUrl: "https://explorer.monerov.online/",
    testnetExplorerUrl: "https://testnet.xmrchain.com/",
    stagenetExplorerUrl: "http://139.162.60.17:8082/",
    nettype: 0, /* 0 - MAINNET, 1 - TESTNET, 2 - STAGENET */
    coinUnitPlaces: 11,
    txMinConfirms: 10,         // corresponds to CRYPTONOTE_DEFAULT_TX_SPENDABLE_AGE in Monero
    txCoinbaseMinConfirms: 60, // corresponds to CRYPTONOTE_MINED_MONEY_UNLOCK_WINDOW in Monero
    coinSymbol: 'XMV',
    openAliasPrefix: "xmv",
    coinName: 'MoneroV',
    coinUriPrefix: 'monerov:',
    addressPrefix: 30264,
    integratedAddressPrefix: 22583,
    subAddressPrefix: 20152,
    addressPrefixTestnet: 53,
    integratedAddressPrefixTestnet: 54,
    subAddressPrefixTestnet: 63,
    addressPrefixStagenet: 24,
    integratedAddressPrefixStagenet: 25,
    subAddressPrefixStagenet: 36,
    feePerKB: new JSBigInt('2000000000'),//20^10 - not used anymore, as fee is dynamic.
    dustThreshold: new JSBigInt('1000000000'),//10^10 used for choosing outputs/change - we decompose all the way down if the receiver wants now regardless of threshold
    txChargeRatio: 0.5,
    defaultMixin: 10, // minimum mixin for hardfork v8 is 10 (ring size 11)
    txChargeAddress: '',
    idleTimeout: 30,
    idleWarningDuration: 20,
    maxBlockNumber: 500000000,
    avgBlockTime: 60,
    debugMode: false
};
