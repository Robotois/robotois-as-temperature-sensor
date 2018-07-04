const Sensor = require('../');

const temp = Sensor();

setTimeout(() => {
  console.log('temp value:', temp.read());
})
