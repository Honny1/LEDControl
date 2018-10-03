const char INDEX_HTML[] PROGMEM = R"=====(<!DOCTYPE HTML>
  <html lang="en">
  <head>
    <meta charset="utf-8" />
    <meta http-equiv="X-UA-Compatible" content="IE=edge,chrome=1" />
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>LED CONTROLLER</title>
    <style type="text/css">
      input[type=text], input[type=password], input[type=date], input[type=datetime], input[type=datetime-local], input[type=month], input[type=week], input[type=email], input[type=number], input[type=search], input[type=tel], input[type=time], input[type=url], input[type=color], textarea, input, .niceInput {
        border-radius: 0;
        background-color: rgba(255, 255, 255, 0.75);
        border-style: solid;
        border-width: 1px;
        border-color: #ccc;
        box-shadow: inset 0 1px 2px rgba(0,0,0,.1);
        color: rgba(0,0,0,.75);
        /*display: block;*/
        font-family: inherit;
        font-size: 12px;
        height: 3rem;
        margin: 0 0 1rem;
        padding: .5rem;
        width: 6em; /*75%;*/
        -webkit-box-sizing: border-box;
        -moz-box-sizing: border-box;
        box-sizing: border-box;
        -webkit-transition: border-color .15s linear,background .15s linear;
        -moz-transition: border-color .15s linear,background .15s linear;
        -ms-transition: border-color .15s linear,background .15s linear;
        -o-transition: border-color .15s linear,background .15s linear;
        transition: border-color .15s linear,background .15s linear;
}

.wrap {
    text-align: center;
}
.center-block {
    display: inline-block;
}
body{
    background-color: rgba(0, 0, 0, 0.75);
    font-family: Lato, sans-serif;
  }
  .paticka{
    color: black;
  }.paticka>p>a{
    color: rgba( 0, 0, 255, 0.7);
    text-decoration: none;
  }.paticka>p>a:hover {
    color: blue;
  }
  button {
  float: left;
  width: 60px;
  height: 60px;
  font-size: 25px;
  margin: 5px;
  border-radius: 30px;
  -webkit-transition-duration: 0.4s; /* Safari */
  transition-duration: 0.2s;
  cursor: pointer;
  /*text-align: center;*/
  font-family: 'Lato', sans-serif;
  font-weight: bold;
  outline:none;
  border: none;
  color:white;  }

#container {
  max-width: 280px;
  margin: auto;
  margin-top: 50px;
  background-color: rgba(189, 183, 170, 0.75);
  /*background-color: #BDB7AA;*/
  border: 2px solid #AAB0BD;
  border-radius: 15px;
  padding: 5px;
  padding-top: 20px;
  padding-bottom: 20px;
  margin-top: 20px; }

.power {
  font-size: 25px;
  background-color: rgba(255, 255, 255, 0.95);
  /*background-color: white;*/
  color: black; }
.power:hover {
  border: 2px solid black;
  color: black; }
#hony{
  text-align: center;
  font-family: Lato, sans-serif;
  font-weight: bold;}
#off {
  font-size: 20px;
  background-color: black;
  color: white; 
  text-align: left;}
#off:hover {
  font-size: 20px;
  background-color: white;
  border: 2px solid black;
  color: black; 
  text-align: left;}

#on {
  font-size: 20px;
  background-color: red;  
  color: white;
  text-align: center;}
#on:hover {
  font-size: 20px;
  text-align: center;
  background-color: white;
  border: 2px solid red;
  color: red;
  text-align: center;}

#red {  background-color: #FF191B; 
text-align: center;}
#red:hover {
  background-color: white;
  border: 2px solid #FF191B;
  color: black; 
  text-align: center;}

#red1 { background-color: #FF5319;  }
#red1:hover {
  background-color: white;
  border: 2px solid #FF5319;  }

#red2 { background-color: #FF6A5E;  }
#red2:hover {
  background-color: white;
  border: 2px solid #FF6A5E;  }

#red3 { background-color: #FF926B;  }
#red3:hover {
  background-color: white;
  border: 2px solid #FF926B;  }

#red4 { background-color: #F3F62F;  }
#red4:hover {
  background-color: white;
  border: 2px solid #F3F62F;  }

#green {  background-color: #288F00;  }
#green:hover {
  background-color: white;
  border: 2px solid #288F00;
  color: black; }

#green1 { background-color: #3CD45F;  }
#green1:hover {
  background-color: white;
  border: 2px solid #3CD45F;
  color: black;
  }
#green2 { background-color: #47E3C6;  }
#green2:hover {
  background-color: white;
  border: 2px solid #47E3C6;
  color: black; }

#green3 { background-color: #44C5DE;  }
#green3:hover {
  background-color: white;
  border: 2px solid #44C5DE;  }

#green4 { background-color: #289AE3;  }
#green4:hover {
  background-color: white;
  border: 2px solid #289AE3;
  color: black; }

