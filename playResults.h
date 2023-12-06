//Play results - used specifically when the study method is in action - removes the option to go back to home
namespace playResults{
  String runStudyPlay(int playResult){
    String studyPlay = "";

    studyPlay += "<html>";
    studyPlay += "<head>";
    studyPlay += "<meta http-equiv=\"content-type\" content=\"text/html;charset=UTF-8\">";
    studyPlay += "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">";
    studyPlay += "<title>Play Results</title>";
    studyPlay += "<style>";
    studyPlay += "html {";
    studyPlay += "height: 100%;";
    studyPlay += "width: 100%;";
    studyPlay += "}";
    studyPlay += "html {";
    studyPlay += "font-family: Helvetica;";
    studyPlay += "background-color: #76a2ea;";
    studyPlay += "display: inline-block;";
    studyPlay += "margin: 0px auto;";
    studyPlay += "text-align: center;";
    studyPlay += "}";
    studyPlay += "h1 {";
    studyPlay += "font-size: 64px;";
    studyPlay += "}";
    studyPlay += "h3 {";
    studyPlay += "font-size: 32px;";
    studyPlay += "}";
    studyPlay += "body {";
    studyPlay += "color:white;";
    studyPlay += "}";
    studyPlay += "button {";
    studyPlay += "background-color: #4caeac;";
    studyPlay += "border: none;";
    studyPlay += "color: white;";
    studyPlay += "padding: 16px 40px;";
    studyPlay += "border-radius: 10px;";
    studyPlay += "text-decoration: none;";
    studyPlay += "font-size: 30px;";
    studyPlay += "margin: 6px;";
    studyPlay += "cursor: pointer;}";
    studyPlay += "a {";
    studyPlay += "text-decoration: none;";
    studyPlay += "color: white;";
    studyPlay += "}";
    studyPlay += "form {";
    studyPlay += "margin: 10px;";
    studyPlay += "text-align: left;";
    studyPlay += "font-size: 20px;";
    studyPlay += "}";
    studyPlay += ".textBox {";
    studyPlay += "padding: 5px;";
    studyPlay += "margin: 10px;";
    studyPlay += "}";
    studyPlay += ".submit {";
    studyPlay += "margin: 20px;";
    studyPlay += "border: black 1px;";
    studyPlay += "border-radius: 10%;";
    studyPlay += "padding: 5px;";
    studyPlay += "font-size: 24px;";
    studyPlay += "}";
    studyPlay += "p {";
    studyPlay += "font-size: 22px;";
    studyPlay += "}";
    studyPlay += "</style>";
    studyPlay += "</head>";
    studyPlay += "<body>";
    if (playResult == 1){
      studyPlay += "<h1>It's a Draw!<h1>";
      studyPlay += "<h2>You both had the same idea</h2>";
    } else if (playResult == 2){
      studyPlay += "<h1>You Lost!</h1>";
      studyPlay += "<h2>Better luck next time</h2>";
    } else {
      studyPlay += "<h1>You Won!</h1>";
      studyPlay += "<h2>Nice going</h2>";
    }

    studyPlay += "<button><a href=\"/whileStudying\">Back to Studying</a></button><br>";
    studyPlay += "</body>";
    studyPlay += "</html>";

    return studyPlay;
  }
}