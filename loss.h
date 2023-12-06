//Play loss page
const char loss[] PROGMEM = R"=====(
<html>

<head>
    <meta http-equiv="content-type" content="text/html;charset=UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <title>Loss.</title>
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
  margin: 6px;
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
    <h1>You lost!</h1>
    <h2>Better luck next time!</h2><br>
    <button><a href="/play">Play Again</a></button>
    <button><a href="/page4">Back to Home</a></button><br>
</body>

</html>
)=====";
