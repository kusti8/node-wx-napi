var binary = require("node-pre-gyp");
var path = require("path");
var binding_path = binary.find(
  path.resolve(path.join(__dirname, "../package.json"))
);
var oldpath = process.cwd();
process.chdir(path.dirname(binding_path));
var wx = require(binding_path);
process.chdir(oldpath);

module.exports = wx;
