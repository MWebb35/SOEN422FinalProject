//Stats page
namespace stats{
  String runPage(String wins, String games, String minutes, String interrupts, String petName){
    String htmlStats = "";
    htmlStats += "<html>";
    htmlStats += "<head>";
    htmlStats += "<meta http-equiv=\"content-type\" content=\"text/html;charset=UTF-8\">";
    htmlStats += "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">";
    htmlStats += "<title>Stats</title>";
    htmlStats += "<style>";
    htmlStats += "html {";
    htmlStats += "height: 100%;";
    htmlStats += "width: 100%;";
    htmlStats += "}";
    htmlStats += "html {";
    htmlStats += "font-family: Helvetica;";
    htmlStats += "background-color: #76a2ea;";
    htmlStats += "display: inline-block;";
    htmlStats += "margin: 0px auto;";
    htmlStats += "text-align: center;";
    htmlStats += "}";
    htmlStats += "h1 {";
    htmlStats += "font-size: 64px;";
    htmlStats += "}";
    htmlStats += "h3 {";
    htmlStats += "font-size: 32px;";
    htmlStats += "}";
    htmlStats += "body {";
    htmlStats += "color:white;";
    htmlStats += "}";
    htmlStats += "button {";
    htmlStats += "background-color: #4caeac;";
    htmlStats += "border: none;";
    htmlStats += "color: white;";
    htmlStats += "padding: 16px 40px;";
    htmlStats += "border-radius: 10px;";
    htmlStats += "text-decoration: none;";
    htmlStats += "font-size: 30px;";
    htmlStats += "margin: 6px;";
    htmlStats += "cursor: pointer;}";
    htmlStats += "a {";
    htmlStats += "text-decoration: none;";
    htmlStats += "color: white;";
    htmlStats += "}";
    htmlStats += "form {";
    htmlStats += "margin: 10px;";
    htmlStats += "text-align: left;";
    htmlStats += "font-size: 20px;";
    htmlStats += "}";
    htmlStats += ".textBox {";
    htmlStats += "padding: 5px;";
    htmlStats += "margin: 10px;";
    htmlStats += "}";
    htmlStats += ".submit {";
    htmlStats += "margin: 20px;";
    htmlStats += "border: black 1px;";
    htmlStats += "border-radius: 10%;";
    htmlStats += "padding: 5px;";
    htmlStats += "font-size: 24px;";
    htmlStats += "}";
    htmlStats += "p {";
    htmlStats += "font-size: 22px;";
    htmlStats += "}";
    htmlStats += "h2 {";
    htmlStats += "font-size: 32px;";
    htmlStats += "}";
    htmlStats += "</style>";
    htmlStats += "</head>";
    htmlStats += "<body>";
    htmlStats += "<h1>Statistics</h1>";

    htmlStats += "<h2>Play</h2>";
    htmlStats += "<p><b>Games:</b> "+games+"</p>";
    htmlStats += "<p><b>Wins:</b> "+wins+"</p>";

    htmlStats += "<h2>Sleep</h2>";
    htmlStats += "<p><b>Minutes:</b> "+minutes+"</p>";
    htmlStats += "<p><b>Times sleep was interrupted: </b>"+interrupts+"</p>";
    if (interrupts > minutes){
      htmlStats += "<p>\nTry to stay focussed when your pet is asleep</p>";
    } else {
      htmlStats += "<p>\nGreat job staying focussed while your pet is asleep! Keep it up!</p>";
    }
    htmlStats += "<button><a href=\"/page4\">Home</a></button><br>";
    htmlStats += "</body>";
    htmlStats += "</html>";
//)=====";
return htmlStats;
  }
}
