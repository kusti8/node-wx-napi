const wx = require("./lib/wx");
console.log("Making app");
const app = new wx.WxApp();
app.OnInit(() => console.log("Init"));
setInterval(() => {
  app.loop();
  if (frame.getClosed()) console.log("is closed");
  //console.log("Looping");
}, 1);
console.log(wx.desktopSize());
console.log("Making frame");
const frame = new wx.WxFrame();
console.log("showing frame");
frame.SetBackgroundColour(0, 0, 255);
frame.Show(true);
const panel = new wx.WxPanel(frame);
panel.SetBackgroundColour(255, 0, 255);
panel.Show(true);
// frame.OnResize((width, height) => {
//   console.log("Resized", width, height);
// });
frame.OnClose(() => {
  console.log("Closed");
});
setTimeout(() => {
  console.log("Setting size");
  frame.SetSize(200, 200);
  console.log(frame.GetSize());
  frame.SetLoc(50, 50);
}, 5000);
console.log(wx.desktopSize());
