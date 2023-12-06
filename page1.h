//ROOT PAGE
const char htmlPage1[] PROGMEM = R"=====(
<html>

<head>
    <meta http-equiv="content-type" content="text/html;charset=UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1">
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
} </style>
</head>

<body>
    <div class="container">
        <h1>Study Buddy</h1>
        <h2>Your digital friend to active learning</h2>
        <p>
            <button><a href="/page2">Login</a></button>
            <button><a href="/page3">Sign Up</a></button>
        </p>
    </div>
</body>

</html>
)=====";