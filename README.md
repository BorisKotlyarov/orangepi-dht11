# Orange pi DHT11 sensor

## Before Install
```bash
git clone https://github.com/zhaolei/WiringOP.git -b h3
 
cd WiringOP
chmod +x ./build
sudo ./build
```

## Usage 
```javascript

const dht11 = require(`orangepi-dht11`);

const pin = 7;
const result = dht11(pin);
console.log(result); 
// { error: '', temperature: 27.600000381469727, humidity: 44 }
```
