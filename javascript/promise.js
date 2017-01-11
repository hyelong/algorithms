
var p = new Promise(function(resolve, reject) {
	if(false) {
		resolve('Success!');
	}
	else {
		reject('Failure!');
	}
});

p.then(function(s) {
  console.log(s);
}).catch(function(s) {
	console.log(s);
});

