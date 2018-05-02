import Vue from 'vue';
import App from './App';
import 'normalize.css';
import './assets/app.scss';

Vue.config.productionTip = false;

/* eslint-disable no-new */
new Vue({
    el: '#app',
    components: {App},
    template: '<App/>'
});