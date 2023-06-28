<template>
  <div class="container">
    <div class="item1">
      <div class="ICON"></div>
      <div class="LOGO"></div>
    </div>
    <div class="item2">
      <div class="login">
        <tbody>
          <tr>
            <th><label class="label" for="id">ID</label></th>
            <th><input type="text" placeholder="User email" v-model="userEmail"></th>
          </tr>
          <tr>
            <th><label class="label" for="password">PW</label></th>
            <th><input type="password" placeholder="Password" v-model="userPassword" @keyup.enter="goToMonitor"></th>
          </tr>
        </tbody>
        <div class="d-grid gap-2 col-6" style="margin: 30px auto;">
          <button class="login_btn" type="button" @click="goToMonitor">로그인</button>
        </div>
        <div style="display: flex; justify-content: center;">
        </div>
      </div>
    </div>
    <dir style="position: absolute; right: 3%; bottom: 2%;" @click="logout">
      <div><a href="/admin/member" style="text-decoration: none; color: white; font-size: 28px;" @click="logout">회원/허브 등록</a></div>
    </dir>
  </div>
</template>

<script>
import { api } from "@/utils/axios";

export default {
  name: 'LoginPage',
  data(){
    return{
      userEmail: "",
      userPassword: "",
    }
  },
  methods:{
    handleButtonClick(){
      console.log("버튼 눌림")
    },
    goToMonitor() {
      const emailParts = this.userEmail.split("@");
      const username = emailParts[0];
      api.member.login({
        email: this.userEmail,
        passwd: this.userPassword,
      })
      .then((res) => {
        console.log(res.data);
        localStorage.setItem('username', username);
        localStorage.setItem('user', JSON.stringify(res.data));
        localStorage.setItem('startTime', new Date().getTime());
        this.$router.push({name : 'Monitor'});
      })
      .catch((error) => {
        console.log(this.userEmail);
        console.log(this.userPassword);
        console.error(error);
        if (error.response && error.response.status === 400) {
        alert("로그인에 실패했습니다.");
        } else {
        alert("잘못된 접근입니다.");
        };
      });
    },
    logout(){
      localStorage.removeItem('user');
      localStorage.removeItem('startTime');
    },
  }
}
</script>

<style scoped>
.container{
  display: flex;
  /* position: static; */
}
.item1{
  background-color: rgb(169, 201, 202);
  position: absolute;
  width: 40%;
  height: 100%;
  top: 0;
  left: 0;
}
.ICON{
  background-image: url("../assets/ICON_ICANFARM.png");
  background-size: cover;
  width: 135px;
  height: 154px;
  top: 2%;
  left: 2%;
}
.LOGO{
  background-image: url("../assets/LOGO_ICANFARM.png");
  background-size: cover;
  width: 325px;
  height: 554px;
  margin: auto;
}
.item2{
  background-color: rgb(45, 51, 51);
  position: absolute;
  width: 60%;
  height: 100%;
  top: 0;
  left: 40%;
  display: flex;
  justify-content: center;
  align-items: center;
}
/* .login{
  border: 1px white solid;

} */
.label{
  color: white;
  font-size: 64px;
  margin: 10px 50px;
}
input{
  font-size: 36px;
  /* width: 540px;
  height: 100x; */
}
.login_btn{
  background-color: rgb(90, 100, 100);
  color: white;
  font-size: 48px;
}

</style>