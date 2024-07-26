const dht11 = require('./index');

const pin = 7;
const result = dht11(pin);
console.log(result);
