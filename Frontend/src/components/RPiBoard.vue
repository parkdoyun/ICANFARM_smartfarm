<template>
  <div class="container">
    <div class="item1">
      <div class="nav1">
        <div class="ICON"></div>
        <div style="font-size: 36px;">{{ userName }}</div>
        <div><button v-bind:title="default_hub">Hub No. {{ default_hub }}</button></div>
      </div>
      <div class="nav2">
        <div>
          <router-link to="/monitor" style="text-decoration: none; color: black;">Monitor</router-link>
        </div>
        <div>
          <div><a href="/" style="text-decoration: none; color: black;" @click="logout">LOGOUT</a></div>
        </div>
      </div>
      <router-view/>
    </div>

    <div class="item2">
      <div class="PW_box">
        <!-- <div></div> -->
        <label for="" style="font-size: 48px; font-weight: bold;">RPi Password</label>
        <input type="text" style="font-size: 64px; text-align: center;" v-model="newPassword" @input="onInput" maxlength="6" size="6" :placeholder="inputValue" @keyup.enter="changeRPiPW">
        <button type="button" style="font-size: 24px; height: 50px; width: 100px;" :disabled="newPassword.length !== 6" @click="changeRPiPW">SAVE</button>
      </div>
    </div>

    <div class="modal" tabindex="-1" v-if="isModalOpen" @keyup.enter="closeModal">
      <div class="modal-dialog">
        <div class="modal-content">
          <div class="modal-header">
            <h5 class="modal-title"><h2>New RPi Password</h2></h5>
            <button type="button" class="btn-close" data-bs-dismiss="modal" aria-label="Close" @click="closeModal"></button>
          </div>
          <div class="modal-body">
            <p>{{ message }}</p>
          </div>
        </div>
      </div>
    </div>

  </div>
</template>

<script>
import { api } from "@/utils/axios";
import 'bootstrap/dist/css/bootstrap.css';
import 'bootstrap/dist/js/bootstrap.js';

export default {
  name: 'LoginPage',
  data(){
    return{
      userName: "",
      isModalOpen: false,
      inputValue: '',
      newPassword: '',
      member_id: null,
      default_hub: null,
      message: "",
    }
  },
  mounted(){
    this.member_id = localStorage.getItem('user');
    this.userName = localStorage.getItem('username');
    api.member.getDefaultHub(this.member_id)
    .then((res) => {
      this.default_hub = res.data;
    })
    .catch((err) => {
      console.log('ERROR');
    });
    api.member.getRPiPW(this.member_id)
    .then((res) => {
      this.inputValue = res.data;
    })
    .catch((err) => {
      console.log('error')
    })
    const startTime = localStorage.getItem('startTime');
    if(startTime){
      this.startTime = new Date(parseInt(startTime));
      this.intervalId = setInterval(this.updateUptime, 1000);
    }
  },
  beforeRouteLeave(to, from, next) {
  localStorage.setItem('startTime', this.startTime.getTime());
  next();
  },
  methods:{
    logout(){
      localStorage.removeItem('user');
      localStorage.removeItem('startTime');
      localStorage.removeItem('username');
    },
    updateUptime(){
      const now = new Date();
      const diff = now.getTime() - this.startTime.getTime();
      this.uptime = (diff/(1000*60*60)).toFixed(2);
      // const hours = Math.floor(diff/(1000*60*60));
      // const minutes = Math.floor((diff/(1000*60)%60));
      // const seconds = Math.floor((diff/1000)%60);
      // this.uptime = `${hours} 시간 ${minutes} 분 ${seconds} 초`
    },
    changeRPiPW(){
      api.member.setRPiPW({
        member_id: this.member_id,
        pwd: this.newPassword,
      })
      .then((res) => {
        console.log(res);
        this.message = res.data;
        this.isModalOpen = true;
      })
      .catch((err) => {
        console.log("에러다요")
        console.log(err.response)
      });
    },
    onInput(event){
      event.target.value = event.target.value.replace(/\D/g, "");
      this.newPassword = event.target.value;
    },
    closeModal() {
      this.isModalOpen = false;
    },
  }
}
</script>

<style scoped>
.item1{
  display: flex;
  /* justify-content: space-between; */
  background-color: rgb(169, 201, 202);
  position: absolute;
  width: 100%;
  height: 10%;
  top: 0;
  left: 0;
}
.item1 > *{
  margin: 0px 10px;
}
.item1 > * > div{
  margin: 0px 7px;
}
.nav1{
  display: flex;
  align-items: center;
  margin-right: auto;
}
.nav2{
  display: flex;
  align-items: center;
  color: white;
  margin-left: auto;
}
.ICON{
  background-image: url("../assets/ICON_ICANFARM.png");
  background-size: cover;
  position: relative;
  width: 81px;
  height: 91px;
}
.item2{
  display: flex;
  background-color: rgb(45, 51, 51);
  position: absolute;
  width: 100%;
  height: 90%;
  top: 10%;
  left: 0;
  justify-content: center;
  align-items: center;
}
.PW_box{
  background-color: rgb(217, 217, 217);
  border-radius: 50px;
  display: flex;
  flex-direction: column;
  align-items: center;
  justify-content: center;
  position: relative;
  padding: 10% 20%;
}
.PW_box > *{
  margin: 20px 0;
}
.modal {
  display: block;
  position: fixed;
  z-index: 1;
  left: 0;
  top: 0;
  width: 100%;
  height: 100%;
  background-color: rgba(0, 0, 0, 0.4);
}
.modal-content {
  background-color: white;
  margin: 15% auto;
  padding: 20px;
  border: 1px solid #888;
  width: 80%;
}
</style>