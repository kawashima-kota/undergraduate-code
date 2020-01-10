import Vue from 'vue'
import Router from 'vue-router'
import BookSearch from './components/BookSearch.vue'
import BookForm from './components/BookForm.vue'
import Home from './components/Home.vue'

Vue.use(Router)

export default new Router({
  mode: 'history',
  base: process.env.BASE_URL,
  routes: [
    //トップページ（登録済みレビューの一覧）
    {
      path: '/',
      name: 'home',
      component: Home
    },
    //GoogleBooksの検索フォーム
    {
      path: '/search',
      name: 'search',
      component: BookSearch
    },
    //書籍レビューのためのフォーム
    {
      path: '/form',
      name: 'form',
      component: BookForm
    },
    //最終的な受け皿
    { path: '*', redirect: {name: 'home'}}
  ]
})
