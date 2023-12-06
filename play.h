//Play page - three buttons for rock, paper and scissors accordingly
const char play[] PROGMEM = R"=====(
<html>

<head>
    <meta http-equiv="content-type" content="text/html;charset=UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <title>Play</title>
    <style>
html {
  height: 100%;
  width: 100%;
}

html {
  font-family: Helvetica;
  background-color: #76a2ea;
  display: inline-block;
  margin: 0px auto;
  text-align: center;
}

h1 {
  font-size: 64px;
}

body {
  color:white;
}

button {
  background-color: #4caeac;
  border: none;
  color: white;
  padding: 16px 40px;
  border-radius: 10px;
  text-decoration: none;
  font-size: 30px;
  margin: 10px;
  cursor: pointer;}

a {
  text-decoration: none;
  color: white;
}

form {
 margin: 10px;
 text-align: left;
 font-size: 20px;
}

.textBox {
  padding: 5px;
  margin: 10px;
}

.submit {
  margin: 20px;
  border: black 1px;
  border-radius: 10%;
  padding: 5px;
  font-size: 24px;
}
</style>
</head>

<body>
    <div class="container">
        <h1>Play</h1>
        <form action='/play' method='POST'>
          <button name="ROCK" type="submit" value="1">Rock</button><br>
          <button name="PAPER" type="submit" value="2">Paper</button><br>
          <button name="SCISSORS" type="submit" value="3">Scissors</button>
        </form>
    </div>
</body>

</html>
)=====";
