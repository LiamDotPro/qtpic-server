'use strict';

var _express = require('express');

var _express2 = _interopRequireDefault(_express);

var _cors = require('cors');

var _cors2 = _interopRequireDefault(_cors);

var _morgan = require('morgan');

var _morgan2 = _interopRequireDefault(_morgan);

var _path = require('path');

var _path2 = _interopRequireDefault(_path);

var _bodyParser = require('body-parser');

var _bodyParser2 = _interopRequireDefault(_bodyParser);

function _interopRequireDefault(obj) { return obj && obj.__esModule ? obj : { default: obj }; }

var app = (0, _express2.default)();

app.use('/public', _express2.default.static(_path2.default.join(__dirname, 'public')));

app.use((0, _morgan2.default)('dev'));
app.use((0, _cors2.default)());

app.use(_bodyParser2.default.urlencoded({
    extended: true
}));

app.use(_bodyParser2.default.json());

var port = process.env.port || 3000;

var router = _express2.default.Router();

app.get('/', function (req, res) {
    console.log(req);
    res.json({ msg: 'Server is running.' });
});
router.get('/test', function (req, res) {
    res.json({ msg: 'Server is running.' });
});
app.get('/abc', function (req, res) {
    return res.send('Hello World!');
});

app.use('/api', router);

app.listen(port);
console.log('Listening on port ' + port);
//# sourceMappingURL=server.js.map