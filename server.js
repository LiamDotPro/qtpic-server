const express = require('express');
const bodyParser = require('body-parser');

const app = express();
app.use(bodyParser.urlencoded({ extended: true }));
app.use(bodyParser.json);

const port = process.env.port || 3000;

const router = express.Router();

app.get('/', (req, res) => {
    console.log(req);
    res.json({ msg: 'Server is running.' });
});
router.get('/test', (req, res) => {
    res.json({ msg: 'Server is running.' });
});
app.get('/abc', (req, res) => res.send('Hello World!'))

app.use('/api', router);

app.listen(port);
console.log(`Listening on port ${port}`);
