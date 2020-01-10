import Vue from 'vue'
import App from './App.vue'
import router from './router'
import store from './store'
import './plugins/element.js'

//プロダクションのコツをコンソールに表示してくれる機能
Vue.config.productionTip = false

//$httpプロパティを追加
Vue.prototype.$http = (url, opts) => fetch(url, opts)
// Vue.prototype.$http = fetch


//アプリを起動(以下がrouterやstoreを使った際の標準的な記述)
new Vue({
  router,
  store,
  render: h => h(App)
}).$mount('#app')
