const Sensor = require('../');

const temp = new Sensor();

setTimeout(() => {
  console.log('temp value:', temp.read());
})
