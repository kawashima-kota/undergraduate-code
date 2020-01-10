Vue.filter('empty',function(val){
    if(val == ''){
      return '情報がありません．';
    }
    return val;
});

var app = new Vue({
  el:'#app',
  data:{
    //表示中のロジック数
    count:0,
    //「古典」のチェック状態
    showClassical:false,
    //「非古典」のチェック状態
    showNonClassical:false,
    //「その他」のチェック状態
    showOthers:false,
    //「並び替え」の選択値
    sortOrder:1,
    //論理のリスト
    logics:[],
    //エラーの有無
    isError:false,
    message:''
  },
  created: function(){
    var url='logics.js';

    $.ajax({
      url:url,
      type:'GET',
      dataType:'jsonp',
      jsonp:'callback',
      jsonpCallback:'logics'
    })

    .done(function(data,textStatus,jqXHR){
      console.log(data);
      this.logics = data;
    }.bind(this))
    .fail(function(jqXHR,textStatus,errorThrown){
      console.log('通信が失敗しました');
      this.isError = true;
      this.message = '読み込みに失敗しました．'
    }.bind(this));
  },
  computed:{
    //絞り込み後のリストを返す算出プロパティ
    filteredList:function(){
      var newList = []; //絞り込み後のリストを格納する配列
      for(var i=0; i< this.logics.length; i++){
        var isShow = true; //フラグ
        if(this.showClassical && !this.logics[i].isClassical){
          isShow = false;
        }
        if(this.showNonClassical && !this.logics[i].isNonClassical){
          isShow = false;
        }
        if(this.showOthers && !this.logics[i].isOther){
          isShow = false;
        }
        //表示対象のロジックだけ新しい配列に追加する
        if(isShow){
          newList.push(this.logics[i]);
        }
      }
      return newList;
    }
  },
  watch:{
    showClassical:function(newVal,oldVal){
      console.log('showClassicalウォッチャが呼び出されました');
    },
    showNonClassical:function(newVal,oldVal){
      console.log('showNonClassicalウォッチャが呼び出されました');
    },
    showOthers:function(newVal,oldVal){
      console.log('showOthersウォッチャが呼び出されました');
    },
  }
});
