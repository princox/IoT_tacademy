
/**
 * Module dependencies.
 */

var express = require('express')
  , routes = require('./routes')
  , user = require('./routes/user')
  , http = require('http')
  , path = require('path');

var app = express();

// all environments
app.set('port', process.env.PORT || 3000);
app.set('views', __dirname + '/views');
app.set('view engine', 'jade');
app.use(express.favicon());
app.use(express.logger('dev'));
app.use(express.bodyParser());
app.use(express.methodOverride());
app.use(app.router);
app.use(express.static(path.join(__dirname, 'public')));

// development only
if ('development' == app.get('env')) {
  app.use(express.errorHandler());
  
}
var MongoClient = require('mongodb').MongoClient;
var request = require('request'); 
var url = 'mongodb://localhost:27017/arduino';
var dbConn = null;
MongoClient.connect(url, function(err, db) { // DB에 접속
   console.log("Connected correctly to server");
   if (!err) dbConn = db;
   
   console.log('request!!!'); // 아두이노 접속 시도
   request('http://192.168.0.38/', function (error, response, body) {
    if (!error && response.statusCode == 200) {
      console.log(body);//body = JSON 문자열
      var obj = JSON.parse(body);//JSON 문자열 --> JSON 객체
      console.log(obj.temp);
      console.log(obj.humidity);
      
      
      var collection = db.collection('dht11');
      
      //var collection = db.collection('dht11'); // 몽고디비 컬랙션 선택
      collection.save(obj, function(err, result){ // 데이터 저장
       console.log(result);
      });
    }
  });
 });

app.get('/dht11', function(req, res){
 if(dbConn != null){
	 var collection = dbConn.collection('dht11');
	 collection.find({}).toArray(function(err, docs){
		 res.send(JSON.stringify(docs));
	 });
 }
});
app.get('/', routes.index);
app.get('/users', user.list);

http.createServer(app).listen(app.get('port'), function(){
  console.log('Express server listening on port ' + app.get('port'));
});
