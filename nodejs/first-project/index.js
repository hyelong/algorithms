var CountStream = require('./countstream');
var countStream = new CountStream('book');
var http = require('http');

console.log(require.resolve('./countstream'));
console.log('path: ',__dirname);
console.log('file name: ',__filename);
http.get('http://www.manning.com', function(res){
  res.pipe(countStream);  
});

countStream.on('total', function(count){
  console.log('Total matches:', count);
});
