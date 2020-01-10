<template>
  <div id="form">
    <!--選択中の書籍を表示-->
    <BookInfo :book="book"></BookInfo>
    <hr />
    <!--レビュー入力のためのフォームを準備-->
    <el-form ref="form" :model="form" :rules="rules" label-width="120px">
      <!--読了日-->
      <el-form-item label="読了日">
        <el-date-picker type="date" v-model="form.read"></el-date-picker>
      </el-form-item>
      <!--感想-->
      <el-form-item label="感想" prop="memo">
        <el-input type="textarea" size="large" v-model="form.memo"></el-input>
      </el-form-item>
      <!--登録-->
      <el-form-item>
        <el-button type="primary" @click="onsubmit">登録</el-button>
      </el-form-item>
    </el-form>
  </div>
</template>

<script>
import { mapGetters, mapActions  } from 'vuex'
import BookInfo from '@/components/BookInfo.vue'
import { UPDATE_CURRENT, UPDATE_BOOK } from '@/mutation-types'

export default {
  name: 'book-form',
  components: {
    BookInfo
  },
  data() {
    return {
      book: {},//選択中の書籍
      form: { //フォームの内容
        read: new Date(),
        memo: ''
      },
      rules: {
        memo: [
          { required: true, message: 'メモが未入力です。', trigger: 'blur' }
        ]
      }
      /*
      rules: {
        memo: [{
          validator: (rule, value, callback) => {
            console.log(rule);
            if (!value) {
              return callback(new Error('メモが未入力です。'))
            }
          },
          trigger: 'change'
        }]
      }
      */
    }
  },
  computed: mapGetters([ 'current', 'getBookById' ]),
  //ページロード時の処理
  created() {
    //選択中に書籍がない場合(/)へリダイレクト
    if (!this.current) {
      this.$router.push('/')
    }
    //選択中の書籍をbookプロパティに詰め替え
    this.book = Object.assign({}, this.current)
  },
  //マウント時の処理
  mounted() {
    //選択中の書籍でストア内の情報を検索
    let b = this.getBookById(this.book.id)
    //すでにレビューが存在する場合は，その内容をフォームに反映
    if (b) {
      this.form.read = b.read
      this.form.memo = b.memo
    }
  },
  methods: {
    ...mapActions([UPDATE_BOOK, UPDATE_CURRENT]),
    //登録ボタンでデータを登録
    onsubmit() {
      //入力値の検証を実行
      this.$refs['form'].validate((valid) => {
        //検証に成功したらストアにも反映
        if (valid) {
          this[UPDATE_BOOK](
            Object.assign({}, this.book, this.form)
          )
          //選択中の書籍をクリア
          this[UPDATE_CURRENT](null)
          //処理成功の通知メッセージを表示
          this.$notify({
            title: 'Reading Recorder',
            message: this.$createElement('p', { style: 'color: #009' },
              '読書情報の登録／更新に成功しました。'),
            duration: 2000
          })
          //フォームの内容をクリア
          this.form.read = new Date()
          this.form.memo = ''
          //トップページにリダイレクト
          this.$router.push('/')
        }
      })
    }
  }
}
</script>

<style scoped>
#form {
  margin-top: 15px;
}
</style>
