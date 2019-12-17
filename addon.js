const addon = require('./');
const fs = require('fs');

fs.readFile('./input.txt', 'utf8',(err, data)=> {
  if(err) throw err;
  else
  compute(data)
});

let check = (str1, str2) => str1.search(String.fromCharCode(str2))+1 ? true :false


const compute = data => {
  let raw = data;
  raw = raw.split(/[ .,;:\/ -]/);
  let alphabets='abcdefghijklmnopqrstuvwxyz'

  let incomingObj = new addon.obj();
  raw.forEach(input => {
    let randomNum;
    for(let i = 0; i < 5; ++i)
    {
      randomNum = Math.random() % 27;
    }

    if(randomNum === 26)
    {
      if(incomingObj.hasUpper(input))
       {
        console.log("Incoming Word: " +incomingObj.findUpper(input, alphabets.toUpperCase()));
      }
      else
      {
        console.log("Incoming Word: " +incomingObj.findLower(check, word, alphabets));
      }

    }
    else
    {
	//if(incomingObj.hasUpper(input, String.fromCharCode(randomNum+ 65)))
      if(incomingObj.hasUpper(input, String.fromCharCode(randomNum+ 97)))
      {
        console.log("Incoming Word: " + incomingObj.findUpper(input, alphabets.toUpperCase()));
      }
      else
      {
        console.log("Incoming Word: " +incomingObj.findLower(check, input, alphabets));
      }
    }

    console.log('Uppercase: ', incomingObj.ucletters);
    console.log('Lowercase: ', incomingObj.lcletters);
    console.log("-----------------------------------------");
    incomingObj = new addon.obj();
  });
};

//compute(content);
