<template>
  <div class="container">
    <div class="Nav">
      <div>
        <div class="item1" style="background-color: rgb(169, 201, 202);">
          <div class="ICON" style="margin: 10px;"></div>
          <div class="LOGO" style="margin: 5px;"></div>
        </div>
        <div style="margin: 20% 0% 0% 0%;">
          <div style="display: flex; align-items: center; background-color: rgb(169, 201, 202);">
            <div class="MemIcon" style="margin: 10px;"></div>
            <router-link to="/admin/member" style="position: relative; width: 80%; text-decoration: none; color: white; font-size: 36px;">회원 등록  &gt;&gt;</router-link>
          </div>
          <div>
            <div style="display: flex; align-items: center;">
              <div class="HubIcon" style="margin: 10px;"></div>
              <router-link to="/admin/hub" style="position: relative; width: 80%; text-decoration: none; color: white; font-size: 36px;">허브 등록  &gt;&gt;</router-link>
            </div>
          </div>
          <div>
            <div style="display: flex; align-items: center;">
              <div class="MamIcon" style="margin: 10px;"></div>
              <router-link to="/admin/manage" style="position: relative; width: 80%; text-decoration: none; color: white; font-size: 36px;">회원 관리  &gt;&gt;</router-link>
            </div>
          </div>
        </div>
      </div>
      <div><router-link to="/" style="text-decoration: none; color: white; font-size: 48px;">&lt;&lt; LOGIN</router-link></div>
    </div>
    <router-view/>

    <div class="item2">
      <tbody>
        <tr>
          <th>이메일:</th>
          <th><input type="text" v-model="userEmail" @keyup.enter="emailCheck"></th>
          <th><button @click="emailCheck">중복확인</button></th>
        </tr>
        <tr>
          <th>PW:</th>
          <th><input type="text" v-model="userPasswd"></th>
        </tr>
        <tr>
          <th>이름:</th>
          <th><input type="text" v-model="userName"></th>
        </tr>
      </tbody>
      <div style="font-size: 36px; width: 200px;"><button :disabled="!isSaveEnabled" @click="saveMember">저장</button></div>
    </div>
  </div>
</template>

<script>

import { api } from "@/utils/axios"

export default {
  data() {
    return {
      userEmail: "",
      userPasswd: "",
      userName: "",
      isEmailAvailable: false,
    };
  },
  computed: {
    isSaveEnabled(){
      return this.userEmail && this.userPasswd && this.userName && this.isEmailAvailable;
    }
  },
  methods: {
    // https://getbootstrap.com/docs/5.3/components/alerts/#examples
    // 디자인 바꿔서
    emailCheck(){
      const User = this.userEmail;
      api.admin.checkEmail(User)
      .then((res) => {
        alert(res.data);
        this.isEmailAvailable = true;
      }).catch((err) => {
        alert("이미 사용중인 이메일입니다.");
        this.isEmailAvailable = false;
      });
    },
    saveMember(){
      api.admin.setMember({
        email: this.userEmail,
        passwd: this.userPasswd,
        name: this.userName,
      }).then((res) => {
        console.log(res);
        alert("회원 저장에 성공하였습니다.");
      }).catch((err) => {
        console.error(err);
      });
    },
  }

}
</script>

<style scoped>
.container{
  display: flex;
}
.Nav{
  background-color: rgb(61, 91, 101);
  position: absolute;
  width: 20%;
  height: 100%;
  top: 0;
  left: 0;
  display: flex;
  flex-direction: column;
  justify-content: space-between;
}
.item1{
  display: flex;
  /* justify-content: center; */
  align-items: center;
}
.ICON{
  background-image: url("../assets/ICON_ICANFARM.png");
  background-size: cover;
  width: 90px;
  height: 100px;
  /* top: 1%;
  Left: 1%; */
}
.LOGO{
  /* border: solid 1px black; */
  background-image: url("../assets/LINE_ICANFARM.png");
  background-size: cover;
  width: 235px;
  height: 39px;
  /* position: relative;
  left: 6%;
  top: 4%; */
  /* margin: auto; */
}

.MemIcon{
  background-image: url("../assets/ICON_Members.png");
  background-size: cover;
  position: relative; 
  width: 20%;
  height: 70px;
  /* width: 70px;
  height: 70px; */
}
.HubIcon{
  background-image: url("../assets/ICON_Hub.png");
  background-size: cover;
  position: relative; 
  width: 20%;
  height: 70px;
}
.MamIcon{
  background-image: url("../assets/ICON_Member.png");
  background-size: cover;
  position: relative; 
  width: 20%;
  height: 70px;
}

.item2{
  position: absolute;
  width: 80%;
  height: 100%;
  top: 0;
  left: 20%;
  display: flex;
  flex-direction: column;
  justify-content: center;
  align-items: center;
}
.item2 tbody{
  border-spacing: 30px 70px;
  font-size: 36px;
}
.item2 button{
  display: block;
  margin: 0 auto;
  width: 200px;
}

</style>