//SIGN UP PAGE
const char htmlPage3[] PROGMEM = R"=====(
<html>

<head>
    <meta http-equiv="content-type" content="text/html;charset=UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <title>Sign Up</title>
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
    <div class="container">
        <h1>Sign Up</h1>
        <h2>Hello! It's great to have you here</h2>

        <p>We need some details before we can match you with your perfect pet</p>

        <form action='/page3' method='POST'>
        
        
        Enter a username:<br> <input class="textBox" type='text' name='USERNAME' placeholder='Your username'><br>
        
        Enter a password:<br> <input class="textBox" type='password' name='PASSWORD' placeholder='password'<br>
        
        <br>Enter your password again:<input class="textBox" type='password' name='PASSWORDAGAIN' placeholder='password'<br>
        
        <br>What would you like to call your pet? <br>
        <input class="textBox" type='text' name='PETNAME' placeholder='Pet Name'><br>
        
        <input class="submit" type='submit' name='SUBMITSIGNUP' value='Submit'></form>
    </div>
</body>

</html>
)=====";