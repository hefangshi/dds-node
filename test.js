var assert = require('assert');
var time = new Date();
var binding = require('./build/Release/dds');
console.log("init time:",new Date()-time,"ms");
var pbn = "E:AT5.AJT.A632.KJ7 Q763.KQ9.KQJ94.T 942.87653..98653 KJ8.42.T875.AQ42";
time = new Date();
console.log("pbn:",pbn);
console.log("result:");
expect = [ [ 8, 5, 8, 5, 5 ],
  [ 5, 8, 4, 8, 10 ],
  [ 10, 3, 10, 3, 5 ],
  [ 5, 8, 5, 8, 9 ] ];
binding.CalcDDtablePBN(pbn,function(result){
  console.log(result);
  assert.deepEqual(expect, result);
  console.log("calc time:",new Date()-time,"ms");
});
console.log('done');
