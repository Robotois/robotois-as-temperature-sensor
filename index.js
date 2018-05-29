const Sensor = require('bindings')('TempSensor');

/**
 * Creates an instance of TempSensor.
 * @param {int} port The port number where this component us connected.
 * @param {int} add The second argument.
 * @returns {TempSensor}.
 */
function TempSensor(add = 0) {
  const self = this;
  // EventEmitter.call(this);
  this.temp = new Sensor(add);

  // process.on('SIGINT', () => {
  //   self.ph.release();
  // });
  //
  // process.on('SIGTERM', () => {
  //   self.ph.release();
  // });
}

TempSensor.prototype.deviceInfo = function deviceInfo() {
  this.temp.getInfo();
}

TempSensor.prototype.read = function deviceInfo() {
  return this.temp.reading();
}

module.exports = TempSensor;
