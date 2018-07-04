const Sensor = require('bindings')('TempSensor');

const round = (value, decimals) => {
  return Number(Math.round(value+'e'+decimals)+'e-'+decimals);
}

/**
 * Creates an instance of TempSensor.
 * @param {int} add The second argument.
 * @returns {TempSensor}.
 */
function TempSensor({ client, topic }, addr = 0) {
  const self = this;
  // EventEmitter.call(this);
  this.temp = new Sensor(addr);
  this.prevValue = -100;
  this.client = client;
  this.topic = topic;
  this.eventInterval = false;

  process.on('SIGINT', () => {
    self.disableMonitor();
  });

  process.on('SIGTERM', () => {
    self.disableMonitor();
  });
}

TempSensor.prototype.initClient = function initClient() {
  if (this.client) {
    this.client.subscribe(this.topic);
  }
}

TempSensor.prototype.publishValue = function publishValue(value) {
  const message = {
    reported: {
      sensors: {
        temp: value
      }
    }
  }
  this.client.publish(this.topic, JSON.stringify(message));
}

TempSensor.prototype.deviceInfo = function deviceInfo() {
  this.temp.getInfo();
}

TempSensor.prototype.read = function read() {
  let value = this.temp.reading();
  if (value === -100) { // error reading the sensor
    // console.log('[tempSensor] - reading error:', value);
    return this.prevValue;
  }
  const rounded = round(value, 2);
  if (this.client !== undefined && this.prevValue !== rounded) {
    this.publishValue(rounded.toString());
    this.prevValue = rounded;
  }
  return rounded;
}

TempSensor.prototype.enableMonitor = function enableEvents() {
  if (!this.eventInterval) {
    this.eventInterval = setInterval(() => {
      this.read();
    }, 2000);
  }
}

TempSensor.prototype.disableMonitor = function disableMonitor() {
  clearInterval(this.eventInterval);
  this.eventInterval = false;
}

const SensorCreator = (opt = {}) => {
  const { client, topic } = opt;
  const sensor = new TempSensor({ client, topic });
  // sensor.initClient();
  return sensor
}

module.exports = SensorCreator;
