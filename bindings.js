var mod;

if(process.env.DEBUG) {
    mod = require('./build/Debug/addon.node');
} else {
    mod = require('./build/Release/addon.node');
}

module.exports = mod;