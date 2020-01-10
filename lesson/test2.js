//JsonPのURL
var url='file:///Users/kawashimakouta/Desktop/vue/lesson/logics.js';

$.ajax({
  url:url,
  type:'GET',
  dataType:'jsonp',
  jsonp:'callback',
  jsonpCallback:'logics'
})

.done(function(data,textStatus,jqXHR){
  console.log(data);
})
.fail(function(jqXHR,textStatus,errorThrown){
  console.log('通信が失敗しました');
});
