const wx = require("./lib/wx");
console.log("Making app");
const app = new wx.WxApp();
app.OnInit(() => console.log("Init"));
setInterval(() => {
  app.loop();
  //console.log("Looping");
}, 1);
console.log("Making frame");
const frame = new wx.WxFrame();
console.log("showing frame");
frame.Show(true);
