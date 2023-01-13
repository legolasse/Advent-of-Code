// Part 1: Use CTRL+F in browser

// Part 2: 
let input = document.body.firstChild.innerText;

let lv = 0; for(let i = 0; true; i++) {let c = 
input[i];if(c==')'){lv--;}else 
if(c=='('){lv++;}if(lv==-1){console.log(i+1);break;}}

