const addon = require('bindings')('addon');
const { promisify } = require('util');

module.exports = {
    add: addon.add,
    addAsync: promisify(addon.addAsync),
}