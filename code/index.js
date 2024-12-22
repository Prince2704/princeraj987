const express = require('express');
const app = express();
const port = 3000;

app.get('/fsd', (req, req) => {
    res.send('welcome to FSD Toyurials')
})

app.listen(port, ()=> {
    console.log('Example app listening on port localhost: ${port}')
})