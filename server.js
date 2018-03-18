import express from 'express';
import cors from 'cors';
import morgan from 'morgan';
import path from 'path';
import bodyParser from 'body-parser';

let app = express();

app.use('/public', express.static(path.join(__dirname, 'public')));

app.use(morgan('dev'));
app.use(cors());

app.use(bodyParser.urlencoded({
    extended: true
}));

app.use(bodyParser.json());

const port = process.env.port || 3000;

const router = express.Router();

app.get('/', (req, res) => {
    console.log(req);
    res.json({msg: 'Server is running.'});
});
router.get('/test', (req, res) => {
    res.json({msg: 'Server is running.'});
});
app.get('/abc', (req, res) => res.send('Hello World!'))

app.use('/api', router);

app.listen(port);
console.log(`Listening on port ${port}`);
