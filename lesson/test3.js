$('#load').on('click',clickHandler);

function clickHandler(event){
  $.ajax({
    url:'logics.json',
    type:'GET',
    dataType:'json'
  })
  .done(function(data,textStatus,jqXHR){
    console.log(data);
    console.log(jqXHR);
    updateScreen(data);
  })
  .fail(function(jqXHR,textStatus,errorThrown){
    console.log('通信が失敗しました');
  });
}

function updateScreen(logics){
  //リストの子ノードを全て削除する
  $('#result').empty();
  //子ノードをDOMに挿入する
  var list = '';
  for(var i=0; i<logics.length; i++){
      list += '<div>';
      list += 'ロジック名:'+logics[i].name+'<br>';
      list += '古典か否か:'+logics[i].isClassical;
      list += '</div>';
  }
  $('#result').append(list);
}
