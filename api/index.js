const mysql = require('mysql2');
const fs = require('fs');
const express = require('express');
const bodyParser = require('body-parser');

const app = express();
app.use(express.json());

app.use(bodyParser.urlencoded({extended: true}));
app.use(bodyParser.json())

const PORT = process.env.PORT || 3000;

var config =
{
    host: 'tagamotchi.mysql.database.azure.com',
    user: 'root123',
    password: 'Admin123!',
    database: 'tamagotchi',
    port: 3306
};

const conn = new mysql.createConnection(config);

conn.connect(
    function (err) { 
    if (err) { 
        console.log("!!! Cannot connect !!! Error:");
        throw err;
    }
    else
    {
       console.log("Connection established");
    }
});

app.get("/Status", (request, response) => {
    console.log(request.query.username);
    
    const status = {
       "Status": "Running"
    };
    
    response.send(status);
 });

 app.get("/GetUsername" , (request, response) => {
    console.log(request);
    console.log(request.query);
    conn.query('SELECT * FROM placeholder WHERE userName = (?)',[request.query.username], 
    function (error, results, fields){
        if (error) throw error;
        else console.log(results);
        response.send(results);
    });
 })

 app.get("/GetPetDetails", (request, response) => {
    conn.query('SELECT petName FROM petdetails WHERE userName = (?)', [request.query.username], function (error, results, fields){
        if (error) throw error;
        else console.log(results);
        response.send(results);
    })
 });
 
 app.get("/GetEverything" , (request, response) =>{
    conn.query('SELECT * FROM placeholder', function (error, results, fields){
        if (error) throw error;
        else console.log(results);
        response.send("Get request recieved");
    });
 });

 app.get("/GetEverythingPet", (request, response) => {
    conn.query('SELECT * FROM petdetails WHERE username = (?)', [request.query.username], function (error, results, fields){
        if (error) throw error;
        else console.log(results);
        response.send(results);   
    } )
 })


app.get("/UpdateWins" , (request, response) => {
    conn.query('UPDATE petdetails SET wins = wins + 1 WHERE userName = (?)' , [request.query.username], function (error, results, fields){
        if (error) throw error;
        else console.log(results);
        response.send("Wins Updated");
    })
})

app.get("/UpdateMinutes" , (request, response) => {
    conn.query('UPDATE petdetails SET minutes = minutes + 1 WHERE userName = (?)' , [request.query.username], function (error, results, fields){
        if (error) throw error;
        else console.log(results);
        response.send("Minutes Updated");
    })
})

app.get("/UpdateGames", (request, response) => {
    conn.query('UPDATE petdetails SET games = games + 1 WHERE userName = (?)' , [request.query.username], function (error, results, fields){
        if (error) throw error;
        else console.log(results);
        response.send("Games Updated");
    })
})

app.get("/UpdateInterrupts", (request, response) => {
    conn.query('UPDATE petdetails SET interrupts = interrupts + 1 WHERE userName = (?)' , [request.query.username], function (error, results, fields){
        if (error) throw error;
        else console.log(results);
        response.send("Interrupts Updated");
    })
})
 
app.post("/PostUsername", (request, response) =>{
    console.log("We in the postUsername");
    console.log(request.body.username)
    console.log(request.body)
    console.log(request)

    conn.query('INSERT INTO placeholder (userName, passwords) VALUES (?,?);', [request.body.username,request.body.password], 
    function (err, results, fields) {
        if (err) throw err;
    else console.log('Inserted ' + results.affectedRows + ' row(s).');
    response.send("yes");
    })
});

app.post("/PostPet", (request, response) => {
    console.log("We in the postPet");
    console.log(request.body.username)
    console.log(request.body)
    console.log(request)
    conn.query('INSERT INTO petdetails (userName, petName, wins, games, minutes, interrupts) VALUES (?,?,?,?,?,?);', [request.body.username,request.body.petname,request.body.wins,request.body.games,request.body.minutes,request.body.interrupts], 
    function (err, results, fields) {
        if (err) throw err;
    else console.log('Inserted ' + results.affectedRows + ' row(s).');
    response.send("yes");
    })
});

app.listen(PORT, () => {
    console.log("Server Listening on PORT:", PORT);
});