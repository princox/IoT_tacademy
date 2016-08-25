/**
 * Module dependencies.
 */

var express = require('express'), routes = require('./routes'), user = require('./routes/user'), http = require('http'), path = require('path');

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
	if (!err)
		dbConn = db;

	console.log('request!!!'); // 아두이노 접속 시도
	request('http://192.168.0.38/', function(error, response, body) {
		if (!error && response.statusCode == 200) {
			console.log(body);//body = JSON 문자열
			var obj = JSON.parse(body);//JSON 문자열 --> JSON 객체
			console.log(obj.temp);
			console.log(obj.humidity);

			var collection = db.collection('dht11');

			//var collection = db.collection('dht11'); // 몽고디비 컬랙션 선택
			collection.save(obj, function(err, result) { // 데이터 저장
				console.log(result);
			});
		}
	});
});

app.get('/dht11', function(req, res) {
	if (dbConn != null) {
		var collection = dbConn.collection('dht11');
		collection.find({}).toArray(function(err, docs) {

			docs = JSON.stringify(docs); //이미 받은 db 를 수정하기 위하여 순수한 문자열로 바꿔서 
			docs = JSON.parse(docs); //다시 docs 객체화시켜서 db에 넣는

			for (var i = 0; i < docs.length; i++) {
				var obj = docs[i];
				if (obj.encrypt == true) {
					var decipher = crypto.createDecipher('aes256', 'password');
					decipher.update(obj.temp, 'hex', 'ascii');
					var decipherd = decipher.final('ascii');
					obj.temp = Number(decipherd);

					

					if (typeof obj.humidity != "number") { //숫자가 아니면 암호화 문자임
						var decipher2 = crypto.createDecipher('aes256', 'password');
						decipher2.update(obj.humidity, 'hex', 'ascii');
						var decipherd2 = decipher2.final('ascii');
						obj.humidity = Number(decipherd2);

					}

				}
			}

			res.send(JSON.stringify(docs));
		});
	}
});

var mqtt = require("mqtt");
var crypto = require("crypto"); //모듈로딩
var ciphers = crypto.getCiphers();

var client = mqtt.connect('mqtt://192.168.0.39');
client.on('connect', function() {
	client.subscribe('dht11');
});

client.on('message', function(topic, message) {
	console.log(message.toString());
	var json = message.toString();
	json = JSON.parse(json);

	if (dbConn != null) {
		var collection = dbConn.collection('dht11');
		json.encrypt = true;
		//암호화 모듈을 저장 temp와 humidity를 암호, crypto는 내장모듈이어서 npm 설치하지 않아도 된다.
		var cipher = crypto.createCipher('ase256', 'password');
		cipher.update(String(json.temp), 'ascii', 'hex');
		var cipherd = cipher.final('hex');
		json.temp = cipher;

		var cipher2 = crypto.createCipher('aes256', 'password');
		cipher2.update(String(json, humidity), 'ascii', 'hex');
		var cipherd2 = cipher2.final('hex');
		json.humidity = cipherd2;

		collection.save(json, function(err, result) {
			if (err)
				console.log(err);
			else
				console.log('저장완료!');
		});
	}
});
app.get('/', routes.index);
app.get('/users', user.list);

http.createServer(app).listen(app.get('port'), function() {
	console.log('Express server listening on port ' + app.get('port'));
});