#blue { background-color: #122B9C;  }
#blue:hover {
  background-color: white;
  border: 2px solid #122B9C;
  color: black; }

#blue1 {  background-color: #6C6CD4;  }
#blue1:hover {
  background-color: white;
  border: 2px solid #6C6CD4;
  color: black; }

#blue2 {  background-color: #5D2AE3;  }
#blue2:hover {
  background-color: white;
  border: 2px solid #5D2AE3;
  color: black; }

#blue3 {  background-color: #906090;  }
#blue3:hover {
  background-color: white;
  border: 2px solid #906090;
  color: black; }

#blue4 {  background-color: #BE11E3;  }
#blue4:hover {
  background-color: white;
  border: 2px solid #BE11E3;
  color: black; 
  text-align: center;}

#white {
  background-color: white;
  color: black;
  text-align: center;}
#white:hover {
  background-color: white;
  border: 2px solid black;
  color: black;
  text-align: center;}
.function1 {
  font-size: 20px; 
  text-align: center;}
.function1:hover {
  background-color: white;
  /*border: 2px solid #5A6170;*/
  color: black;
  font-size: 20px;
  text-align: center;  
  text-align: center;}
.function {
  font-size: 13px;
  background-color: rgba(90, 97, 112, 0.75);
  /*background-color: #5A6170;*/  }
.function:hover {
  background-color: white;
  border: 2px solid #5A6170;
  color: black;
  font-size: 13px;
  text-align: center;  }
    </style>
  </head>
  <body>
  <div style="min-width: 290px; text-align: center;" id="container">
  <center>
  <table>
  <tr> 
      <td><a href="lightup"><button class="power,center-block" >+</button></a></td>
      <td><a href="lightdown"><button class="power,center-block" >-</button></a></td>
      <td><a href="off"><button id="off" class="off,center-block">OFF</button></a></td>
      <td><a href="on"><button id="on" class="function1,center-block">ON</button></a></td>
      <div style="clear : both"></div>
  </tr>
  <tr>
      <td><a href="red"><button id="red" class="center-block">R</button></a></td>
      <td><a href="green"><button id="green" class="center-block">G</button></a></td>
      <td><a href="blue"><button id="blue" class="center-block">B</button></a></td>
      <td><a href="white"><button id="white"class="center-block">W</button></a></td>
      <div style="clear : both"></div>
  </tr>
  <tr>
      <td><a href="red1"><button id="red1" class="center-block"></button></a></td>
      <td><a href="green1"><button id="green1" class="center-block"></button></a></td>
      <td><a href="blue1"><button id="blue1" class="center-block"></button></a></td>
      <td><a href="Breathing"><button class="function,center-block">Breathing</button></a></td>
      <div style="clear : both"></div>
  </tr>
  <tr>
      <td><a href="red2"><button id="red2" class="center-block"></button></a></td>
      <td><a href="green2"><button id="green2" class="center-block"></button></a></td>
      <td><a href="blue2"><button id="blue2" class="center-block"></button></a></td>
      <td><a href="Strobe"><button class="function,center-block">Strobe</button></a></td>
      <div style="clear : both"></div>
  </tr>
  <tr>
      <td><a href="red3"><button id="red3" class="center-block"></button></a></td>
      <td><a href="green3"><button id="green3" class="center-block"></button></a></td>
      <td><a href="blue3"><button id="blue3" class="center-block"></button></a></td>
      <td><a href="RAINBOW"><button class="function,center-block">Rainbow</button></a></td>
      <div style="clear : both"></div>
  </tr>
  <tr>
      <td><a href="red4"><button id="red4" class="center-block"></button></a></td>
      <td><a href="green4"><button id="green4" class="center-block"></button></a></td>
      <td><a href="blue4"><button id="blue4" class="center-block"></button></a></td>
      <td><a href="TwinkleRandom"><button style="font-size: 11px;" class="function,center-block">Twinkle Random</button></a></td>
      <div style="clear : both"></div>
  </tr>
      <script src="http://jscolor.com/release/2.0/jscolor-2.0.5/jscolor.js"></script>
        <form action="SetColor" method="POST">
          
            <tr>
              <td colspan="3">
                <input style="width: 200px; text-align: center;" valign="bottom" align="bottom" name="color" placeholder="color" id="background-color" value="ABE60B" class="jscolor {text-align: center; position: center, borderColor:'#FFF', insetColor:'#FFF', backgroundColor:'#424242', }" class="mui-input">
              </td>
                <td>
                  <button class="function" type="submit" value="SetColor">Set color</button>
                </td>
            </tr>
          </table>
      </center>
      <div style="clear : both"></div>

      <div class="paticka" style="text-align: center;">
        <p style="text-align: center; font-size: 75%; border:0%; padding:0%"> Copyright &copy; 2018, By Hony & <a href="https://buchticka.eu">Buchticka.eu</a> Team</p>
      </div>
    </div>
  </body>
  </html>
)=====";
